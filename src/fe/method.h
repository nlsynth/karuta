// -*- C++ -*-
#ifndef _fe_method_h_
#define _fe_method_h_

#include "fe/common.h"

namespace fe {

class Method {
public:
  Method();

  void Dump() const;
  void Dump(DumpStream &os) const;

  const vector<Stmt*> &GetStmts() const;
  vector<Stmt*> &GetMutableStmts();
  VarDeclSet *GetArgs() const;
  void SetArgs(VarDeclSet *args);
  VarDeclSet *GetReturns() const;
  void SetReturns(VarDeclSet *returns);
  Annotation *GetAnnotation() const;
  void SetAnnotation(Annotation *an);

private:
  vector<Stmt*> stmts_;
  VarDeclSet *args_;
  VarDeclSet *returns_;
  Annotation *annotation_;
};

}  // namespace fe

#endif  // _fe_method_h_
