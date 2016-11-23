// -*- C++ -*-
#ifndef _fe_method_h_
#define _fe_method_h_

#include "nli.h"

namespace synth {
class ResourceParams;
}  // namespace synth
class DumpStream;

namespace fe {

class Stmt;
class VarDeclSet;

class Method {
public:
  Method();
  void Dump() const;
  void Dump(DumpStream &os) const;

  vector<Stmt*> stmts_;
  VarDeclSet *args_;
  VarDeclSet *returns_;
  synth::ResourceParams *imported_resource_;
};

}  // namespace fe

#endif  // _fe_method_h_
