// -*- C++ -*-
#ifndef _fe_expr_h_
#define _fe_expr_h_

#include "fe/common.h"
#include "fe/nodecode.h"
#include "fe/scanner_pos.h"
#include "iroha/numeric.h"

namespace fe {

class Expr {
public:
  explicit Expr(NodeCode type);

  void Dump();
  void Dump(DumpStream &os);

  enum NodeCode GetType() const;

  ScannerPos &GetPos();

  const iroha::Numeric &GetNum() const;
  void SetNum(const iroha::Numeric &num);
  sym_t GetSym() const;
  void SetSym(sym_t sym);
  const string &GetString();
  void SetString(const string &str);

  Expr *GetFunc() const;
  void SetFunc(Expr *func);
  Expr *GetArgs() const;
  void SetArgs(Expr *args);
  Expr *GetLhs() const;
  void SetLhs(Expr *lhs);
  Expr *GetRhs() const;
  void SetRhs(Expr *rhs);

private:
  NodeCode type_;
  ScannerPos pos_;

  iroha::Numeric num_;
  sym_t sym_;
  string str_;

  Expr *func_;
  Expr *args_;
  Expr *lhs_;
  Expr *rhs_;
};

// mainly for multiple var decls (e.g. var x, y int).
class ExprSet {
public:
  void Dump(DumpStream &os);
  vector<Expr*> exprs;
};

}  // namespace fe

#endif  // _fe_expr_h_
