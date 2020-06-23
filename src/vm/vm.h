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
  Thread *AddThreadFromMethod(Thread *parent, Object *object, Method *method,
			      int index);
  void Yield(Thread *thr);
  void GC();
  IntArray *GetDefaultMemory();

  Method *NewMethod(bool is_toplevel);
  Object *NewEmptyObject();
  Profile *GetProfile() const;
  unsigned int GetGlobalTickCount();
  void AddGlobalTickCount(unsigned int t);

  // root of the objects.
  Object *root_object_;
  // Kernel.
  Object *kernel_object_;
  Object *numerics_object_;
  Object *array_prototype_object_;
  Object *bool_type_;
  Object *default_mem_;

private:
  set<Thread*> threads_;
  set<Thread*> yielded_threads_;

  std::unique_ptr<Pool<Method> > methods_;
  std::unique_ptr<Profile> profile_;
  set<Object*> objects_;

  unsigned int tick_count_;

  void InstallBoolType();
  void InstallObjects();
};

}  // namespace vm

#endif  // _vm_vm_h_
