// -*- C++ -*-
#ifndef _synth_object_method_h_
#define _synth_object_method_h_

#include "synth/common.h"

namespace synth {

class ObjectMethod {
public:
  ObjectMethod(MethodSynth *synth, InsnWalker *walker, vm::Insn *insn);

  void Synth();
  void Scan();

private:
  string GetSynthName(vm::Object *obj);
  IInsn *SynthAxiAccess(vm::Object *array_obj, bool is_store);
  IInsn *SynthMailboxWidth(vm::Object *mailbox_obj);
  IInsn *SynthMailboxAccess(vm::Object *mailbox_obj, bool is_put);

  MethodSynth *synth_;
  InsnWalker *walker_;
  vm::Insn *insn_;
};

}  // namespace synth

#endif  // _synth_object_method_h_
