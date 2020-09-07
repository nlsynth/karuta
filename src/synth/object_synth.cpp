#include "synth/object_synth.h"

#include "base/status.h"
#include "base/stl_util.h"
#include "iroha/iroha.h"
#include "karuta/annotation.h"
#include "synth/design_synth.h"
#include "synth/thread_synth.h"
#include "vm/method.h"
#include "vm/object.h"
#include "vm/thread_wrapper.h"

namespace synth {

ObjectSynth::ObjectSynth(vm::Object *obj, DesignSynth *design_synth,
                         bool is_root, const string &name)
    : obj_(obj),
      design_synth_(design_synth),
      mod_(nullptr),
      is_root_(is_root),
      obj_name_(name) {
  mod_ = new IModule(design_synth_->GetIDesign(), obj_name_);
  design_synth_->GetIDesign()->modules_.push_back(mod_);
  CollectThreads(mod_);
}

ObjectSynth::~ObjectSynth() { STLDeleteValues(&threads_); }

bool ObjectSynth::HasSynthesizable(vm::Object *obj) {
  // Either runnable threads or visible resource.
  vector<vm::ThreadWrapper::ThreadEntry> thread_entries;
  vm::ThreadWrapper::GetThreadEntryMethods(obj, &thread_entries, false);
  if (thread_entries.size() > 0) {
    return true;
  }
  return ThreadSynth::HasExtVisibleResource(obj);
}

void ObjectSynth::AddTaskEntryName(const string &task_entry) {
  if (task_entry_names_.find(task_entry) != task_entry_names_.end()) {
    return;
  }
  ThreadSynth *th =
      new ThreadSynth(this, task_entry.c_str(), task_entry.c_str(), nullptr, 0);
  th->SetIsTask(true);
  threads_.push_back(th);
  task_entry_names_.insert(task_entry);
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
      Status::os(Status::USER_ERROR)
          << "Failed to synthesize object: " << obj_name_;
      MessageFlush::Get(Status::USER_ERROR);
      return false;
    }
    if (thr->IsPrimary()) {
      primary_thr = thr;
    }
  }
  CHECK(primary_thr != nullptr);
  primary_thr->CollectUnclaimedMembers();
  return true;
}

vm::VM *ObjectSynth::GetVM() const { return design_synth_->GetVM(); }

vm::Object *ObjectSynth::GetObject() const { return obj_; }

void ObjectSynth::CollectThreads(IModule *mod) {
  vector<vm::ThreadWrapper::ThreadEntry> thread_entries;
  vm::ThreadWrapper::GetThreadEntryMethods(obj_, &thread_entries, false);

  vector<string> ext_entries;
  CollectExtEntries(&ext_entries);

  // Falls back to native main().
  if (thread_entries.size() == 0) {
    ThreadSynth *ts = new ThreadSynth(this, "main", "main", obj_, 0);
    threads_.push_back(ts);
  }
  for (auto &te : thread_entries) {
    threads_.push_back(new ThreadSynth(this, te.thread_name, te.method_name,
                                       te.thread_obj, te.index));
  }
  for (string &ee : ext_entries) {
    threads_.push_back(new ThreadSynth(this, ee, ee, obj_, 0));
  }
}

void ObjectSynth::ResolveTableCallsAll() {
  for (auto *thr : threads_) {
    vector<TableCall> &table_calls = thr->GetTableCalls();
    for (auto &c : table_calls) {
      ResolveTableCall(c);
    }
  }
}

void ObjectSynth::ResolveTableCall(const TableCall &call) {
  ObjectSynth *callee_osynth =
      design_synth_->GetObjectSynth(call.callee_obj, true);
  ThreadSynth *callee_thr = callee_osynth->GetThreadByName(call.callee_func);
  ITable *callee_table = nullptr;
  if (callee_thr != nullptr) {
    callee_table = callee_thr->GetITable();
  }
  IInsn *insn = nullptr;
  if (call.is_sub_obj_call) {
    insn = ThreadSynth::InjectSubModuleCall(call.call_state, call.call_insn,
                                            callee_table);
  } else if (call.is_data_flow_call) {
    bool no_wait = call.callee_method->GetAnnotation()->IsNoWait();
    insn =
        ThreadSynth::InjectDataFlowCall(call.caller_thread, call.call_state,
                                        call.call_insn, callee_table, no_wait);
  } else {
    CHECK(call.is_ext_stub_call);
    string name = call.callee_method->GetAnnotation()->GetName();
    if (name.empty()) {
      name = call.callee_func;
    }
    insn = ThreadSynth::InjectExtStubCall(call.call_state, call.call_insn, name,
                                          call.is_ext_flow_stub_call);
  }
  if (insn == nullptr) {
    Status::os(Status::USER_ERROR)
        << "Failed to synthesize function call: " << call.callee_func;
    MessageFlush::Get(Status::USER_ERROR);
    return;
  }
  int d = design_synth_->GetObjectDistance(obj_, call.callee_obj);
  if (d > 0) {
    // Sets distance to every related resources.
    IResource *res = insn->GetResource();
    res->GetParams()->SetDistance(d);
    IResource *parent_res = res->GetParentResource();
    if (parent_res != nullptr) {
      parent_res->GetParams()->SetDistance(d);
    }
    for (IInsn *dinsn : insn->depending_insns_) {
      dinsn->GetResource()->GetParams()->SetDistance(d);
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

IModule *ObjectSynth::GetIModule() { return mod_; }

DesignSynth *ObjectSynth::GetDesignSynth() { return design_synth_; }

const vector<ThreadSynth *> &ObjectSynth::GetAllThreads() const {
  return threads_;
}

const string &ObjectSynth::GetName() const { return obj_name_; }

void ObjectSynth::DeterminePrimaryThread() {
  for (auto *thr : threads_) {
    if (thr->GetEntryMethodName() == "main") {
      thr->SetPrimary();
      return;
    }
  }
  if (threads_.size() == 1) {
    threads_[0]->SetPrimary();
    return;
  }
  // TODO: fix ordering instability.
  threads_[0]->SetPrimary();
}

void ObjectSynth::CollectExtEntries(vector<string> *entries) {
  map<sym_t, vm::Method *> member_methods;
  obj_->GetAllMemberMethods(&member_methods);
  for (auto it : member_methods) {
    vm::Method *method = it.second;
    if (method->GetAnnotation()->IsExtEntry()) {
      entries->push_back(sym_str(it.first));
    }
  }
}

}  // namespace synth
