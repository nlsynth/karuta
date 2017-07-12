// -*- C++ -*-
#ifndef _fe_builder_h_
#define _fe_builder_h_

#include "fe/common.h"
#include "fe/nodecode.h"

namespace fe {

struct WidthSpec {
  // Each member should be a pointer (or other primitive type), because this
  // struct is a part of YYSTYPE union.
  const iroha::NumericWidth *width;
  sym_t name;
  // name is primitive type name (either int, bool, object or string).
  bool is_primitive;
  bool is_ptr;

  static WidthSpec Int(bool is_signed, int width, bool is_ptr);
  static WidthSpec Name(sym_t name, bool is_primitive, bool is_ptr);

  // Code to convert to/from pointer form of NumericWidth.
  static const iroha::NumericWidth *MakeIntPtr(bool is_signed, int int_part);
  static const iroha::NumericWidth *ToPtr(const iroha::NumericWidth &w);
  static const iroha::NumericWidth GetWidth(sym_t name,
					    const iroha::NumericWidth *w);
};

class Builder {
 public:
  static Expr *StrExpr(const string &str);
  static Expr *SymExpr(sym_t num);
  static Expr *NumExpr(uint64_t num);
  static Expr *BinopExpr(Expr *lhs, Expr *rhs, int op);
  static Expr *FuncallExpr(Expr *func, Expr *args);
  static Expr *IncDecExpr(Expr *expr, int op, bool is_post);
  static Expr *SignedExpr(int sign, Expr *arg);
  static Expr *TriTerm(Expr *cond, Expr *lhs, Expr *rhs);
  static Expr *ElmSymRefExpr(Expr *expr, sym_t sym);
  static Expr *LogicInvertExpr(Expr *expr);
  static Expr *BitInvertExpr(Expr *expr);
  static ExprSet *ExprList(ExprSet *exprs, Expr *expr);
  static EnumDecl *EnumItemList(EnumDecl *decls, sym_t item);
  static VarDeclSet *VarDeclList(VarDeclSet *decls, VarDecl *decl);
  static VarDeclSet *ArgDeclList(VarDeclSet *decls, VarDecl *decl);
  static VarDeclSet *ReturnDeclList(VarDeclSet *decls, VarDecl *decl);
  static VarDecl *ReturnType(bool is_primitive, sym_t type_name, const iroha::NumericWidth *w);
  static void SetArrayLength(VarDecl *decl, int length);
  static Expr *ArrayRefExpr(Expr *array, Expr *index);
  static Expr *BitRangeRefExpr(Expr *val, Expr *msb, Expr *lsb);
  static Expr *RefExpr(Expr *addr);
  static void SetArrayInitializer(VarDecl *decl, ArrayInitializer *initializer);

  static VarDecl *MaybePtrVar(Expr *var, bool is_ptr);
  static VarDecl *BuildVarDecl(bool is_primitive, sym_t type,
			       const iroha::NumericWidth *w,
			       VarDecl *var);
  static void SetVarDeclAnnotation(VarDecl *decl, Annotation *an);
  static Stmt *DoWhileStmt();

  static Stmt *NewStmt(int type);
  static Expr *NewExpr(NodeCode type);
};

}  // namespace fe

#endif  // _fe_builder_h_
