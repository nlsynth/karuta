#include "vm/method.h"

#include "base/dump_stream.h"
#include "fe/method.h"
#include "fe/var_decl.h"
#include "vm/insn.h"

namespace vm {

Method::Method(bool is_toplevel) :
  method_fn_(nullptr), alt_impl_(nullptr),
  parse_tree_(nullptr), is_toplevel_(is_toplevel) {
}

Method::~Method() {
  STLDeleteValues(&insns_);
  STLDeleteValues(&method_regs_);
}

int Method::GetNumArgRegisters() const {
  if (parse_tree_ != nullptr &&
      parse_tree_->args_) {
    return parse_tree_->args_->decls.size();
  }
  return 0;
}

int Method::GetNumReturnRegisters() const {
  return return_types_.size();
}

const numeric::Width *Method::GetNthArgWidth(int i) {
  return parse_tree_->args_->decls[i]->GetWidth();
}

const char *Method::AlternativeImplementation() {
  return alt_impl_;
}

const string &Method::GetSynthName() const {
  return synth_name_;
}

void Method::SetSynthName(const string &s) {
  synth_name_ = s;
}

bool Method::IsTopLevel() const {
  return is_toplevel_;
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
