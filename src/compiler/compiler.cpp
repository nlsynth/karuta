// Compiles a parse tree into vm instructions.
#include "compiler/compiler.h"

#include "pool.h"
#include "status.h"
#include "compiler/expr_compiler.h"
#include "fe/expr.h"
#include "fe/method.h"
#include "fe/stmt.h"
#include "fe/var_decl.h"
#include "vm/insn.h"
#include "vm/insn_annotator.h"
#include "vm/method.h"
#include "vm/object.h"
#include "vm/opcode.h"
#include "vm/value.h"
#include "vm/vm.h"

#include <map>
using std::map;

namespace compiler {

bool Compiler::dbg_bytecode_;

class VarScope {
public:
  // local name -> Register.
  map<sym_t, vm::Register*> local_regs_;
};

// static
vm::Method *Compiler::CompileMethod(vm::VM *vm, vm::Object *obj,
				    const fe::Method *parse_tree,
				    vm::Method *method) {
  if (method && !method->parse_tree_) {
    // native method.
    return method;
  }
  std::unique_ptr<Compiler> compiler(new Compiler(vm, obj, parse_tree));
  return compiler->Compile(method);
}

void Compiler::SetByteCodeDebug(bool enable) {
  dbg_bytecode_ = enable;
}

Compiler::Compiler(vm::VM *vm, vm::Object *obj, const fe::Method *parse_tree)
  : vm_(vm), obj_(obj), tree_(parse_tree), last_queued_insn_(nullptr) {
  exc_ = new ExprCompiler(this);
}

vm::Method *Compiler::Compile(vm::Method *method) {
  method_ = method;
  if (!method_) {
    // top level.
    method_ = vm_->NewMethod(true /* toplevel */);
  }
  if (method_->insns_.size() > 0) {
    // already compiled.
    return method_;
  }

  PushScope();
  method_->parse_tree_ = tree_;

  SetupArgumentRegisters();
  SetupReturnRegisters();

  for (size_t i = 0; i < tree_->stmts_.size(); ++i) {
    CompileStmt(tree_->stmts_[i]);
    CompilePreIncDec();
    FlushPendingInsns();
    CompilePostIncDec();
  }
  PopScope();
  EmitNop();
  AddLabel(sym_return);
  // If a jump targets the label at the last insn.
  EmitNop();
  FlushPendingInsns();
  ResolveLabels();
  vm::InsnAnnotator::AnnotateMethod(vm_, obj_, method_);
  if (dbg_bytecode_) {
    // Top level result will be output after execution.
    if (!method_->IsTopLevel()) {
      method_->Dump();
    }
  }

  return method_;
}

vm::Object *Compiler::GetObj() const {
  return obj_;
}

void Compiler::AddLabel(sym_t label) {
  label_insn_map_[label] = last_queued_insn_;
}

void Compiler::ResolveLabels() {
  for (size_t i = 0; i < method_->insns_.size(); ++i) {
    vm::Insn *insn = method_->insns_[i];
    if (insn->op_ == vm::OP_GOTO) {
      if (insn->insn_stmt_) {
	insn->jump_target_ = InsnIndexFromLabel(insn->insn_stmt_->sym_);
      } else if (insn->label_) {
	insn->jump_target_ = InsnIndexFromLabel(insn->label_);
      } else {
	insn->jump_target_ = InsnIndexFromLabel(sym_return);
      }
    }
    if (insn->op_ == vm::OP_IF) {
      if (insn->insn_stmt_) {
	// generated by if-stmt.
	insn->jump_target_ = InsnIndexFromLabel(insn->insn_stmt_->label_f_);
      } else {
	// generated by tri term-expr.
	insn->jump_target_ = InsnIndexFromLabel(insn->label_);
      }
    }
  }
}

void Compiler::EmitNop() {
  vm::Insn *insn = new vm::Insn;
  insn->op_ = vm::OP_NOP;
  EmitInsn(insn);
}

void Compiler::CompilePreIncDec() {
  DoCompilePrePostIncDec(false, &pre_inc_dec_exprs_);
}

void Compiler::CompilePostIncDec() {
  DoCompilePrePostIncDec(true, &post_inc_dec_exprs_);
}

void Compiler::DoCompilePrePostIncDec(bool is_post, vector<fe::Expr*> *exprs) {
  for (size_t i = 0; i < exprs->size(); ++i) {
    CompileIncDecExpr(exprs->at(i));
  }
  if (is_post) {
    post_inc_dec_exprs_.clear();
  } else {
    pre_inc_dec_exprs_.clear();
  }
}

void Compiler::CompileIncDecExpr(fe::Expr *expr) {
  vm::Insn *insn = new vm::Insn;
  if (expr->type_ == fe::UNIOP_PRE_INC ||
      expr->type_ == fe::UNIOP_POST_INC) {
    insn->op_ = vm::OP_PRE_INC;
  } else {
    insn->op_ = vm::OP_PRE_DEC;
  }
  vm::Register *reg = exc_->CompileSymExpr(expr->args_);
  if (!reg) {
    Status::os(Status::USER) << "Invalid inc/dec";
    MessageFlush::Get(Status::USER);
    return;
  }
  insn->dst_regs_.push_back(reg);
  insn->src_regs_.push_back(reg);
  EmitInsnNow(insn);
}

void Compiler::FlushPendingInsns() {
  for (size_t i = 0; i < pending_insns_.size(); ++i) {
    vm::Insn *insn = pending_insns_[i];
    method_->insns_.push_back(insn);
  }
  pending_insns_.clear();
}

void Compiler::SetupArgumentRegisters() {
  if (!tree_->args_) {
    return;
  }
  SetupDeclSetRegisters(*tree_->args_, nullptr);
}

void Compiler::SetupReturnRegisters() {
  if (!tree_->returns_) {
    return;
  }
  SetupDeclSetRegisters(*tree_->returns_, &method_->return_types_);
}

void Compiler::SetupDeclSetRegisters(fe::VarDeclSet &vds,
				     vector<vm::RegisterType> *types) {
  for (size_t i = 0; i < vds.decls.size(); ++i) {
    fe::VarDecl *decl = vds.decls[i];
    vm::Register *reg = AllocRegister();
    if (decl->GetNameExpr()) {
      reg->orig_name_ = decl->GetNameExpr()->sym_;
    }
    VarScope *scope = CurrentScope();
    if (reg->orig_name_) {
      scope->local_regs_[reg->orig_name_] = reg;
    }
    vm::InsnAnnotator::AnnotateByDecl(vm_, decl, reg);
    if (types) {
      types->push_back(reg->type_);
    }
  }
}

vm::Register *Compiler::GetNthReturnRegister(int nth) {
  if (tree_->args_) {
    nth += tree_->args_->decls.size();
  }
  return method_->method_regs_[nth];
}

void Compiler::PushScope() {
  VarScope *scope = new VarScope;
  bindings_.push_back(scope);
}

void Compiler::PopScope() {
  VarScope *scope = *(bindings_.rbegin());
  delete scope;
  bindings_.pop_back();
}

VarScope *Compiler::CurrentScope() {
  return *(bindings_.rbegin());
}

void Compiler::EmitInsn(vm::Insn *insn) {
  pending_insns_.push_back(insn);
  last_queued_insn_ = insn;
}

void Compiler::EmitInsnNow(vm::Insn *insn) {
  method_->insns_.push_back(insn);
  last_queued_insn_ = insn;
}

void Compiler::CompileStmt(fe::Stmt *stmt) {
  switch (stmt->type_) {
  case fe::STMT_EXPR:
    exc_->CompileExpr(stmt->expr_);
    break;
  case fe::STMT_FUNCDECL:
    CompileFuncDecl(stmt);
    break;
  case fe::STMT_IMPORT:
    CompileImportStmt(stmt);
    break;
  case fe::STMT_SPAWN:
    CompileSpawnStmt(stmt);
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
    PushScope();
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
    CHECK(false) << "Unknown stmt:" << fe::NodeName(stmt->type_);
    break;
  }
}

void Compiler::CompileGoto(fe::Stmt *stmt) {
  vm::Insn *insn = new vm::Insn;
  insn->op_ = vm::OP_GOTO;
  insn->insn_stmt_ = stmt;
  EmitInsn(insn);
}

void Compiler::CompileReturn(fe::Stmt *stmt) {
  size_t num_returns = method_->GetNumReturnRegisters();
  vector<fe::Expr*> value_exprs;
  exc_->FlattenCommas(stmt->expr_, &value_exprs);
  CHECK(num_returns == value_exprs.size());
  vector<vm::Register *> regs;
  for (size_t i = 0; i < value_exprs.size(); ++i) {
    regs.push_back(exc_->CompileExpr(value_exprs[i]));
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

void Compiler::CompileLabel(fe::Stmt *stmt) {
  AddLabel(stmt->sym_);
}

void Compiler::CompileIfStmt(fe::Stmt *stmt) {
  vm::Insn *insn = new vm::Insn;
  insn->op_ = vm::OP_IF;
  insn->src_regs_.push_back(exc_->CompileExpr(stmt->expr_));
  insn->insn_stmt_ = stmt;
  EmitInsn(insn);
}

void Compiler::CompileVarDeclStmt(fe::Stmt *stmt) {
  fe::Expr *var_expr = stmt->decl_->GetNameExpr();
  vm::Register *rhs_val = nullptr;
  if (stmt->decl_->GetInitialVal() != nullptr) {
    rhs_val = exc_->CompileExpr(stmt->decl_->GetInitialVal());
  }

  if (var_expr->type_ == fe::EXPR_ELM_SYM_REF) {
    CHECK(IsTopLevel());
    if (rhs_val) {
      vm::InsnAnnotator::AnnotateByDecl(vm_, stmt->decl_, rhs_val);
    }
    CompileMemberDeclStmt(stmt, var_expr, vm::OP_VARDECL, rhs_val);
    return;
  }

  // local variable.
  CHECK(var_expr->type_ == fe::EXPR_SYM);
  sym_t name = var_expr->sym_;
  vm::Register *reg = AllocRegister();
  reg->orig_name_ = name;
  VarScope *scope = CurrentScope();
  scope->local_regs_[name] = reg;
  vm::InsnAnnotator::AnnotateByDecl(vm_, stmt->decl_, reg);
  if (stmt->decl_->GetObjectName() != sym_null) {
    if (IsTopLevel()) {
      // Set type object later.
      vm::Insn *insn = new vm::Insn;
      insn->op_ = vm::OP_SET_TYPE_OBJECT;
      insn->dst_regs_.push_back(reg);
      insn->insn_stmt_ = stmt;
      EmitInsn(insn);
    } else {
      CHECK(reg->type_object_ != nullptr);
    }
  }

  if (rhs_val) {
    SimpleAssign(rhs_val, reg);
  }
}

void Compiler::CompileThreadDecl(fe::Stmt *stmt) {
  fe::Expr *var_expr = stmt->expr_->lhs_;
  CHECK(var_expr->type_ == fe::EXPR_ELM_SYM_REF);
  CompileMemberDeclStmt(stmt, var_expr, vm::OP_THREAD_DECL, nullptr);
}

void Compiler::CompileChannelDecl(fe::Stmt *stmt) {
  fe::Expr *var_expr = stmt->expr_;
  CHECK(var_expr->type_ == fe::EXPR_ELM_SYM_REF);
  CompileMemberDeclStmt(stmt, var_expr, vm::OP_CHANNEL_DECL, nullptr);
}
                  
void Compiler::CompileMailboxDecl(fe::Stmt *stmt) {
  fe::Expr *var_expr = stmt->expr_;
  CHECK(var_expr->type_ == fe::EXPR_ELM_SYM_REF);
  CompileMemberDeclStmt(stmt, var_expr, vm::OP_MAILBOX_DECL, nullptr);
}

void Compiler::CompileMemberDeclStmt(fe::Stmt *stmt, fe::Expr *var_expr,
				     vm::OpCode op, vm::Register *initial_val) {
  CHECK(IsTopLevel());
  vm::Register *obj_reg = CompilePathHead(var_expr);
  // Object manipulation. do in the executor.
  vm::Insn *insn = new vm::Insn;
  insn->op_ = op;
  insn->insn_stmt_ = stmt;
  insn->obj_reg_ = obj_reg;
  if (op == vm::OP_THREAD_DECL) {
    insn->label_ = stmt->expr_->func_->func_->sym_;
  }
  if (op == vm::OP_CHANNEL_DECL ||
      op == vm::OP_MAILBOX_DECL) {
    insn->label_ = stmt->expr_->sym_;
  }
  EmitInsn(insn);
  if (op == vm::OP_VARDECL && initial_val) {
    insn = new vm::Insn;
    insn->op_ = vm::OP_MEMBER_WRITE;
    insn->label_ = var_expr->sym_;
    insn->obj_reg_ = obj_reg;
    insn->src_regs_.push_back(initial_val);
    insn->src_regs_.push_back(obj_reg);
    insn->dst_regs_.push_back(insn->src_regs_[0]);
    EmitInsn(insn);
  }
}

void Compiler::CompileImportStmt(fe::Stmt *stmt) {
  vm::Insn *insn = new vm::Insn;
  insn->op_ = vm::OP_IMPORT;
  insn->insn_stmt_ = stmt;
  EmitInsn(insn);
}

void Compiler::CompileSpawnStmt(fe::Stmt *stmt) {
  vm::Insn *insn = new vm::Insn;
  insn->op_ = vm::OP_SPAWN;
  insn->insn_expr_ = stmt->expr_;
  EmitInsn(insn);
}

void Compiler::SimpleAssign(vm::Register *src, vm::Register *dst) {
  vm::Insn *insn = new vm::Insn;
  insn->op_ = vm::OP_ASSIGN;
  insn->src_regs_.push_back(dst);
  insn->src_regs_.push_back(src);
  insn->dst_regs_.push_back(dst);
  EmitInsn(insn);
}

vm::Register *Compiler::LookupLocalVar(sym_t name) {
  for (int i = bindings_.size() - 1; i >= 0; --i) {
    VarScope *scope = bindings_[i];
    vm::Register *reg = scope->local_regs_[name];
    if (reg) {
      return reg;
    }
  }
  return nullptr;
}

void Compiler::CompileFuncDecl(fe::Stmt *stmt) {
  vm::Insn *insn = new vm::Insn;
  insn->op_ = vm::OP_FUNCDECL;
  insn->label_ = stmt->expr_->sym_;
  insn->insn_stmt_ = stmt;
  insn->obj_reg_ = CompilePathHead(stmt->expr_);
  EmitInsn(insn);
}

vm::Register *Compiler::CompilePathHead(fe::Expr *path_elem) {
  if (path_elem->type_ == fe::EXPR_SYM) {
    return EmitLoadObj(nullptr);
  }
  return TraverseMemberPath(path_elem->args_);
}

vm::Register *Compiler::TraverseMemberPath(fe::Expr *path_elem) {
  if (path_elem->type_ == fe::EXPR_SYM) {
    vm::Register *obj_reg = LookupLocalVar(path_elem->sym_);
    if (obj_reg == nullptr) {
      obj_reg = EmitLoadObj(path_elem->sym_);
    }
    return obj_reg;
  }
  vm::Register *obj_reg = TraverseMemberPath(path_elem->args_);
  return EmitMemberLoad(obj_reg, path_elem->sym_);
}

vm::Register *Compiler::AllocRegister() {
  vm::Register *reg = new vm::Register;
  reg->id_ = method_->method_regs_.size();
  method_->method_regs_.push_back(reg);
  return reg;
}

int Compiler::InsnIndexFromLabel(sym_t label) {
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

vm::Register *Compiler::EmitLoadObj(sym_t label) {
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

vm::Register *Compiler::EmitMemberLoad(vm::Register *obj_reg, sym_t m) {
  vm::Insn *insn = new vm::Insn;
  insn->src_regs_.push_back(obj_reg);
  insn->op_ = vm::OP_MEMBER_READ;
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

void Compiler::AddPrePostIncDecExpr(fe::Expr *expr, bool is_post) {
  if (is_post) {
    post_inc_dec_exprs_.push_back(expr);
  } else {
    pre_inc_dec_exprs_.push_back(expr);
  }
}

vm::Object *Compiler::GetVMObject(vm::Register *obj_reg) {
  if (obj_reg == nullptr) {
    return vm_->kernel_object_;
  }
  return reg_obj_map_[obj_reg];
}

bool Compiler::IsTopLevel() const {
  return method_->IsTopLevel();
}

}  // namespace compiler
