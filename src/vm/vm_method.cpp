#include "vm/method.h"

#include "base/dump_stream.h"
#include "base/stl_util.h"
#include "fe/method.h"
#include "fe/var_decl.h"
#include "karuta/annotation.h"
#include "vm/insn.h"

namespace vm {

Method::Method(bool is_toplevel)
    : is_toplevel_(is_toplevel),
      method_fn_(nullptr),
      parse_tree_(nullptr),
      alt_impl_(nullptr),
      compile_failed_(false) {}

Method::~Method() {
  STLDeleteValues(&insns_);
  STLDeleteValues(&method_regs_);
}

Method::method_func Method::GetMethodFunc() const { return method_fn_; }

void Method::SetMethodFunc(method_func func) { method_fn_ = func; }

const fe::Method *Method::GetParseTree() const { return parse_tree_; }

void Method::SetParseTree(const fe::Method *method) { parse_tree_ = method; }

int Method::GetNumArgRegisters() const {
  if (parse_tree_ != nullptr && parse_tree_->GetArgs() != nullptr) {
    return parse_tree_->GetArgs()->decls.size();
  }
  return 0;
}

int Method::GetNumReturnRegisters() const {
  // return_types_ is 0 before compilation, so use the parse tree instead.
  if (parse_tree_ != nullptr && parse_tree_->GetReturns() != nullptr) {
    return parse_tree_->GetReturns()->decls.size();
  }
  // Use the value for a non native method.
  return return_types_.size();
}

const iroha::NumericWidth &Method::GetNthArgWidth(int i) {
  return parse_tree_->GetArgs()->decls[i]->GetWidth();
}

const char *Method::AlternativeImplementation() { return alt_impl_; }

void Method::SetAlternativeImplementation(const char *alt) { alt_impl_ = alt; }

const string &Method::GetSynthName() const { return synth_name_; }

void Method::SetSynthName(const string &s) { synth_name_ = s; }

bool Method::IsTopLevel() const { return is_toplevel_; }

Annotation *Method::GetAnnotation() const {
  if (parse_tree_ != nullptr && parse_tree_->GetAnnotation() != nullptr) {
    return parse_tree_->GetAnnotation();
  }
  return Annotation::EmptyAnnotation();
}

void Method::Dump() const {
  DumpStream ds(cout);
  Dump(ds);
}

void Method::Dump(DumpStream &ds) const {
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

  int num_args = GetNumArgRegisters();
  int num_rets = GetNumReturnRegisters();
  for (size_t i = 0; i < method_regs_.size(); ++i) {
    Register *reg = method_regs_[i];
    ds.push_indent();
    ds.indent();
    ds.os << "r" << reg->id_;
    if (i < num_args) {
      ds.os << "a";
    } else if (i < num_args + num_rets) {
      ds.os << "r";
    }
    ds.os << ":";
    reg->Dump(ds);
    ds.os << "\n";
    ds.pop_indent();
  }
}

void Method::SetCompileFailure() { compile_failed_ = true; }

bool Method::IsCompileFailure() const { return compile_failed_; }

bool Method::IsThreadEntry() const {
  auto *an = GetAnnotation();
  if (an->IsThreadEntry()) {
    return true;
  }
  if (parse_tree_ != nullptr) {
    return parse_tree_->GetIsProcess();
  }
  return false;
}

}  // namespace vm
