// -*- C++ -*-
#ifndef _fe_stmt_h_
#define _fe_stmt_h_

#include "fe/common.h"
#include "fe/nodecode.h"
#include "fe/scanner_pos.h"
#include "iroha/numeric.h"

namespace fe {

class Stmt {
public:
  explicit Stmt(enum NodeCode type);

  void Dump();
  void Dump(DumpStream &os);

  enum NodeCode GetType() const;

  ScannerPos &GetPos();

  Expr *GetExpr() const;
  void SetExpr(Expr *expr);
  sym_t GetSym() const;
  void SetSym(sym_t sym);
  Method *GetMethodDef() const;
  void SetMethodDef(Method *method_def);
  const string &GetString();
  void SetString(const string &str);
  VarDecl *GetVarDecl();
  void SetVarDecl(VarDecl *decl);
  EnumDecl *GetEnumDecl();
  void SetEnumDecl(EnumDecl *decl);
  iroha::NumericWidth &GetWidth();
  void SetWidth(iroha::NumericWidth &width);

  Annotation *GetAnnotation();
  void SetAnnotation(Annotation *an);

  sym_t GetLabel(bool is_join, bool is_t);
  void SetLabel(bool is_join, bool is_t, sym_t label);

private:
  enum NodeCode type_;
  ScannerPos pos_;

  Expr *expr_;
  sym_t sym_;
  Method *method_def_;
  string str_;
  VarDecl *decl_;
  EnumDecl *enum_;
  Annotation *annotation_;
  iroha::NumericWidth width_;

  // IF stmt.
  sym_t label_t_;
  sym_t label_f_;
  sym_t label_join_;
};

}  // namespace fe

#endif  // _fe_stmt_h_
