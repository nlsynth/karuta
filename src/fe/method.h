// -*- C++ -*-
#ifndef _fe_method_h_
#define _fe_method_h_

#include "fe/common.h"

namespace fe {

class Method {
public:
  Method(const string &name);

  void Dump() const;
  void Dump(DumpStream &os) const;
  const string &GetName() const;

  const vector<Stmt*> &GetStmts() const;
  vector<Stmt*> &GetMutableStmts();
  VarDeclSet *GetArgs() const;
  void SetArgs(VarDeclSet *args);
  VarDeclSet *GetReturns() const;
  void SetReturns(VarDeclSet *returns);
  Annotation *GetAnnotation() const;
  void SetAnnotation(Annotation *an);
  bool GetIsProcess() const;
  void SetIsProcess(bool is_process);

private:
  const string name_;
  vector<Stmt*> stmts_;
  VarDeclSet *args_;
  VarDeclSet *returns_;
  Annotation *annotation_;
  bool is_process_;
};

}  // namespace fe

#endif  // _fe_method_h_
