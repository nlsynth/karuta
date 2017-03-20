#include "vm/native_methods.h"

#include <stdlib.h>

#include "pool.h"
#include "status.h"
#include "synth/resource_params.h"
#include "synth/synth.h"
#include "synth/object_method_names.h"
#include "vm/channel.h"
#include "vm/method.h"
#include "vm/object.h"
#include "vm/string_wrapper.h"
#include "vm/thread.h"
#include "vm/thread_wrapper.h"
#include "vm/value.h"
#include "vm/vm.h"

namespace vm {

void NativeMethods::Assert(Thread *thr, Object *obj,
			   const vector<Value> &args) {
  CHECK(args.size() == 1) << "Assert got " << args.size() << "args.";
  const Value &arg = args[0];
  VM *vm = thr->GetVM();
  CHECK(arg.type_ == Value::ENUM_ITEM) << "Assert argument is not an enum item";
  CHECK(arg.enum_val_.enum_type == vm->bool_type_.get());
  if (arg.enum_val_.val == 0) {
    cout << "ASSERTION FAILURE\n";
  }
}

void NativeMethods::Clone(Thread *thr, Object *obj,
			  const vector<Value> &args) {
  Value value;
  value.type_ = Value::OBJECT;
  value.object_ = obj->Clone(thr->GetVM());
  SetReturnValue(thr, value);
}

void NativeMethods::Dump(Thread *thr, Object *obj,
			 const vector<Value> &args) {
  obj->Dump();
}

void NativeMethods::Exit(Thread *thr, Object *obj,
			 const vector<Value> &args) {
  thr->Exit();
}

void NativeMethods::Print(Thread *thr, Object *obj,
			  const vector<Value> &args) {
  cout << "print: ";
  for (size_t i = 0; i < args.size(); ++i) {
    args[i].Dump(cout);
    cout << "\n";
  }
}


void NativeMethods::Run(Thread *thr, Object *obj,
			const vector<Value> &args) {
  ThreadWrapper::Run(thr->GetVM(), obj);
}

void NativeMethods::SetDump(Thread *thr, Object *obj,
			    const vector<Value> &args) {
  SetMemberString(thr, "$dump_file_name", obj, args);
}

void NativeMethods::SetIROutput(Thread *thr, Object *obj,
				const vector<Value> &args) {
  SetMemberString(thr, "$ir_file_name", obj, args);
}

void NativeMethods::SetIrohaPath(Thread *thr, Object *obj,
				 const vector<Value> &args) {
  SetMemberString(thr, "$iroha_path", obj, args);
}

void NativeMethods::RunIroha(Thread *thr, Object *obj,
			     const vector<Value> &args) {
  if (args.size() != 1 || args[0].type_ != Value::OBJECT ||
      !StringWrapper::IsString(args[0].object_)) {
    Status::os(Status::USER) << "Missing argument for runIroha()";
    return;
  }
  int res =
    synth::Synth::RunIroha(obj, StringWrapper::String(args[0].object_));
  if (res != 0) {
    Status::os(Status::USER) << "runIroha() failed: " << res;
  }
}

void NativeMethods::Synth(Thread *thr, Object *obj,
			   const vector<Value> &args) {
  if (args.size() != 1 || args[0].type_ != Value::OBJECT ||
      !StringWrapper::IsString(args[0].object_)) {
  }
  synth::Synth::Synthesize(thr->GetVM(), obj,
			   StringWrapper::String(args[0].object_));
}

void NativeMethods::SetMemberString(Thread *thr, const char *name,
				    Object *obj,
				    const vector<Value> &args) {
  if (args.size() == 1 && args[0].type_ == Value::OBJECT &&
      StringWrapper::IsString(args[0].object_)) {
    const string &fn = StringWrapper::String(args[0].object_);
    Value value;
    value.object_ = StringWrapper::NewStringWrapper(thr->GetVM(), fn);
    value.type_ = Value::OBJECT;
    obj->InstallValue(sym_lookup(name), value);
  }
}

void NativeMethods::Compile(Thread *thr, Object *obj,
			    const vector<Value> &args) {
  string phase;
  if (args.size() == 1) {
    CHECK(StringWrapper::IsString(args[0].object_));
    phase = StringWrapper::String(args[0].object_);
  }
  if (phase.empty()) {
    bool ok = synth::Synth::Synthesize(thr->GetVM(), obj,
				       synth::Synth::IrPath(obj));
    if (!ok) {
      Status::os(Status::USER) << "failed synthesize the design.";
      thr->UserError();
    }
  } else {
    int res = synth::Synth::RunIrohaOpt(phase, obj);
    if (res > 0) {
      Status::os(Status::USER) << "compile(" << phase << ") failed.";
      thr->UserError();
    }
  }
}

void NativeMethods::SetSynthParam(Thread *thr, Object *obj,
				  const vector<Value> &args) {
  if (args.size() != 2 ||
      !StringWrapper::IsString(args[0].object_) ||
      !StringWrapper::IsString(args[1].object_)) {
    Status::os(Status::USER) << "Invalid argument type of setSynthParam()";
    return;
  }
  Value *value = obj->LookupValue(sym_lookup("$synth_params"), true);
  if (value->type_ == Value::NONE) {
    value->type_ = Value::RESOURCE_PARAMS;
    value->resource_params_ = Importer::Import(nullptr);
  }
  value->resource_params_
    ->AddParam(StringWrapper::String(args[0].object_),
	       StringWrapper::String(args[1].object_));
}

void NativeMethods::WidthOf(Thread *thr, Object *obj,
			    const vector<Value> &args) {
  if (args.size() != 1 || args[0].type_ != Value::NUM) {
    Status::os(Status::USER) << "Invalid argument to widthof()";
    MessageFlush::Get(Status::USER);
    return;
  }
  Value value;
  value.type_ = Value::NUM;
  numeric::Numeric::MakeConst(numeric::Width::GetWidth(args[0].num_.type),
			      0, &value.num_);
  SetReturnValue(thr, value);
}

void NativeMethods::Wait(Thread *thr, Object *obj,
			 const vector<Value> &args) {
}

void NativeMethods::WriteHdl(Thread *thr, Object *obj,
			     const vector<Value> &args) {
  CHECK(args.size() == 1);
  const Value& arg = args[0];
  CHECK(StringWrapper::IsString(arg.object_));
  synth::Synth::WriteHdl(StringWrapper::String(arg.object_), obj);
}

void NativeMethods::IsMain(Thread *thr, Object *obj,
			   const vector<Value> &args) {
  Value value;
  value.type_ = Value::ENUM_ITEM;
  value.enum_val_.enum_type = thr->GetVM()->bool_type_.get();
  value.enum_val_.val = thr->IsRootThread() ? 1 : 0;
  SetReturnValue(thr, value);
}

void NativeMethods::GC(Thread *thr, Object *obj,
		       const vector<Value> &args) {
  thr->GetVM()->GC();
}

void NativeMethods::SetReturnValue(Thread *thr, const Value &value) {
  thr->SetReturnValueFromNativeMethod(value);
}

void Method::InstallNativeRootObjectMethods(VM *vm, Object *obj) {
  vector<RegisterType> rets;
  rets.push_back(ObjectType());
  InstallNativeMethod(vm, obj, "clone", &NativeMethods::Clone, rets);
  rets.clear();
  InstallNativeMethod(vm, obj, "dump", &NativeMethods::Dump, rets);
  InstallNativeMethod(vm, obj, "run", &NativeMethods::Run, rets);
}

void Method::InstallNativeKernelObjectMethods(VM *vm, Object *obj) {
  vector<RegisterType> rets;
  InstallNativeMethodWithAltImpl(vm, obj, "wait", &NativeMethods::Wait, rets, "__wait");
  Method *m;
  m = InstallNativeMethod(vm, obj, "print", &NativeMethods::Print, rets);
  m->SetSynthName(synth::kPrint);
  m = InstallNativeMethod(vm, obj, "assert", &NativeMethods::Assert, rets);
  m->SetSynthName(synth::kAssert);
  InstallNativeMethod(vm, obj, "compile", &NativeMethods::Compile, rets);
  InstallNativeMethod(vm, obj, "__compile", &NativeMethods::Compile, rets);
  InstallNativeMethod(vm, obj, "exit", &NativeMethods::Exit, rets);
  InstallNativeMethod(vm, obj, "setDump", &NativeMethods::SetDump, rets);
  InstallNativeMethod(vm, obj, "setIROutput", &NativeMethods::SetIROutput, rets);
  InstallNativeMethod(vm, obj, "setIrohaPath", &NativeMethods::SetIrohaPath, rets);
  InstallNativeMethod(vm, obj, "runIroha", &NativeMethods::RunIroha, rets);
  InstallNativeMethod(vm, obj, "synth", &NativeMethods::Synth, rets);
  InstallNativeMethod(vm, obj, "setSynthParam",
		      &NativeMethods::SetSynthParam, rets);
  InstallNativeMethod(vm, obj, "widthof", &NativeMethods::WidthOf, rets);
  InstallNativeMethod(vm, obj, "writeHdl", &NativeMethods::WriteHdl, rets);
}

Method *Method::InstallNativeMethodWithAltImpl(VM *vm, Object *obj,
					       const char *name,
					       method_func func,
					       const vector<RegisterType> &types,
					       const char *alt) {
  Method *method = vm->NewMethod(false /* not toplevel */);
  method->method_fn_ = func;
  method->alt_impl_ = alt;
  method->return_types_ = types;
  Value value;
  value.type_ = Value::METHOD;
  value.method_ = method;
  obj->InstallValue(sym_lookup(name), value);
  return method;
}

Method *Method::InstallNativeMethod(VM *vm, Object *obj, const char *name,
				    method_func func,
				    const vector<RegisterType> &types) {
  return InstallNativeMethodWithAltImpl(vm, obj, name, func, types, nullptr);
}

void Method::InstallEnvNativeMethods(VM *vm, Object *env) {
  vector<RegisterType> rets;
  InstallNativeMethod(vm, env, "gc", &NativeMethods::GC, rets);
  rets.push_back(BoolType(vm));
  InstallNativeMethod(vm, env, "isMain", &NativeMethods::IsMain, rets);
}

RegisterType Method::ObjectType() {
  return RegisterType(Value::OBJECT, nullptr, nullptr, sym_null, false);
}

RegisterType Method::BoolType(VM *vm) {
  return RegisterType(Value::ENUM_ITEM, vm->bool_type_.get(), nullptr,
		      sym_null, false);
}

RegisterType Method::IntType(int w) {
  return RegisterType(Value::NUM, nullptr,
		      numeric::Width::MakeInt(false, w, 0), sym_null,
		      false);
}

}  // namespace vm
