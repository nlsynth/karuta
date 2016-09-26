// -*- C++ -*-
#ifndef _isynth_method_context_h_
#define _isynth_method_context_h_

#include "isynth/common.h"

namespace isynth {

class StateWrapper {
public:
  StateWrapper();

  IState *state_;
  MethodContext *callee_method_;
  string func_name_;
  vm::Insn *vm_insn_;
  // for sub obj task call.
  string obj_name_;
  vm::Object *callee_vm_obj_;
};

class MethodContext {
public:
  MethodContext(MethodSynth *synth);
  ~MethodContext();

  IInsn *method_insn_;
  vector<StateWrapper *> states_;

  StateWrapper *LastState();

private:
  MethodSynth *synth_;
};

}  // namespace isynth

#endif  // _isynth_method_context_h_
