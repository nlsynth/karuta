#include "synth/object_method.h"

#include "base/status.h"
#include "iroha/iroha.h"
#include "karuta/annotation.h"
#include "synth/insn_walker.h"
#include "synth/method_context.h"
#include "synth/method_synth.h"
#include "synth/object_method_names.h"
#include "synth/object_synth.h"
#include "synth/resource_set.h"
#include "synth/resource_synth.h"
#include "synth/shared_resource_set.h"
#include "synth/thread_synth.h"
#include "vm/array_wrapper.h"
#include "vm/channel_wrapper.h"
#include "vm/insn.h"
#include "vm/mailbox_wrapper.h"
#include "vm/method.h"
#include "vm/object.h"

namespace synth {

ObjectMethod::ObjectMethod(MethodSynth *synth, InsnWalker *walker,
                           ResourceSynth *rsynth, vm::Insn *insn)
    : synth_(synth), walker_(walker), rsynth_(rsynth), insn_(insn) {}

void ObjectMethod::Synth() {
  vm::Object *obj = walker_->GetObjByReg(insn_->obj_reg_);
  string name = GetSynthName(obj);
  IInsn *iinsn = nullptr;
  ResourceSet *rset = synth_->GetResourceSet();
  if (name == kPrint) {
    iinsn = new IInsn(rset->PrintResource());
  } else if (name == kAssert) {
    iinsn = new IInsn(rset->AssertResource());
  } else if (name == kAxiLoad) {
    iinsn = SynthAxiAccess(obj, false);
  } else if (name == kAxiStore) {
    iinsn = SynthAxiAccess(obj, true);
  } else if (name == kGetTickCount) {
    iinsn = SynthGetTickCount(obj);
  } else if (name == kDecrementTick) {
    iinsn = SynthDecrementTick(obj);
  } else if (name == kSlaveWait) {
    iinsn = SynthWait(obj);
  } else if (name == kMailboxWidth) {
    iinsn = SynthMailboxWidth(obj);
  } else if (name == kMailboxGet) {
    iinsn = SynthMailboxAccess(obj, true, false);
  } else if (name == kMailboxPut) {
    iinsn = SynthMailboxAccess(obj, true, true);
  } else if (name == kMailboxWait) {
    iinsn = SynthMailboxAccess(obj, false, false);
  } else if (name == kMailboxNotify) {
    iinsn = SynthMailboxAccess(obj, false, true);
  } else if (name == kSramRead) {
    iinsn = SynthMemoryAccess(obj, false);
  } else if (name == kSramWrite) {
    iinsn = SynthMemoryAccess(obj, true);
  } else if (name == kChannelRead) {
    iinsn = SynthChannelAccess(obj, false);
  } else if (name == kChannelWrite || name == kChannelNoWaitWrite) {
    iinsn = SynthChannelAccess(obj, true);
  } else if (name == kIORead || name == kIOWait) {
    iinsn = SynthExtIO(obj, false);
  } else if (name == kIOWrite) {
    iinsn = SynthExtIO(obj, true);
  } else if (name == kIOPeek) {
    iinsn = SynthExtIO(obj, true);
  } else {
    CHECK(false) << name;
  }
  if (iinsn == nullptr) {
    return;
  }
  StateWrapper *sw = synth_->AllocState();
  sw->state_->insns_.push_back(iinsn);
  for (vm::Register *arg : insn_->src_regs_) {
    IRegister *iarg = synth_->FindLocalVarRegister(arg);
    iinsn->inputs_.push_back(iarg);
  }
  if (name == kSramWrite) {
    iinsn->SetOperand(iroha::operand::kSramWrite);
  }
  if (name == kSramRead) {
    iinsn->SetOperand(iroha::operand::kSramReadAddress);
    iinsn = new IInsn(iinsn->GetResource());
    iinsn->SetOperand(iroha::operand::kSramReadData);
    sw = synth_->AllocState();
    sw->state_->insns_.push_back(iinsn);
  }
}

void ObjectMethod::Scan() {
  vm::Object *obj = walker_->GetObjByReg(insn_->obj_reg_);
  CHECK(obj);
  string name = GetSynthName(obj);
  SharedResourceSet *sres = walker_->GetSharedResourceSet();
  if (name == kAxiLoad || name == kAxiStore || name == kSlaveWait ||
      name == kMailboxPut || name == kMailboxGet || name == kMailboxNotify ||
      name == kMailboxWait || name == kChannelWrite ||
      name == kChannelNoWaitWrite || name == kChannelRead || name == kIORead ||
      kIOWrite || kIOPeek) {
    vm::Object *parent_obj = walker_->GetParentObjByObj(obj);
    sres->AddObjectAccessor(walker_->GetThreadSynth(), parent_obj, obj, insn_,
                            name, false);
  }
}

IInsn *ObjectMethod::SynthAxiAccess(vm::Object *array_obj, bool is_store) {
  Annotation *a = vm::ArrayWrapper::GetAnnotation(array_obj);
  if (a == nullptr || !a->IsAxiMaster()) {
    Status::os(Status::USER_ERROR) << "AXI access methods are allowed on for a "
                                      "master (add @AxiMaster() annotation).";
    return nullptr;
  }
  IResource *axim_res = synth_->GetResourceSet()->GetAxiMasterPort(array_obj);
  SharedResource *array_sres =
      synth_->GetSharedResourceSet()->GetByObj(array_obj, nullptr);
  array_sres->SetOwnerIResource(axim_res->GetParentResource());
  rsynth_->MayAddAxiMasterPort(synth_->GetObject(), array_obj);
  IInsn *iinsn = new IInsn(axim_res);
  if (is_store) {
    iinsn->SetOperand(iroha::operand::kWrite);
  } else {
    iinsn->SetOperand(iroha::operand::kRead);
  }
  return iinsn;
}

IInsn *ObjectMethod::SynthWait(vm::Object *array_obj) {
  Annotation *a = vm::ArrayWrapper::GetAnnotation(array_obj);
  if (a != nullptr) {
    if (a->IsAxiSlave()) {
      return SynthAxiWait(array_obj);
    }
    if (a->IsExportSramIf()) {
      return SynthSramWait(array_obj);
    }
  }
  Status::os(Status::USER_ERROR)
      << "wait method is allowed on for a slave "
      << "(add @AxiSlave() or @SramIf() annotation).";
  return nullptr;
}

IInsn *ObjectMethod::SynthAxiWait(vm::Object *array_obj) {
  IResource *axis_res = synth_->GetResourceSet()->GetAxiSlavePort(array_obj);
  SharedResource *array_sres =
      synth_->GetSharedResourceSet()->GetByObj(array_obj, nullptr);
  array_sres->SetOwnerIResource(axis_res->GetParentResource());
  rsynth_->MayAddAxiSlavePort(synth_->GetObject(), array_obj);
  IInsn *iinsn = new IInsn(axis_res);
  return iinsn;
}

IInsn *ObjectMethod::SynthSramWait(vm::Object *array_obj) {
  IResource *sramif_res = synth_->GetResourceSet()->GetSramIfPort(array_obj);
  SharedResource *array_sres =
      synth_->GetSharedResourceSet()->GetByObj(array_obj, nullptr);
  array_sres->SetOwnerIResource(sramif_res->GetParentResource());
  rsynth_->MayAddSramIfPort(synth_->GetObject(), array_obj);
  IInsn *iinsn = new IInsn(sramif_res);
  return iinsn;
}

IInsn *ObjectMethod::SynthMailboxWidth(vm::Object *mailbox_obj) {
  int width = vm::MailboxWrapper::GetWidth(mailbox_obj);
  ResourceSet *rset = synth_->GetResourceSet();
  IInsn *iinsn = new IInsn(rset->AssignResource());
  IRegister *wreg = DesignTool::AllocConstNum(synth_->GetITable(), 32, width);
  iinsn->inputs_.push_back(wreg);
  return iinsn;
}

IInsn *ObjectMethod::SynthMailboxAccess(vm::Object *mailbox_obj,
                                        bool is_blocking, bool is_put) {
  SharedResource *sres =
      synth_->GetSharedResourceSet()->GetByObj(mailbox_obj, nullptr);
  rsynth_->MayAddSharedRegExtWriter(mailbox_obj);
  IResource *res = nullptr;
  ResourceSet *rset = synth_->GetResourceSet();
  if (sres->GetOwnerThread() == synth_->GetThreadSynth()) {
    res = rset->GetMailbox(mailbox_obj, true, false);
    sres->SetOwnerIResource(res);
  }
  res = rset->GetMailbox(mailbox_obj, false, is_put);
  sres->AddAccessorResource(res, synth_->GetThreadSynth());
  IInsn *iinsn = new IInsn(res);
  if (is_blocking) {
    if (is_put) {
      iinsn->SetOperand(iroha::operand::kPutMailbox);
    } else {
      iinsn->SetOperand(iroha::operand::kGetMailbox);
    }
  } else {
    if (is_put) {
      iinsn->SetOperand(iroha::operand::kNotify);
    } else {
      iinsn->SetOperand(iroha::operand::kWaitNotify);
    }
  }
  return iinsn;
}

string ObjectMethod::GetSynthName(vm::Object *obj) {
  vm::Value *value = obj->LookupValue(insn_->label_, false);
  CHECK(value != nullptr && value->type_ == vm::Value::METHOD);
  vm::Method *method = value->method_;
  return method->GetSynthName();
}

IInsn *ObjectMethod::SynthMemoryAccess(vm::Object *obj, bool is_write) {
  ResourceSet *rset = synth_->GetResourceSet();
  IResource *res = rset->GetExternalArrayResource(obj);
  IInsn *iinsn = new IInsn(res);
  return iinsn;
}

IInsn *ObjectMethod::SynthChannelAccess(vm::Object *ch_obj, bool is_write) {
  CHECK(vm::ChannelWrapper::IsChannel(ch_obj));
  int width = vm::ChannelWrapper::ChannelWidth(ch_obj);
  ResourceSet *rset = synth_->GetResourceSet();
  SharedResource *sres =
      synth_->GetSharedResourceSet()->GetByObj(ch_obj, nullptr);
  int depth = vm::ChannelWrapper::ChannelDepth(ch_obj);
  if (sres->GetOwnerThread() == synth_->GetThreadSynth()) {
    IResource *channel_res =
        rset->GetChannelResource(ch_obj, true, false, width, depth);
    sres->SetOwnerIResource(channel_res);
  }
  IResource *accessor_res =
      rset->GetChannelResource(ch_obj, false, is_write, width, depth);
  sres->AddAccessorResource(accessor_res, synth_->GetThreadSynth());
  IInsn *iinsn = new IInsn(accessor_res);
  string name = GetSynthName(ch_obj);
  if (name == kChannelNoWaitWrite) {
    iinsn->SetOperand(iroha::operand::kNoWait);
  }
  return iinsn;
}

IInsn *ObjectMethod::SynthGetTickCount(vm::Object *obj) {
  SharedResource *sres = synth_->GetSharedResourceSet()->GetByObj(obj, nullptr);
  bool is_owner = IsOwner(sres);
  IResource *res = synth_->GetResourceSet()->GetTicker(obj, is_owner);
  if (is_owner) {
    sres->SetOwnerIResource(res);
  } else {
    sres->AddAccessorResource(res, synth_->GetThreadSynth());
  }
  return new IInsn(res);
}

IInsn *ObjectMethod::SynthDecrementTick(vm::Object *obj) {
  SharedResource *sres = synth_->GetSharedResourceSet()->GetByObj(obj, nullptr);
  bool is_owner = IsOwner(sres);
  IResource *res = synth_->GetResourceSet()->GetTicker(obj, is_owner);
  if (is_owner) {
    sres->SetOwnerIResource(res);
  } else {
    sres->AddAccessorResource(res, synth_->GetThreadSynth());
  }
  return new IInsn(res);
}

IInsn *ObjectMethod::SynthExtIO(vm::Object *obj, bool is_write) {
  SharedResource *sres = synth_->GetSharedResourceSet()->GetByObj(obj, nullptr);
  bool is_owner = IsOwner(sres);
  rsynth_->MayAddIO(obj, is_owner);
  ResourceSet *rset = synth_->GetResourceSet();
  IResource *res = rset->GetExtIOByObject(obj, is_owner);
  if (is_owner) {
    sres->SetOwnerIResource(res);
  } else {
    sres->AddAccessorResource(res, synth_->GetThreadSynth());
  }
  IInsn *iinsn = new IInsn(res);
  string name = GetSynthName(obj);
  if (name == kIOWait) {
    iinsn->SetOperand("wait");
  }
  return iinsn;
}

bool ObjectMethod::IsOwner(SharedResource *sres) {
  if (sres->GetOwnerThread() == synth_->GetThreadSynth()) {
    return true;
  }
  return false;
}

}  // namespace synth
