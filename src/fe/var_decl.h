// -*- C++ -*-
#ifndef _fe_var_decl_h_
#define _fe_var_decl_h_

#include "fe/common.h"
#include "iroha/numeric.h"

namespace fe {

class ArrayInitializer {
public:
  vector<uint64_t> num_;
  void Dump(DumpStream &ds) const;
};

class ArrayShape {
public:
  explicit ArrayShape(int l);

  // 1 dimension for now.
  vector<int> length;
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
  void SetIsShared(bool is_shared);
  bool GetIsShared() const;
  void SetIsIO(bool is_io, bool is_output);
  bool GetIsIO() const;
  bool GetIsOutput() const;
  Expr *GetInitialVal() const;
  void SetInitialVal(Expr *initial_val);
  ArrayInitializer *GetArrayInitializer() const;
  void SetArrayInitializer(ArrayInitializer *array);
  ArrayShape *GetArrayShape() const;
  void SetArrayShape(ArrayShape *shape);
  Annotation *GetAnnotation() const;
  void SetAnnotation(Annotation *an);

private:
  Expr *name_expr_;
  // int, bool, string, object and so on.
  sym_t type_;

  iroha::NumericWidth width_;
  // for numeric object.
  sym_t object_name_;
  bool is_shared_;
  bool is_io_;
  bool is_output_;
  Expr *initial_val_;
  std::unique_ptr<ArrayInitializer> array_initializer_;
  std::unique_ptr<ArrayShape> array_shape_;
  Annotation *annotation_;
};

class VarDeclSet {
public:
  void Dump(DumpStream &os);
  vector<VarDecl*> decls;
};

}  // namespace fe

#endif  // _fe_var_decl_h_
