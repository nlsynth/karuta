#include "vm/native_objects.h"

#include "synth/object_method_names.h"
#include "vm/method.h"
#include "vm/native_methods.h"
#include "vm/object.h"
#include "vm/vm.h"

namespace vm {

void NativeObjects::InstallNativeRootObjectMethods(VM *vm, Object *obj) {
  vector<RegisterType> rets;
  rets.push_back(ObjectType());
  InstallNativeMethod(vm, obj, "clone", &NativeMethods::Clone, rets);
  rets.clear();
  InstallNativeMethod(vm, obj, "dump", &NativeMethods::Dump, rets);
  InstallNativeMethod(vm, obj, "run", &NativeMethods::Run, rets);
}

void NativeObjects::InstallNativeKernelObjectMethods(VM *vm, Object *obj) {
  vector<RegisterType> rets;
  InstallNativeMethodWithAltImpl(vm, obj, "wait",
				 &NativeMethods::Wait, rets, "__wait");
  Method *m;
  m = InstallNativeMethod(vm, obj, "print", &NativeMethods::Print, rets);
  m->SetSynthName(synth::kPrint);
  m = InstallNativeMethod(vm, obj, "assert", &NativeMethods::Assert, rets);
  m->SetSynthName(synth::kAssert);
  InstallNativeMethod(vm, obj, "compile", &NativeMethods::Compile, rets);
  InstallNativeMethod(vm, obj, "__compile", &NativeMethods::Compile, rets);
  InstallNativeMethodWithAltImpl(vm, obj, "exit",
				 &NativeMethods::Exit, rets, "__exit");
  m = InstallNativeMethod(vm, obj, "main", &NativeMethods::Main, rets);
  m->SetSynthName(synth::kMain);
  rets.push_back(ObjectType());
  InstallNativeMethod(vm, obj, "new", &NativeMethods::New, rets);
  rets.clear();
  InstallNativeMethod(vm, obj, "setDump", &NativeMethods::SetDump, rets);
  InstallNativeMethod(vm, obj, "setIROutput",
		      &NativeMethods::SetIROutput, rets);
  InstallNativeMethod(vm, obj, "setIrohaPath",
		      &NativeMethods::SetIrohaPath, rets);
  InstallNativeMethod(vm, obj, "runIroha", &NativeMethods::RunIroha, rets);
  InstallNativeMethod(vm, obj, "synth", &NativeMethods::Synth, rets);
  InstallNativeMethod(vm, obj, "setSynthParam",
		      &NativeMethods::SetSynthParam, rets);
  InstallNativeMethod(vm, obj, "writeHdl", &NativeMethods::WriteHdl, rets);
  InstallNativeMethod(vm, obj, "yield", &NativeMethods::Yield, rets);
  rets.push_back(IntType(32));
  InstallNativeMethod(vm, obj, "widthof", &NativeMethods::WidthOf, rets);
}

Method *NativeObjects::InstallNativeMethodWithAltImpl(VM *vm, Object *obj,
						      const char *name,
						      Method::method_func func,
						      const vector<RegisterType> &ret_types,
						      const char *alt) {
  Method *method = vm->NewMethod(false /* not toplevel */);
  method->SetMethodFunc(func);
  method->SetAlternativeImplementation(alt);
  method->return_types_ = ret_types;
  Value value;
  value.type_ = Value::METHOD;
  value.method_ = method;
  obj->InstallValue(sym_lookup(name), value);
  return method;
}

Method *NativeObjects::InstallNativeMethod(VM *vm, Object *obj,
					   const char *name,
					   Method::method_func func,
					   const vector<RegisterType> &ret_types) {
  return InstallNativeMethodWithAltImpl(vm, obj, name, func, ret_types,
					nullptr);
}

void NativeObjects::InstallEnvNativeMethods(VM *vm, Object *env) {
  vector<RegisterType> rets;
  InstallNativeMethod(vm, env, "gc", &NativeMethods::GC, rets);
  InstallNativeMethod(vm, env, "clearProfile",
		      &NativeMethods::ClearProfile, rets);
  InstallNativeMethod(vm, env, "enableProfile",
		      &NativeMethods::EnableProfile, rets);
  InstallNativeMethod(vm, env, "disableProfile",
		      &NativeMethods::DisableProfile, rets);
  rets.push_back(BoolType(vm));
  InstallNativeMethod(vm, env, "isMain", &NativeMethods::IsMain, rets);
  rets.clear();
  rets.push_back(ObjectType());
  InstallNativeMethod(vm, env, "newTicker", &NativeMethods::GetTicker, rets);
}

Method *NativeObjects::FindMethod(Object *obj, Method::method_func func) {
  for (auto it : obj->members_) {
    Value &v = it.second;
    if (v.type_ == Value::METHOD && v.method_->GetMethodFunc() == func) {
      return v.method_;
    }
  }
  return nullptr;
}

RegisterType NativeObjects::ObjectType() {
  iroha::NumericWidth dw;
  return RegisterType(Value::OBJECT, nullptr, dw, sym_null, false);
}

RegisterType NativeObjects::BoolType(VM *vm) {
  iroha::NumericWidth dw;
  return RegisterType(Value::ENUM_ITEM, vm->bool_type_, dw,
		      sym_null, false);
}

RegisterType NativeObjects::IntType(int w) {
  return RegisterType(Value::NUM, nullptr,
		      iroha::NumericWidth(false, w), sym_null,
		      false);
}

}  // namespace vm
