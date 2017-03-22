// -*- C++ -*-
#ifndef _fe_var_decl_h_
#define _fe_var_decl_h_

#include "nli.h"

class DumpStream;

namespace numeric {
class Width;
}  // namespace numeric

namespace fe {

class Expr;

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

  Expr *name_expr_;
  // int, bool, string, object and so on.
  sym_t type_;

private:
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
