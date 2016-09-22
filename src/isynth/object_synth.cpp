#include "isynth/object_synth.h"

#include "iroha/i_design.h"
#include "isynth/thread_synth.h"
#include "status.h"
#include "vm/thread_wrapper.h"

namespace isynth {

ObjectSynth::ObjectSynth(vm::VM *vm, vm::Object *obj,
			 const char *object_name,
			 IDesign *design, ChannelSynth *channel)
  : vm_(vm), obj_(obj), obj_name_(object_name),
    design_(design), channel_(channel) {
}

ObjectSynth::~ObjectSynth() {
  STLDeleteValues(&threads_);
}

bool ObjectSynth::Synth() {
  IModule *mod = new IModule(design_, obj_name_);

  CollectThreads(mod);

  for (auto *thr : threads_) {
    if (!thr->Synth()) {
      Status::os(Status::USER) << "Failed to synthesize object: " << obj_name_;
      MessageFlush::Get(Status::USER);
      return false;
    }
  }
  design_->modules_.push_back(mod);
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

  if (thread_entries.size() == 0) {
    threads_.push_back(new ThreadSynth(this, "main", "main", mod));
  } else {
    for (auto &te : thread_entries) {
      threads_.push_back(new ThreadSynth(this, te.thread_name.c_str(), te.method_name.c_str(), mod));
    }
  }
}

}  // namespace isynth
