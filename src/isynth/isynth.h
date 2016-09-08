// -*- C++ -*-
#ifndef _isynth_isynth_h_
#define _isynth_isynth_h_

#include "nli.h"

namespace vm {
class Object;
class VM;
}  // namespace vm

namespace isynth {

class ISynth {
public:
  static bool Synthesize(vm::VM *vm, vm::Object *obj, const string &ofn);
};

}  // namespace isynth

#endif  // _isynth_isynth_h_
