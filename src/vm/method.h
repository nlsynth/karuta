// -*- C++ -*-
#ifndef _vm_method_h_
#define _vm_method_h_

#include "vm/common.h"
#include "vm/register.h"  // for RegisterType

namespace vm {

// This can be either native implementation or in N language.
class Method {
public:
  Method(bool is_toplevel);
  ~Method();
  void Dump();
  void Dump(DumpStream &os);

  int GetNumArgRegisters() const;
  int GetNumReturnRegisters() const;
  const iroha::NumericWidth &GetNthArgWidth(int i);
  const char *AlternativeImplementation();
  const string &GetSynthName() const;
  void SetSynthName(const string &s);
  bool IsTopLevel() const;
  Annotation *GetAnnotation() const;

  typedef void (*method_func)(Thread *thr, Object *obj,
			      const vector<Value> &args);

  // native
  method_func method_fn_;
  const char *alt_impl_;
  // non native
  const fe::Method *parse_tree_;

  vector<Insn*> insns_;
  // Args. Returns. Locals.
  vector<Register*> method_regs_;
  vector<RegisterType> return_types_;

  // method_native.cpp
  static void InstallNativeRootObjectMethods(VM *vm, Object *obj);
  static void InstallNativeKernelObjectMethods(VM *vm, Object *obj);
  static Method *InstallNativeMethod(VM *vm, Object *obj, const char *name,
				     method_func func, const vector<RegisterType> &types);
  static Method *InstallNativeMethodWithAltImpl(VM *vm, Object *obj,
						const char *name,
						method_func func,
						const vector<RegisterType> &types,
						const char *alt);
  static void InstallEnvNativeMethods(VM *vm, Object *obj);

  static RegisterType ObjectType();
  static RegisterType BoolType(VM *vm);
  static RegisterType IntType(int w);

private:
  bool is_toplevel_;
  string synth_name_;
};

}  // namespace vm

#endif  // _vm_method_h_
