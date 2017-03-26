// -*- C++ -*-
#ifndef _synth_method_context_h_
#define _synth_method_context_h_

#include "synth/common.h"

namespace synth {

class StateWrapper {
public:
  StateWrapper();

  IState *state_;
  MethodContext *callee_method_;
  string callee_func_name_;
  vm::Insn *vm_insn_;
  // for sub obj task call.
  string obj_name_;
  vm::Object *callee_vm_obj_;
};

class MethodContext {
public:
  MethodContext(MethodSynth *synth);
  ~MethodContext();

  // Pseudo insn to represent the entory of this method.
  // This insn holds args/rets information.
  IInsn *method_insn_;
  vector<StateWrapper *> states_;

  StateWrapper *LastState();

private:
  MethodSynth *synth_;
};

}  // namespace synth

#endif  // _synth_method_context_h_
