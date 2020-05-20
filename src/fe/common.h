// -*- C++ -*-
#ifndef _fe_common_
#define _fe_common_

#include "base/pool.h"
#include "karuta/karuta.h"

class Annotation;
class AnnotationKeyValueSet;
class DumpStream;

extern void yyerror(const char *msg);

namespace iroha {
class NumericWidth;
}  // namespace iroha

namespace vm {
class Method;
class Object;
class VM;
}  // namespace vm

namespace fe {

class ArrayInitializer;
class ArrayShape;
class EnumDecl;
class Expr;
class ExprSet;
class FileImage;
class Method;
class ScannerInfo;
class Stmt;
class VarDecl;
class VarDeclSet;

class NodePool {
public:
  static void Init();
  static void Release();

  static void AddEnumDecl(EnumDecl *decl);
  static void AddExpr(Expr *expr);
  static void AddExprSet(ExprSet *expr_set);
  static void AddStmt(Stmt *stmt);
  static void AddMethod(Method *method);
  static void AddVarDecl(VarDecl *decl);
  static void AddVarDeclSet(VarDeclSet *decl_set);

  static Pool<Expr> *exprs_;
  static Pool<ExprSet> *expr_sets_;
  static Pool<EnumDecl> *enums_;
  static Pool<Method> *methods_;
  static Pool<Stmt> *stmts_;
  static Pool<VarDecl> *decls_;
  static Pool<VarDeclSet> *decl_sets_;
};

}  // namespace fe

using namespace fe;

#endif  // _fe_common_
