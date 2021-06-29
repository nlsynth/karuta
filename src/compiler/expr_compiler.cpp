#include "compiler/expr_compiler.h"

#include "base/status.h"
#include "compiler/method_compiler.h"
#include "fe/expr.h"
#include "fe/method.h"
#include "fe/var_decl.h"
#include "iroha/numeric.h"
#include "vm/array_wrapper.h"
#include "vm/decl_annotator.h"
#include "vm/insn.h"
#include "vm/insn_annotator.h"
#include "vm/vm_method.h"
#include "vm/numeric_object.h"
#include "vm/object.h"
#include "vm/register.h"

namespace compiler {

ExprCompiler::ExprCompiler(MethodCompiler *compiler) : compiler_(compiler) {}

void ExprCompiler::FlattenCommas(fe::Expr *expr, vector<fe::Expr *> *commas) {
  if (!expr) {
    return;
  }
  if (expr->GetType() == fe::BINOP_COMMA) {
    FlattenCommas(expr->GetLhs(), commas);
    commas->push_back(expr->GetRhs());
  } else {
    commas->push_back(expr);
  }
}

vm::Register *ExprCompiler::CompileExprToOneReg(fe::Expr *expr) {
  RegisterTuple tp = CompileExpr(expr);
  if (tp.regs.size() > 1) {
    // Returns the last value for now.
    // TODO: Implement tuple passing and CHECK(tp.regs.size() <= 2) instead.
    return tp.regs[tp.regs.size() - 1];
  }
  return tp.GetOne();
}

RegisterTuple ExprCompiler::CompileExpr(fe::Expr *expr) {
  auto type = expr->GetType();
  if (type == fe::EXPR_SYM) {
    return RegisterTuple(CompileSymExpr(expr));
  }
  if (type == fe::EXPR_FUNCALL) {
    return RegisterTuple(CompileFuncallExpr(nullptr, expr));
  }
  if (type == fe::UNIOP_POST_INC || type == fe::UNIOP_POST_DEC) {
    compiler_->AddPrePostIncDecExpr(expr, true);
    return CompileExpr(expr->GetArgs());
  }
  if (type == fe::UNIOP_PRE_INC || type == fe::UNIOP_PRE_DEC) {
    compiler_->AddPrePostIncDecExpr(expr, false);
    return CompileExpr(expr->GetArgs());
  }
  if (type == fe::BINOP_ASSIGN || type == fe::BINOP_ADD_ASSIGN ||
      type == fe::BINOP_SUB_ASSIGN || type == fe::BINOP_MUL_ASSIGN ||
      type == fe::BINOP_DIV_ASSIGN || type == fe::BINOP_LSHIFT_ASSIGN ||
      type == fe::BINOP_RSHIFT_ASSIGN || type == fe::BINOP_AND_ASSIGN ||
      type == fe::BINOP_XOR_ASSIGN || type == fe::BINOP_OR_ASSIGN) {
    return CompileAssign(expr);
  }
  if (type == fe::BINOP_ARRAY_REF) {
    return RegisterTuple(CompileArrayRef(expr));
  }
  if (type == fe::BINOP_COMMA) {
    return CompileComma(expr);
  }
  if (type == fe::BINOP_ELM_REF) {
    return CompileElmRef(expr);
  }
  if (type == fe::EXPR_TRI_TERM) {
    return RegisterTuple(CompileTriTerm(expr));
  }
  return RegisterTuple(CompileSimpleExpr(expr));
}

vm::Register *ExprCompiler::CompileSimpleExpr(fe::Expr *expr) {
  vm::Register *dst_reg = compiler_->AllocRegister();
  vm::Insn *insn = new vm::Insn;
  vm::OpCode op = GetOpCodeFromExpr(expr);
  insn->op_ = MayRewriteToOpWithType(op);
  insn->insn_expr_ = expr;
  insn->dst_regs_.push_back(dst_reg);
  switch (insn->op_) {
    case vm::OP_ADD:
    case vm::OP_TL_ADD_MAY_WITH_TYPE:
    case vm::OP_SUB:
    case vm::OP_TL_SUB_MAY_WITH_TYPE:
    case vm::OP_MUL:
    case vm::OP_TL_MUL_MAY_WITH_TYPE:
    case vm::OP_DIV:
    case vm::OP_TL_DIV_MAY_WITH_TYPE:
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
    case vm::OP_RSHIFT: {
      vm::Register *lhs = CompileExprToOneReg(expr->GetLhs());
      vm::Register *rhs = CompileExprToOneReg(expr->GetRhs());
      if (!lhs || !rhs) {
        return nullptr;
      }
      insn->src_regs_.push_back(lhs);
      insn->src_regs_.push_back(rhs);
      PropagateRegisterType(insn, lhs, rhs, &dst_reg->type_);
    } break;
    case vm::OP_NUM: {
      // using same register for src/dst.
      dst_reg->type_.value_type_ = vm::Value::NUM;
      iroha::Numeric::CopyValue(expr->GetNum(), nullptr,
                                &dst_reg->initial_num_);
      dst_reg->type_.is_const_ = true;
      dst_reg->type_.num_width_ = expr->GetNum().type_;
      dst_reg->SetIsDeclaredType(true);
      insn->src_regs_.push_back(dst_reg);
    } break;
    case vm::OP_STR: {
      dst_reg->type_.value_type_ = vm::Value::OBJECT;
      dst_reg->SetIsDeclaredType(true);
    } break;
    case vm::OP_BIT_INV:
    case vm::OP_LOGIC_INV:
    case vm::OP_PLUS:
    case vm::OP_MINUS: {
      vm::Register *val = CompileExprToOneReg(expr->GetArgs());
      insn->src_regs_.push_back(val);
    } break;
    case vm::OP_BIT_RANGE: {
      vm::Register *val = CompileExprToOneReg(expr->GetArgs());
      vm::Register *msb = CompileExprToOneReg(expr->GetLhs());
      vm::Register *lsb = CompileExprToOneReg(expr->GetRhs());
      insn->src_regs_.push_back(val);
      insn->src_regs_.push_back(msb);
      insn->src_regs_.push_back(lsb);
    } break;
    default:
      CHECK(false) << "Unknown expr:" << fe::NodeName(expr->GetType());
      break;
  }
  vm::Register *rewritten = MayRewriteOperator(insn);
  if (rewritten != nullptr) {
    return rewritten;
  }
  compiler_->EmitInsn(insn);
  MayEmitTypeDoneInsn(insn);
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
  vector<vm::Register *> indexes;
  fe::Expr *array_expr = ResolveArray(expr, &indexes);
  vm::Insn *insn = new vm::Insn;
  insn->op_ = vm::OP_ARRAY_READ;
  insn->src_regs_ = indexes;
  insn->insn_expr_ = array_expr;
  insn->dst_regs_.push_back(compiler_->AllocRegister());
  insn->obj_reg_ = CompileExprToOneReg(array_expr);

  if (!compiler_->IsTopLevel()) {
    // Identify array element object.
    // This works only for constant index for now.
    vm::Object *array_obj = compiler_->GetVMObject(insn->obj_reg_);
    if (array_obj != nullptr && vm::ArrayWrapper::IsObjectArray(array_obj)) {
      if (indexes.size() == 1 && indexes[0]->type_.is_const_) {
        int idx = indexes[0]->initial_num_.GetValue0();
        vm::Object *elm_obj = vm::ArrayWrapper::Get(array_obj, idx);
        compiler_->RegisterVMObject(insn->dst_regs_[0], elm_obj);
      }
    }
  }
  compiler_->EmitInsn(insn);
  return insn->dst_regs_[0];
}

vm::Register *ExprCompiler::CompileSymExpr(fe::Expr *expr) {
  sym_t name = expr->GetSym();
  vm::Register *reg = compiler_->LookupLocalVar(name);
  if (reg) {
    return reg;
  }

  return CompileMemberSym(expr);
}

vm::Register *ExprCompiler::CompileMemberSym(fe::Expr *expr) {
  vm::Register *obj_reg = compiler_->EmitLoadObj(nullptr);
  vm::Register *reg = compiler_->EmitMemberLoad(obj_reg, expr->GetSym());
  reg->orig_name_ = expr->GetSym();

  vm::Value *value = compiler_->GetObj()->LookupValue(expr->GetSym(), false);
  if (value) {
    vm::DeclAnnotator::AnnotateByValue(value, reg);
  }

  return reg;
}

vm::OpCode ExprCompiler::GetOpCodeFromExpr(fe::Expr *expr) {
  switch (expr->GetType()) {
    case fe::BINOP_ADD:
      return vm::OP_ADD;
    case fe::BINOP_SUB:
      return vm::OP_SUB;
    case fe::BINOP_MUL:
      return vm::OP_MUL;
    case fe::BINOP_DIV:
      return vm::OP_DIV;
    case fe::BINOP_GT:
      return vm::OP_GT;
    case fe::BINOP_LT:
      return vm::OP_LT;
    case fe::BINOP_GTE:
      return vm::OP_GTE;
    case fe::BINOP_LTE:
      return vm::OP_LTE;
    case fe::BINOP_EQ:
      return vm::OP_EQ;
    case fe::BINOP_NE:
      return vm::OP_NE;
    case fe::BINOP_LAND:
      return vm::OP_LAND;
    case fe::BINOP_LOR:
      return vm::OP_LOR;
    case fe::BINOP_AND:
      return vm::OP_AND;
    case fe::BINOP_OR:
      return vm::OP_OR;
    case fe::BINOP_XOR:
      return vm::OP_XOR;
    case fe::BINOP_CONCAT:
      return vm::OP_CONCAT;
    case fe::BINOP_LSHIFT:
      return vm::OP_LSHIFT;
    case fe::BINOP_RSHIFT:
      return vm::OP_RSHIFT;
    case fe::EXPR_NUM:
      return vm::OP_NUM;
    case fe::EXPR_STR:
      return vm::OP_STR;
    case fe::UNIOP_BIT_INV:
      return vm::OP_BIT_INV;
    case fe::UNIOP_LOGIC_INV:
      return vm::OP_LOGIC_INV;
    case fe::UNIOP_PLUS:
      return vm::OP_PLUS;
    case fe::UNIOP_MINUS:
      return vm::OP_MINUS;
    case fe::EXPR_BIT_RANGE:
      return vm::OP_BIT_RANGE;
    default:
      CHECK(false) << "Unknown expr:" << fe::NodeName(expr->GetType());
  }
  return vm::OP_INVALID;
}

vm::OpCode ExprCompiler::MayRewriteToOpWithType(vm::OpCode op) {
  if (compiler_->IsTopLevel()) {
    switch (op) {
      case vm::OP_ADD:
        return vm::OP_TL_ADD_MAY_WITH_TYPE;
      case vm::OP_SUB:
        return vm::OP_TL_SUB_MAY_WITH_TYPE;
      case vm::OP_MUL:
        return vm::OP_TL_MUL_MAY_WITH_TYPE;
      case vm::OP_DIV:
        return vm::OP_TL_DIV_MAY_WITH_TYPE;
      default:
        break;
    }
  }
  return op;
}

vm::Register *ExprCompiler::CompileTriTerm(fe::Expr *expr) {
  vm::Register *cond = CompileExprToOneReg(expr->GetArgs());
  vm::Register *res = compiler_->AllocRegister();
  sym_t f_label = sym_alloc_tmp_sym("_f");
  vm::Insn *if_insn = new vm::Insn;
  if_insn->op_ = vm::OP_IF;
  if_insn->src_regs_.push_back(cond);
  if_insn->label_ = f_label;
  compiler_->EmitInsn(if_insn);
  // LHS.
  vm::Register *lhs = CompileExprToOneReg(expr->GetLhs());
  compiler_->SimpleAssign(lhs, res);
  // Go to join.
  sym_t join_label = sym_alloc_tmp_sym("_join");
  vm::Insn *jump_insn = new vm::Insn;
  jump_insn->op_ = vm::OP_GOTO;
  jump_insn->label_ = join_label;
  compiler_->EmitInsn(jump_insn);
  // RHS.
  compiler_->AddLabel(f_label);
  vm::Register *rhs = CompileExprToOneReg(expr->GetRhs());
  compiler_->SimpleAssign(rhs, res);
  // Join.
  compiler_->AddLabel(join_label);
  return res;
}

RegisterTuple ExprCompiler::CompileComma(fe::Expr *expr) {
  vector<fe::Expr *> value_exprs;
  FlattenCommas(expr, &value_exprs);
  RegisterTuple rt;
  for (size_t i = 0; i < value_exprs.size(); ++i) {
    rt.regs.push_back(CompileExprToOneReg(value_exprs[i]));
  }
  return rt;
}

RegisterTuple ExprCompiler::CompileElmRef(fe::Expr *expr) {
  vm::Register *obj_reg = CompileExprToOneReg(expr->GetLhs());
  fe::Expr *rhs = expr->GetRhs();
  if (rhs->GetType() == fe::EXPR_SYM) {
    vm::Register *res_reg;
    sym_t elm_name = expr->GetRhs()->GetSym();
    res_reg = compiler_->EmitMemberLoad(obj_reg, elm_name);
    res_reg->orig_name_ = elm_name;
    return RegisterTuple(res_reg);
  } else if (rhs->GetType() == fe::EXPR_FUNCALL) {
    return CompileFuncallExpr(obj_reg, rhs);
  }
  CHECK(false);
  return RegisterTuple(nullptr);
}

RegisterTuple ExprCompiler::CompileFuncallExpr(vm::Register *obj_reg,
                                               fe::Expr *expr) {
  return CompileMultiValueFuncall(obj_reg, expr, 1);
}

RegisterTuple ExprCompiler::CompileMultiValueFuncall(vm::Register *obj_reg,
                                                     fe::Expr *funcall,
                                                     int num_lhs) {
  vm::Insn *call_insn = new vm::Insn;
  if (compiler_->IsTopLevel()) {
    call_insn->op_ = vm::OP_TL_FUNCALL_WITH_CHECK;
  } else {
    call_insn->op_ = vm::OP_FUNCALL;
  }
  call_insn->insn_expr_ = funcall;
  if (obj_reg == nullptr) {
    call_insn->obj_reg_ = compiler_->CompilePathHead(funcall->GetFunc());
  } else {
    if (obj_reg->type_.object_name_ != sym_null &&
        obj_reg->type_.value_type_ == vm::Value::NUM) {
      // custom struct accessor.
      vm::Register *numeric_obj =
          LoadNumericTypeRegister(obj_reg->type_.object_name_);
      CHECK(numeric_obj);
      call_insn->obj_reg_ = numeric_obj;
      call_insn->src_regs_.push_back(obj_reg);
    } else {
      call_insn->obj_reg_ = obj_reg;
    }
  }
  call_insn->label_ = funcall->GetFunc()->GetSym();

  vector<fe::Expr *> args;
  FlattenCommas(funcall->GetArgs(), &args);
  for (size_t i = 0; i < args.size(); ++i) {
    RegisterTuple rp = CompileExpr(args[i]);
    if (i == 0 && rp.regs.size() > 1) {
      // Processes tuple argument.
      for (vm::Register *reg : rp.regs) {
        call_insn->src_regs_.push_back(reg);
      }
      CHECK(args.size() == 1);
      // Does not see the remaining args.
      break;
    }
    vm::Register *reg = rp.GetOne();
    if (!reg) {
      return RegisterTuple();
    }
    call_insn->src_regs_.push_back(reg);
  }
  compiler_->EmitInsn(call_insn);

  vm::Method *method = GetCalleeMethod(call_insn);
  if (method != nullptr) {
    int num_args = method->GetNumArgRegisters();
    CHECK(call_insn->src_regs_.size() >= num_args)
        << "Insufficient number of arguments " << args.size() << " < "
        << num_args;
  }
  if (!compiler_->IsTopLevel() && method == nullptr) {
    // Missing method. The error was already reported.
    return RegisterTuple();
  }
  return EmitFuncallDone(call_insn, method, num_lhs);
}

RegisterTuple ExprCompiler::EmitFuncallDone(vm::Insn *call_insn,
                                            vm::Method *method, int num_lhs) {
  RegisterTuple rt;
  vm::Insn *done_insn = new vm::Insn;
  if (compiler_->IsTopLevel()) {
    done_insn->op_ = vm::OP_TL_FUNCALL_DONE_WITH_CHECK;
  } else {
    done_insn->op_ = vm::OP_FUNCALL_DONE;
  }
  done_insn->insn_expr_ = call_insn->insn_expr_;
  done_insn->obj_reg_ = call_insn->obj_reg_;
  done_insn->label_ = call_insn->label_;

  // If this is top level, The number of return values
  // can be determined only from LHS expression.
  // Types are also unknown, so let the executor see them later.
  if (compiler_->IsTopLevel()) {
    for (int i = 0; i < num_lhs; ++i) {
      vm::Register *reg = compiler_->AllocRegister();
      done_insn->dst_regs_.push_back(reg);
      rt.regs.push_back(reg);
    }
    compiler_->EmitInsn(done_insn);
    CHECK(num_lhs > 0);
    return rt;
  }

  int num_rets = method->GetNumReturnRegisters();
  if (!(num_rets == 0 && num_lhs == 1)) {
    CHECK(num_lhs <= num_rets) << sym_cstr(call_insn->label_) << " " << num_rets
                               << "return values, but " << num_lhs << " lhs";
  }
  for (int i = 0; i < num_rets; ++i) {
    vm::Register *reg = compiler_->AllocRegister();
    reg->type_.value_type_ = vm::Value::NUM;
    if (method->return_types_.size() > i) {
      reg->type_ = method->return_types_[i];
    } else {
      fe::VarDecl *vd = method->GetParseTree()->GetReturns()->decls[i];
      reg->type_.object_name_ = vd->GetObjectName();
      reg->type_.num_width_ = vd->GetWidth();
    }
    done_insn->dst_regs_.push_back(reg);
    rt.regs.push_back(reg);
  }
  compiler_->EmitInsn(done_insn);
  return rt;
}

void ExprCompiler::MayEmitTypeDoneInsn(vm::Insn *insn) {
  if (insn->op_ == vm::OP_TL_ADD_MAY_WITH_TYPE ||
      insn->op_ == vm::OP_TL_ADD_MAY_WITH_TYPE ||
      insn->op_ == vm::OP_TL_ADD_MAY_WITH_TYPE) {
    vm::Insn *done_insn = new vm::Insn;
    done_insn->op_ = vm::OP_TL_MAY_WITH_TYPE_DONE;
    done_insn->src_regs_ = insn->src_regs_;
    done_insn->dst_regs_ = insn->dst_regs_;
    compiler_->EmitInsn(done_insn);
  }
}

vm::Method *ExprCompiler::GetCalleeMethod(vm::Insn *call_insn) {
  if (compiler_->IsTopLevel()) {
    return nullptr;
  }
  vm::Object *obj = compiler_->GetVMObject(call_insn->obj_reg_);
  if (obj == nullptr) {
    Status::os(Status::USER_ERROR)
        << "Failed to find corresponding object to r:"
        << call_insn->obj_reg_->id_ << " " << sym_cstr(call_insn->label_);
    return nullptr;
  }
  vm::Value *method_value = obj->LookupValue(call_insn->label_, false);
  if (method_value == nullptr || method_value->type_ != vm::Value::METHOD) {
    Status::os(Status::USER_ERROR)
        << "Failed to find method: " << sym_cstr(call_insn->label_);
    return nullptr;
  }
  return method_value->method_;
}

RegisterTuple ExprCompiler::CompileAssign(fe::Expr *expr) {
  // Special pattern.
  // (x, y) = ...
  if (expr->GetLhs()->GetType() == fe::BINOP_COMMA) {
    return CompileMultiAssign(expr->GetLhs(), expr->GetRhs());
  }

  // RHS.
  vm::Register *rhs_reg = CompileExprToOneReg(expr->GetRhs());
  if (!rhs_reg) {
    return RegisterTuple();
  }
  if (expr->GetType() != fe::BINOP_ASSIGN) {
    // now rhs corresponds lhs op= rhs.
    // update to lhs op rhs.
    rhs_reg = UpdateModifyOp(expr->GetType(), expr->GetLhs(), rhs_reg);
  }

  vm::Insn *insn = new vm::Insn;
  return RegisterTuple(CompileAssignToLhs(insn, expr->GetLhs(), rhs_reg));
}

RegisterTuple ExprCompiler::CompileMultiAssign(fe::Expr *lhs_expr,
                                               fe::Expr *rhs_expr) {
  vector<fe::Expr *> values;
  FlattenCommas(lhs_expr, &values);
  RegisterTuple lhs;
  for (auto *v : values) {
    lhs.regs.push_back(CompileSymExpr(v));
  }
  RegisterTuple rhs;
  if (rhs_expr->GetType() == fe::EXPR_FUNCALL) {
    rhs = CompileMultiValueFuncall(nullptr, rhs_expr, values.size());
  } else if (rhs_expr->GetType() == fe::BINOP_ELM_REF) {
    rhs = CompileExpr(rhs_expr);
  } else if (rhs_expr->GetType() == fe::BINOP_COMMA) {
    // Assigns to temporary registers to avoid unnecesary dependency.
    // e.g. (x, y) = (y, x) => x = y, y = x => (x,y) == (y,y)!
    RegisterTuple tmp = CompileComma(rhs_expr);
    for (vm::Register *reg : tmp.regs) {
      vm::Register *dst = compiler_->AllocRegister();
      compiler_->SimpleAssign(reg, dst);
      rhs.regs.push_back(dst);
    }
  } else {
    CHECK(false);
  }
  CHECK(lhs.regs.size() == rhs.regs.size());
  for (int i = 0; i < lhs.regs.size(); ++i) {
    compiler_->SimpleAssign(rhs.regs[i], lhs.regs[i]);
  }
  return lhs;
}

vm::Register *ExprCompiler::CompileAssignToLhs(vm::Insn *insn, fe::Expr *lhs,
                                               vm::Register *rhs_reg) {
  if (lhs->GetType() == fe::BINOP_ELM_REF) {
    return CompileAssignToElmRef(insn, lhs, rhs_reg);
  } else if (lhs->GetType() == fe::BINOP_ARRAY_REF) {
    return CompileAssignToArray(insn, lhs, rhs_reg);
  } else if (lhs->GetType() == fe::EXPR_SYM) {
    return CompileAssignToSym(insn, lhs, rhs_reg);
  } else {
    CHECK(false);
  }
  return nullptr;
}

vm::Register *ExprCompiler::CompileAssignToArray(vm::Insn *insn, fe::Expr *lhs,
                                                 vm::Register *rhs_reg) {
  // SRC: RHS_REG INDEX
  // DST: LHS_REG
  // OBJ: ARRAY
  if (compiler_->IsTopLevel()) {
    insn->op_ = vm::OP_TL_ARRAY_WRITE_WITH_CHECK;
  } else {
    insn->op_ = vm::OP_ARRAY_WRITE;
  }
  // index
  vector<vm::Register *> indexes;
  fe::Expr *array_expr = ResolveArray(lhs, &indexes);
  insn->insn_expr_ = array_expr;

  // rhs
  insn->src_regs_.push_back(rhs_reg);
  // indexes.
  for (vm::Register *reg : indexes) {
    insn->src_regs_.push_back(reg);
  }
  // array
  if (array_expr->GetType() == fe::EXPR_SYM) {
    vm::Value *value =
        compiler_->GetObj()->LookupValue(array_expr->GetSym(), false);
    CHECK(value != nullptr || compiler_->IsTopLevel())
        << "undeclared array: " << sym_cstr(array_expr->GetSym());
    insn->obj_reg_ = compiler_->EmitMemberLoad(compiler_->EmitLoadObj(nullptr),
                                               array_expr->GetSym());
  } else {
    CHECK(array_expr->GetType() == fe::BINOP_ELM_REF);
    RegisterTuple rt = CompileElmRef(array_expr);
    insn->obj_reg_ = rt.GetOne();
  }
  insn->dst_regs_.push_back(insn->src_regs_[1]);
  compiler_->EmitInsn(insn);
  return insn->dst_regs_[0];
}

fe::Expr *ExprCompiler::ResolveArray(fe::Expr *access_expr,
                                     vector<vm::Register *> *indexes) {
  if (access_expr->GetType() == fe::BINOP_ARRAY_REF) {
    indexes->push_back(CompileExprToOneReg(access_expr->GetRhs()));
  }
  fe::Expr *lhs = access_expr->GetLhs();
  if (lhs->GetType() == fe::EXPR_SYM || lhs->GetType() == fe::BINOP_ELM_REF) {
    return access_expr->GetLhs();
  } else {
    return ResolveArray(lhs, indexes);
  }
}

vm::Register *ExprCompiler::CompileAssignToElmRef(vm::Insn *insn, fe::Expr *lhs,
                                                  vm::Register *rhs_reg) {
  vm::Register *lhs_obj = CompileExprToOneReg(lhs->GetLhs());
  CHECK(lhs->GetRhs()->GetType() == fe::EXPR_SYM);
  insn->op_ = vm::OP_MEMBER_WRITE;
  insn->label_ = lhs->GetRhs()->GetSym();
  insn->obj_reg_ = lhs_obj;
  insn->src_regs_.push_back(rhs_reg);
  insn->dst_regs_.push_back(insn->src_regs_[0]);
  compiler_->EmitInsn(insn);
  return insn->dst_regs_[0];
}

vm::Register *ExprCompiler::CompileAssignToSym(vm::Insn *insn, fe::Expr *lhs,
                                               vm::Register *rhs_reg) {
  // local var - OP_ASSIGN
  //  SRC: LHS_REG, RHS_REG
  //  DST: LHS_REG
  // member var - OP_MEMBER_WRITE
  //  OBJ: OBJ_REG
  //  SRC: RHS_REG
  //  DST: RHS_REG
  vm::Register *lhs_reg = compiler_->LookupLocalVar(lhs->GetSym());
  insn->label_ = lhs->GetSym();
  if (lhs_reg) {
    insn->op_ = vm::OP_ASSIGN;
    insn->src_regs_.push_back(lhs_reg);
  } else {
    insn->op_ = vm::OP_MEMBER_WRITE;
    insn->obj_reg_ = compiler_->EmitLoadObj(nullptr);
  }
  insn->src_regs_.push_back(rhs_reg);
  insn->dst_regs_.push_back(insn->src_regs_[0]);
  compiler_->EmitInsn(insn);
  return insn->dst_regs_[0];
}

vm::Register *ExprCompiler::UpdateModifyOp(fe::NodeCode type,
                                           fe::Expr *lhs_expr,
                                           vm::Register *rhs_reg) {
  vm::Register *lhs_reg = CompileExprToOneReg(lhs_expr);
  vm::Insn *insn = new vm::Insn;
  if (type == fe::BINOP_ADD_ASSIGN) {
    insn->op_ = MayRewriteToOpWithType(vm::OP_ADD);
  } else if (type == fe::BINOP_SUB_ASSIGN) {
    insn->op_ = MayRewriteToOpWithType(vm::OP_SUB);
  } else if (type == fe::BINOP_MUL_ASSIGN) {
    insn->op_ = MayRewriteToOpWithType(vm::OP_MUL);
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
  vm::Register *rewritten = MayRewriteOperator(insn);
  if (rewritten != nullptr) {
    return rewritten;
  }
  MayEmitTypeDoneInsn(insn);
  return reg;
}

vm::Register *ExprCompiler::MayRewriteOperator(vm::Insn *orig_insn) {
  if (orig_insn->op_ != vm::OP_ADD && orig_insn->op_ != vm::OP_SUB &&
      orig_insn->op_ != vm::OP_MUL) {
    return nullptr;
  }
  if (orig_insn->src_regs_[0]->type_.object_name_ == sym_null ||
      orig_insn->src_regs_[0]->type_.object_name_ !=
          orig_insn->src_regs_[1]->type_.object_name_) {
    return nullptr;
  }
  vm::Register *type_obj_reg =
      LoadNumericTypeRegister(orig_insn->src_regs_[0]->type_.object_name_);
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
  if (compiler_->IsTopLevel()) {
    call_insn->op_ = vm::OP_TL_FUNCALL_WITH_CHECK;
  } else {
    call_insn->op_ = vm::OP_FUNCALL;
  }
  call_insn->obj_reg_ = type_obj_reg;
  call_insn->label_ = label;
  call_insn->src_regs_.push_back(orig_insn->src_regs_[0]);
  call_insn->src_regs_.push_back(orig_insn->src_regs_[1]);
  compiler_->EmitInsn(call_insn);

  vm::Insn *done_insn = new vm::Insn;
  if (compiler_->IsTopLevel()) {
    done_insn->op_ = vm::OP_TL_FUNCALL_DONE_WITH_CHECK;
  } else {
    done_insn->op_ = vm::OP_FUNCALL_DONE;
  }
  done_insn->obj_reg_ = call_insn->obj_reg_;
  done_insn->label_ = call_insn->label_;
  done_insn->dst_regs_.push_back(orig_insn->dst_regs_[0]);
  done_insn->dst_regs_[0]->type_.object_name_ =
      orig_insn->src_regs_[0]->type_.object_name_;
  compiler_->EmitInsn(done_insn);
  return orig_insn->dst_regs_[0];
}

vm::Register *ExprCompiler::LoadNumericTypeRegister(sym_t obj_name) {
  vm::Register *numerics_reg = compiler_->EmitLoadObj(sym_lookup("Numerics"));
  return compiler_->EmitMemberLoad(numerics_reg, obj_name);
}

void ExprCompiler::PropagateRegisterType(vm::Insn *insn, vm::Register *lhs,
                                         vm::Register *rhs,
                                         vm::RegisterType *t) {
  if (insn->op_ == vm::OP_ADD || insn->op_ == vm::OP_TL_ADD_MAY_WITH_TYPE ||
      insn->op_ == vm::OP_SUB || insn->op_ == vm::OP_TL_SUB_MAY_WITH_TYPE) {
    *t = lhs->type_;
  }
}

void ExprCompiler::CompileIncDecExpr(fe::Expr *expr) {
  vm::Register *reg = nullptr;
  if (expr->GetArgs()->GetType() == fe::EXPR_SYM) {
    reg = compiler_->LookupLocalVar(expr->GetArgs()->GetSym());
  }
  if (reg == nullptr) {
    CompileIncDecNonLocal(expr);
    return;
  }
  vm::Insn *insn = new vm::Insn;
  if (expr->GetType() == fe::UNIOP_PRE_INC ||
      expr->GetType() == fe::UNIOP_POST_INC) {
    insn->op_ = vm::OP_PRE_INC;
  } else {
    insn->op_ = vm::OP_PRE_DEC;
  }
  insn->dst_regs_.push_back(reg);
  insn->src_regs_.push_back(reg);
  compiler_->SetDelayInsnEmit(false);
  compiler_->EmitInsn(insn);
  compiler_->SetDelayInsnEmit(true);
}

void ExprCompiler::CompileIncDecNonLocal(fe::Expr *expr) {
  compiler_->SetDelayInsnEmit(false);
  vm::Register *rhs = CompileExprToOneReg(expr->GetArgs());

  vm::Insn *insn = new vm::Insn;
  insn->op_ = vm::OP_NUM;
  vm::Register *one = compiler_->AllocRegister();
  one->type_.value_type_ = vm::Value::NUM;
  one->initial_num_.SetValue0(1);
  one->initial_num_.type_ = rhs->type_.num_width_;
  one->type_.is_const_ = true;
  one->type_.num_width_ = rhs->type_.num_width_;
  one->SetIsDeclaredType(true);
  insn->src_regs_.push_back(one);
  insn->dst_regs_.push_back(one);
  compiler_->EmitInsn(insn);

  vm::Register *dst = compiler_->AllocRegister();
  dst->type_.value_type_ = vm::Value::NUM;
  dst->type_.is_const_ = true;
  dst->type_.num_width_ = rhs->type_.num_width_;
  dst->SetIsDeclaredType(false);

  insn = new vm::Insn;
  if (expr->GetType() == fe::UNIOP_PRE_INC ||
      expr->GetType() == fe::UNIOP_POST_INC) {
    insn->op_ = vm::OP_ADD;
  } else {
    insn->op_ = vm::OP_SUB;
  }
  insn->insn_expr_ = expr;
  insn->dst_regs_.push_back(dst);
  insn->src_regs_.push_back(rhs);
  insn->src_regs_.push_back(one);
  compiler_->EmitInsn(insn);

  insn = new vm::Insn;
  CompileAssignToLhs(insn, expr->GetArgs(), dst);

  compiler_->SetDelayInsnEmit(true);
}

void ExprCompiler::EmitRun() {
  vm::Register *obj_reg = compiler_->EmitLoadObj(nullptr);
  EmitFuncallForEpilogue("run", obj_reg, nullptr);
}

void ExprCompiler::EmitCompile() {
  vm::Register *obj_reg = compiler_->EmitLoadObj(nullptr);
  EmitFuncallForEpilogue("compile", obj_reg, nullptr);
}

void ExprCompiler::EmitWriteHdl(const string &fn) {
  vm::Insn *insn = new vm::Insn;
  insn->op_ = vm::OP_STR;
  insn->label_ = sym_lookup(fn.c_str());
  vm::Register *fn_reg = compiler_->AllocRegister();
  fn_reg->type_.value_type_ = vm::Value::OBJECT;
  fn_reg->SetIsDeclaredType(true);
  insn->dst_regs_.push_back(fn_reg);
  compiler_->EmitInsn(insn);

  vm::Register *obj_reg = compiler_->EmitLoadObj(nullptr);
  EmitFuncallForEpilogue("writeHdl", obj_reg, fn_reg);
}

void ExprCompiler::EmitFuncallForEpilogue(const char *name,
                                          vm::Register *obj_reg,
                                          vm::Register *arg_reg) {
  vm::Insn *insn = new vm::Insn;
  insn->op_ = vm::OP_TL_FUNCALL_WITH_CHECK;
  insn->obj_reg_ = obj_reg;
  insn->label_ = sym_lookup(name);
  if (arg_reg != nullptr) {
    insn->src_regs_.push_back(arg_reg);
  }
  compiler_->EmitInsn(insn);
}

}  // namespace compiler
