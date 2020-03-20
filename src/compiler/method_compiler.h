// -*- C++ -*-
#ifndef _compiler_method_compiler_h_
#define _compiler_method_compiler_h_

#include "compiler/common.h"

#include "vm/opcode.h"

#include <map>

using std::map;

namespace compiler {

class VarScope;

class VarScope {
public:
  VarScope();
  // local name -> Register.
  std::map<sym_t, vm::Register*> local_regs_;
  fe::Expr *obj_expr_;
  fe::VarDecl *loop_var_;
};

class MethodCompiler {
public:
  MethodCompiler(const CompileOptions &opts, vm::VM *vm, vm::Object *obj,
		 vm::Method *method);
  ~MethodCompiler();

  void Compile();

  static void SetByteCodeDebug(string flags);

  // public: for ExprCompiler
  vm::Object *GetObj() const;
  vm::Register *EmitLoadObj(sym_t label);
  void EmitInsn(vm::Insn *insn);
  vm::Register *AllocRegister();
  vm::Register *LookupLocalVar(sym_t name);
  bool IsTopLevel() const;
  void AddLabel(sym_t label);
  void SimpleAssign(vm::Register *src, vm::Register *dst);
  vm::Register *CompilePathHead(fe::Expr *path_expr);
  vm::Register *EmitMemberLoad(vm::Register *obj_reg, sym_t m);
  void AddPrePostIncDecExpr(fe::Expr *expr, bool is_post);
  vm::Object *GetVMObject(vm::Register *obj_reg);
  void RegisterVMObject(vm::Register *reg, vm::Object *obj);
  void SetDelayInsnEmit(bool delay);

private:
  void CompileStmt(fe::Stmt *stmt);
  void CompileFuncDecl(fe::Stmt *stmt);
  void CompileImportStmt(fe::Stmt *stmt);
  void CompileIfStmt(fe::Stmt *stmt);
  void CompileLabel(fe::Stmt *stmt);
  void CompileGoto(fe::Stmt *stmt);
  void CompileReturn(fe::Stmt *stmt);
  void CompileVarDeclStmt(fe::Stmt *stmt);
  void CompileThreadDecl(fe::Stmt *stmt);
  void CompileChannelDecl(fe::Stmt *stmt);
  void CompileMailboxDecl(fe::Stmt *stmt);
  // var, thread, channel.
  void CompileMemberDeclStmt(fe::Stmt *stmt, fe::Expr *var_expr, vm::OpCode op,
			     vm::Register *initial_val);
  vm::Register *CompileSymExpr(fe::Expr *expr);
  void PushScope(fe::Stmt *stmt);
  void PopScope();
  void MaySetUnrollAnnotation(fe::Stmt *stmt, VarScope *scope);
  void EmitNop();
  void EmitYield();
  void ResolveLabels();
  VarScope *CurrentScope();
  void CompilePreIncDec();
  void CompilePostIncDec();
  void DoCompilePrePostIncDec(bool is_post, vector<fe::Expr*> *exprs);
  void FlushPendingInsns();
  void SetupArgumentRegisters();
  void SetupReturnRegisters();
  void SetupDeclSetRegisters(fe::VarDeclSet &vds,
			     vector<vm::RegisterType> *types);
  vm::Register *GetNthReturnRegister(int nth);
  vm::Register *TraverseMemberPath(fe::Expr *e);
  int InsnIndexFromLabel(sym_t label);
  void SetWidthByDecl(fe::VarDecl *decl, vm::Register *reg);
  void MayEmitEpilogueCode();
  vm::Register *LookupOrAllocateLocalVar(sym_t name);

  static string dbg_bytecode_;

  const CompileOptions &opts_;
  vm::VM *vm_;
  vm::Object *obj_;
  vm::Method *method_;
  const fe::Method *tree_;
  vector<vm::Insn*> pending_insns_;
  vector<VarScope*> bindings_;
  vm::Insn *last_queued_insn_;
  bool delay_insn_emit_;
  map<sym_t, vm::Insn *> label_insn_map_;
  vector<fe::Expr*> pre_inc_dec_exprs_;
  vector<fe::Expr*> post_inc_dec_exprs_;
  map<vm::Register *, vm::Object *> reg_obj_map_;

  std::unique_ptr<ExprCompiler> exc_;
  std::unique_ptr<LoopMarker> loop_marker_;
};

}  // namespace compiler

#endif  // _compiler_method_compiler_h_
