// -*- C++ -*-
#ifndef _vm_method_h_
#define _vm_method_h_

#include "vm/common.h"
#include "vm/register.h"  // for RegisterType

namespace vm {

// This can be either native implementation or in Karuta language.
class Method {
 public:
  Method(bool is_toplevel);
  ~Method();

  typedef void (*method_func)(Thread *thr, Object *obj,
                              const vector<Value> &args);

  void Dump() const;
  void Dump(DumpStream &os) const;

  method_func GetMethodFunc() const;
  void SetMethodFunc(method_func func);
  const fe::Method *GetParseTree() const;
  void SetParseTree(const fe::Method *method);
  int GetNumArgRegisters() const;
  int GetNumReturnRegisters() const;
  const iroha::NumericWidth &GetNthArgWidth(int i);
  const char *AlternativeImplementation();
  void SetAlternativeImplementation(const char *alt);
  const string &GetSynthName() const;
  void SetSynthName(const string &s);
  bool IsTopLevel() const;
  Annotation *GetAnnotation() const;
  void SetCompileFailure();
  bool IsCompileFailure() const;
  bool IsThreadEntry() const;

  vector<Insn *> insns_;
  // Args. Returns. Locals.
  vector<Register *> method_regs_;
  vector<RegisterType> return_types_;

 private:
  bool is_toplevel_;
  // native
  method_func method_fn_;
  // non native
  const fe::Method *parse_tree_;
  const char *alt_impl_;
  string synth_name_;
  bool compile_failed_;
};

}  // namespace vm

#endif  // _vm_method_h_
