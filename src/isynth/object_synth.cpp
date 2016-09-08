#include "isynth/object_synth.h"

#include "iroha/i_design.h"
#include "isynth/thread_synth.h"
#include "status.h"

namespace isynth {

ObjectSynth::ObjectSynth(vm::VM *vm, vm::Object *obj,
			 const char *object_name,
			 IDesign *design)
  : vm_(vm), obj_(obj), obj_name_(object_name), design_(design) {
}

ObjectSynth::~ObjectSynth() {
}

bool ObjectSynth::Synth() {
  IModule *mod = new IModule(design_, obj_name_);
  ThreadSynth thr(this, "main", mod);
  if (!thr.Synth()) {
    Status::os(Status::USER) << "Failed to synthesize object: " << obj_name_;
    MessageFlush::Get(Status::USER);
    return false;
  }
  design_->modules_.push_back(mod);
  return true;
}

vm::VM *ObjectSynth::GetVM() {
  return vm_;
}

vm::Object *ObjectSynth::GetObject() {
  return obj_;
}

}  // namespace isynth
