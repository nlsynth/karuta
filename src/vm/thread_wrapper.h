// -*- C++ -*-
#ifndef _vm_thread_wrapper_h_
#define _vm_thread_wrapper_h_

#include "vm/common.h"

namespace vm {

class ThreadWrapperData;

class ThreadWrapper {
public:
  static Object *NewThreadWrapper(VM *vm, sym_t method_name, bool is_soft);
  static void Run(VM *vm, Object *obj);
  static void DeleteThreadByMethodName(Object *obj, const string &name);

  struct ThreadEntry {
    string method_name;
    string thread_name;
    Object *thread_obj;
    bool is_soft_thread;
  };
  static void GetThreadEntryMethods(Object *obj, vector<ThreadEntry> *methods,
				    bool with_soft_thread);
private:
  static ThreadWrapperData *GetData(Value &value);
};

}  // namespace vm

#endif  // _vm_thread_wrapper_h_
