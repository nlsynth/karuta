#include "fe/var_decl.h"

#include "dump_stream.h"
#include "fe/expr.h"

namespace fe {

VarDecl::VarDecl() : name_expr(NULL), type(NULL), width(NULL),
		     initial_val(NULL), array_length(-1),
		     array_initializer(NULL) {
}

void VarDecl::Dump() {
  DumpStream ds(cout);
  Dump(ds);
}

void VarDecl::Dump(DumpStream &ds) {
  if (type) {
    ds.indent();
    ds.os << "type: " << sym_cstr(type) << " ";
  }
  if (name_expr) {
    ds.os << "\n";
    ds.indent();
    ds.os << "name:\n";
    ds.push_indent();
    name_expr->Dump(ds);
    ds.pop_indent();
  } else {
    ds.indent();
    ds.os << "{null}\n";
  }
  if (width) {
    ds.indent();
    NumberWidth::Dump(width, ds.os);
    ds.os << "\n";
  }
  if (array_length >= 0) {
    ds.indent();
    ds.os << "[" << array_length << "]\n";
  }
  if (array_initializer) {
    array_initializer->Dump(ds);
  }
  if (initial_val) {
    ds.indent();
    ds.os << "initial:\n";
    ds.push_indent();
    initial_val->Dump(ds);
    ds.pop_indent();
  }
}

void VarDeclSet::Dump(DumpStream &ds) {
  for (size_t i = 0; i < decls.size(); ++i) {
    decls[i]->Dump(ds);
  }
}

void ArrayInitializer::Dump(DumpStream &ds) const {
  ds.indent();
  ds.os << "[";
  for (size_t i = 0; i < num_.size(); ++i) {
    if (i > 0) {
      ds.os << ",";
    }
    ds.os << num_[i];
  }
  ds.os << "]\n";
}

}  // namespace fe
