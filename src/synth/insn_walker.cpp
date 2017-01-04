#include "synth/insn_walker.h"

#include "synth/design_synth.h"
#include "synth/object_synth.h"
#include "synth/shared_resource_set.h"
#include "synth/thread_synth.h"
#include "vm/insn.h"
#include "vm/object.h"
#include "vm/value.h"

namespace synth {

InsnWalker::InsnWalker(ThreadSynth *thr_synth) {
  vm_ = thr_synth->GetObjectSynth()->GetVM();
  obj_ = thr_synth->GetObjectSynth()->GetObject();
  DesignSynth *ds = thr_synth->GetObjectSynth()->GetDesignSynth();
  shared_resource_set_ = ds->GetSharedResourceSet();
}

void InsnWalker::MaybeLoadMemberObject(vm::Insn *insn) {
  if (insn->op_ == vm::OP_MEMBER_READ) {
    vm::Value *value = obj_->LookupValue(insn->label_, false);
    if (!value->is_const_ && value->type_ == vm::Value::OBJECT) {
      member_reg_to_obj_map_[insn->dst_regs_[0]] = value->object_;
    }
  }
}

void InsnWalker::LoadObj(vm::Insn *insn) {
  if (insn->label_) {
    vm::Value *value = obj_->LookupValue(insn->label_, false);
    // Can be OBJECT, INT_ARRAY, OBJECT_ARRAY.
    vm::Object *member = value->object_;
    CHECK(member);
    member_reg_to_obj_map_[insn->dst_regs_[0]] = member;
  } else {
    // loading "this" obj.
    member_reg_to_obj_map_[insn->dst_regs_[0]] = obj_;
  }
}

bool InsnWalker::IsNativeFuncall(vm::Insn *insn) {
  sym_t func_name = insn->label_;
  if (func_name == sym_lookup("print") ||
      func_name == sym_lookup("assert")) {
    return true;
  }
  return false;
}

vm::Object *InsnWalker::GetCalleeObject(vm::Insn *insn) {
  if (insn->obj_reg_ != nullptr) {
    return member_reg_to_obj_map_[insn->obj_reg_];
  }
  return nullptr;
}

bool InsnWalker::IsSubObjCall(vm::Insn *insn) {
  vm::Object *callee_obj = GetCalleeObject(insn);
  if (insn->obj_reg_ != nullptr && callee_obj != obj_) {
    return true;
  }
  return false;
}

}  // namespace synth
