// -*- C++ -*-
#ifndef _fe_common_
#define _fe_common_

#include "nli.h"
#include "base/pool.h"

class Annotation;
class DumpStream;
class ResourceParamValueSet;

namespace numeric {
class Width;
}  // namespace numeric

namespace vm {
class Method;
class VM;
}  // namespace vm

namespace fe {

class ArrayInitializer;
class EnumDecl;
class Expr;
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
