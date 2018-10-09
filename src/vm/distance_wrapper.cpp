#include "vm/distance_wrapper.h"

#include "base/annotation.h"
#include "vm/object.h"
#include "vm/vm.h"

namespace vm {

static const char *kDistanceObjectKey = "distance";

class DistanceWrapperData : public ObjectSpecificData {
public:
  virtual const char *ObjectTypeKey() {
    return kDistanceObjectKey;
  }
  int GetDistance(sym_t name) {
    return distance_[name];
  }
  void SetDistance(sym_t name, int d) {
    distance_[name] = d;
  }
  map<sym_t, int> distance_;
};

Object *DistanceWrapper::GetAttachedDistanceObject(VM *vm, Object *owner_obj, bool create) {
  sym_t d = sym_lookup("$distance_params");
  Value *value = owner_obj->LookupValue(d, create);
  if (value != nullptr && value->type_ == Value::OBJECT) {
    return value->object_;
  }
  if (!create) {
    return nullptr;
  }
  Object *obj = vm->root_object_->Clone(vm);
  obj->object_specific_.reset(new DistanceWrapperData);
  return obj;
}

void DistanceWrapper::MaySetDistanceAnnotation(sym_t name, Annotation *an, VM *vm, Object *obj) {
  if (an == nullptr) {
    return;
  }
  int d = an->GetDistance();
  if (d == 0) {
    return;
  }
  Object *distance_obj = GetAttachedDistanceObject(vm, obj, true);
  DistanceWrapperData *data = (DistanceWrapperData *)distance_obj->object_specific_.get();
  data->SetDistance(name, d);
}

int DistanceWrapper::GetDistance(VM *vm, Object *obj, sym_t name) {
  Object *distance_obj = GetAttachedDistanceObject(vm, obj, false);
  if (distance_obj == nullptr) {
    return 0;
  }
  DistanceWrapperData *data = (DistanceWrapperData *)distance_obj->object_specific_.get();
  return data->GetDistance(name);
}

}  // namespace vm
