#include "isynth/method_context.h"

#include "isynth/method_synth.h"

namespace isynth {

StateWrapper::StateWrapper()
  : state_(nullptr), callee_method_(nullptr),
    vm_insn_(nullptr), callee_vm_obj_(nullptr) {
}

MethodContext::MethodContext(MethodSynth *synth)
  : method_insn_(nullptr), synth_(synth) {
}

MethodContext::~MethodContext() {
  STLDeleteValues(&states_);
}

StateWrapper *MethodContext::LastState() {
  if (states_.size() > 0) {
    return *(states_.rbegin());
  }
  return nullptr;
}

}  // namespace isynth
