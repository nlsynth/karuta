// -*- C++ -*-
#ifndef _vm_numeric_object_h_
#define _vm_numeric_object_h_

#include "vm/common.h"
#include "vm/opcode.h"

namespace vm {

class NumericObject {
public:
  static Object *Get(VM *vm, sym_t name);
  static bool IsNumericObject(VM *vm, Object *obj);
  static int Width(Object *obj);
  static sym_t GetMethodName(Object *obj, enum OpCode op);
};

}  // namespace vm

#endif  // _vm_numeric_object_h_
