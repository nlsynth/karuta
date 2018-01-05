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
#include "vm/tls_wrapper.h"

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
    Status::os(Status::USER_ERROR) << "Failed to find method: " << method_name_;
    MessageFlush::Get(Status::USER_ERROR);
    return false;
  }
  vm::Method *method = value->method_;

  auto *parse_tree = method->GetParseTree();
  if (parse_tree == nullptr) {
    return true;
  }
  compiler::Compiler::CompileMethod(vm_, obj_, method);
  if (method->IsCompileFailure()) {
    return false;
  }
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
  if (IsExtStubCall(insn)) {
    return;
  }
  if (IsSubObjCall(insn)) {
    RequestSubObj(callee_obj);
    // Add the entry point.
    DesignSynth *ds = thr_synth_->GetObjectSynth()->GetDesignSynth();
    ObjectSynth *callee_synth = ds->GetObjectSynth(callee_obj);
    callee_synth->AddTaskEntryName(sym_str(insn->label_));
  } else {
    // Normal method or numeric call.
    thr_synth_->RequestMethod(callee_obj,
			      sym_str(insn->label_));
  }
}

void MethodScanner::RequestSubObj(vm::Object *callee_obj) {
  DesignSynth *ds = thr_synth_->GetObjectSynth()->GetDesignSynth();
  (void) ds->GetObjectSynth(callee_obj);
}

void MethodScanner::MemberAccess(vm::Insn *insn) {
  vm::Value *value = obj_->LookupValue(insn->label_, false);
  CHECK(value);
  shared_resource_set_->AddMemberAccessor(thr_synth_, insn->label_, insn,
					  vm::TlsWrapper::IsTlsValue(value));
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
