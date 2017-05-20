// -*- C++ -*-
#ifndef _fe_stmt_h_
#define _fe_stmt_h_

#include "fe/common.h"
#include "fe/nodecode.h"
#include "numeric/numeric.h"

namespace fe {

class Stmt {
public:
  void Dump();
  void Dump(DumpStream &os);

  enum NodeCode type_;
  Expr *expr_;
  Method *method_def_;
  sym_t sym_;
  string str_;
  VarDecl *decl_;
  EnumDecl *enum_;
  iroha::NumericWidth width_;

  // IF stmt.
  sym_t label_t_;
  sym_t label_f_;
  sym_t label_join_;
};

}  // namespace fe

#endif  // _fe_stmt_h_
