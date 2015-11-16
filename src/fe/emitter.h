// -*- C++ -*-
#ifndef _fe_emitter_h_
#define _fe_emitter_h_

#include "nli.h"

namespace numeric {
class Width;
}  // namespace numeric

namespace dfg {
class import_params;
}  // namespace dfg

namespace fe {

class Expr;
class Method;
class Stmt;
class VarDecl;
class VarDeclSet;

struct MethodDecl {
  Method *method_;
  Expr *name_;
};

class Emitter {
public:
  static void BeginFunction(Expr *name);
  static MethodDecl EndFunction();
  static void SetCurrentFunctionArgs(VarDeclSet *decls);
  static void SetCurrentFunctionReturns(VarDeclSet *decls);
  static void SetImportedResource(dfg::import_params *params);
  static void BeginBlock();
  static void EndBlock();
  static void EmitExprStmt(Expr *expr);
  static void EmitImportStmt(const char *str);
  static void EmitSpawnStmt(Expr *expr);
  static void EmitVarDeclStmtSet(VarDeclSet *vds);
  static Stmt *EmitIfStmt(Expr *cond);
  static Stmt *EmitForStmt(Expr *cond);
  static void EmitLabel(sym_t label);
  static void EmitGoto(sym_t label);
  static void EmitReturnStmt(Expr *expr);
  static void EmitThreadDeclStmt(Expr *var, Expr *funcall);
  static void EmitChannelDeclStmt(Expr *var, sym_t type_name,
				  const numeric::Width *width);

private:
  static vector<MethodDecl> method_stack_;
  static Stmt *BuildFuncDeclStmt(MethodDecl *decl);
  static MethodDecl &CurrentMethod();
  static void EmitStmt(Stmt *stmt);

  static Stmt *NewStmt(int type);
};

}  // namespace fe

using namespace fe;

#endif  // _fe_emitter_h_
