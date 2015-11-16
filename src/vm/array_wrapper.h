// -*- C++ -*-
#ifndef _vm_array_wrapper_h_
#define _vm_array_wrapper_h_

#include "nli.h"

namespace numeric {
class Width;
}  // namespace numeric

namespace vm {

class IntArray;
class Object;
class VM;

class ArrayWrapper {
public:
  static bool IsObjectArray(Object *obj);
  static bool IsIntArray(Object *obj);
  static string ToString(Object *obj);

  static Object *NewObjectArrayWrapper(VM *vm, int size);
  static Object *NewIntArrayWrapper(VM *vm, int size,
				    const numeric::Width *width);
  static Object *Copy(VM *vm, Object *obj);

  static Object *Get(Object *obj, int nth);
  static void Set(Object *obj, int nth, Object *elem);
  static IntArray *GetIntArray(Object *obj);
};

}  // namespace vm

#endif // _vm_array_wrapper_h_
