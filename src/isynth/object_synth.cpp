#include "isynth/object_synth.h"

#include "iroha/i_design.h"
#include "isynth/thread_synth.h"
#include "status.h"
#include "vm/thread_wrapper.h"

namespace isynth {

ObjectSynth::ObjectSynth(vm::VM *vm, vm::Object *obj,
			 const char *object_name,
			 const vector<string> &task_entries,
			 IDesign *design, ChannelSynth *channel)
  : vm_(vm), obj_(obj), obj_name_(object_name),
    task_entries_(task_entries),
    design_(design), channel_(channel), mod_(nullptr) {
}

ObjectSynth::~ObjectSynth() {
  STLDeleteValues(&threads_);
}

bool ObjectSynth::Synth() {
  mod_ = new IModule(design_, obj_name_);

  CollectThreads(mod_);

  for (auto *thr : threads_) {
    if (!thr->Synth()) {
      Status::os(Status::USER) << "Failed to synthesize object: " << obj_name_;
      MessageFlush::Get(Status::USER);
      return false;
    }
  }
  ProcessSubModuleCalls();
  for (auto *member_obj : member_objs_) {
    member_obj->Synth();
    member_obj->GetIModule()->SetParentModule(mod_);
  }

  design_->modules_.push_back(mod_);
  return true;
}

vm::VM *ObjectSynth::GetVM() const {
  return vm_;
}

vm::Object *ObjectSynth::GetObject() const {
  return obj_;
}

ChannelSynth *ObjectSynth::GetChannelSynth() const {
  return channel_;
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

void ObjectSynth::ProcessSubModuleCalls() {
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
      new ObjectSynth(vm_, it.first, obj_names[it.first].c_str(), entries,
		      design_, channel_);
    member_objs_.push_back(obj);
  }
}

IModule *ObjectSynth::GetIModule() {
  return mod_;
}

}  // namespace isynth
