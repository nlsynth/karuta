// -*- C++ -*-
#ifndef _fe_stmt_h_
#define _fe_stmt_h_

#include "fe/common.h"
#include "fe/nodecode.h"
#include "numeric/numeric_type.h"  // from iroha

namespace fe {

class Stmt {
public:
  explicit Stmt(enum NodeCode type);

  void Dump();
  void Dump(DumpStream &os);

  void SetAnnotation(Annotation *an);
  Annotation *GetAnnotation();

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

private:
  Annotation *annotation_;
};

}  // namespace fe

#endif  // _fe_stmt_h_
