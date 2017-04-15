// -*- C++ -*-
#ifndef _fe_var_decl_h_
#define _fe_var_decl_h_

#include "fe/common.h"

namespace fe {

class ArrayInitializer {
public:
  vector<int> num_;
  void Dump(DumpStream &ds) const;
};

class VarDecl {
public:
  VarDecl();
  void Dump();
  void Dump(DumpStream &os);

  Expr *GetNameExpr() const;
  void SetNameExpr(Expr *name);
  sym_t GetType() const;
  void SetType(sym_t type);
  const numeric::Width *GetWidth() const;
  void SetWidth(const numeric::Width *width);
  sym_t GetObjectName() const;
  void SetObjectName(sym_t object_name);
  Expr *GetInitialVal() const;
  void SetInitialVal(Expr *initial_val);
  int GetArrayLength();
  void SetArrayLength(int array_length);
  ArrayInitializer *GetArrayInitializer() const;
  void SetArrayInitializer(ArrayInitializer *array);

private:
  Expr *name_expr_;
  // int, bool, string, object and so on.
  sym_t type_;

  const numeric::Width *width_;
  // for numeric object.
  sym_t object_name_;
  Expr *initial_val_;
  int array_length_;
  ArrayInitializer *array_initializer_;
};

class VarDeclSet {
public:
  void Dump(DumpStream &os);
  vector<VarDecl*> decls;
};

}  // namespace fe

#endif  // _fe_var_decl_h_
