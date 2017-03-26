#include "synth/object_synth.h"

#include "iroha/i_design.h"
#include "synth/design_synth.h"
#include "synth/thread_synth.h"
#include "status.h"
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

void ObjectSynth::Prepare(const char *name, bool is_root) {
  obj_name_ = string(name);
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

void ObjectSynth::AddEntryName(const string &task_entry) {
  ThreadSynth *th =
    new ThreadSynth(this, task_entry.c_str(), task_entry.c_str(), mod_);
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
  for (auto *thr : threads_) {
    if (!thr->Synth()) {
      Status::os(Status::USER) << "Failed to synthesize object: " << obj_name_;
      MessageFlush::Get(Status::USER);
      return false;
    }
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
    threads_.push_back(new ThreadSynth(this, "main", "main", mod));
  }
  for (auto &te : thread_entries) {
    threads_.push_back(new ThreadSynth(this, te.thread_name.c_str(), te.method_name.c_str(), mod));
  }
}

void ObjectSynth::ResolveSubModuleCalls() {
  for (auto *thr : threads_) {
    vector<SubObjCall> &calls = thr->GetSubObjCalls();
    for (auto &c : calls) {
      ObjectSynth *callee_osynth =
	design_synth_->GetObjectSynth(c.callee_obj);
      ThreadSynth *callee_thr = callee_osynth->GetThreadByName(c.callee_func);
      ITable *callee_table = callee_thr->GetITable();
      ThreadSynth::InjectSubModuleCall(c.call_state, c.call_insn, callee_table);
    }
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
