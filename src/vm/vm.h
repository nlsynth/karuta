// -*- C++ -*-
#ifndef _vm_vm_h_
#define _vm_vm_h_

#include "pool.h"
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
  void GC();
  IntArray *GetDefaultMemory();

  Method *NewMethod(bool is_toplevel);
  Object *NewObject();

  // root of the objects.
  Object *root_object_;
  // Kernel.
  Object *kernel_object_;
  std::unique_ptr<EnumType> bool_type_;

private:
  set<Thread*> threads_;
  std::unique_ptr<IntArray> memory_;

  std::unique_ptr<Pool<Method> > methods_;
  set<Object*> objects_;

  void InstallBoolType();
  void InstallObjects();
};

}  // namespace vm

#endif  // _vm_vm_h_
