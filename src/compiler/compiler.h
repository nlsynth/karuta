// -*- C++ -*-
#ifndef _compiler_compiler_h_
#define _compiler_compiler_h_

#include "nli.h"

#include "fe/nodecode.h"
#include "vm/opcode.h"
#include "vm/value.h"

#include <map>

using std::map;

namespace fe {
class Expr;
class Method;
class Stmt;
class VarDeclSet;
}  // namespace fe

namespace vm {
class Insn;
class Method;
class Object;
class Register;
class RegisterType;
class VM;
class Value;
}  // namespace vm

namespace compiler {

class VarScope;

class Compiler {
public:
  Compiler(vm::VM *vm, vm::Object *obj, const fe::Method *parse_tree);

  static vm::Method *CompileMethod(vm::VM *vm, vm::Object *obj,
				   const fe::Method *parse_tree,
				   vm::Method *method);

  static void SetByteCodeDebug(bool enable);

private:
  // stub can be NULL.
  vm::Method *Compile(vm::Method *stub);
  void CompileStmt(fe::Stmt *stmt);
  vm::Register *CompileExpr(fe::Expr *expr);
  vm::Register *CompileRefLhsExpr(fe::Expr *lhs_expr, vm::Insn *insn);
  vm::OpCode GetOpCodeFromExpr(fe::Expr *expr);
  vm::Register *CompileAssign(fe::Expr *expr);
  vm::Register *CompileAssignToArray(vm::Insn *insn, fe::Expr *lhs,
				     vm::Register *rhs_reg);
  vm::Register *CompileAssignToElmRef(vm::Insn *insn, fe::Expr *lhs,
				      vm::Register *rhs_reg);
  vm::Register *CompileAssignToSym(vm::Insn *insn, fe::Expr *lhs,
				      vm::Register *rhs_reg);
  vm::Register *CompileAssignToUniopRef(vm::Insn *insn, fe::Expr *lhs,
					vm::Register *rhs_reg);
  vm::Register *CompileArrayRef(fe::Expr *expr);
  vm::Register *CompileComma(fe::Expr *expr);
  vm::Register *CompileElmRef(fe::Expr *expr);
  vm::Register *CompileTriTerm(fe::Expr *expr);
  vm::Register *CompileRef(fe::Expr *expr);
  vm::Register *CompileFuncallExpr(fe::Expr *expr);
  vm::Register *CompileMultiValueFuncall(fe::Expr *funcall,
					 fe::Expr *lhs);
  void CompileFuncDecl(fe::Stmt *stmt);
  void CompileImportStmt(fe::Stmt *stmt);
  void CompileSpawnStmt(fe::Stmt *stmt);
  void CompileIfStmt(fe::Stmt *stmt);
  void CompileLabel(fe::Stmt *stmt);
  void CompileGoto(fe::Stmt *stmt);
  void CompileReturn(fe::Stmt *stmt);
  void CompileVarDeclStmt(fe::Stmt *stmt);
  void CompileThreadDecl(fe::Stmt *stmt);
  void CompileChannelDecl(fe::Stmt *stmt);
  // var, thread, channel.
  void CompileMemberDeclStmt(fe::Stmt *stmt, fe::Expr *var_expr, vm::OpCode op,
			     vm::Register *initial_val);
  vm::Register *CompileSymExpr(fe::Expr *expr);
  vm::Register *LookupLocalVar(sym_t name);
  vm::Register *AllocRegister();
  vm::Register *CompileMemberSym(fe::Expr *expr);
  void PushScope();
  void PopScope();
  void AddLabel(sym_t label);
  void EmitNop();
  void ResolveLabels();
  VarScope *CurrentScope();
  void EmitInsn(vm::Insn *insn);
  void EmitInsnNow(vm::Insn *insn);
  void CompilePreIncDec();
  void CompilePostIncDec();
  void DoCompilePrePostIncDec(bool is_post, vector<fe::Expr*> *exprs);
  void CompileIncDecExpr(fe::Expr *expr);
  void FlushPendingInsns();
  void SetupArgumentRegisters();
  void SetupReturnRegisters();
  void SetupDeclSetRegisters(fe::VarDeclSet &vds,
			     vector<vm::RegisterType> *types);
  void SimpleAssign(vm::Register *src, vm::Register *dst);
  vm::Register *GetNthReturnRegister(int nth);
  vm::Register *CompilePathHead(fe::Expr *path_expr);
  vm::Register *TraverseMemberPath(fe::Expr *e);
  vm::Register *UpdateModifyOp(fe::NodeCode type, fe::Expr *lhs_expr,
			       vm::Register *rhs_reg);
  int InsnIndexFromLabel(sym_t label);
  vm::Register *EmitLoadObj(sym_t label);
  vm::Register *EmitLoadPathObj(fe::Expr *path_expr);
  vm::Register *EmitMemberLoad(vm::Register *obj_reg, sym_t m);
  bool IsTopLevel() const;
  vm::Value::ValueType GetVariableType(sym_t name);

  static bool dbg_bytecode_;

  vm::VM *vm_;
  vm::Object *obj_;
  const fe::Method *tree_;
  vm::Method *method_;
  vector<vm::Insn*> pending_insns_;
  vector<fe::Expr*> pre_inc_dec_exprs_;
  vector<fe::Expr*> post_inc_dec_exprs_;
  vector<VarScope*> bindings_;
  vm::Insn *last_queued_insn_;
  map<sym_t, vm::Insn *> label_insn_map_;
};

}  // namespace compiler

#endif  // _compiler_compiler_h_
