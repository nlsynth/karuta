// -*- C++ -*-
//
// Thread Local Storage.
//
#ifndef _vm_tls_wrapper_h_
#define _vm_tls_wrapper_h_

#include "vm/common.h"

namespace vm {

class TlsWrapper {
 public:
  static bool IsTls(Object *obj);
  static bool IsTlsValue(Value *value);
  static void InjectTlsWrapper(VM *vm, Value *value);
  // null thread to get the base value.
  static Value *GetValue(Object *tls_obj, Thread *thr);
  static Object *Copy(VM *vm, Object *tls_obj);
  static Object *GetBaseObject(Object *tls_obj);
};

}  // namespace vm

#endif  // _vm_tls_wrapper_h_
