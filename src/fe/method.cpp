#include "fe/method.h"

#include "base/dump_stream.h"
#include "fe/stmt.h"
#include "fe/var_decl.h"

namespace fe {

Method::Method() : args_(nullptr), returns_(nullptr), annotation_(nullptr) {
}

void Method::Dump() const {
  DumpStream ds(cout);
  Dump(ds);
}

void Method::Dump(DumpStream &ds) const {
  for (size_t i = 0; i < stmts_.size(); ++i) {
    stmts_[i]->Dump(ds);
  }
  if (args_) {
    ds.indent();
    ds.os << "args:\n";
    ds.push_indent();
    args_->Dump(ds);
    ds.pop_indent();
  }
  if (returns_) {
    ds.indent();
    ds.os << "returns:\n";
    ds.push_indent();
    returns_->Dump(ds);
    ds.pop_indent();
  }
}

}  // namespace fe
