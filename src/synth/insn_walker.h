// -*- C++ -*-
#ifndef _synth_insn_walker_h_
#define _synth_insn_walker_h_

#include "synth/common.h"

#include <map>

using std::map;

namespace synth {

// Base class to walk insns in a method.
// This can be used to share code by both synthesizing phase and
// preprocesses.
class InsnWalker {
protected:
  InsnWalker(ThreadSynth *thr_synth);
  void LoadObj(vm::Insn *insn);
  void MaybeLoadMemberObject(vm::Insn *insn);
  bool IsNativeFuncall(vm::Insn *insn);
  bool IsSubObjCall(vm::Insn *insn);
  vm::Object *GetCalleeObject(vm::Insn *insn);

  vm::VM *vm_;
  vm::Object *obj_;
  map<vm::Register *, vm::Object *> member_reg_to_obj_map_;
};

}  // namespace synth

#endif  // _synth_insn_walker_h_
