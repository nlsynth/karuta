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
  IInsn *SynthAxiAccess(bool is_store);

  MethodSynth *synth_;
  vm::Insn *insn_;
};

}  // namespace synth

#endif  // _synth_object_method_h_
