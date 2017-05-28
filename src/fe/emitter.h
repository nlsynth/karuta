// -*- C++ -*-
#ifndef _fe_emitter_h_
#define _fe_emitter_h_

#include "fe/common.h"

namespace fe {

class EnumDecl;
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
  static void SetCurrentFunctionParams();
  static void SetCurrentFunctionArgs(VarDeclSet *decls);
  static void SetCurrentFunctionReturns(VarDeclSet *decls);
  static Annotation *SetAnnotation(sym_t key, AnnotationValueSet *values);
  static void SetCurrentFunctionAnnotation(Annotation *an);
  static void BeginBlock();
  static void EndBlock();
  static void EmitNop();
  static void EmitExprStmt(Expr *expr);
  static void EmitImportStmt(const char *str);
  static void EmitSpawnStmt(Expr *expr);
  static void EmitVarDeclStmtSet(VarDeclSet *vds);
  static void EmitEnumTypeDeclStmt(Expr *name, EnumDecl *decl);
  static Stmt *EmitIfStmt(Expr *cond);
  static Stmt *EmitForStmt(Expr *cond);
  static Stmt *EmitWhileStmt(Expr *cond);
  static void EmitDoWhileStmt(Stmt *stmt, Expr *cond);
  static void EmitLabel(sym_t label);
  static void EmitGoto(sym_t label);
  static void EmitReturnStmt(Expr *expr);
  static void EmitThreadDeclStmt(Expr *var, Expr *funcall);
  static void EmitChannelDeclStmt(Expr *var, sym_t type_name,
				  const iroha::NumericWidth *width,
				  sym_t object_name);
  static void EmitMailboxDeclStmt(Expr *var, sym_t type_name,
				  const iroha::NumericWidth *width,
				  sym_t object_name);

private:
  static vector<MethodDecl> method_stack_;
  // For var decl.
  static Annotation *annotation_;
  // For func decl (may have var decls inside).
  static Annotation *func_annotation_;

  static Stmt *BuildFuncDeclStmt(MethodDecl *decl);
  static MethodDecl &CurrentMethod();
  static void EmitStmt(Stmt *stmt);

  static Stmt *NewStmt(int type);
};

}  // namespace fe

using namespace fe;

#endif  // _fe_emitter_h_
