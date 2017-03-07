#include "synth/object_method.h"

#include "iroha/iroha.h"
#include "synth/insn_walker.h"
#include "synth/method_context.h"
#include "synth/method_synth.h"
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
  if (name == "print") {
    iinsn = new IInsn(rset->PrintResource());
  } else if (name == "assert") {
    iinsn = new IInsn(rset->AssertResource());
  } else if (name == "load") {
    iinsn = SynthAxiAccess(obj, false);
  } else if (name == "store") {
    iinsn = SynthAxiAccess(obj, true);
  } else if (name == "mailbox_width") {
    iinsn = SynthMailboxWidth(obj);
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
  if (name == "load" || name == "store") {
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

string ObjectMethod::GetSynthName(vm::Object *obj) {
  vm::Value *value = obj->LookupValue(insn_->label_, false);
  CHECK(value != nullptr && value->type_ == vm::Value::METHOD);
  vm::Method *method = value->method_;
  return method->GetSynthName();
}

}  // namespace synth
