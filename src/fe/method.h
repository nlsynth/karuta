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

  vector<Stmt*> stmts_;
  VarDeclSet *args_;
  VarDeclSet *returns_;
  Annotation *imported_resource_;
};

}  // namespace fe

#endif  // _fe_method_h_
