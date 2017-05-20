// -*- C++ -*-
#ifndef _fe_expr_h_
#define _fe_expr_h_

#include "fe/common.h"

#include "fe/nodecode.h"
#include "numeric/numeric.h"

namespace fe {

class Expr {
public:
  void Dump();
  void Dump(DumpStream &os);

  NodeCode type_;
  iroha::Numeric num_;
  sym_t sym_;
  string str_;

  Expr *func_;
  Expr *args_;
  Expr *lhs_;
  Expr *rhs_;
};

}  // namespace fe

#endif  // _fe_expr_h_
