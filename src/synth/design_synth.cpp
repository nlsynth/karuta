#include "synth/design_synth.h"

#include <list>

#include "iroha/i_design.h"
#include "iroha/iroha.h"
#include "synth/channel_synth.h"
#include "synth/shared_resource_set.h"
#include "synth/object_synth.h"

namespace synth {

DesignSynth::DesignSynth(vm::VM *vm, vm::Object *obj) : vm_(vm), obj_(obj) {
  channel_synth_.reset(new ChannelSynth);
  i_design_.reset(new IDesign);
  shared_resources_.reset(new SharedResourceSet);
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
  o->Prepare("main", true);
  // Pass 1: Scan.
  if (!ScanObjs()) {
    return false;
  }
  shared_resources_->ResolveResourceTypes();
  FixupObjTree(o);
  // Pass 2: Synth.
  if (!SynthObjRec(o)) {
    return false;
  }
  shared_resources_->ResolveResourceAccessors();
  for (auto it : obj_synth_map_) {
    it.second->ResolveTableCallsAll();
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

SharedResourceSet *DesignSynth::GetSharedResourceSet() {
  return shared_resources_.get();
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
  for (ObjectSynth *child : obj_children_map_[osynth]) {
    if (!SynthObjRec(child)) {
      return false;
    }
    child->GetIModule()->SetParentModule(osynth->GetIModule());
  }
  return true;
}

void DesignSynth::AddChildObjSynth(ObjectSynth *parent, ObjectSynth *child) {
  obj_children_map_[parent].insert(child);
}

void DesignSynth::FixupObjTree(ObjectSynth *root) {
  std::list<ObjectSynth *> q;
  set<ObjectSynth *> seen;
  q.push_back(root);
  // BFS traversal.
  while (q.size() > 0) {
    ObjectSynth *o = *(q.begin());
    seen.insert(o);
    q.pop_front();
    set<ObjectSynth *> children = obj_children_map_[o];
    for (ObjectSynth *child : children) {
      if (seen.find(child) != seen.end()) {
	// Erase this child as it is already seen.
	obj_children_map_[o].erase(child);
      } else {
	q.push_back(child);
      }
    }
  }
}

}  // namespace synth
