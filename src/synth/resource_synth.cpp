#include "synth/resource_synth.h"

#include "base/annotation.h"
#include "fe/method.h"
#include "iroha/iroha.h"
#include "synth/design_synth.h"
#include "synth/resource_set.h"
#include "synth/object_synth.h"
#include "synth/thread_synth.h"
#include "vm/array_wrapper.h"
#include "vm/method.h"
#include "vm/object.h"

namespace synth {

ResourceSynth::ResourceSynth(ResourceSet *rset, ThreadSynth *thr_synth)
  : rset_(rset), thr_synth_(thr_synth) {
}

void ResourceSynth::MayAddAxiMasterPort(vm::Object *owner_obj,
					vm::Object *array_obj) {
  Annotation *a = vm::ArrayWrapper::GetAnnotation(array_obj);
  if (a == nullptr || !a->IsAxiMaster()) {
    return;
  }
  IResource *master_port = rset_->GetAxiMasterPort(array_obj);
  SetArrayName(owner_obj, array_obj, master_port);
  master_port->GetParams()->SetAddrWidth(a->GetAddrWidth());
  if (!a->IsAxiExclusive()) {
    master_port->GetParams()->SetSramPortIndex("0");
  }
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
  slave_port->GetParams()->SetAddrWidth(a->GetAddrWidth());
  SetArrayName(owner_obj, array_obj, slave_port);
}

void ResourceSynth::SetArrayName(vm::Object *owner_obj, vm::Object *array_obj,
				 IResource *res) {
  DesignSynth *ds = thr_synth_->GetObjectSynth()->GetDesignSynth();
  string name = ds->GetObjectName(array_obj);
  if (!name.empty()) {
    res->GetParams()->SetPortNamePrefix(name + "_");
  }
}

IResource *ResourceSynth::MayAddExtIO(vm::Method *method,
				      bool is_output) {
  string name;
  Annotation *an = method->parse_tree_->annotation_;
  int nth_reg;
  if (is_output) {
    name = an->GetOutputPinName();
    nth_reg = 0;
  } else {
    name = an->GetInputPinName();
    nth_reg = method->GetNumArgRegisters();
  }
  vm::Register *reg = method->method_regs_[nth_reg];
  int width;
  if (reg->type_.value_type_ == vm::Value::ENUM_ITEM) {
    width = 0;
  } else {
    width = reg->type_.width_.GetWidth();
  }
  return rset_->GetExtIO(name, is_output, width);
}

}  // namespace synth
