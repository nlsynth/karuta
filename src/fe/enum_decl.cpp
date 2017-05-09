#include "fe/enum_decl.h"

#include "base/dump_stream.h"

namespace fe {

void EnumDecl::Dump() {
  DumpStream ds(cout);
  Dump(ds);
}

void EnumDecl::Dump(DumpStream &ds) {
  ds.indent();
  ds.os << "enum\n";
  ds.push_indent();
  for (sym_t item : items) {
    ds.indent();
    ds.os << "item: " << sym_cstr(item) << "\n";
  }
  ds.pop_indent();
}
  
}  // namespace fe
