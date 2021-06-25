#include "synth/resource_synth.h"

#include "base/status.h"
#include "iroha/iroha.h"
#include "karuta/annotation.h"
#include "synth/design_synth.h"
#include "synth/object_synth.h"
#include "synth/resource_set.h"
#include "synth/thread_synth.h"
#include "vm/array_wrapper.h"
#include "vm/io_wrapper.h"
#include "vm/mailbox_wrapper.h"
#include "vm/vm_method.h"
#include "vm/object.h"

namespace synth {

ResourceSynth::ResourceSynth(ResourceSet *rset, ThreadSynth *thr_synth)
    : rset_(rset), thr_synth_(thr_synth) {}

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
  ConfigureSlavePort(owner_obj, array_obj, a, slave_port);
}

void ResourceSynth::MayAddSramIfPort(vm::Object *owner_obj,
                                     vm::Object *array_obj) {
  Annotation *a = vm::ArrayWrapper::GetAnnotation(array_obj);
  if (a == nullptr) {
    return;
  }
  if (!a->IsExportSramIf() && !a->IsAxiMasterAndExport()) {
    return;
  }
  IResource *sram_if_port = rset_->GetSramIfPort(array_obj);
  ConfigureSlavePort(owner_obj, array_obj, a, sram_if_port);
}

void ResourceSynth::ConfigureSlavePort(vm::Object *owner_obj,
                                       vm::Object *array_obj, Annotation *an,
                                       IResource *if_port) {
  if (if_port->GetParams()->GetWidth() > 0) {
    // already configured.
    return;
  }
  if_port->GetParams()->SetWidth(vm::ArrayWrapper::GetDataWidth(array_obj));
  if_port->GetParams()->SetAddrWidth(an->GetAddrWidth());
  SetArrayName(owner_obj, array_obj, if_port);
  if (!an->IsAxiExclusive()) {
    if_port->GetParams()->SetSramPortIndex("0");
  }
}

void ResourceSynth::MayConfigureExternalSram(vm::Object *obj, IResource *res) {
  Annotation *a = vm::ArrayWrapper::GetAnnotation(obj);
  if (a == nullptr || !a->IsExternal()) {
    return;
  }
  res->GetArray()->SetExternal(true);
  string n = a->GetName();
  if (!n.empty()) {
    res->GetParams()->SetPortNamePrefix(n);
  }
}

void ResourceSynth::MayAddExternalSram(vm::Object *array_obj) {
  Annotation *a = vm::ArrayWrapper::GetAnnotation(array_obj);
  if (a == nullptr || !a->IsExternal()) {
    return;
  }
  IResource *res = rset_->GetExternalArrayResource(array_obj);
  MayConfigureExternalSram(array_obj, res);
}

void ResourceSynth::SetArrayName(vm::Object *owner_obj, vm::Object *array_obj,
                                 IResource *res) {
  DesignSynth *ds = thr_synth_->GetObjectSynth()->GetDesignSynth();
  string name = ds->GetObjectName(array_obj);
  if (!name.empty()) {
    res->GetParams()->SetPortNamePrefix(name + "_");
  }
}

IResource *ResourceSynth::MayAddExtIO(vm::Method *method, bool is_output) {
  string name;
  Annotation *an = method->GetAnnotation();
  int nth_reg;
  if (is_output) {
    name = an->GetOutputPinName();
    nth_reg = 0;
    if (method->GetNumArgRegisters() != 1) {
      Status::os(Status::USER_ERROR)
          << "Ext output method must have 1 argument.";
      return nullptr;
    }
  } else {
    name = an->GetInputPinName();
    nth_reg = method->GetNumArgRegisters();
    if (method->GetNumReturnRegisters() != 1) {
      Status::os(Status::USER_ERROR)
          << "Ext output method must have 1 return value.";
      return nullptr;
    }
  }
  vm::Register *reg = method->method_regs_[nth_reg];
  int width;
  if (reg->type_.value_type_ == vm::Value::ENUM_ITEM) {
    width = 0;
  } else {
    width = reg->type_.num_width_.GetWidth();
  }
  int d = an->GetDistance();
  IResource *res = rset_->GetExtIOByName(name, is_output, width, d);
  return res;
}

void ResourceSynth::MayAddSharedRegExtWriter(vm::Object *mailbox_obj) {
  Annotation *an = vm::MailboxWrapper::GetAnnotation(mailbox_obj);
  if (an == nullptr || !(an->IsExportMailbox() || an->IsExtIO())) {
    return;
  }
  IResource *res = rset_->GetMailboxExtWriter(mailbox_obj);
  res->GetParams()->SetPortNamePrefix(an->GetName());
  string s = an->GetWenSuffix();
  if (!s.empty()) {
    res->GetParams()->SetWenSuffix(s);
  }
  s = an->GetNotifySuffix();
  if (!s.empty()) {
    res->GetParams()->SetNotifySuffix(s);
  }
  s = an->GetPutSuffix();
  if (!s.empty()) {
    res->GetParams()->SetPutSuffix(s);
  }
}

void ResourceSynth::MayAddIO(vm::Object *io, bool is_owner) {
  if (!vm::IOWrapper::IsIO(io)) {
    return;
  }
  rset_->GetExtIOByObject(io, is_owner);
}

}  // namespace synth
