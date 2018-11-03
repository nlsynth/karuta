#include "synth/method_context.h"

#include "base/stl_util.h"
#include "synth/method_synth.h"

namespace synth {

StateWrapper::StateWrapper()
  : index_(-1), state_(nullptr), vm_insn_(nullptr),
    is_sub_obj_call_(false), is_data_flow_call_(false),
    is_ext_stub_call_(false), is_ext_flow_stub_call_(false),
    callee_vm_obj_(nullptr) {
}

MethodContext::MethodContext(MethodSynth *synth)
  : method_signature_insn_(nullptr), synth_(synth) {
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

}  // namespace synth
