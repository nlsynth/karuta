// -*- C++ -*-
#ifndef _isynth_object_synth_h_
#define _isynth_object_synth_h_

#include "isynth/common.h"

namespace isynth {

class ObjectSynth {
public:
  ObjectSynth(vm::VM *vm, vm::Object *obj, const char *object_name,
	      IDesign *design);
  virtual ~ObjectSynth();

  bool Synth();

  vm::VM *GetVM();
  vm::Object *GetObject();

private:
  vm::VM *vm_;
  vm::Object *obj_;
  const string obj_name_;
  IDesign *design_;
};

}  // namespace isynth

#endif  // _isynth_object_synth_h_
