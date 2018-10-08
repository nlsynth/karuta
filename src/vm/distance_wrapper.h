// -*- C++ -*-
#ifndef _vm_distance_wrapper_h_
#define _vm_distance_wrapper_h_

#include "vm/common.h"

namespace vm {

// Holds the distance to each member object if specified by an annotation.
class DistanceWrapper {
public:
  static void MaySetDistanceAnnotation(sym_t name, Annotation *an, VM *vm, Object *obj);
  static int GetDistance(VM *vm, Object *obj, sym_t name);

private:
  // This attaches an object to each normal object.
  static Object *GetAttachedDistanceObject(VM *vm, Object *owner_obj, bool create);
};

}  // namespace vm

#endif  // _vm_distance_wrapper_h_
