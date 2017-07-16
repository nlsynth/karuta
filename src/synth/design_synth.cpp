#include "synth/design_synth.h"

#include <list>

#include "iroha/i_design.h"
#include "iroha/iroha.h"
#include "synth/channel_synth.h"
#include "synth/shared_resource_set.h"
#include "synth/object_synth.h"
#include "synth/object_tree.h"

namespace synth {

DesignSynth::DesignSynth(vm::VM *vm, vm::Object *obj)
  : vm_(vm), root_obj_(obj) {
  channel_synth_.reset(new ChannelSynth);
  i_design_.reset(new IDesign);
  shared_resources_.reset(new SharedResourceSet);
  obj_tree_.reset(new ObjectTree(obj));
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

  if (!SynthObjects()) {
    return false;
  }

  channel_synth_->Resolve(i_design_.get());

  DesignTool::Validate(i_design_.get());

  iroha::OptAPI *optimizer = iroha::Iroha::CreateOptimizer(i_design_.get());
  optimizer->ApplyPhase("clean_pseudo_resource");
  return true;
}

bool DesignSynth::SynthObjects() {
  obj_tree_->Build();
  ObjectSynth *o = GetObjectSynth(root_obj_);
  o->Prepare("main", true /* is_root */);
  // Pass 1: Scan.
  if (!ScanObjs()) {
    return false;
  }
  shared_resources_->DetermineOwnerThreadAll();
  // Pass 2: Synth.
  if (!SynthObjRec(o)) {
    return false;
  }
  shared_resources_->ResolveResourceAccessors();
  for (auto it : obj_synth_map_) {
    it.second->ResolveTableCallsAll();
  }
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
  string name = obj_tree_->GetObjectName(obj);
  if (!name.empty()) {
    osynth->Prepare(name.c_str(), false);
  }
  obj_synth_map_[obj] = osynth;
  return osynth;
}

SharedResourceSet *DesignSynth::GetSharedResourceSet() {
  return shared_resources_.get();
}

string DesignSynth::GetObjectName(vm::Object *obj) {
  return obj_tree_->GetObjectName(obj);
}

bool DesignSynth::ScanObjs() {
  int num_scan;
  // Loop until every objects stops to request rescan.
  do {
    num_scan = 0;
    map<vm::Object *, ObjectSynth *> m = obj_synth_map_;
    for (auto it : m) {
      bool ok = true;
      ObjectSynth *osynth = it.second;
      if (osynth->Scan(&ok)) {
	++num_scan;
      }
      if (!ok) {
	return false;
      }
    }
  } while (num_scan > 0);
  return true;
}

bool DesignSynth::SynthObjRec(ObjectSynth *osynth) {
  if (!osynth->Synth()) {
    return false;
  }
  auto m = obj_tree_->GetChildObjects(osynth->GetObject());
  for (auto it : m) {
    vm::Object *cobj = it.first;
    auto cit = obj_synth_map_.find(cobj);
    if (cit != obj_synth_map_.end()) {
      ObjectSynth *csynth = cit->second;
      if (!SynthObjRec(csynth)) {
	return false;
      }
      csynth->GetIModule()->SetParentModule(osynth->GetIModule());
    }
  }
  return true;
}

}  // namespace synth
