#include "vm/tls_wrapper.h"

#include "base/status.h"
#include "vm/array_wrapper.h"
#include "vm/gc.h"
#include "vm/object.h"
#include "vm/thread.h"
#include "vm/vm.h"

namespace vm {

static const char *kTlsObjectKey = "tls";

class TlsWrapperData : public ObjectSpecificData {
 public:
  virtual ~TlsWrapperData() {}

  virtual const char *ObjectTypeKey() { return kTlsObjectKey; }

  virtual void Scan(GC *gc) {
    gc->ScanObject(baseValue.object_);
    for (auto it : values) {
      gc->ScanObject(it.second.object_);
    }
  }

  Value baseValue;
  map<Thread *, Value> values;
};

bool TlsWrapper::IsTls(Object *obj) {
  return (obj->ObjectTypeKey() == kTlsObjectKey);
}

bool TlsWrapper::IsTlsValue(Value *value) {
  if (value->type_ == Value::OBJECT && value->object_ != nullptr &&
      IsTls(value->object_)) {
    return true;
  }
  return false;
}

void TlsWrapper::InjectTlsWrapper(VM *vm, Value *value) {
  if (value->type_ == Value::OBJECT || value->type_ == Value::OBJECT_ARRAY) {
    Status::os(Status::USER_ERROR)
        << "Can't attach @ThreadLocal() to object(s).";
    return;
  }
  Object *tls_obj = vm->root_object_->Clone();
  TlsWrapperData *data = new TlsWrapperData();
  tls_obj->object_specific_.reset(data);
  data->baseValue = *value;
  value->object_ = tls_obj;
  value->type_ = Value::OBJECT;
}

Object *TlsWrapper::Copy(VM *vm, Object *tls_obj) {
  Object *new_obj = vm->root_object_->Clone();
  TlsWrapperData *new_data = new TlsWrapperData();
  new_obj->object_specific_.reset(new_data);
  TlsWrapperData *data = (TlsWrapperData *)tls_obj->object_specific_.get();
  new_data->baseValue = data->baseValue;
  return new_obj;
}

Value *TlsWrapper::GetValue(Object *tls_obj, Thread *thr) {
  TlsWrapperData *data = (TlsWrapperData *)tls_obj->object_specific_.get();
  CHECK(data);
  if (thr == nullptr) {
    return &data->baseValue;
  }
  auto it = data->values.find(thr);
  if (it == data->values.end()) {
    data->values[thr] = data->baseValue;
    if (data->baseValue.object_ != nullptr &&
        data->baseValue.type_ == Value::INT_ARRAY) {
      data->values[thr].object_ =
          ArrayWrapper::Copy(thr->GetVM(), data->baseValue.object_);
    }
  }
  return &data->values[thr];
}

Object *TlsWrapper::GetBaseObject(Object *tls_obj) {
  TlsWrapperData *data = (TlsWrapperData *)tls_obj->object_specific_.get();
  return data->baseValue.object_;
}

}  // namespace vm
