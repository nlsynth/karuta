#include "vm/vm.h"

#include "base/status.h"
#include "fe/expr.h"
#include "vm/array_wrapper.h"
#include "vm/enum_type_wrapper.h"
#include "vm/channel.h"
#include "vm/gc.h"
#include "vm/int_array.h"
#include "vm/method.h"
#include "vm/object.h"
#include "vm/opcode.h"
#include "vm/thread.h"

namespace vm {

VM::VM() {
  methods_.reset(new Pool<Method>());

  root_object_ = NewObject();
  InstallBoolType();
  Method::InstallNativeRootObjectMethods(this, root_object_);
  InstallObjects();
}

VM::~VM() {
  STLDeleteValues(&threads_);
  STLDeleteValues(&objects_);
}

void VM::Run() {
  bool ran = true;
  while (ran) {
    ran = false;
    for (Thread *thr : threads_) {
      if (thr->IsRunnable()) {
	thr->Run();
	ran = true;
      }
    }
  }

  for (Thread *thr : threads_) {
    if (!thr->IsDone()) {
      Status::os(Status::USER_ERROR) << "Remaining thread";
      MessageFlush::Get(Status::USER_ERROR);
    }
  }
  Status::CheckAllErrors(true);
}

void VM::AddThreadFromMethod(Thread *parent, Object *object, Method *method) {
  Thread *thread = new Thread(this, parent, object, method);
  threads_.insert(thread);
}

void VM::GC() {
  GC::Run(this, &threads_, &objects_);
}

void VM::InstallBoolType() {
  bool_type_ = EnumTypeWrapper::NewEnumTypeWrapper(this, sym_lookup("bool"));
  EnumTypeWrapper::AddItem(bool_type_, sym_lookup("false"));
  EnumTypeWrapper::AddItem(bool_type_, sym_lookup("true"));

  Value value;
  value.type_ = Value::ENUM_TYPE;
  value.object_ = bool_type_;
  root_object_->InstallValue(sym_lookup("bool"), value);

  Value true_value;
  true_value.type_ = Value::ENUM_ITEM;
  true_value.enum_val_.val = 1;
  true_value.enum_val_.enum_type = bool_type_;
  true_value.is_const_ = true;
  root_object_->InstallValue(sym_lookup("true"), true_value);

  Value false_value;
  false_value.type_ = Value::ENUM_ITEM;
  false_value.enum_val_.val = 0;
  false_value.enum_val_.enum_type = bool_type_;
  false_value.is_const_ = true;
  root_object_->InstallValue(sym_lookup("false"), false_value);
}

void VM::InstallObjects() {
  Value object_value;
  object_value.type_ = Value::OBJECT;
  object_value.object_ = root_object_;
  root_object_->InstallValue(sym_lookup("Object"), object_value);

  kernel_object_ = root_object_->Clone(this);
  object_value.object_ = kernel_object_;
  kernel_object_->InstallValue(sym_lookup("Kernel"), object_value);
  Method::InstallNativeKernelObjectMethods(this, kernel_object_);

  Object *global = root_object_->Clone(this);
  object_value.object_ = global;
  kernel_object_->InstallValue(sym_lookup("Global"), object_value);

  numerics_object_ = root_object_->Clone(this);
  object_value.object_ = numerics_object_;
  kernel_object_->InstallValue(sym_lookup("Numerics"), object_value);

  Object *env = root_object_->Clone(this);
  object_value.object_ = env;
  kernel_object_->InstallValue(sym_lookup("Env"), object_value);
  Method::InstallEnvNativeMethods(this, env);

  default_mem_ =
    ArrayWrapper::NewIntArrayWrapper(this, 0, iroha::NumericWidth(false, 32),
				     nullptr);
  ArrayWrapper::InstallSramIfMethods(this, default_mem_);
  object_value.object_ = default_mem_;
  kernel_object_->InstallValue(sym_lookup("Mem"), object_value);
}

IntArray *VM::GetDefaultMemory() {
  return ArrayWrapper::GetIntArray(default_mem_);
}

int VM::GetAddressSpaceWidth(Object *obj) {
  return obj->address_width_;
}

Method *VM::NewMethod(bool is_toplevel) {
  Method *method = new Method(is_toplevel);
  methods_->Add(method);
  return method;
}

Object *VM::NewObject() {
  Object *object = new Object;
  objects_.insert(object);
  return object;
}

}  // namespace vm
