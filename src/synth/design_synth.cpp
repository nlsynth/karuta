#include "synth/design_synth.h"

#include "iroha/i_design.h"
#include "iroha/iroha.h"
#include "synth/channel_synth.h"
#include "synth/object_synth.h"

namespace synth {

DesignSynth::DesignSynth(vm::VM *vm, vm::Object *obj) : vm_(vm), obj_(obj) {
  channel_synth_.reset(new ChannelSynth);
  i_design_.reset(new IDesign);
}

DesignSynth::~DesignSynth() {
}

bool DesignSynth::Synth() {
  // Libraries of neon light assumes positive reset.
  iroha::ResourceParams *params = i_design_->GetParams();
  params->SetResetPolarity(true);

  const string &prefix = Env::GetModulePrefix();
  if (!prefix.empty()) {
    params->SetModuleNamePrefix(prefix + "_");
  }

  ObjectSynth *o = GetObjectSynth(obj_);
  o->Prepare("main");
  SynthObjRec(o);
  for (auto it : obj_synth_map_) {
    it.second->ResolveSubModuleCalls();
  }

  channel_synth_->Resolve(i_design_.get());

  DesignTool::Validate(i_design_.get());

  iroha::OptAPI *optimizer = iroha::Iroha::CreateOptimizer(i_design_.get());
  optimizer->ApplyPhase("clean_pseudo_resource");
  return true;
}

vm::VM *DesignSynth::GetVM() {
  return vm_;
}

ChannelSynth *DesignSynth::GetChannelSynth() {
  return channel_synth_.get();
}

IDesign *DesignSynth::GetIDesign() {
  return i_design_.get();
}

ObjectSynth *DesignSynth::GetObjectSynth(vm::Object *obj) {
  auto it = obj_synth_map_.find(obj);
  if (it != obj_synth_map_.end()) {
    return it->second;
  }
  ObjectSynth *osynth = new ObjectSynth(obj, this);
  obj_synth_map_[obj] = osynth;
  return osynth;
}

bool DesignSynth::SynthObjRec(ObjectSynth *osynth) {
  if (!osynth->Synth()) {
    return false;
  }
  for (ObjectSynth *child : obj_children_map_[osynth]) {
    if (!child->Synth()) {
      return false;
    }
    child->GetIModule()->SetParentModule(osynth->GetIModule());
  }
  return true;
}

void DesignSynth::AddChildObjSynth(ObjectSynth *parent, ObjectSynth *child) {
  obj_children_map_[parent].insert(child);
}

}  // namespace synth
