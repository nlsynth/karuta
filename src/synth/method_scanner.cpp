#include "synth/method_scanner.h"

#include "base/status.h"
#include "compiler/compiler.h"
#include "synth/design_synth.h"
#include "synth/object_synth.h"
#include "synth/object_method.h"
#include "synth/shared_resource_set.h"
#include "synth/thread_synth.h"
#include "vm/insn.h"
#include "vm/method.h"
#include "vm/object.h"

namespace synth {

MethodScanner::MethodScanner(ThreadSynth *thr_synth,
			     vm::Object *obj,
			     const string &method_name)
  : InsnWalker(thr_synth, obj),
    thr_synth_(thr_synth), method_name_(method_name) {
}

bool MethodScanner::Scan() {
  vm::Value *value = obj_->LookupValue(sym_lookup(method_name_.c_str()), false);
  if (!value || value->type_ != vm::Value::METHOD) {
    Status::os(Status::USER) << "Failed to find method: " << method_name_;
    MessageFlush::Get(Status::USER);
    return false;
  }
  vm::Method *method = value->method_;

  if (method->parse_tree_ == nullptr) {
    return true;
  }
  compiler::Compiler::CompileMethod(vm_, obj_,
				    method->parse_tree_,
				    method);
  for (size_t i = 0; i < method->insns_.size(); ++i) {
    ScanInsn(method->insns_[i]);
  }
  return true;
}

void MethodScanner::ScanInsn(vm::Insn *insn) {
  switch(insn->op_) {
  case vm::OP_FUNCALL:
    Funcall(insn);
    break;
  case vm::OP_LOAD_OBJ:
    InsnWalker::LoadObj(insn);
    break;
  case vm::OP_MEMBER_READ:
    InsnWalker::MaybeLoadMemberObject(insn);
    MemberAccess(insn);
    break;
  case vm::OP_MEMBER_WRITE:
    MemberAccess(insn);
    break;
  case vm::OP_ARRAY_READ:
  case vm::OP_ARRAY_WRITE:
    ArrayAccess(insn);
    break;
  default:
    break;
  }
}

void MethodScanner::Funcall(vm::Insn *insn) {
  if (IsNativeFuncall(insn)) {
    NativeFuncall(insn);
    return;
  }
  vm::Object *callee_obj = GetCalleeObject(insn);
  if (IsDataFlowCall(insn)) {
    if (callee_obj != obj_) {
      RequestSubObj(callee_obj);
    }
    return;
  }
  if (IsSubObjCall(insn)) {
    RequestSubObj(callee_obj);
    // Add the entry point.
    DesignSynth *ds = thr_synth_->GetObjectSynth()->GetDesignSynth();
    ObjectSynth *callee_synth = ds->GetObjectSynth(callee_obj);
    callee_synth->AddTaskEntryName(string(sym_cstr(insn->label_)));
  } else {
    // Normal method or numeric call.
    thr_synth_->RequestMethod(callee_obj,
			      string(sym_cstr(insn->label_)));
  }
}

void MethodScanner::RequestSubObj(vm::Object *callee_obj) {
  DesignSynth *ds = thr_synth_->GetObjectSynth()->GetDesignSynth();
  ObjectSynth *callee_synth = ds->GetObjectSynth(callee_obj);
  ObjectSynth *this_synth = ds->GetObjectSynth(obj_);
  ds->AddChildObjSynth(this_synth, callee_synth);

  vector<sym_t> names;
  obj_->LookupMemberNames(callee_obj, &names);
  CHECK(names.size() > 0);
  callee_synth->Prepare(sym_cstr(names[0]), false);
}

void MethodScanner::MemberAccess(vm::Insn *insn) {
  shared_resource_set_->AddMemberAccessor(thr_synth_, insn->label_, insn);
}

void MethodScanner::ArrayAccess(vm::Insn *insn) {
  vm::Object *array_obj = member_reg_to_obj_map_[insn->obj_reg_];
  CHECK(array_obj);
  shared_resource_set_->AddObjectAccessor(thr_synth_, array_obj, insn, "");
}

void MethodScanner::NativeFuncall(vm::Insn *insn) {
  ObjectMethod m(nullptr, this, nullptr, insn);
  m.Scan();
}

}  // namespace synth
