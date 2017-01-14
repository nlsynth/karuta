// -*- C++ -*-
#ifndef _vm_thread_wrapper_h_
#define _vm_thread_wrapper_h_

#include "vm/common.h"

namespace vm {

class ThreadWrapper {
public:
  static Object *NewThreadWrapper(VM *vm, sym_t name, Method *method);
  static void Run(VM *vm, Object *obj);

  struct ThreadEntry {
    string method_name;
    string thread_name;
  };
  static void GetThreadMethods(Object *obj, vector<ThreadEntry> *methods);
};

}  // namespace vm

#endif  // _vm_thread_wrapper_h_
