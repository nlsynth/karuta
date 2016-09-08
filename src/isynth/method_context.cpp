#include "isynth/method_context.h"

#include "isynth/method_synth.h"

namespace isynth {

StateWrapper::StateWrapper()
  : state_(nullptr), callee_method_(nullptr) {
}

MethodContext::MethodContext(MethodSynth *synth)
  : method_insn_(nullptr), synth_(synth) {
}

MethodContext::~MethodContext() {
  STLDeleteValues(&states_);
}

}  // namespace isynth

