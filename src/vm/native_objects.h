// -*- C++ -*-
#ifndef _vm_native_objects_h_
#define _vm_native_objects_h_

#include "vm/common.h"
#include "vm/method.h"    // for method_func
#include "vm/register.h"  // for RegisterType

namespace vm {

class NativeObjects {
 public:
  static void InstallNativeRootObjectMethods(VM *vm, Object *obj);
  static void InstallNativeKernelObjectMethods(VM *vm, Object *obj);
  static Method *InstallNativeMethod(VM *vm, Object *obj, const char *name,
                                     Method::method_func func,
                                     const vector<RegisterType> &ret_types);
  static Method *InstallNativeMethodWithAltImpl(
      VM *vm, Object *obj, const char *name, Method::method_func func,
      const vector<RegisterType> &ret_types, const char *alt);
  static void InstallEnvNativeMethods(VM *vm, Object *obj);
  static Method *FindMethod(Object *obj, Method::method_func func);

  static RegisterType ObjectType();
  static RegisterType BoolType(VM *vm);
  static RegisterType IntType(int w);
};

}  // namespace vm

#endif  // _vm_native_objects_h_
