#include "vm/gc.h"

#include "vm/executor.h"
#include "vm/object.h"
#include "vm/thread.h"
#include "vm/vm.h"

namespace vm {

GC::GC(VM *vm, set<Thread *> *threads, set<Object *> *objs)
  : vm_(vm), threads_(threads), objs_(objs) {
}
  
void GC::Run(VM *vm, set<Thread *> *threads, set<Object *> *objs) {
  GC gc(vm, threads, objs);
  gc.Collect();
}

void GC::Collect() {
  AddRoot(vm_->root_object_);
  AddRoot(vm_->kernel_object_);

  for (Thread *th : *threads_) {
    vector<MethodFrame *> &frame_stack = th->MethodStack();
    for (MethodFrame *frame : frame_stack) {
      AddRootFromMethodFrame(frame);
    }
  }
  LOG(INFO) << "GC: Allocated size=" << objs_->size()
	    << " Root size=" << reachables_.size();
  frontier_ = reachables_;
  Scan();
  LOG(INFO) << "GC: Reachables size=" << reachables_.size();
  Sweep();
}

void GC::AddRoot(Object *obj) {
  if (obj) {
    reachables_.insert(obj);
  }
}

void GC::AddRootFromMethodFrame(MethodFrame *frame) {
  AddRoot(frame->obj_);
  for (Value &reg : frame->reg_values_) {
    AddRoot(reg.object_);
  }
  for (Value &reg : frame->returns_) {
    AddRoot(reg.object_);
  }
}

void GC::Scan() {
  while (frontier_.size() > 0) {
    Object *obj = *(frontier_.begin());
    frontier_.erase(obj);
    ScanObject(obj);
  }
}

void GC::ScanObject(Object *obj) {
  for (auto &it : obj->members_) {
    Value &value = it.second;
    if (value.object_) {
      Object *o = value.object_;
      if (reachables_.find(o) == reachables_.end()) {
	frontier_.insert(o);
	reachables_.insert(o);
      }
    }
  }
}

void GC::Sweep() {
  set<Object *> garbages;
  for (Object *o : *objs_) {
    if (reachables_.find(o) == reachables_.end()) {
      garbages.insert(o);
    }
  }
  LOG(INFO) << "GC: Garbages count=" << garbages.size();
  for (Object *o : garbages) {
    objs_->erase(o);
  }
}

}  // namespace vm
