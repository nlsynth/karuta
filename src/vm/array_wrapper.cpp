#include "array_wrapper.h"

#include <sstream>

#include "vm/int_array.h"
#include "vm/method.h"
#include "vm/object.h"
#include "vm/vm.h"

namespace vm {

static const char *kObjectArrayKey = "object_array";
static const char *kIntArrayKey = "int_array";

class ArrayWrapperData : public ObjectSpecificData {
public:
  ArrayWrapperData(int size, bool is_int, const numeric::Width *width) {
    if (is_int) {
      int_array_ = IntArray::Create(width, size);
    } else {
      int_array_ = nullptr;
      objs_.resize(size);
    }
  }
  ArrayWrapperData(ArrayWrapperData *src) {
    objs_ = src->objs_;
    if (src->int_array_) {
      int_array_ = IntArray::Copy(src->int_array_);
    } else {
      int_array_ = nullptr;
    }
  }


  vector<Object *> objs_;
  IntArray *int_array_;

  virtual const char *ObjectTypeKey() {
    if (int_array_) {
      return kIntArrayKey;
    } else {
      return kObjectArrayKey;
    }
  }
};

bool ArrayWrapper::IsObjectArray(Object *obj) {
  return (obj->ObjectTypeKey() == kObjectArrayKey);
}

bool ArrayWrapper::IsIntArray(Object *obj) {
  return (obj->ObjectTypeKey() == kIntArrayKey);
}

Object *ArrayWrapper::Copy(VM *vm, Object *src_obj) {
  Object *array_obj = vm->array_object_->Clone(vm);
  ArrayWrapperData *src_data =
    (ArrayWrapperData *)src_obj->object_specific_.get();
  ArrayWrapperData *data = new ArrayWrapperData(src_data);
  array_obj->object_specific_.reset(data);
  return array_obj;
}

string ArrayWrapper::ToString(Object *obj) {
  std::ostringstream os;
  ArrayWrapperData *data = (ArrayWrapperData *)obj->object_specific_.get();
  if (IsObjectArray(obj)) {
    os << "(obj)size=" << data->objs_.size();
  } else if (IsIntArray(obj)) {
    os << "(int)size=" << data->int_array_->GetLength();
  } else {
    os << "NOT ARRAY";
  }
  return os.str();
}

Object *ArrayWrapper::NewObjectArrayWrapper(VM *vm, int size) {
  Object *array_obj = vm->array_object_->Clone(vm);
  ArrayWrapperData *data = new ArrayWrapperData(size, false, nullptr);
  array_obj->object_specific_.reset(data);
  return array_obj;
}

Object *ArrayWrapper::NewIntArrayWrapper(VM *vm, int size,
					 const numeric::Width *width) {
  Object *array_obj = vm->array_object_->Clone(vm);
  ArrayWrapperData *data = new ArrayWrapperData(size, true, width);
  array_obj->object_specific_.reset(data);
  return array_obj;
}

Object *ArrayWrapper::Get(Object *obj, int nth) {
  ArrayWrapperData *data = (ArrayWrapperData *)obj->object_specific_.get();
  CHECK(nth >= 0 && nth < (int)data->objs_.size());
  return data->objs_[nth];
}

void ArrayWrapper::Set(Object *obj, int nth, Object *elem) {
  ArrayWrapperData *data = (ArrayWrapperData *)obj->object_specific_.get();
  CHECK(nth >= 0 && nth < (int)data->objs_.size());
  data->objs_[nth] = elem;
}

IntArray *ArrayWrapper::GetIntArray(Object *obj) {
  CHECK(obj->ObjectTypeKey() == kIntArrayKey);
  ArrayWrapperData *data = (ArrayWrapperData *)obj->object_specific_.get();
  return data->int_array_;
}

void ArrayWrapper::Load(Thread *thr, Object *obj, const vector<Value> &args) {
  CHECK(args.size() == 1) << "load requires an address";
}

void ArrayWrapper::InstallArrayMethods(VM *vm, Object *obj) {
  vector<RegisterType> rets;
  Method *m =
    Method::InstallNativeMethod(vm, obj, "load", &ArrayWrapper::Load, rets);
  m->SetHasSynth(true);
}

}  // namespace vm
