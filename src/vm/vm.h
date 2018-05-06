// -*- C++ -*-
#ifndef _vm_vm_h_
#define _vm_vm_h_

#include "base/pool.h"
#include "vm/common.h"

#include <set>

using std::set;

namespace vm {

class VM {
public:
  VM();
  ~VM();

  void Run();
  void AddThreadFromMethod(Thread *parent, Object *object, Method *method);
  void Yield(Thread *thr);
  void GC();
  IntArray *GetDefaultMemory();
  int GetAddressSpaceWidth(Object *obj);

  Method *NewMethod(bool is_toplevel);
  Object *NewObject();

  // root of the objects.
  Object *root_object_;
  // Kernel.
  Object *kernel_object_;
  Object *numerics_object_;
  Object *array_object_;
  Object *bool_type_;
  Object *default_mem_;

private:
  set<Thread*> threads_;
  set<Thread*> yielded_threads_;

  std::unique_ptr<Pool<Method> > methods_;
  set<Object*> objects_;

  void InstallBoolType();
  void InstallObjects();
};

}  // namespace vm

#endif  // _vm_vm_h_
