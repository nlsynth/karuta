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
    design_synth_(design_synth), mod_(nullptr) {
}

ObjectSynth::~ObjectSynth() {
  STLDeleteValues(&threads_);
}

void ObjectSynth::SetName(const char *name) {
  obj_name_ = string(name);
}

void ObjectSynth::AddEntryName(const string &task_entry) {
  task_entries_.insert(task_entry);
}

bool ObjectSynth::Synth() {
  CHECK(!obj_name_.empty());
  mod_ = new IModule(design_synth_->GetIDesign(), obj_name_);

  CollectThreads(mod_);

  for (auto *thr : threads_) {
    if (!thr->Synth()) {
      Status::os(Status::USER) << "Failed to synthesize object: " << obj_name_;
      MessageFlush::Get(Status::USER);
      return false;
    }
  }
  CollectSubModuleCalls();
  for (auto *member_obj : member_objs_) {
    member_obj->Synth();
    member_obj->GetIModule()->SetParentModule(mod_);
  }
  ResolveSubModuleCalls();

  design_synth_->GetIDesign()->modules_.push_back(mod_);
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

  if (thread_entries.size() == 0 && task_entries_.size() == 0) {
    threads_.push_back(new ThreadSynth(this, "main", "main", mod));
  }
  for (auto &te : thread_entries) {
    threads_.push_back(new ThreadSynth(this, te.thread_name.c_str(), te.method_name.c_str(), mod));
  }
  for (auto &te : task_entries_) {
    ThreadSynth *th = new ThreadSynth(this, te.c_str(), te.c_str(), mod);
    th->SetIsTask(true);
    threads_.push_back(th);
  }
}

void ObjectSynth::CollectSubModuleCalls() {
  map<vm::Object *, string> obj_names;
  map<vm::Object *, set<string> > callees;
  for (auto *thr : threads_) {
    vector<SubObjCall> &calls = thr->GetSubObjCalls();
    for (auto &c : calls) {
      callees[c.callee_obj].insert(c.callee_func);
      obj_names[c.callee_obj] = c.callee_obj_name;
    }
  }
  for (auto it : callees) {
    ObjectSynth *obj =
      new ObjectSynth(it.first, design_synth_);
    obj->SetName(obj_names[it.first].c_str());
    for (auto &callee_func_name : it.second) {
      obj->AddEntryName(callee_func_name);
    }
    member_objs_.push_back(obj);
  }
}

void ObjectSynth::ResolveSubModuleCalls() {
  map<vm::Object *, ObjectSynth *> synth_map;
  for (auto *o : member_objs_) {
    synth_map[o->GetObject()] = o;
  }
  for (auto *thr : threads_) {
    vector<SubObjCall> &calls = thr->GetSubObjCalls();
    for (auto &c : calls) {
      ObjectSynth *callee_osynth = synth_map[c.callee_obj];
      ThreadSynth *callee_thr = callee_osynth->GetThreadByName(c.callee_func);
      ITable *callee_table = callee_thr->GetITable();
      ThreadSynth::InjectSubModuleCall(c.call_state, c.call_insn, callee_table);
    }
  }
}

ThreadSynth *ObjectSynth::GetThreadByName(const string &name) {
  for (auto *thr : threads_) {
    if (thr->GetMethodName() == name) {
      return thr;
    }
  }
  return nullptr;
}

IModule *ObjectSynth::GetIModule() {
  return mod_;
}

}  // namespace synth
