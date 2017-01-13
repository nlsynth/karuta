#include "vm/method.h"

#include "dump_stream.h"
#include "fe/method.h"
#include "fe/var_decl.h"
#include "vm/insn.h"

namespace vm {

Method::Method(bool is_toplevel) :
  is_toplevel_(is_toplevel), method_fn_(nullptr),
  alt_impl_(nullptr), parse_tree_(nullptr) {
}

Method::~Method() {
  STLDeleteValues(&insns_);
  STLDeleteValues(&method_regs_);
}

int Method::GetNumReturnRegisters() {
  if (parse_tree_ && parse_tree_->returns_) {
    // Non native && !toplevel.
    return parse_tree_->returns_->decls.size();
  }
  return return_types_.size();
}

const numeric::Width *Method::GetNthArgWidth(int i) {
  return parse_tree_->args_->decls[i]->width;
}

const char *Method::AlternativeImplementation() {
  return alt_impl_;
}

void Method::Dump() {
  DumpStream ds(cout);
  Dump(ds);
}

void Method::Dump(DumpStream &ds) {
  ds.os << "method insns\n";
  for (size_t i = 0; i < insns_.size(); ++i) {
    Insn *insn = insns_[i];
    ds.push_indent();
    ds.indent();
    ds.os << i << ":";
    insn->Dump(ds);
    ds.os << "\n";
    ds.pop_indent();
  }

  for (size_t i = 0; i < method_regs_.size(); ++i) {
    Register *reg = method_regs_[i];
    ds.push_indent();
    ds.indent();
    ds.os << "reg_" << reg->id_ << ":";
    reg->Dump(ds);
    ds.os << "\n";
    ds.pop_indent();
  }
}

}  // namespace vm
