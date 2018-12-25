// -*- C++ -*-
#ifndef _vm_object_util_h_
#define _vm_object_util_h_

#include "vm/common.h"

namespace vm {

class ObjectUtil {
public:
  static int GetAddressWidth(Object *obj);
  static void SetAddressWidth(Object *obj, int width);
};

}  // namespace vm

#endif  // _vm_object_util_h_
