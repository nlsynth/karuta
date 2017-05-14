#include "synth/resource_synth.h"

#include "base/annotation.h"
#include "iroha/iroha.h"
#include "synth/resource_set.h"
#include "vm/array_wrapper.h"

namespace synth {

ResourceSynth::ResourceSynth(ResourceSet *rset) : rset_(rset) {
}

void ResourceSynth::MayAddAxiMasterPort(vm::Object *array_obj) {
  Annotation *a = vm::ArrayWrapper::GetAnnotation(array_obj);
  if (a == nullptr || !a->IsAxiMaster()) {
    return;
  }
  (void) rset_->GetAxiMasterPort(array_obj);
}

void ResourceSynth::MayAddAxiSlavePort(vm::Object *array_obj) {
  Annotation *a = vm::ArrayWrapper::GetAnnotation(array_obj);
  if (a == nullptr || !a->IsAxiSlave()) {
    return;
  }
  IResource *slave_port = rset_->GetAxiSlavePort(array_obj);
  if (slave_port->GetParams()->GetWidth() == 32) {
    // already configured.
    return;
  }
  slave_port->GetParams()->SetWidth(vm::ArrayWrapper::GetDataWidth(array_obj));
}

}  // namespace synth
