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
};

class MethodContext {
public:
  MethodContext(MethodSynth *synth);
  ~MethodContext();

  IInsn *method_insn_;
  vector<StateWrapper *> states_;

private:
  MethodSynth *synth_;
};

}  // namespace isynth

#endif  // _isynth_method_context_h_
