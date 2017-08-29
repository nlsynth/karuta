#include "compiler/expr_compiler.h"

#include "base/status.h"
#include "compiler/compiler.h"
#include "fe/expr.h"
#include "fe/method.h"
#include "fe/var_decl.h"
#include "numeric/numeric_op.h"  // from iroha
#include "vm/insn.h"
#include "vm/insn_annotator.h"
#include "vm/method.h"
#include "vm/numeric_object.h"
#include "vm/object.h"
#include "vm/register.h"

namespace compiler {

ExprCompiler::ExprCompiler(Compiler *compiler) : compiler_(compiler) {
}

void ExprCompiler::FlattenCommas(fe::Expr *expr, vector<fe::Expr*> *commas) {
  if (!expr) {
    return;
  }
  if (expr->type_ == fe::BINOP_COMMA) {
    FlattenCommas(expr->lhs_, commas);
    commas->push_back(expr->rhs_);
  } else {
    commas->push_back(expr);
  }
}

vm::Register *ExprCompiler::CompileExpr(fe::Expr *expr) {
  if (expr->type_ == fe::EXPR_SYM) {
    return CompileSymExpr(expr);
  }
  if (expr->type_ == fe::EXPR_FUNCALL) {
    return CompileFuncallExpr(nullptr, expr);
  }
  if (expr->type_ == fe::UNIOP_POST_INC ||
      expr->type_ == fe::UNIOP_POST_DEC) {
    compiler_->AddPrePostIncDecExpr(expr, true);
    return CompileExpr(expr->args_);
  }
  if (expr->type_ == fe::UNIOP_PRE_INC ||
      expr->type_ == fe::UNIOP_PRE_DEC) {
    compiler_->AddPrePostIncDecExpr(expr, false);
    return CompileExpr(expr->args_);
  }
  if (expr->type_ == fe::BINOP_ASSIGN ||
      expr->type_ == fe::BINOP_ADD_ASSIGN ||
      expr->type_ == fe::BINOP_SUB_ASSIGN ||
      expr->type_ == fe::BINOP_MUL_ASSIGN ||
      expr->type_ == fe::BINOP_LSHIFT_ASSIGN ||
      expr->type_ == fe::BINOP_RSHIFT_ASSIGN ||
      expr->type_ == fe::BINOP_AND_ASSIGN ||
      expr->type_ == fe::BINOP_XOR_ASSIGN ||
      expr->type_ == fe::BINOP_OR_ASSIGN) {
    return CompileAssign(expr);
  }
  if (expr->type_ == fe::BINOP_ARRAY_REF) {
    return CompileArrayRef(expr);
  }
  if (expr->type_ == fe::BINOP_COMMA) {
    return CompileComma(expr);
  }
  if (expr->type_ == fe::BINOP_ELM_REF) {
    return CompileElmRef(expr);
  }
  if (expr->type_ == fe::EXPR_TRI_TERM) {
    return CompileTriTerm(expr);
  }
  if (expr->type_ == fe::UNIOP_REF) {
    return CompileRef(expr);
  }
  return CompileSimpleExpr(expr);
}

vm::Register *ExprCompiler::CompileSimpleExpr(fe::Expr *expr) {
  vm::Register *dst_reg = compiler_->AllocRegister();
  vm::Insn *insn = new vm::Insn;
  insn->op_ = GetOpCodeFromExpr(expr);
  insn->insn_expr_ = expr;
  insn->dst_regs_.push_back(dst_reg);
  switch (insn->op_) {
  case vm::OP_ADD:
  case vm::OP_SUB:
  case vm::OP_MUL:
  case vm::OP_GT:
  case vm::OP_LT:
  case vm::OP_GTE:
  case vm::OP_LTE:
  case vm::OP_EQ:
  case vm::OP_NE:
  case vm::OP_LAND:
  case vm::OP_LOR:
  case vm::OP_AND:
  case vm::OP_OR:
  case vm::OP_XOR:
  case vm::OP_CONCAT:
  case vm::OP_LSHIFT:
  case vm::OP_RSHIFT:
    {
      vm::Register *lhs = CompileExpr(expr->lhs_);
      vm::Register *rhs = CompileExpr(expr->rhs_);
      if (!lhs || !rhs) {
	return nullptr;
      }
      insn->src_regs_.push_back(lhs);
      insn->src_regs_.push_back(rhs);
      PropagateRegisterType(insn, lhs, rhs, &dst_reg->type_);
    }
    break;
  case vm::OP_NUM:
    {
      // using same register for src/dst.
      dst_reg->type_.value_type_ = vm::Value::NUM;
      dst_reg->initial_num_ = expr->num_;
      dst_reg->type_.is_const_ = true;
      dst_reg->type_.width_ = expr->num_.type_;
      dst_reg->SetIsDeclaredType(true);
      insn->src_regs_.push_back(dst_reg);
    }
    break;
  case vm::OP_STR:
    {
      dst_reg->type_.value_type_ = vm::Value::OBJECT;
      dst_reg->SetIsDeclaredType(true);
    }
    break;
  case vm::OP_BIT_INV:
  case vm::OP_LOGIC_INV:
  case vm::OP_PLUS:
  case vm::OP_MINUS:
    {
      vm::Register *val = CompileExpr(expr->args_);
      insn->src_regs_.push_back(val);
    }
    break;
  case vm::OP_BIT_RANGE:
    {
      vm::Register *val = CompileExpr(expr->args_);
      vm::Register *msb = CompileExpr(expr->lhs_);
      vm::Register *lsb = CompileExpr(expr->rhs_);
      insn->src_regs_.push_back(val);
      insn->src_regs_.push_back(msb);
      insn->src_regs_.push_back(lsb);
    }
    break;
  default:
    CHECK(false) << "Unknown expr:" << fe::NodeName(expr->type_);
    break;
  }
  vm::Register *rewritten = MayRewriteOperator(insn);
  if (rewritten != nullptr) {
    return rewritten;
  }
  compiler_->EmitInsn(insn);
  return dst_reg;
}

vm::Value::ValueType ExprCompiler::GetVariableType(sym_t name) {
  vm::Register *reg = compiler_->LookupLocalVar(name);
  if (reg) {
    return reg->type_.value_type_;
  } else {
    vm::Value *value = compiler_->GetObj()->LookupValue(name, false);
    if (!value) {
      Status::os(Status::USER_ERROR)
	<< "'" << sym_cstr(name) << "' is not a member of the object";
      MessageFlush::Get(Status::USER_ERROR);
      return vm::Value::NONE;
    }
    return value->type_;
  }
}

vm::Register *ExprCompiler::CompileArrayRef(fe::Expr *expr) {
  vm::Register *index = CompileExpr(expr->rhs_);
  vm::Insn *insn = new vm::Insn;
  insn->op_ = vm::OP_ARRAY_READ;
  insn->src_regs_.push_back(index);
  insn->insn_expr_ = expr->lhs_;
  insn->dst_regs_.push_back(compiler_->AllocRegister());

  vm::Register *array_reg = compiler_->LookupLocalVar(expr->lhs_->sym_);
  if (array_reg) {
    // Local array
    insn->src_regs_.push_back(array_reg);
  } else {
    insn->obj_reg_ = CompileExpr(expr->lhs_);
  }

  compiler_->EmitInsn(insn);
  return insn->dst_regs_[0];
}

vm::Register *ExprCompiler::CompileSymExpr(fe::Expr *expr) {
  sym_t name = expr->sym_;
  vm::Register *reg = compiler_->LookupLocalVar(name);
  if (reg) {
    return reg;
  }

  return CompileMemberSym(expr);
}

vm::Register *ExprCompiler::CompileMemberSym(fe::Expr *expr) {
  vm::Register *obj_reg = compiler_->EmitLoadObj(nullptr);
  vm::Register *reg = compiler_->EmitMemberLoad(obj_reg, expr->sym_);
  reg->orig_name_ = expr->sym_;

  vm::Value *value = compiler_->GetObj()->LookupValue(expr->sym_, false);
  if (value) {
    vm::InsnAnnotator::AnnotateByValue(value, reg);
  }

  return reg;
}

vm::OpCode ExprCompiler::GetOpCodeFromExpr(fe::Expr *expr) {
  switch (expr->type_) {
  case fe::BINOP_ADD: return vm::OP_ADD;
  case fe::BINOP_SUB: return vm::OP_SUB;
  case fe::BINOP_MUL: return vm::OP_MUL;
  case fe::BINOP_GT: return vm::OP_GT;
  case fe::BINOP_LT: return vm::OP_LT;
  case fe::BINOP_GTE: return vm::OP_GTE;
  case fe::BINOP_LTE: return vm::OP_LTE;
  case fe::BINOP_EQ: return vm::OP_EQ;
  case fe::BINOP_NE: return vm::OP_NE;
  case fe::BINOP_LAND: return vm::OP_LAND;
  case fe::BINOP_LOR: return vm::OP_LOR;
  case fe::BINOP_AND: return vm::OP_AND;
  case fe::BINOP_OR: return vm::OP_OR;
  case fe::BINOP_XOR: return vm::OP_XOR;
  case fe::BINOP_CONCAT: return vm::OP_CONCAT;
  case fe::BINOP_LSHIFT: return vm::OP_LSHIFT;
  case fe::BINOP_RSHIFT: return vm::OP_RSHIFT;
  case fe::EXPR_NUM: return vm::OP_NUM;
  case fe::EXPR_STR: return vm::OP_STR;
  case fe::UNIOP_BIT_INV: return vm::OP_BIT_INV;
  case fe::UNIOP_LOGIC_INV: return vm::OP_LOGIC_INV;
  case fe::UNIOP_PLUS: return vm::OP_PLUS;
  case fe::UNIOP_MINUS: return vm::OP_MINUS;
  case fe::EXPR_BIT_RANGE: return vm::OP_BIT_RANGE;
  default:
    CHECK(false) << "Unknown expr:" << fe::NodeName(expr->type_);
  }
  return vm::OP_INVALID;
}

vm::Register *ExprCompiler::CompileRef(fe::Expr *expr) {
  vm::Register *reg = compiler_->AllocRegister();
  vm::Insn *insn = new vm::Insn;
  insn->insn_expr_ = expr;
  insn->dst_regs_.push_back(reg);
  if (compiler_->IsTopLevel()) {
    insn->op_ = vm::OP_GENERIC_READ;
    CHECK(expr->args_->type_ == fe::EXPR_SYM);
    vm::Register *src = compiler_->LookupLocalVar(expr->args_->sym_);
    if (src) {
      insn->src_regs_.push_back(src);
    } else {
      insn->obj_reg_ = compiler_->EmitLoadObj(expr->args_->sym_);
    }
    insn->label_ = expr->args_->sym_;
  } else {
    vm::Value::ValueType type = GetVariableType(expr->args_->sym_);
    if (type == vm::Value::OBJECT) {
      insn->op_ = vm::OP_CHANNEL_READ;
      insn->obj_reg_ = compiler_->EmitLoadObj(expr->args_->sym_);
    } else if (type == vm::Value::NUM) {
      insn->op_ = vm::OP_MEMORY_READ;
      vm::Register *val = CompileExpr(expr->args_);
      insn->src_regs_.push_back(val);
    } else {
      CHECK(false);
    }
  }
  compiler_->EmitInsn(insn);
  return reg;
}

vm::Register *ExprCompiler::CompileAssignToUniopRef(vm::Insn *insn,
						    fe::Expr *lhs,
						    vm::Register *rhs_reg) {
  // LHS can be either an address or a channel.
  vm::Register *lhs_reg = CompileRefLhsExpr(lhs, insn);
  if (lhs_reg) {
    insn->src_regs_.push_back(lhs_reg);
  }
  insn->src_regs_.push_back(rhs_reg);
  insn->dst_regs_.push_back(insn->src_regs_[0]);
  compiler_->EmitInsn(insn);
  return rhs_reg;
}

vm::Register *ExprCompiler::CompileRefLhsExpr(fe::Expr *lhs_expr,
					      vm::Insn *insn) {
  insn->insn_expr_ = lhs_expr;
  // Does't support: *(x.y) = ...; for now.
  CHECK(lhs_expr->args_->type_ == fe::EXPR_SYM)
    << fe::NodeName(lhs_expr->type_);
  sym_t name = lhs_expr->args_->sym_;
  if (compiler_->IsTopLevel()) {
    insn->op_ = vm::OP_GENERIC_WRITE;
    vm::Register *src = compiler_->LookupLocalVar(lhs_expr->args_->sym_);
    if (src) {
      insn->src_regs_.push_back(src);
    } else {
      insn->obj_reg_ = compiler_->EmitLoadObj(lhs_expr->args_->sym_);
    }
    insn->label_ = name;
    return nullptr;
  } else {
    // Determines if it is a channel or memory.
    vm::Value::ValueType type = GetVariableType(name);
    if (type == vm::Value::OBJECT) {
      insn->op_ = vm::OP_CHANNEL_WRITE;
      insn->obj_reg_ = compiler_->EmitLoadObj(lhs_expr->args_->sym_);
      return compiler_->AllocRegister();
    } else if (type == vm::Value::NUM) {
      insn->op_ = vm::OP_MEMORY_WRITE;
      return CompileExpr(lhs_expr->args_);
    } else {
      CHECK(false);
    }
  }
  return nullptr;
}

vm::Register *ExprCompiler::CompileTriTerm(fe::Expr *expr) {
  vm::Register *cond = CompileExpr(expr->args_);
  vm::Register *res = compiler_->AllocRegister();
  sym_t f_label = sym_alloc_tmp_sym("_f");
  vm::Insn *if_insn = new vm::Insn;
  if_insn->op_ = vm::OP_IF;
  if_insn->src_regs_.push_back(cond);
  if_insn->label_ = f_label;
  compiler_->EmitInsn(if_insn);
  // LHS.
  vm::Register *lhs = CompileExpr(expr->lhs_);
  compiler_->SimpleAssign(lhs, res);
  // Go to join.
  sym_t join_label = sym_alloc_tmp_sym("_join");
  vm::Insn *jump_insn = new vm::Insn;
  jump_insn->op_ = vm::OP_GOTO;
  jump_insn->label_ = join_label;
  compiler_->EmitInsn(jump_insn);
  // RHS.
  compiler_->AddLabel(f_label);
  vm::Register *rhs = CompileExpr(expr->rhs_);
  compiler_->SimpleAssign(rhs, res);
  // Join.
  compiler_->AddLabel(join_label);
  return res;
}

vm::Register *ExprCompiler::CompileComma(fe::Expr *expr) {
  vector<fe::Expr*> value_exprs;
  FlattenCommas(expr, &value_exprs);
  vm::Register *reg = nullptr;
  for (size_t i = 0; i < value_exprs.size(); ++i) {
    reg = CompileExpr(value_exprs[i]);
  }
  // Use the last value.
  return reg;
}

vm::Register *ExprCompiler::CompileElmRef(fe::Expr *expr) {
  vm::Register *obj_reg = CompileExpr(expr->lhs_);
  fe::Expr *rhs = expr->rhs_;
  if (rhs->type_ == fe::EXPR_SYM) {
    vm::Register *res_reg;
    res_reg = compiler_->EmitMemberLoad(obj_reg, expr->rhs_->sym_);
    res_reg->orig_name_ = expr->rhs_->sym_;
    return res_reg;
  } else if (rhs->type_ == fe::EXPR_FUNCALL) {
    return CompileFuncallExpr(obj_reg, rhs);
  }
  CHECK(false);
  return nullptr;
}

vm::Register *ExprCompiler::CompileFuncallExpr(vm::Register *obj_reg,
					       fe::Expr *expr) {
  vector<vm::Register *> lhs_regs;
  lhs_regs.push_back(compiler_->AllocRegister());
  return CompileMultiValueFuncall(obj_reg, expr, lhs_regs);
}

vm::Register *ExprCompiler::CompileMultiValueFuncall(vm::Register *obj_reg,
						     fe::Expr *funcall,
						     vector<vm::Register *> &lhs_regs) {
  vm::Insn *call_insn = new vm::Insn;
  call_insn->op_ = vm::OP_FUNCALL;
  call_insn->insn_expr_ = funcall;
  if (obj_reg == nullptr) {
    call_insn->obj_reg_ = compiler_->CompilePathHead(funcall->func_);
  } else {
    call_insn->obj_reg_ = obj_reg;
  }
  call_insn->label_ = funcall->func_->sym_;

  vector<fe::Expr*> args;
  FlattenCommas(funcall->args_, &args);
  for (size_t i = 0; i < args.size(); ++i) {
    vm::Register *reg = CompileExpr(args[i]);
    if (!reg) {
      return nullptr;
    }
    call_insn->src_regs_.push_back(reg);
  }
  compiler_->EmitInsn(call_insn);

  vm::Method *method = GetCalleeMethod(call_insn);
  if (method != nullptr) {
    int num_args = method->GetNumArgRegisters();
    CHECK(args.size() >= num_args) << "Insufficient number of arguments " <<
      args.size() << " < " << num_args;
  }
  return EmitFuncallDone(call_insn, method, lhs_regs);
}

vm::Register *ExprCompiler::EmitFuncallDone(vm::Insn *call_insn,
					    vm::Method *method,
					    vector<vm::Register *> &lhs_regs) {
  vm::Insn *done_insn = new vm::Insn;
  done_insn->op_ = vm::OP_FUNCALL_DONE;
  done_insn->insn_expr_ = call_insn->insn_expr_;
  done_insn->obj_reg_ = call_insn->obj_reg_;
  done_insn->label_ = call_insn->label_;

  // If this is top level, The number of return values
  // can be determined only from LHS expression.
  // Types are also unknown, so let the executor see them later.
  if (compiler_->IsTopLevel()) {
    for (auto *reg : lhs_regs) {
      done_insn->dst_regs_.push_back(reg);
    }
    compiler_->EmitInsn(done_insn);
    CHECK(lhs_regs.size() > 0);
    return lhs_regs[0];
  }

  int num_rets = method->GetNumReturnRegisters();
  if (!(num_rets == 0 && lhs_regs.size() == 1)) {
    CHECK(lhs_regs.size() <= num_rets) << sym_cstr(call_insn->label_) << " " << num_rets << "return values, but " << lhs_regs.size() << " lhs";
  }
  vector<vm::Register *> rets;
  for (int i = 0; i < num_rets; ++i) {
    vm::Register *reg;
    if (i < lhs_regs.size()) {
      reg = lhs_regs[i];
    } else {
      reg = compiler_->AllocRegister();
    }
    reg->type_.value_type_ = vm::Value::NUM;
    if (method->return_types_.size() > i) {
      reg->type_ = method->return_types_[i];
    } else {
      fe::VarDecl *vd = method->parse_tree_->returns_->decls[i];
      reg->type_.object_name_ = vd->GetObjectName();
      reg->type_.width_ = vd->GetWidth();
    }
    done_insn->dst_regs_.push_back(reg);
    rets.push_back(reg);
  }
  compiler_->EmitInsn(done_insn);
  if (rets.size() > 0) {
    return rets[0];
  }
  return nullptr;
}

vm::Method *ExprCompiler::GetCalleeMethod(vm::Insn *call_insn) {
  if (compiler_->IsTopLevel()) {
    return nullptr;
  }
  vm::Object *obj = compiler_->GetVMObject(call_insn->obj_reg_);
  CHECK(obj) << "Failed to find corresponding object to r:"
	     << call_insn->obj_reg_->id_ << " "
	     << sym_cstr(call_insn->label_);
  vm::Value *method_value = obj->LookupValue(call_insn->label_, false);
  CHECK(method_value && method_value->type_ == vm::Value::METHOD)
    << "method=" << sym_cstr(call_insn->label_);
  return method_value->method_;
}

vm::Register *ExprCompiler::CompileAssign(fe::Expr *expr) {
  // Special pattern.
  // (x, y) = f(...)
  if (expr->rhs_->type_ == fe::EXPR_FUNCALL &&
      expr->lhs_->type_ == fe::BINOP_COMMA) {
    vector<vm::Register *> lhs_regs;
    vector<fe::Expr*> values;
    FlattenCommas(expr->lhs_, &values);
    for (auto *v : values) {
      lhs_regs.push_back(CompileSymExpr(v));
    }
    return CompileMultiValueFuncall(nullptr, expr->rhs_, lhs_regs);
  }

  vm::Insn *insn = new vm::Insn;

  // RHS.
  vm::Register *rhs_reg = CompileExpr(expr->rhs_);
  if (!rhs_reg) {
    return nullptr;
  }
  if (expr->type_ != fe::BINOP_ASSIGN) {
    // now rhs corresponds lhs op= rhs.
    // update to lhs op rhs.
    rhs_reg = UpdateModifyOp(expr->type_, expr->lhs_, rhs_reg);
  }

  if (expr->lhs_->type_ == fe::UNIOP_REF) {
    return CompileAssignToUniopRef(insn, expr->lhs_, rhs_reg);
  } else if (expr->lhs_->type_ == fe::BINOP_ELM_REF) {
    return CompileAssignToElmRef(insn, expr->lhs_, rhs_reg);
  } else if (expr->lhs_->type_ == fe::BINOP_ARRAY_REF) {
    return CompileAssignToArray(insn, expr->lhs_, rhs_reg);
  } else if (expr->lhs_->type_ == fe::EXPR_SYM) {
    return CompileAssignToSym(insn, expr->lhs_, rhs_reg);
  } else {
    CHECK(false);
  }
  return nullptr;
}

vm::Register *ExprCompiler::CompileAssignToArray(vm::Insn *insn, fe::Expr *lhs,
						 vm::Register *rhs_reg) {
  // SRC: INDEX RHS_REG {LOCAL_ARRAY}
  // DST: RHS_REG
  // OBJ: ARRAY
  vm::Register *local_array = nullptr;
  insn->op_ = vm::OP_ARRAY_WRITE;
  // index
  vm::Register *index_reg = CompileExpr(lhs->rhs_);
  fe::Expr *array_expr = lhs->lhs_;
  insn->insn_expr_ = array_expr;

  if (array_expr->type_ == fe::EXPR_SYM) {
    vm::Value *value =
      compiler_->GetObj()->LookupValue(array_expr->sym_, false);
    if (!value) {
      local_array = compiler_->LookupLocalVar(array_expr->sym_);
      CHECK(local_array || compiler_->IsTopLevel()) << "undeclared local array";
    }
  }
  insn->src_regs_.push_back(index_reg);
  insn->src_regs_.push_back(rhs_reg);
  if (local_array) {
    insn->src_regs_.push_back(local_array);
  } else {
    if (array_expr->type_ == fe::EXPR_SYM) {
      insn->obj_reg_ =
	compiler_->EmitMemberLoad(compiler_->EmitLoadObj(nullptr),
				  array_expr->sym_);
    } else {
      insn->obj_reg_ = CompileElmRef(array_expr);
    }
  }
  insn->dst_regs_.push_back(insn->src_regs_[1]);
  compiler_->EmitInsn(insn);
  return insn->dst_regs_[0];
}

vm::Register *ExprCompiler::CompileAssignToElmRef(vm::Insn *insn,
						  fe::Expr *lhs,
						  vm::Register *rhs_reg) {
  vm::Register *lhs_obj = CompileExpr(lhs->lhs_);
  CHECK(lhs->rhs_->type_ == fe::EXPR_SYM);
  insn->op_ = vm::OP_MEMBER_WRITE;
  insn->label_ = lhs->rhs_->sym_;
  insn->obj_reg_ = lhs_obj;
  insn->src_regs_.push_back(rhs_reg);
  insn->src_regs_.push_back(lhs_obj);
  insn->dst_regs_.push_back(insn->src_regs_[0]);
  compiler_->EmitInsn(insn);
  return insn->dst_regs_[0];
}

vm::Register *ExprCompiler::CompileAssignToSym(vm::Insn *insn, fe::Expr *lhs,
					       vm::Register *rhs_reg) {
  // local var
  //  SRC: LHS_REG, RHS_REG
  //  DST: LHS_REG
  // member var
  //  SRC: RHS_REG, OBJ_REG
  //  DST: RHS_REG
  vm::Register *lhs_reg = compiler_->LookupLocalVar(lhs->sym_);
  vm::Register *obj_reg = nullptr;
  insn->label_ = lhs->sym_;
  if (lhs_reg) {
    insn->op_ = vm::OP_ASSIGN;
    insn->src_regs_.push_back(lhs_reg);
  } else {
    obj_reg = compiler_->EmitLoadObj(nullptr);
    insn->op_ = vm::OP_MEMBER_WRITE;
  }
  insn->src_regs_.push_back(rhs_reg);
  insn->dst_regs_.push_back(insn->src_regs_[0]);
  if (obj_reg) {
    insn->src_regs_.push_back(obj_reg);
  }
  compiler_->EmitInsn(insn);
  return insn->dst_regs_[0];
}

vm::Register *ExprCompiler::UpdateModifyOp(fe::NodeCode type,
					   fe::Expr *lhs_expr,
					   vm::Register *rhs_reg) {
  vm::Register *lhs_reg = CompileExpr(lhs_expr);
  vm::Insn *insn = new vm::Insn;
  if (type == fe::BINOP_ADD_ASSIGN) {
    insn->op_ = vm::OP_ADD;
  } else if (type == fe::BINOP_SUB_ASSIGN) {
    insn->op_ = vm::OP_SUB;
  } else if (type == fe::BINOP_MUL_ASSIGN) {
    insn->op_ = vm::OP_MUL;
  } else if (type == fe::BINOP_LSHIFT_ASSIGN) {
    insn->op_ = vm::OP_LSHIFT;
  } else if (type == fe::BINOP_RSHIFT_ASSIGN) {
    insn->op_ = vm::OP_RSHIFT;
  } else if (type == fe::BINOP_AND_ASSIGN) {
    insn->op_ = vm::OP_AND;
  } else if (type == fe::BINOP_OR_ASSIGN) {
    insn->op_ = vm::OP_OR;
  } else if (type == fe::BINOP_XOR_ASSIGN) {
    insn->op_ = vm::OP_XOR;
  } else {
    CHECK(false);
  }
  vm::Register *reg = compiler_->AllocRegister();
  insn->dst_regs_.push_back(reg);
  insn->src_regs_.push_back(lhs_reg);
  insn->src_regs_.push_back(rhs_reg);
  compiler_->EmitInsn(insn);
  return reg;
}

vm::Register *ExprCompiler::MayRewriteOperator(vm::Insn *orig_insn) {
  // Concept proof code.
  if (orig_insn->op_ != vm::OP_ADD &&
      orig_insn->op_ != vm::OP_SUB &&
      orig_insn->op_ != vm::OP_MUL) {
    return nullptr;
  }
  if (orig_insn->src_regs_[0]->type_.object_name_ == sym_null ||
      orig_insn->src_regs_[0]->type_.object_name_ !=
      orig_insn->src_regs_[1]->type_.object_name_) {
    return nullptr;
  }
  vm::Register *numerics_reg = compiler_->EmitLoadObj(sym_lookup("Numerics"));
  vm::Register *type_obj_reg =
    compiler_->EmitMemberLoad(numerics_reg,
			      orig_insn->src_regs_[0]->type_.object_name_);
  vm::Object *type_obj = compiler_->GetVMObject(type_obj_reg);
  if (type_obj == nullptr) {
    // TODO: Warn if the user is trying to use type object in top env.
    return nullptr;
  }
  sym_t label = vm::NumericObject::GetMethodName(type_obj, orig_insn->op_);
  if (label == sym_null) {
    // The operator is not available.
    return nullptr;
  }
  vm::Insn *call_insn = new vm::Insn;
  call_insn->op_ = vm::OP_FUNCALL;
  call_insn->obj_reg_ = type_obj_reg;
  call_insn->label_ = label;
  call_insn->src_regs_.push_back(orig_insn->src_regs_[0]);
  call_insn->src_regs_.push_back(orig_insn->src_regs_[1]);
  compiler_->EmitInsn(call_insn);

  vm::Insn *done_insn = new vm::Insn;
  done_insn->op_ = vm::OP_FUNCALL_DONE;
  done_insn->obj_reg_ = call_insn->obj_reg_;
  done_insn->label_ = call_insn->label_;
  done_insn->dst_regs_.push_back(orig_insn->dst_regs_[0]);
  compiler_->EmitInsn(done_insn);
  return orig_insn->dst_regs_[0];
}

void ExprCompiler::PropagateRegisterType(vm::Insn *insn,
					 vm::Register *lhs, vm::Register *rhs,
					 vm::RegisterType *t) {
  if (insn->op_ == vm::OP_ADD ||
      insn->op_ == vm::OP_SUB) {
    *t = lhs->type_;
  }
}

}  // namespace compiler
