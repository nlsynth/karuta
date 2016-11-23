// -*- C++ -*-
#ifndef _vm_dmodule_wrapper_h_
#define _vm_dmodule_wrapper_h_

#include "nli.h"

namespace synth {
class DModule;
}  // namespace synth
using namespace synth;

namespace vm {

class Object;
class VM;

class DModuleWrapper {
public:
  static bool IsDModule(Object *obj);
  static Object *NewDModuleWrapper(VM *vm, synth::DModule *module);
  static synth::DModule *GetDModule(Object *obj);
};


}  // namespace vm

#endif // _vm_dmodule_wrapper_h_
