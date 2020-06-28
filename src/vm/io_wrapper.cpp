#include "vm/io_wrapper.h"

#include "synth/object_method_names.h"
#include "vm/method.h"
#include "vm/native_methods.h"
#include "vm/native_objects.h"
#include "vm/object.h"
#include "vm/vm.h"

namespace vm {

static const char *kIoKey = "io_wrapper";

class IOWrapperData : public ObjectSpecificData {
public:
  IOWrapperData(const string &name, bool is_output, int width)
    : name_(name), is_output_(is_output), width_(width) {
  }

  string name_;
  bool is_output_;
  int width_;

  virtual const char *ObjectTypeKey() {
    return kIoKey;
  }
};

bool IOWrapper::IsIO(Object *obj) {
  return (obj->ObjectTypeKey() == kIoKey);
}

bool IOWrapper::IsOutput(Object *obj) {
  IOWrapperData *data = (IOWrapperData *)obj->object_specific_.get();
  return data->is_output_;
}

const string &IOWrapper::GetName(Object *obj) {
  IOWrapperData *data = (IOWrapperData *)obj->object_specific_.get();
  return data->name_;
}

int IOWrapper::GetWidth(Object *obj) {
  IOWrapperData *data = (IOWrapperData *)obj->object_specific_.get();
  return data->width_;
}

Object *IOWrapper::NewIOWrapper(VM *vm, const string &name, bool is_output,
				const iroha::NumericWidth &width) {
  Object *obj = vm->root_object_->Clone();
  IOWrapperData *data =
    new IOWrapperData(name, is_output, width.GetWidth());
  obj->object_specific_.reset(data);
  InstallMethods(vm, obj, is_output, width);
  return obj;
}

void IOWrapper::InstallMethods(VM *vm, Object *obj, bool is_output,
			       const iroha::NumericWidth &width) {
  vector<RegisterType> rets;
  Method *m;
  if (is_output) {
    m = NativeObjects::InstallNativeMethod(vm, obj, "write",
					   &IOWrapper::Write, rets);
    m->SetSynthName(synth::kIOWrite);
    rets.push_back(NativeObjects::IntType(width.GetWidth()));
    m = NativeObjects::InstallNativeMethod(vm, obj, "peek",
					   &IOWrapper::Peek, rets);
    m->SetSynthName(synth::kIOPeek);
  } else {
    rets.push_back(NativeObjects::IntType(width.GetWidth()));
    m = NativeObjects::InstallNativeMethod(vm, obj, "read",
					   &IOWrapper::Read, rets);
    m->SetSynthName(synth::kIORead);
  }
}

void IOWrapper::Read(Thread *thr, Object *obj, const vector<Value> &args) {
  Value value;
  value.type_ = Value::NUM;
  iroha::Op::MakeConst0(0, &value.num_);
  NativeMethods::SetReturnValue(thr, value);
}

void IOWrapper::Peek(Thread *thr, Object *obj, const vector<Value> &args) {
}

void IOWrapper::Write(Thread *thr, Object *obj, const vector<Value> &args) {
}

}  // namespace vm
