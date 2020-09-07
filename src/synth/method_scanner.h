// -*- C++ -*-
#ifndef _synth_method_scanner_h_
#define _synth_method_scanner_h_

#include "synth/insn_walker.h"

namespace synth {

class MethodScanner : public InsnWalker {
 public:
  MethodScanner(ThreadSynth *thr_synth, vm::Object *obj,
                const string &method_name);

  bool Scan();

 private:
  void ScanInsn(vm::Insn *insn);

  void Funcall(vm::Insn *insn);
  void MemberAccess(vm::Insn *insn);
  void ArrayAccess(vm::Insn *insn);
  void NativeFuncall(vm::Insn *insn);
  void RequestSubObj(vm::Object *callee_obj);

  ThreadSynth *thr_synth_;
  vm::Method *method_;
  const string &method_name_;
};

}  // namespace synth

#endif  // _synth_method_scanner_h_
