// -*- C++ -*-
#ifndef _vm_enum_type_wrapper_h_
#define _vm_enum_type_wrapper_h_

#include "vm/common.h"

namespace vm {

class EnumTypeWrapper {
 public:
  static bool IsEnumType(Object *obj);
  static Object *NewEnumTypeWrapper(VM *vm, sym_t name);
  static void AddItem(Object *obj, sym_t item);
  static string GetName(const Object *obj);
  static int GetNumItems(const Object *obj);
};

}  // namespace vm

#endif  // _vm_enum_type_wrapper_h_
