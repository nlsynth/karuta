// -*- C++ -*-
#ifndef _vm_method_h_
#define _vm_method_h_

#include "vm/common.h"
#include "vm/register.h"  // for RegisterType

namespace vm {

// This can be either native implementation or in Karuta language.
class Method {
public:
  Method(bool is_toplevel);
  ~Method();

  void Dump();
  void Dump(DumpStream &os);

  typedef void (*method_func)(Thread *thr, Object *obj,
			      const vector<Value> &args);

  method_func GetMethodFunc() const;
  void SetMethodFunc(method_func func);
  const fe::Method *GetParseTree() const;
  void SetParseTree(const fe::Method *method);
  int GetNumArgRegisters() const;
  int GetNumReturnRegisters() const;
  const iroha::NumericWidth &GetNthArgWidth(int i);
  const char *AlternativeImplementation();
  void SetAlternativeImplementation(const char *alt);
  const string &GetSynthName() const;
  void SetSynthName(const string &s);
  bool IsTopLevel() const;
  Annotation *GetAnnotation() const;
  void SetCompileFailure();
  bool IsCompileFailure() const;

  vector<Insn*> insns_;
  // Args. Returns. Locals.
  vector<Register*> method_regs_;
  vector<RegisterType> return_types_;

  // method_native.cpp
  static void InstallNativeRootObjectMethods(VM *vm, Object *obj);
  static void InstallNativeKernelObjectMethods(VM *vm, Object *obj);
  static Method *InstallNativeMethod(VM *vm, Object *obj, const char *name,
				     method_func func,
				     const vector<RegisterType> &ret_types);
  static Method *InstallNativeMethodWithAltImpl(VM *vm, Object *obj,
						const char *name,
						method_func func,
						const vector<RegisterType> &ret_types,
						const char *alt);
  static void InstallEnvNativeMethods(VM *vm, Object *obj);

  static RegisterType ObjectType();
  static RegisterType BoolType(VM *vm);
  static RegisterType IntType(int w);

private:
  bool is_toplevel_;
  // native
  method_func method_fn_;
  // non native
  const fe::Method *parse_tree_;
  const char *alt_impl_;
  string synth_name_;
  bool compile_failed_;
};

}  // namespace vm

#endif  // _vm_method_h_
