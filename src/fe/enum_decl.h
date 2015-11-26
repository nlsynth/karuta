// -*- C++ -*-
#ifndef _fe_enum_decl_h_
#define _fe_enum_decl_h_

#include "nli.h"

class DumpStream;

namespace fe {

class EnumDecl {
public:
  void Dump();
  void Dump(DumpStream &os);

  vector<sym_t> items;
};

}  // namespace fe

#endif  // _fe_enum_decl_h_
