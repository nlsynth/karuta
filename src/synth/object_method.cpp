#include "synth/object_method.h"

#include "iroha/iroha.h"
#include "synth/insn_walker.h"
#include "synth/method_context.h"
#include "synth/method_synth.h"
#include "synth/object_method_names.h"
#include "synth/resource_set.h"
#include "synth/shared_resource_set.h"
#include "vm/mailbox_wrapper.h"
#include "vm/insn.h"
#include "vm/method.h"
#include "vm/object.h"

namespace synth {

ObjectMethod::ObjectMethod(MethodSynth *synth, InsnWalker *walker,
			   vm::Insn *insn)
  : synth_(synth), walker_(walker), insn_(insn) {
}

void ObjectMethod::Synth() {
  vm::Object *obj = walker_->GetObjByReg(insn_->obj_reg_);
  string name = GetSynthName(obj);
  IInsn *iinsn = nullptr;
  ResourceSet *rset = synth_->GetResourceSet();
  if (name == kPrint) {
    iinsn = new IInsn(rset->PrintResource());
  } else if (name == kAssert) {
    iinsn = new IInsn(rset->AssertResource());
  } else if (name == kLoad) {
    iinsn = SynthAxiAccess(obj, false);
  } else if (name == kStore) {
    iinsn = SynthAxiAccess(obj, true);
  } else if (name == kMailboxWidth) {
    iinsn = SynthMailboxWidth(obj);
  } else if (name == kMailboxGet) {
    iinsn = SynthMailboxAccess(obj, false);
  } else if (name == kMailboxPut) {
    iinsn = SynthMailboxAccess(obj, true);
  } else {
    CHECK(false) << name;
  }
  StateWrapper *sw = synth_->AllocState();
  sw->state_->insns_.push_back(iinsn);
  for (vm::Register *arg : insn_->src_regs_) {
    IRegister *iarg = synth_->FindLocalVarRegister(arg);
    iinsn->inputs_.push_back(iarg);
  }
}

void ObjectMethod::Scan() {
  vm::Object *obj = walker_->GetObjByReg(insn_->obj_reg_);
  CHECK(obj);
  string name = GetSynthName(obj);
  SharedResourceSet *sres = walker_->GetSharedResourceSet();
  if (name == kLoad || name == kStore || name == kMailboxPut ||
      name == kMailboxGet) {
    sres->AddObjectAccessor(walker_->GetThreadSynth(), obj, insn_, name);
  }
}

IInsn *ObjectMethod::SynthAxiAccess(vm::Object *array_obj, bool is_store) {
  IResource *res = synth_->GetResourceSet()->GetAxiPort(array_obj);
  IInsn *iinsn = new IInsn(res);
  if (is_store) {
    iinsn->SetOperand("write");
  } else {
    iinsn->SetOperand("read");
  }
  return iinsn;
}

IInsn *ObjectMethod::SynthMailboxWidth(vm::Object *mailbox_obj) {
  int width = vm::MailboxWrapper::GetWidth(mailbox_obj);
  ResourceSet *rset = synth_->GetResourceSet();
  IInsn *iinsn = new IInsn(rset->AssignResource());
  IRegister *wreg =
    DesignTool::AllocConstNum(synth_->GetITable(),
			      32,
			      width);
  iinsn->inputs_.push_back(wreg);
  return iinsn;
}

IInsn *ObjectMethod::SynthMailboxAccess(vm::Object *mailbox_obj, bool is_put) {
  SharedResource *sres =
    synth_->GetSharedResourceSet()->GetByObj(mailbox_obj);
  IResource *res = nullptr;
  ResourceSet *rset = synth_->GetResourceSet();
  if (sres->owner_thr_ == synth_->GetThreadSynth()) {
    res = rset->GetMailbox(mailbox_obj, true, false);
    sres->AddOwnerResource(res);
  }
  res = rset->GetMailbox(mailbox_obj, false, is_put);
  sres->AddAccessorResource(res);
  IInsn *iinsn = new IInsn(res);
  if (is_put) {
    iinsn->SetOperand(iroha::operand::kPutMailbox);
  } else {
    iinsn->SetOperand(iroha::operand::kGetMailbox);
  }
  return iinsn;
}

string ObjectMethod::GetSynthName(vm::Object *obj) {
  vm::Value *value = obj->LookupValue(insn_->label_, false);
  CHECK(value != nullptr && value->type_ == vm::Value::METHOD);
  vm::Method *method = value->method_;
  return method->GetSynthName();
}

}  // namespace synth
