// -*- C++ -*-
#ifndef _vm_method_h_
#define _vm_method_h_

#include "nli.h"
#include "vm/register.h"  // for RegisterType
#include "vm/value.h"

class DumpStream;
class Thread;

namespace fe {
class Method;
}  // namespace fe

namespace vm {

class Insn;
class Object;
class VM;

// This can be either native implementation or in N language.
class Method {
public:
  Method(bool is_toplevel);
  ~Method();
  void Dump();
  void Dump(DumpStream &os);

  int GetNumReturnRegisters();
  const numeric::Width *GetNthArgWidth(int i);
  const char *AlternativeImplementation();

  typedef void (*method_func)(Thread *thr, Object *obj,
			      const vector<Value> &args);

  bool is_toplevel_;

  // native
  method_func method_fn_;
  const char *alt_impl_;
  // non native
  const fe::Method *parse_tree_;

  vector<Insn*> insns_;
  vector<Register*> method_regs_;
  vector<RegisterType> return_types_;

  // method_native.cpp
  static void InstallNativeRootObjectMethods(VM *vm, Object *obj);
  static void InstallNativeKernelObjectMethods(VM *vm, Object *obj);
  static void InstallNativeMethod(VM *vm, Object *obj, const char *name,
				  method_func func, const vector<RegisterType> &types);
  static void InstallNativeMethodWithAltImpl(VM *vm, Object *obj, const char *name,
					     method_func func, const vector<RegisterType> &types,
					     const char *alt);
  static void InstallEnvNativeMethods(VM *vm, Object *obj);

  static RegisterType ObjectType();
  static RegisterType BoolType(VM *vm);
  static RegisterType IntType(int w);
};

}  // namespace vm

#endif  // _vm_method_h_
