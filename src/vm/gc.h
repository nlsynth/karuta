// -*- C++ -*-
#ifndef _vm_gc_h_
#define _vm_gc_h_

#include "vm/common.h"

#include <set>

using std::set;

namespace vm {

class GC {
public:
  GC(VM *vm, set<Thread *> *threads, set<Object *> *objs);

  static void Run(VM *vm, set<Thread *> *threads, set<Object *> *objs);

  void ScanObject(Object *obj);

private:
  void Collect();
  void AddRoot(Object *obj);
  void AddRootFromMethodFrame(MethodFrame *frame);
  void Scan();
  void Sweep();

  VM *vm_;
  set<Thread *> *threads_;
  set<Object *> *objs_;

  set<Object *> reachables_;
  set<Object *> frontier_;
};

}  // namespace vm

#endif  // _vm_gc_h_
