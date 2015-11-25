// -*- C++ -*-
#ifndef _vm_gc_h_
#define _vm_gc_h_

#include "nli.h"

#include "vm/vm.h"

namespace vm {

class GC {
public:
  static void Run(VM *vm, set<Thread *> *threads, set<Object *> *objs);
};

}  // namespace vm

#endif  // _vm_gc_h_
