// -*- C++ -*-
#ifndef _synth_object_method_h_
#define _synth_object_method_h_

#include "synth/common.h"

namespace synth {

class ObjectMethod {
public:
  ObjectMethod(MethodSynth *synth, vm::Insn *insn);

  void Synth();

private:
  IInsn *SynthAxiAccess(vm::Object *array_obj, bool is_store);
  IInsn *SynthMailboxWidth(vm::Object *mailbox_obj);

  MethodSynth *synth_;
  vm::Insn *insn_;
};

}  // namespace synth

#endif  // _synth_object_method_h_
