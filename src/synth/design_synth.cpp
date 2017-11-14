#include "synth/design_synth.h"

#include <list>

#include "base/stl_util.h"
#include "iroha/i_design.h"
#include "iroha/iroha.h"
#include "synth/shared_resource_set.h"
#include "synth/object_synth.h"
#include "synth/object_tree.h"

namespace synth {

DesignSynth::DesignSynth(vm::VM *vm, vm::Object *obj)
  : vm_(vm), root_obj_(obj) {
  i_design_.reset(new IDesign);
  shared_resources_.reset(new SharedResourceSet);
  obj_tree_.reset(new ObjectTree(obj));
}

DesignSynth::~DesignSynth() {
  STLDeleteSecondElements(&obj_synth_map_);
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

  DesignTool::Validate(i_design_.get());

  iroha::OptAPI *optimizer = iroha::Iroha::CreateOptimizer(i_design_.get());
  optimizer->ApplyPhase("clean_pseudo_resource");
  return true;
}

bool DesignSynth::SynthObjects() {
  obj_tree_->Build();
  // Pass 1: Scan.
  ObjectSynth *o = GetObjectSynth(root_obj_);
  CollectScanRootObjRec(root_obj_);
  if (!ScanObjs()) {
    return false;
  }
  DeterminePrimaryThread();
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

IDesign *DesignSynth::GetIDesign() {
  return i_design_.get();
}

ObjectSynth *DesignSynth::GetObjectSynth(vm::Object *obj) {
  auto it = obj_synth_map_.find(obj);
  if (it != obj_synth_map_.end()) {
    return it->second;
  }
  bool is_root = (obj == root_obj_);
  string name = obj_tree_->GetObjectName(obj);
  if (name.empty()) {
    name = "main";
  }
  ObjectSynth *osynth = new ObjectSynth(obj, this, is_root, name);
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

void DesignSynth::CollectScanRootObjRec(vm::Object *obj) {
  if (obj_synth_map_.find(obj) == obj_synth_map_.end()) {
    if (ObjectSynth::HasResource(obj)) {
      (void) GetObjectSynth(obj);
    }
  }
  auto m = obj_tree_->GetChildObjects(obj);
  for (auto it : m) {
    CollectScanRootObjRec(it.first);
  }
}

void DesignSynth::DeterminePrimaryThread() {
  for (auto it : obj_synth_map_) {
    it.second->DeterminePrimaryThread();
  }
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
