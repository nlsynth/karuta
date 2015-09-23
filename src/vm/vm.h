// -*- C++ -*-
#ifndef _vm_vm_h_
#define _vm_vm_h_

#include <set>

using std::set;

#include "nli.h"

#include "pool.h"

namespace fe {
class Expr;
}  // namespace fe

namespace vm {

class IntArray;
class EnumType;
class Thread;
class Method;
class Object;

class VM {
public:
  VM();
  ~VM();

  void Run();
  void AddThreadFromMethod(Thread *parent, Method *method);
  IntArray *GetDefaultMemory();

  Method *NewMethod(bool is_toplevel);
  Object *NewObject();

  // root of the objects.
  Object *root_object_;
  // Kernel.
  Object *kernel_object_;
  // prototype of channel.
  Object *channel_object_;
  // prototype of thread.
  Object *thread_object_;
  // prototype of string.
  Object *string_object_;
  std::unique_ptr<EnumType> bool_type_;
private:
  set<Thread*> threads_;
  std::unique_ptr<IntArray> memory_;

  std::unique_ptr<Pool<Method> > methods_;
  std::unique_ptr<Pool<Object> > objects_;

  void InstallBoolType();
  void InstallObjects();
};

}  // namespace vm

#endif  // _vm_vm_h_
