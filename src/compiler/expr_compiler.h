// -*- C++ -*-
#ifndef _compiler_expr_compiler_h_
#define _compiler_expr_compiler_h_

#include "compiler/common.h"

#include "fe/nodecode.h"
#include "vm/value.h"
#include "vm/opcode.h"

namespace compiler {

class ExprCompiler {
public:
  ExprCompiler(Compiler *compiler);

  RegisterTuple CompileExpr(fe::Expr *expr);
  vm::Register *CompileSymExpr(fe::Expr *expr);
  void CompileIncDecExpr(fe::Expr *expr);
  static void FlattenCommas(fe::Expr *expr, vector<fe::Expr*> *commas);

private:
  vm::Register *CompileExprToOneReg(fe::Expr *expr);
  RegisterTuple CompileAssign(fe::Expr *expr);
  RegisterTuple CompileMultiAssign(fe::Expr *lhs_expr, fe::Expr *rhs_expr);
  vm::Register *CompileAssignToArray(vm::Insn *insn, fe::Expr *lhs,
				     vm::Register *rhs_reg);
  fe::Expr *ResolveArray(fe::Expr *access_expr, vector<vm::Register *> *indexes);
  vm::Register *CompileAssignToElmRef(vm::Insn *insn, fe::Expr *lhs,
				      vm::Register *rhs_reg);
  vm::Register *CompileAssignToSym(vm::Insn *insn, fe::Expr *lhs,
				   vm::Register *rhs_reg);
  vm::Register *CompileMemberSym(fe::Expr *expr);
  vm::Register *CompileArrayRef(fe::Expr *expr);
  vm::Register *CompileAssignToLhs(vm::Insn *insn, fe::Expr *lhs,
				   vm::Register *rhs_reg);
  RegisterTuple CompileComma(fe::Expr *expr);
  RegisterTuple CompileElmRef(fe::Expr *expr);
  RegisterTuple CompileFuncallExpr(vm::Register *obj, fe::Expr *expr);
  RegisterTuple CompileMultiValueFuncall(vm::Register *obj_reg,
					 fe::Expr *funcall,
					 int num_lhs);
  vm::Register *CompileSimpleExpr(fe::Expr *expr);
  vm::Register *CompileTriTerm(fe::Expr *expr);
  void CompileIncDecNonLocal(fe::Expr *expr);

  vm::Value::ValueType GetVariableType(sym_t name);
  vm::OpCode GetOpCodeFromExpr(fe::Expr *expr);
  vm::Register *UpdateModifyOp(fe::NodeCode type, fe::Expr *lhs_expr,
			       vm::Register *rhs_reg);
  vm::Register *MayRewriteOperator(vm::Insn *orig_insn);
  vm::OpCode MayRewriteToOpWithType(vm::OpCode op);
  void PropagateRegisterType(vm::Insn *insn,
			     vm::Register *lhs, vm::Register *rhs,
			     vm::RegisterType *t);
  RegisterTuple EmitFuncallDone(vm::Insn *call_insn,
				vm::Method *method,
				int num_lhs);
  void MayEmitTypeDoneInsn(vm::Insn *insn);
  vm::Method *GetCalleeMethod(vm::Insn *call_insn);
  vm::Register *LoadNumericTypeRegister(sym_t obj_name);

  Compiler *compiler_;
};

}  // namespace compiler

#endif  // _compiler_expr_compiler_h_
