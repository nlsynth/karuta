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

  Expr *name_expr;
  sym_t type;
  const numeric::Width *width;
  Expr *initial_val;
  int array_length;
  ArrayInitializer *array_initializer;
};

class VarDeclSet {
public:
  void Dump(DumpStream &os);
  vector<VarDecl*> decls;
};

}  // namespace fe

#endif  // _fe_var_decl_h_
