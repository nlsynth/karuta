// -*- C++ -*-
#ifndef _fe_common_
#define _fe_common_

#include "nli.h"
#include "pool.h"

namespace fe {

class EnumDecl;
class Expr;
class Stmt;
class Method;
class VarDecl;
class VarDeclSet;

class NodePool {
public:
  static void Init();
  static void Release();

  static void AddEnumDecl(EnumDecl *decl);
  static void AddExpr(Expr *expr);
  static void AddStmt(Stmt *stmt);
  static void AddMethod(Method *method);
  static void AddVarDecl(VarDecl *decl);
  static void AddVarDeclSet(VarDeclSet *decl_set);

  static Pool<Expr> *exprs_;
  static Pool<EnumDecl> *enums_;
  static Pool<Method> *methods_;
  static Pool<Stmt> *stmts_;
  static Pool<VarDecl> *decls_;
  static Pool<VarDeclSet> *decl_sets_;
};

}  // namespace fe

using namespace fe;

#endif  // _fe_common_
