#include "synth/insn_walker.h"

#include "base/annotation.h"
#include "base/status.h"
#include "fe/method.h"
#include "synth/design_synth.h"
#include "synth/object_synth.h"
#include "synth/shared_resource_set.h"
#include "synth/thread_synth.h"
#include "vm/array_wrapper.h"
#include "vm/insn.h"
#include "vm/method.h"
#include "vm/numeric_object.h"
#include "vm/object.h"
#include "vm/tls_wrapper.h"
#include "vm/value.h"

namespace synth {

InsnWalker::InsnWalker(ThreadSynth *thr_synth, vm::Object *obj)
  : thr_synth_(thr_synth), obj_(obj) {
  vm_ = thr_synth->GetObjectSynth()->GetVM();
  DesignSynth *ds = thr_synth->GetObjectSynth()->GetDesignSynth();
  shared_resource_set_ = ds->GetSharedResourceSet();
}

void InsnWalker::MaybeLoadMemberObject(vm::Insn *insn) {
  if (insn->op_ == vm::OP_MEMBER_READ) {
    vm::Object *obj = member_reg_to_obj_map_[insn->src_regs_[0]];
    vm::Value *value = obj->LookupValue(insn->label_, false);
    if (value == nullptr) {
      Status::os(Status::USER_ERROR) << "member not found: "
				     << sym_cstr(insn->label_);
      return;
    }
    if (!value->is_const_) {
      if (vm::TlsWrapper::IsTlsValue(value)) {
	vm::Object *base_obj =
	  vm::TlsWrapper::GetBaseObject(value->object_);
	member_reg_to_obj_map_[insn->dst_regs_[0]] = base_obj;
	member_to_owner_obj_map_[base_obj] = obj;
	thread_local_objs_.insert(base_obj);
      } else if (value->IsObjectType()) {
	member_reg_to_obj_map_[insn->dst_regs_[0]] = value->object_;
	member_to_owner_obj_map_[value->object_] = obj;
      }
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
    member_to_owner_obj_map_[member] = src_obj;
  } else {
    // loading "this" obj.
    member_reg_to_obj_map_[insn->dst_regs_[0]] = obj_;
  }
}

void InsnWalker::MaybeLoadObjectArrayElement(vm::Insn *insn) {
  if (insn->op_ != vm::OP_ARRAY_READ) {
    return;
  }
  vm::Object *array_obj = member_reg_to_obj_map_[insn->obj_reg_];
  if (vm::ArrayWrapper::IsObjectArray(array_obj)) {
    // NOTE: InsnAnnotator::TypeArrayRead has similar code.
    vm::Register *idx_reg = insn->src_regs_[0];
    CHECK(idx_reg->type_.is_const_);
    int idx = idx_reg->initial_num_.GetValue0();
    vm::Object *elm_obj = vm::ArrayWrapper::Get(array_obj, idx);
    member_reg_to_obj_map_[insn->dst_regs_[0]] = elm_obj;
  }
}

vm::Object *InsnWalker::GetObject() {
  return obj_;
}

bool InsnWalker::IsNativeFuncall(vm::Insn *insn) {
  vm::Method *method = GetCalleeMethod(insn);
  return !(method->GetSynthName().empty());
}

vm::Method *InsnWalker::GetCalleeMethod(vm::Insn *insn) {
  vm::Object *obj = GetCalleeObject(insn);
  CHECK(obj);
  sym_t func_name = insn->label_;
  vm::Value *value = obj->LookupValue(func_name, false);
  CHECK(value != nullptr && value->type_ == vm::Value::METHOD);
  return value->method_;
}

vm::Object *InsnWalker::GetCalleeObject(vm::Insn *insn) {
  if (insn->obj_reg_ != nullptr) {
    return member_reg_to_obj_map_[insn->obj_reg_];
  }
  // self.
  return obj_;
}

bool InsnWalker::IsSubObjCall(vm::Insn *insn) {
  vm::Object *callee_obj = GetCalleeObject(insn);
  if (callee_obj != obj_) {
    if (vm::NumericObject::IsNumericObject(vm_, callee_obj)) {
      return false;
    }
    if (vm::ArrayWrapper::IsIntArray(callee_obj)) {
      return false;
    }
    if (IsDataFlowCall(insn)) {
      return false;
    }
    return true;
  }
  return false;
}

bool InsnWalker::IsDataFlowCall(vm::Insn *insn) {
  vm::Method *method = GetCalleeMethod(insn);
  return method->GetAnnotation()->IsDataFlowEntry();
}

bool InsnWalker::IsExtStubCall(vm::Insn *insn) {
  vm::Method *method = GetCalleeMethod(insn);
  return method->GetAnnotation()->IsExtMethodStub() ||
    method->GetAnnotation()->IsExtFlowStub();
}

bool InsnWalker::IsExtFlowStubCall(vm::Insn *insn) {
  vm::Method *method = GetCalleeMethod(insn);
  return method->GetAnnotation()->IsExtFlowStub();
}

vm::Object *InsnWalker::GetObjByReg(vm::Register *reg) {
  return member_reg_to_obj_map_[reg];
}

vm::Object *InsnWalker::GetParentObjByObj(vm::Object *obj) {
  return member_to_owner_obj_map_[obj];
}

SharedResourceSet *InsnWalker::GetSharedResourceSet() {
  return shared_resource_set_;
}

ThreadSynth *InsnWalker::GetThreadSynth() {
  return thr_synth_;
}

}  // namespace synth
