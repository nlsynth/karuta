// -*- C++ -*-
#ifndef _synth_design_synth_h_
#define _synth_design_synth_h_

#include "synth/common.h"

#include <map>

namespace synth {

class DesignSynth {
public:
  DesignSynth(vm::VM *vm, vm::Object *obj);
  ~DesignSynth();

  bool Synth();

  vm::VM *GetVM();
  ChannelSynth *GetChannelSynth();
  IDesign *GetIDesign();
  ObjectSynth *GetObjectSynth(vm::Object *obj);

private:
  vm::VM *vm_;
  vm::Object *obj_;
  std::unique_ptr<ChannelSynth> channel_synth_;
  std::unique_ptr<IDesign> i_design_;
  std::map<vm::Object *, ObjectSynth *> obj_synth_map_;
};

}  // namespace synth

#endif  // _synth_design_synth_h_
