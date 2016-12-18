#include "synth/object_synth.h"

#include "iroha/i_design.h"
#include "synth/design_synth.h"
#include "synth/thread_synth.h"
#include "status.h"
#include "vm/thread_wrapper.h"

namespace synth {

ObjectSynth::ObjectSynth(vm::Object *obj,
			 const char *object_name,
			 const vector<string> &task_entries,
			 DesignSynth *design_synth)
  : obj_(obj), obj_name_(object_name),
    task_entries_(task_entries),
    design_synth_(design_synth), mod_(nullptr) {
}

ObjectSynth::~ObjectSynth() {
  STLDeleteValues(&threads_);
}

bool ObjectSynth::Synth() {
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
  return vm_;
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
    vector<string> entries;
    for (auto &callee_func_name : it.second) {
      entries.push_back(callee_func_name);
    }
    ObjectSynth *obj =
      new ObjectSynth(it.first, obj_names[it.first].c_str(), entries,
		      design_synth_);
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
