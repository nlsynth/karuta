// -*- C++ -*-
#ifndef _synth_isynth_h_
#define _synth_isynth_h_

#include "nli.h"

namespace vm {
class Object;
class VM;
}  // namespace vm

namespace synth {

class ISynth {
public:
  static bool Synthesize(vm::VM *vm, vm::Object *obj, const string &ofn);
};

}  // namespace synth

#endif  // _synth_isynth_h_
