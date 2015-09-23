// -*- C++ -*-
#ifndef _vm_dmodule_wrapper_h_
#define _vm_dmodule_wrapper_h_

#include "nli.h"

namespace dfg {
class DModule;
}  // namespace dfg

namespace vm {

class Object;
class VM;

class DModuleWrapper {
public:
  static bool IsDModule(Object *obj);
  static Object *NewDModuleWrapper(VM *vm, dfg::DModule *module);
  static dfg::DModule *GetDModule(Object *obj);
};


}  // namespace vm

#endif // _vm_dmodule_wrapper_h_
