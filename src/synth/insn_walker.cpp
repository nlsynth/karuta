#include "synth/insn_walker.h"

#include "synth/design_synth.h"
#include "synth/object_synth.h"
#include "synth/shared_resource_set.h"
#include "synth/thread_synth.h"
#include "vm/insn.h"
#include "vm/method.h"
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
    vm::Object *obj = member_reg_to_obj_map_[insn->src_regs_[0]];
    vm::Value *value = obj->LookupValue(insn->label_, false);
    CHECK(value);
    if (!value->is_const_ && value->IsObjectType()) {
      member_reg_to_obj_map_[insn->dst_regs_[0]] = value->object_;
    }
  }
}

void InsnWalker::LoadObj(vm::Insn *insn) {
  if (insn->label_) {
    vm::Object *src_obj;
    if (insn->obj_reg_) {
      src_obj = member_reg_to_obj_map_[insn->obj_reg_];
    } else {
      src_obj = obj_;
    }
    vm::Value *value = src_obj->LookupValue(insn->label_, false);
    // Can be OBJECT, INT_ARRAY, OBJECT_ARRAY.
    vm::Object *member = value->object_;
    CHECK(member) << sym_cstr(insn->label_);
    member_reg_to_obj_map_[insn->dst_regs_[0]] = member;
  } else {
    // loading "this" obj.
    member_reg_to_obj_map_[insn->dst_regs_[0]] = obj_;
  }
}

bool InsnWalker::IsNativeFuncall(vm::Insn *insn) {
  vm::Object *obj = GetCalleeObject(insn);
  if (obj == nullptr) {
    obj = obj_;
  }
  sym_t func_name = insn->label_;
  vm::Value *value = obj->LookupValue(func_name, false);
  CHECK(value != nullptr && value->type_ == vm::Value::METHOD);
  vm::Method *method = value->method_;
  return method->GetHasSynth();
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
