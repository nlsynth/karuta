#include "vm/tls_wrapper.h"

#include "vm/array_wrapper.h"
#include "vm/gc.h"
#include "vm/object.h"
#include "vm/thread.h"
#include "vm/vm.h"

namespace vm {

static const char *kTlsObjectKey = "tls";

class TlsWrapperData : public ObjectSpecificData {
public:
  virtual ~TlsWrapperData() {
  }

  virtual const char *ObjectTypeKey() {
    return kTlsObjectKey;
  }

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
  if (value->type_ == Value::OBJECT &&
      value->object_ != nullptr &&
      IsTls(value->object_)) {
    return true;
  }
  return false;
}

void TlsWrapper::InjectTlsWrapper(VM *vm, Value *value) {
  Object *tls_obj = vm->root_object_->Clone(vm);
  TlsWrapperData *data = new TlsWrapperData();
  tls_obj->object_specific_.reset(data);
  data->baseValue = *value;
  value->object_ = tls_obj;
  value->type_ = Value::OBJECT;
}

Value *TlsWrapper::GetValue(Object *tls_obj, Thread *thr) {
  TlsWrapperData *data = (TlsWrapperData *)tls_obj->object_specific_.get();
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

}  // namespace vm
