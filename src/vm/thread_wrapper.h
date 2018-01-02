// -*- C++ -*-
#ifndef _vm_thread_wrapper_h_
#define _vm_thread_wrapper_h_

#include "vm/common.h"

namespace vm {

class ThreadWrapper {
public:
  static Object *NewThreadWrapper(VM *vm, sym_t method_name);
  static void Run(VM *vm, Object *obj);

  struct ThreadEntry {
    string method_name;
    string thread_name;
    Object *thread_obj;
  };
  static void GetThreadMethods(Object *obj, vector<ThreadEntry> *methods);
};

}  // namespace vm

#endif  // _vm_thread_wrapper_h_
