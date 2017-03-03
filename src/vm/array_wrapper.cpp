#include "array_wrapper.h"

#include <sstream>

#include "vm/int_array.h"
#include "vm/method.h"
#include "vm/object.h"
#include "vm/thread.h"
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
  Object *array_obj = vm->root_object_->Clone(vm);
  InstallMethods(vm, array_obj);
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
  Object *array_obj = vm->root_object_->Clone(vm);
  InstallMethods(vm, array_obj);
  ArrayWrapperData *data = new ArrayWrapperData(size, false, nullptr);
  array_obj->object_specific_.reset(data);
  return array_obj;
}

Object *ArrayWrapper::NewIntArrayWrapper(VM *vm, int size,
					 const numeric::Width *width) {
  Object *array_obj = vm->root_object_->Clone(vm);
  InstallMethods(vm, array_obj);
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
  MemAccess(thr, obj, args, true);
}

void ArrayWrapper::Store(Thread *thr, Object *obj, const vector<Value> &args) {
  CHECK(args.size() == 1) << "store requires an address";
  MemAccess(thr, obj, args, false);
}

void ArrayWrapper::MemAccess(Thread *thr, Object *obj,
			     const vector<Value> &args,
			     bool is_load) {
  IntArray *mem = thr->GetVM()->GetDefaultMemory();
  ArrayWrapperData *data = (ArrayWrapperData *)obj->object_specific_.get();
  IntArray *arr = data->int_array_;
  auto length = arr->GetLength();
  const Value &addr_value = args[0];
  int addr = addr_value.num_.int_part;
  for (int i = 0; i < length; ++i) {
    if (is_load) {
      arr->Write(i, mem->Read(addr + i));
    } else {
      mem->Write(i, arr->Read(addr + i));
    }
  }
}

void ArrayWrapper::InstallMethods(VM *vm, Object *obj) {
  vector<RegisterType> rets;
  Method *m =
    Method::InstallNativeMethod(vm, obj, "load", &ArrayWrapper::Load, rets);
  m->SetHasSynth(true);
  m = Method::InstallNativeMethod(vm, obj, "store", &ArrayWrapper::Store, rets);
  m->SetHasSynth(true);
}

}  // namespace vm
