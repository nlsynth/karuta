#include "synth/object_method.h"

#include "synth/method_context.h"
#include "synth/method_synth.h"
#include "synth/resource_set.h"
#include "vm/insn.h"

namespace synth {

ObjectMethod::ObjectMethod(MethodSynth *synth, vm::Insn *insn)
  : synth_(synth), insn_(insn) {
}

void ObjectMethod::Synth() {
  ResourceSet *rset = synth_->GetResourceSet();
  IInsn *iinsn;
  if (insn_->label_ == sym_lookup("print")) {
    iinsn = new IInsn(rset->PrintResource());
  } else if (insn_->label_ == sym_lookup("assert")) {
    iinsn = new IInsn(rset->AssertResource());
  } else if (insn_->label_ == sym_lookup("load")) {
    iinsn = SynthAxiAccess(false);
  } else if (insn_->label_ == sym_lookup("store")) {
    iinsn = SynthAxiAccess(true);
  } else {
    CHECK(false);
  }
  StateWrapper *sw = synth_->AllocState();
  sw->state_->insns_.push_back(iinsn);
  for (vm::Register *arg : insn_->src_regs_) {
    IRegister *iarg = synth_->FindLocalVarRegister(arg);
    iinsn->inputs_.push_back(iarg);
  }
}

IInsn *ObjectMethod::SynthAxiAccess(bool is_store) {
  vm::Object *array_obj = synth_->GetObjByReg(insn_->obj_reg_);
  IResource *res = synth_->GetResourceSet()->GetAxiPort(array_obj);
  IInsn *iinsn = new IInsn(res);
  if (is_store) {
    iinsn->SetOperand("write");
  } else {
    iinsn->SetOperand("read");
  }
  return iinsn;
}

}  // namespace synth
