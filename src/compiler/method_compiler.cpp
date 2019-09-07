#include "compiler/method_compiler.h"

#include "base/status.h"
#include "compiler/compiler.h"
#include "compiler/expr_compiler.h"
#include "compiler/reg_checker.h"
#include "fe/expr.h"
#include "fe/method.h"
#include "fe/stmt.h"
#include "fe/var_decl.h"
#include "vm/insn.h"
#include "vm/decl_annotator.h"
#include "vm/insn_annotator.h"
#include "vm/method.h"
#include "vm/object.h"
#include "vm/value.h"
#include "vm/vm.h"

namespace compiler {

VarScope::VarScope() : obj_expr_(nullptr) {
}

string MethodCompiler::dbg_bytecode_;

void MethodCompiler::SetByteCodeDebug(string flags) {
  dbg_bytecode_ = flags;
}

MethodCompiler::MethodCompiler(const CompileOptions &opts,
			       vm::VM *vm, vm::Object *obj, vm::Method *method)
  : opts_(opts), vm_(vm), obj_(obj), method_(method),
    tree_(method->GetParseTree()),
    last_queued_insn_(nullptr), delay_insn_emit_(true) {
  exc_.reset(new ExprCompiler(this));
}

MethodCompiler::~MethodCompiler() {
  for (auto *s : bindings_) {
    delete s;
  }
}

void MethodCompiler::Compile() {
  if (method_->insns_.size() > 0) {
    // already compiled.
    return;
  }
  if (method_->IsCompileFailure()) {
    return;
  }

  PushScope(nullptr);
  method_->SetParseTree(tree_);

  SetupArgumentRegisters();
  SetupReturnRegisters();

  // For a label at the beginning.
  EmitNop();

  auto &stmts = tree_->GetStmts();
  for (size_t i = 0; i < stmts.size(); ++i) {
    CompileStmt(stmts[i]);
    CompilePreIncDec();
    FlushPendingInsns();
    CompilePostIncDec();
    if (Status::CheckAllErrors(false)) {
      method_->SetCompileFailure();
      return;
    }
  }
  MayEmitEpilogueCode();
  PopScope();
  EmitNop();
  AddLabel(sym_return);
  // If a jump targets the label at the last insn.
  EmitNop();
  FlushPendingInsns();
  ResolveLabels();
  if (vm::ByteCodeDebugMode::PreExec(dbg_bytecode_) &&
      method_->IsTopLevel()) {
    method_->Dump();
  }
  vm::InsnAnnotator::AnnotateMethod(vm_, obj_, method_);
  if (vm::ByteCodeDebugMode::IsEnabled(dbg_bytecode_)) {
    // Top level result will be output after execution.
    if (!method_->IsTopLevel()) {
      method_->Dump();
    }
  }

  RegChecker checker(method_);
  checker.Check();

  if (Status::CheckAllErrors(false)) {
    method_->SetCompileFailure();
  }
}

vm::Object *MethodCompiler::GetObj() const {
  return obj_;
}

void MethodCompiler::AddLabel(sym_t label) {
  label_insn_map_[label] = last_queued_insn_;
}

void MethodCompiler::ResolveLabels() {
  for (size_t i = 0; i < method_->insns_.size(); ++i) {
    vm::Insn *insn = method_->insns_[i];
    if (insn->op_ == vm::OP_GOTO) {
      if (insn->insn_stmt_) {
	insn->jump_target_ = InsnIndexFromLabel(insn->insn_stmt_->GetSym());
      } else if (insn->label_) {
	insn->jump_target_ = InsnIndexFromLabel(insn->label_);
      } else {
	insn->jump_target_ = InsnIndexFromLabel(sym_return);
      }
    }
    if (insn->op_ == vm::OP_IF) {
      if (insn->insn_stmt_) {
	// generated by if-stmt.
	insn->jump_target_ =
	  InsnIndexFromLabel(insn->insn_stmt_->GetLabel(false, false));
      } else {
	// generated by tri term-expr.
	insn->jump_target_ = InsnIndexFromLabel(insn->label_);
      }
    }
  }
}

void MethodCompiler::EmitNop() {
  vm::Insn *insn = new vm::Insn;
  insn->op_ = vm::OP_NOP;
  EmitInsn(insn);
}

void MethodCompiler::CompilePreIncDec() {
  DoCompilePrePostIncDec(false, &pre_inc_dec_exprs_);
}

void MethodCompiler::CompilePostIncDec() {
  DoCompilePrePostIncDec(true, &post_inc_dec_exprs_);
}

void MethodCompiler::DoCompilePrePostIncDec(bool is_post,
					    vector<fe::Expr*> *exprs) {
  for (size_t i = 0; i < exprs->size(); ++i) {
    exc_->CompileIncDecExpr(exprs->at(i));
  }
  if (is_post) {
    post_inc_dec_exprs_.clear();
  } else {
    pre_inc_dec_exprs_.clear();
  }
}

void MethodCompiler::FlushPendingInsns() {
  for (size_t i = 0; i < pending_insns_.size(); ++i) {
    vm::Insn *insn = pending_insns_[i];
    method_->insns_.push_back(insn);
  }
  pending_insns_.clear();
}

void MethodCompiler::SetupArgumentRegisters() {
  if (!tree_->GetArgs()) {
    return;
  }
  SetupDeclSetRegisters(*(tree_->GetArgs()), nullptr);
}

void MethodCompiler::SetupReturnRegisters() {
  if (!tree_->GetReturns()) {
    return;
  }
  SetupDeclSetRegisters(*(tree_->GetReturns()), &method_->return_types_);
}

void MethodCompiler::SetupDeclSetRegisters(fe::VarDeclSet &vds,
					   vector<vm::RegisterType> *types) {
  for (size_t i = 0; i < vds.decls.size(); ++i) {
    fe::VarDecl *decl = vds.decls[i];
    vm::Register *reg = AllocRegister();
    if (decl->GetNameExpr()) {
      reg->orig_name_ = decl->GetNameExpr()->GetSym();
    }
    VarScope *scope = CurrentScope();
    if (reg->orig_name_) {
      scope->local_regs_[reg->orig_name_] = reg;
    }
    SetWidthByDecl(decl, reg);
    if (types) {
      types->push_back(reg->type_);
    }
  }
}

void MethodCompiler::SetWidthByDecl(fe::VarDecl *decl, vm::Register *reg) {
  vm::DeclAnnotator::AnnotateByDecl(vm_, decl, reg);
}

vm::Register *MethodCompiler::GetNthReturnRegister(int nth) {
  if (tree_->GetArgs()) {
    nth += tree_->GetArgs()->decls.size();
  }
  return method_->method_regs_[nth];
}

void MethodCompiler::PushScope(fe::Stmt *stmt) {
  VarScope *scope = new VarScope;
  if (stmt != nullptr) {
    scope->obj_expr_ = stmt->GetExpr();
    if (scope->obj_expr_ != nullptr) {
      RegisterTuple rt = exc_->CompileExpr(scope->obj_expr_);
      vm::Insn *insn = new vm::Insn;
      insn->op_ = vm::OP_MEMBER_WRITE;
      insn->label_ = sym_lookup("parent");
      insn->obj_reg_ = rt.GetOne();
      insn->src_regs_.push_back(EmitLoadObj(nullptr));
      insn->src_regs_.push_back(insn->obj_reg_);
      insn->dst_regs_.push_back(insn->src_regs_[0]);
      EmitInsn(insn);

      insn = new vm::Insn;
      insn->op_ = vm::OP_PUSH_CURRENT_OBJECT;
      insn->obj_reg_ = rt.GetOne();
      EmitInsn(insn);
    }
  }
  bindings_.push_back(scope);
}

void MethodCompiler::PopScope() {
  VarScope *scope = *(bindings_.rbegin());
  if (scope->obj_expr_ != nullptr) {
    vm::Insn *insn = new vm::Insn;
    insn->op_ = vm::OP_POP_CURRENT_OBJECT;
    EmitInsn(insn);
  }
  delete scope;
  bindings_.pop_back();
}

VarScope *MethodCompiler::CurrentScope() {
  return *(bindings_.rbegin());
}

void MethodCompiler::EmitInsn(vm::Insn *insn) {
  if (delay_insn_emit_) {
    pending_insns_.push_back(insn);
    last_queued_insn_ = insn;
  } else {
    method_->insns_.push_back(insn);
    last_queued_insn_ = insn;
  }
}

void MethodCompiler::CompileStmt(fe::Stmt *stmt) {
  switch (stmt->GetType()) {
  case fe::STMT_EXPR:
    exc_->CompileExpr(stmt->GetExpr());
    break;
  case fe::STMT_FUNCDECL:
    CompileFuncDecl(stmt);
    break;
  case fe::STMT_IMPORT:
    CompileImportStmt(stmt);
    break;
  case fe::STMT_VARDECL:
    CompileVarDeclStmt(stmt);
    break;
  case fe::STMT_IF:
    CompileIfStmt(stmt);
    break;
  case fe::STMT_GOTO:
    CompileGoto(stmt);
    break;
  case fe::STMT_LABEL:
    CompileLabel(stmt);
    break;
  case fe::STMT_PUSH_BINDING:
    PushScope(stmt);
    break;
  case fe::STMT_POP_BINDING:
    PopScope();
    break;
  case fe::STMT_RETURN:
    CompileReturn(stmt);
    break;
  case fe::STMT_THREAD_DECL:
    CompileThreadDecl(stmt);
    break;
  case fe::STMT_CHANNEL_DECL:
    CompileChannelDecl(stmt);
    break;
  case fe::STMT_MAILBOX_DECL:
    CompileMailboxDecl(stmt);
    break;
  default:
    CHECK(false) << "Unknown stmt:" << fe::NodeName(stmt->GetType());
    break;
  }
}

void MethodCompiler::CompileGoto(fe::Stmt *stmt) {
  vm::Insn *insn = new vm::Insn;
  insn->op_ = vm::OP_GOTO;
  insn->insn_stmt_ = stmt;
  EmitInsn(insn);
}

void MethodCompiler::CompileReturn(fe::Stmt *stmt) {
  size_t num_returns = method_->GetNumReturnRegisters();
  vector<fe::Expr*> value_exprs;
  exc_->FlattenCommas(stmt->GetExpr(), &value_exprs);
  CHECK(num_returns == value_exprs.size());
  vector<vm::Register *> regs;
  for (size_t i = 0; i < value_exprs.size(); ++i) {
    RegisterTuple rt = exc_->CompileExpr(value_exprs[i]);
    regs.push_back(rt.GetOne());
  }
  for (size_t i = 0; i < value_exprs.size(); ++i) {
    vm::Insn *insn = new vm::Insn;
    insn->op_ = vm::OP_ASSIGN;
    insn->insn_expr_ = value_exprs[i];
    insn->dst_regs_.push_back(GetNthReturnRegister(i));
    insn->src_regs_.push_back(GetNthReturnRegister(i));
    insn->src_regs_.push_back(regs[i]);
    EmitInsn(insn);
  }

  // Goto the last insn.
  vm::Insn *insn = new vm::Insn;
  insn->op_ = vm::OP_GOTO;
  insn->insn_stmt_ = nullptr;
  EmitInsn(insn);
}

void MethodCompiler::CompileLabel(fe::Stmt *stmt) {
  AddLabel(stmt->GetSym());
}

void MethodCompiler::CompileIfStmt(fe::Stmt *stmt) {
  vm::Insn *insn = new vm::Insn;
  insn->op_ = vm::OP_IF;
  RegisterTuple rt = exc_->CompileExpr(stmt->GetExpr());
  insn->src_regs_.push_back(rt.GetOne());
  insn->insn_stmt_ = stmt;
  EmitInsn(insn);
}

void MethodCompiler::CompileVarDeclStmt(fe::Stmt *stmt) {
  fe::VarDecl *vdd = stmt->GetVarDecl();
  fe::Expr *var_expr = vdd->GetNameExpr();
  vm::Register *rhs_val = nullptr;
  if (vdd->GetInitialVal() != nullptr) {
    RegisterTuple rt = exc_->CompileExpr(vdd->GetInitialVal());
    rhs_val = rt.GetOne();
  }

  bool is_member_decl = false;
  if (var_expr->GetType() == fe::EXPR_ELM_SYM_REF) {
    CHECK(IsTopLevel() && vdd->GetIsShared());
    is_member_decl = true;
  }
  if (IsTopLevel() && vdd->GetIsShared()) {
    CHECK(bindings_.size() == 1);
    is_member_decl = true;
  }

  if (is_member_decl) {
    if (rhs_val != nullptr) {
      SetWidthByDecl(stmt->GetVarDecl(), rhs_val);
    }
    CompileMemberDeclStmt(stmt, var_expr, vm::OP_VARDECL, rhs_val);
    return;
  }

  // local variable.
  CHECK(var_expr->GetType() == fe::EXPR_SYM);
  sym_t name = var_expr->GetSym();
  vm::Register *reg = LookupOrAllocateLocalVar(name);
  SetWidthByDecl(stmt->GetVarDecl(), reg);
  sym_t obj_name = stmt->GetVarDecl()->GetObjectName();
  if (obj_name != sym_null) {
    if (IsTopLevel()) {
      // Set type object later.
      vm::Insn *insn = new vm::Insn;
      insn->op_ = vm::OP_SET_TYPE_OBJECT;
      insn->dst_regs_.push_back(reg);
      insn->insn_stmt_ = stmt;
      EmitInsn(insn);
    } else {
      if (obj_name == nullptr) {
	Status::os(Status::USER_ERROR)
	  << "Data type: " << sym_cstr(obj_name) << " is not found";
	return;
      }
    }
  }

  if (rhs_val) {
    SimpleAssign(rhs_val, reg);
  }
}

void MethodCompiler::CompileThreadDecl(fe::Stmt *stmt) {
  fe::Expr *var_expr = stmt->GetExpr()->GetLhs();
  CompileMemberDeclStmt(stmt, var_expr, vm::OP_THREAD_DECL, nullptr);
}

void MethodCompiler::CompileChannelDecl(fe::Stmt *stmt) {
  fe::Expr *var_expr = stmt->GetExpr();
  CompileMemberDeclStmt(stmt, var_expr, vm::OP_CHANNEL_DECL, nullptr);
}
                  
void MethodCompiler::CompileMailboxDecl(fe::Stmt *stmt) {
  fe::Expr *var_expr = stmt->GetExpr();
  CompileMemberDeclStmt(stmt, var_expr, vm::OP_MAILBOX_DECL, nullptr);
}

void MethodCompiler::CompileMemberDeclStmt(fe::Stmt *stmt, fe::Expr *var_expr,
					   vm::OpCode op,
					   vm::Register *initial_val) {
  CHECK(IsTopLevel());
  vm::Register *obj_reg = CompilePathHead(var_expr);
  // Object manipulation. do in the executor.
  vm::Insn *insn = new vm::Insn;
  insn->op_ = op;
  insn->insn_stmt_ = stmt;
  insn->obj_reg_ = obj_reg;
  if (op == vm::OP_THREAD_DECL) {
    insn->label_ = stmt->GetExpr()->GetFunc()->GetFunc()->GetSym();
  }
  if (op == vm::OP_CHANNEL_DECL ||
      op == vm::OP_MAILBOX_DECL) {
    insn->label_ = stmt->GetExpr()->GetSym();
  }
  EmitInsn(insn);
  if (op == vm::OP_VARDECL && initial_val) {
    insn = new vm::Insn;
    insn->op_ = vm::OP_MEMBER_WRITE;
    insn->label_ = var_expr->GetSym();
    insn->obj_reg_ = obj_reg;
    insn->src_regs_.push_back(initial_val);
    insn->src_regs_.push_back(obj_reg);
    insn->dst_regs_.push_back(insn->src_regs_[0]);
    EmitInsn(insn);
  }
}

void MethodCompiler::CompileImportStmt(fe::Stmt *stmt) {
  vm::Insn *insn = new vm::Insn;
  insn->op_ = vm::OP_IMPORT;
  insn->insn_stmt_ = stmt;
  sym_t name = stmt->GetSym();
  if (name != sym_null) {
    // import "fn" as v
    vm::Register *reg = LookupOrAllocateLocalVar(name);
    insn->dst_regs_.push_back(reg);
  }
  EmitInsn(insn);
}

void MethodCompiler::SimpleAssign(vm::Register *src, vm::Register *dst) {
  vm::Insn *insn = new vm::Insn;
  insn->op_ = vm::OP_ASSIGN;
  insn->src_regs_.push_back(dst);
  insn->src_regs_.push_back(src);
  insn->dst_regs_.push_back(dst);
  EmitInsn(insn);
}

vm::Register *MethodCompiler::LookupLocalVar(sym_t name) {
  for (int i = bindings_.size() - 1; i >= 0; --i) {
    VarScope *scope = bindings_[i];
    vm::Register *reg = scope->local_regs_[name];
    if (reg) {
      return reg;
    }
  }
  return nullptr;
}

vm::Register *MethodCompiler::LookupOrAllocateLocalVar(sym_t name) {
  vm::Register *reg = LookupLocalVar(name);
  if (reg == nullptr) {
    VarScope *scope = CurrentScope();
    reg = AllocRegister();
    reg->orig_name_ = name;
    scope->local_regs_[name] = reg;
  }
  return reg;
}

void MethodCompiler::CompileFuncDecl(fe::Stmt *stmt) {
  vm::Insn *insn = new vm::Insn;
  insn->op_ = vm::OP_FUNCDECL;
  insn->label_ = stmt->GetExpr()->GetSym();
  insn->insn_stmt_ = stmt;
  insn->obj_reg_ = CompilePathHead(stmt->GetExpr());
  EmitInsn(insn);
}

vm::Register *MethodCompiler::CompilePathHead(fe::Expr *path_elem) {
  if (path_elem->GetType() == fe::EXPR_SYM) {
    return EmitLoadObj(nullptr);
  }
  return TraverseMemberPath(path_elem->GetArgs());
}

vm::Register *MethodCompiler::TraverseMemberPath(fe::Expr *path_elem) {
  if (path_elem->GetType() == fe::EXPR_SYM) {
    vm::Register *obj_reg = LookupLocalVar(path_elem->GetSym());
    if (obj_reg == nullptr) {
      obj_reg = EmitLoadObj(path_elem->GetSym());
    }
    return obj_reg;
  }
  vm::Register *obj_reg = TraverseMemberPath(path_elem->GetArgs());
  return EmitMemberLoad(obj_reg, path_elem->GetSym());
}

vm::Register *MethodCompiler::AllocRegister() {
  vm::Register *reg = new vm::Register;
  reg->id_ = method_->method_regs_.size();
  method_->method_regs_.push_back(reg);
  return reg;
}

int MethodCompiler::InsnIndexFromLabel(sym_t label) {
  vm::Insn *insn = label_insn_map_[label];
  CHECK(insn) << sym_cstr(label);
  // TODO(yusuke): don't do a linear search.
  for (size_t i = 0; i < method_->insns_.size(); ++i) {
    if (method_->insns_[i] == insn) {
      return i + 1;
    }
  }
  CHECK(false);
  return -1;
}

vm::Register *MethodCompiler::EmitLoadObj(sym_t label) {
  vm::Insn *obj_insn = new vm::Insn;
  obj_insn->op_ = vm::OP_LOAD_OBJ;
  vm::Register *obj_reg = AllocRegister();
  obj_insn->dst_regs_.push_back(obj_reg);
  obj_insn->label_ = label;
  EmitInsn(obj_insn);

  if (label) {
    vm::Value *obj_value = obj_->LookupValue(label, false);
    if (obj_value != nullptr &&
	obj_value->IsObjectType()) {
      reg_obj_map_[obj_reg] = obj_value->object_;
    }
  } else {
    reg_obj_map_[obj_reg] = obj_;
  }
  return obj_reg;
}

vm::Register *MethodCompiler::EmitMemberLoad(vm::Register *obj_reg, sym_t m) {
  vm::Insn *insn = new vm::Insn;
  insn->src_regs_.push_back(obj_reg);
  if (IsTopLevel()) {
    insn->op_ = vm::OP_MEMBER_READ_WITH_CHECK;
  } else {
    insn->op_ = vm::OP_MEMBER_READ;
  }
  insn->label_ = m;
  vm::Register *value_reg = AllocRegister();
  insn->dst_regs_.push_back(value_reg);
  EmitInsn(insn);

  vm::Object *vm_obj = GetVMObject(obj_reg);
  if (vm_obj) {
    vm::Value *obj_value = vm_obj->LookupValue(m, false);
    if (obj_value != nullptr &&
	obj_value->IsObjectType()) {
      reg_obj_map_[value_reg] = obj_value->object_;
    }
  }
  return value_reg;
}

void MethodCompiler::AddPrePostIncDecExpr(fe::Expr *expr, bool is_post) {
  if (is_post) {
    post_inc_dec_exprs_.push_back(expr);
  } else {
    pre_inc_dec_exprs_.push_back(expr);
  }
}

vm::Object *MethodCompiler::GetVMObject(vm::Register *obj_reg) {
  if (obj_reg == nullptr) {
    return vm_->kernel_object_;
  }
  return reg_obj_map_[obj_reg];
}

void MethodCompiler::RegisterVMObject(vm::Register *reg, vm::Object *obj) {
  reg_obj_map_[reg] = obj;
}

void MethodCompiler::SetDelayInsnEmit(bool delay) {
  delay_insn_emit_ = delay;
}

bool MethodCompiler::IsTopLevel() const {
  return method_->IsTopLevel();
}

void MethodCompiler::MayEmitEpilogueCode() {
  if (opts_.run) {
    exc_->EmitRun();
  }
  if (opts_.outputs.size() > 0) {
    exc_->EmitCompile();
  }
  for (const string &s : opts_.outputs) {
    exc_->EmitWriteHdl(s);
  }
}

}  // namespace compiler

