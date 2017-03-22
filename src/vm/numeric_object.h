// -*- C++ -*-
#ifndef _vm_numeric_object_h_
#define _vm_numeric_object_h_

#include "vm/common.h"

namespace vm {

class NumericObject {
public:
  static Object *Get(VM *vm, sym_t name);
  static int Width(Object *obj);
};

}  // namespace vm

#endif  // _vm_numeric_object_h_
