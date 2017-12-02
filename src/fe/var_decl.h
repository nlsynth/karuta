// -*- C++ -*-
#ifndef _fe_var_decl_h_
#define _fe_var_decl_h_

#include "fe/common.h"
#include "numeric/numeric_type.h"  // from iroha

namespace fe {

class ArrayInitializer {
public:
  vector<uint64_t> num_;
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
  const iroha::NumericWidth &GetWidth() const;
  void SetWidth(const iroha::NumericWidth &width);
  sym_t GetObjectName() const;
  void SetObjectName(sym_t object_name);
  Expr *GetInitialVal() const;
  void SetInitialVal(Expr *initial_val);
  int GetArrayLength();
  void SetArrayLength(int array_length);
  ArrayInitializer *GetArrayInitializer() const;
  void SetArrayInitializer(ArrayInitializer *array);
  Annotation *GetAnnotation() const;
  void SetAnnotation(Annotation *an);

private:
  Expr *name_expr_;
  // int, bool, string, object and so on.
  sym_t type_;

  iroha::NumericWidth width_;
  // for numeric object.
  sym_t object_name_;
  Expr *initial_val_;
  int array_length_;
  ArrayInitializer *array_initializer_;
  Annotation *annotation_;
};

class VarDeclSet {
public:
  void Dump(DumpStream &os);
  vector<VarDecl*> decls;
};

}  // namespace fe

#endif  // _fe_var_decl_h_
