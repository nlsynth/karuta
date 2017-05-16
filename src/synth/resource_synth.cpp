#include "synth/resource_synth.h"

#include "base/annotation.h"
#include "iroha/iroha.h"
#include "synth/resource_set.h"
#include "vm/array_wrapper.h"
#include "vm/object.h"

namespace synth {

ResourceSynth::ResourceSynth(ResourceSet *rset) : rset_(rset) {
}

void ResourceSynth::MayAddAxiMasterPort(vm::Object *owner_obj,
					vm::Object *array_obj) {
  Annotation *a = vm::ArrayWrapper::GetAnnotation(array_obj);
  if (a == nullptr || !a->IsAxiMaster()) {
    return;
  }
  IResource *master_port = rset_->GetAxiMasterPort(array_obj);
  SetArrayName(owner_obj, array_obj, master_port);
}

void ResourceSynth::MayAddAxiSlavePort(vm::Object *owner_obj,
				       vm::Object *array_obj) {
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
  SetArrayName(owner_obj, array_obj, slave_port);
}

void ResourceSynth::SetArrayName(vm::Object *owner_obj, vm::Object *array_obj,
				 IResource *res) {
  vector<sym_t> slots;
  owner_obj->LookupMemberNames(array_obj, &slots);
  if (slots.size() == 1) {
    res->GetParams()->SetPortNamePrefix(string(sym_cstr(slots[0])) + "_");
  }
}

}  // namespace synth
