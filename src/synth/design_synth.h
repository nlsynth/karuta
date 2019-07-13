// -*- C++ -*-
#ifndef _synth_design_synth_h_
#define _synth_design_synth_h_

#include "synth/common.h"

#include <map>
#include <set>

namespace synth {

class DesignSynth {
public:
  DesignSynth(vm::VM *vm, vm::Object *obj);
  ~DesignSynth();

  bool Synth();

  vm::VM *GetVM();
  IDesign *GetIDesign();
  ObjectSynth *GetObjectSynth(vm::Object *obj, bool cr);
  SharedResourceSet *GetSharedResourceSet();
  string GetObjectName(vm::Object *obj);
  int GetObjectDistance(vm::Object *src, vm::Object *dst);

private:
  bool SynthObjects();
  bool SynthObjRec(ObjectSynth *osynth);
  bool ScanObjs();
  void CollectScanRootObjRec(vm::Object *obj);
  void DeterminePrimaryThread();
  bool GetResetPolarity(Annotation *an);
  void SetSynthParams();

  vm::VM *vm_;
  vm::Object *root_obj_;
  std::unique_ptr<IDesign> i_design_;
  std::unique_ptr<SharedResourceSet> shared_resources_;
  std::unique_ptr<ObjectTree> obj_tree_;
  std::map<vm::Object *, ObjectSynth *> obj_synth_map_;
};

}  // namespace synth

#endif  // _synth_design_synth_h_
