#include "synth/object_synth.h"

#include "base/status.h"
#include "iroha/i_design.h"
#include "synth/design_synth.h"
#include "synth/thread_synth.h"
#include "vm/thread_wrapper.h"

namespace synth {

ObjectSynth::ObjectSynth(vm::Object *obj,
			 DesignSynth *design_synth)
  : obj_(obj),
    design_synth_(design_synth), mod_(nullptr), is_root_(false) {
}

ObjectSynth::~ObjectSynth() {
  STLDeleteValues(&threads_);
}

void ObjectSynth::Prepare(const char *obj_name, bool is_root) {
  obj_name_ = string(obj_name);
  // This method can be called multiple times, if multiple callers depend
  // on this object.
  if (mod_ != nullptr) {
    return;
  }
  mod_ = new IModule(design_synth_->GetIDesign(), obj_name_);
  design_synth_->GetIDesign()->modules_.push_back(mod_);
  is_root_ = is_root;
  CollectThreads(mod_);
}

void ObjectSynth::AddTaskEntryName(const string &task_entry) {
  ThreadSynth *th =
    new ThreadSynth(this, task_entry.c_str(), task_entry.c_str(), nullptr);
  th->SetIsTask(true);
  threads_.push_back(th);
}

bool ObjectSynth::Scan(bool *ok) {
  CHECK(!obj_name_.empty());
  *ok = true;
  int num_scanned = 0;
  for (auto *thr : threads_) {
    if (scanned_threads_.find(thr) != scanned_threads_.end()) {
      continue;
    }
    if (!thr->Scan()) {
      *ok = false;
      return false;
    }
    scanned_threads_.insert(thr);
    ++num_scanned;
  }
  // scanned threads may have added new dependencies.
  return num_scanned > 0;
}

bool ObjectSynth::Synth() {
  ThreadSynth *primary_thr = nullptr;
  for (auto *thr : threads_) {
    if (!thr->Synth()) {
      Status::os(Status::USER) << "Failed to synthesize object: " << obj_name_;
      MessageFlush::Get(Status::USER);
      return false;
    }
    if (thr->IsPrimary()) {
      primary_thr = thr;
    }
  }
  if (primary_thr != nullptr) {
    primary_thr->CollectUnclaimedMembers();
  }
  return true;
}

vm::VM *ObjectSynth::GetVM() const {
  return design_synth_->GetVM();
}

vm::Object *ObjectSynth::GetObject() const {
  return obj_;
}

ChannelSynth *ObjectSynth::GetChannelSynth() const {
  return design_synth_->GetChannelSynth();
}

void ObjectSynth::CollectThreads(IModule *mod) {
  vector<vm::ThreadWrapper::ThreadEntry> thread_entries;
  vm::ThreadWrapper::GetThreadMethods(obj_, &thread_entries);

  if (thread_entries.size() == 0 && is_root_) {
    ThreadSynth *ts = new ThreadSynth(this, "main", "main", obj_);
    // TODO set primary thread if there's no main.
    // (from DesignSynth after scan phase)
    ts->SetPrimary();
    threads_.push_back(ts);
  }
  for (auto &te : thread_entries) {
    threads_.push_back(new ThreadSynth(this, te.thread_name.c_str(),
				       te.method_name.c_str(), te.thread_obj));
  }
}

void ObjectSynth::ResolveTableCallsAll() {
  for (auto *thr : threads_) {
    vector<TableCall> &sub_obj_calls = thr->GetSubObjCalls();
    for (auto &c : sub_obj_calls) {
      ResolveTableCall(c);
    }
    vector<TableCall> &data_flow_calls = thr->GetDataFlowCalls();
    for (auto &c : data_flow_calls) {
      ResolveTableCall(c);
    }
  }
}

void ObjectSynth::ResolveTableCall(const TableCall &call) {
  ObjectSynth *callee_osynth =
    design_synth_->GetObjectSynth(call.callee_obj);
  ThreadSynth *callee_thr = callee_osynth->GetThreadByName(call.callee_func);
  ITable *callee_table = callee_thr->GetITable();
  if (call.is_sub_obj_call) {
    ThreadSynth::InjectSubModuleCall(call.call_state, call.call_insn,
				     callee_table);
  } else {
    ThreadSynth::InjectDataFlowCall(call.caller_thread,
				    call.call_state, call.call_insn,
				    callee_table);
  }
}

ThreadSynth *ObjectSynth::GetThreadByName(const string &name) {
  for (auto *thr : threads_) {
    if (thr->GetEntryMethodName() == name) {
      return thr;
    }
  }
  return nullptr;
}

IModule *ObjectSynth::GetIModule() {
  return mod_;
}

DesignSynth *ObjectSynth::GetDesignSynth() {
  return design_synth_;
}

}  // namespace synth
