// -*- C++ -*-
#ifndef _synth_object_method_h_
#define _synth_object_method_h_

#include "synth/common.h"

namespace synth {

class ObjectMethod {
public:
  ObjectMethod(MethodSynth *synth, InsnWalker *walker, ResourceSynth *rsynth,
	       vm::Insn *insn);

  void Synth();
  void Scan();

private:
  string GetSynthName(vm::Object *obj);
  IInsn *SynthAxiAccess(vm::Object *array_obj, bool is_store);
  IInsn *SynthAxiWait(vm::Object *array_obj);
  IInsn *SynthMailboxWidth(vm::Object *mailbox_obj);
  IInsn *SynthMailboxAccess(vm::Object *mailbox_obj,
			    bool is_blocking, bool is_put);
  IInsn *SynthMemoryAccess(vm::Object *mem, bool is_write);
  IInsn *SynthChannelAccess(vm::Object *ch_obj, bool is_write);
  IInsn *SynthGetTickCount(vm::Object *obj);

  MethodSynth *synth_;
  InsnWalker *walker_;
  ResourceSynth *rsynth_;
  vm::Insn *insn_;
};

}  // namespace synth

#endif  // _synth_object_method_h_
