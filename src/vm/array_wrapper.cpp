#include "vm/array_wrapper.h"

#include <sstream>

#include "synth/object_method_names.h"
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
  ArrayWrapperData(VM *vm, uint64_t size, bool is_int,
		   const iroha::NumericWidth &width,
		   Annotation *an) {
    if (is_int) {
      int_array_ = IntArray::Create(width, size);
    } else {
      int_array_ = nullptr;
      objs_.resize(size);
      // Sets non null object so that vm/ doesn't have to care about nullptr.
      for (int i = 0; i < size; ++i) {
	objs_[i] = vm->root_object_;
      }
    }
    an_ = an;
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
  Annotation *an_;

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
  iroha::NumericWidth dw;
  ArrayWrapperData *data = new ArrayWrapperData(vm, size, false, dw, nullptr);
  array_obj->object_specific_.reset(data);
  return array_obj;
}

Object *ArrayWrapper::NewIntArrayWrapper(VM *vm, uint64_t size,
					 const iroha::NumericWidth &width,
					 Annotation *an) {
  Object *array_obj = vm->root_object_->Clone(vm);
  InstallMethods(vm, array_obj);
  ArrayWrapperData *data = new ArrayWrapperData(vm, size, true, width, an);
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

Annotation *ArrayWrapper::GetAnnotation(Object *obj) {
  ArrayWrapperData *data = (ArrayWrapperData *)obj->object_specific_.get();
  return data->an_;
}

int ArrayWrapper::GetDataWidth(Object *obj) {
  IntArray *a = GetIntArray(obj);
  return a->GetDataWidth().GetWidth();
}

void ArrayWrapper::Load(Thread *thr, Object *obj, const vector<Value> &args) {
  CHECK(args.size() > 0) << "load requires an address";
  MemAccess(thr, obj, args, true);
}

void ArrayWrapper::Store(Thread *thr, Object *obj, const vector<Value> &args) {
  CHECK(args.size() > 0) << "store requires an address";
  MemAccess(thr, obj, args, false);
}

void ArrayWrapper::MemAccess(Thread *thr, Object *obj,
			     const vector<Value> &args,
			     bool is_load) {
  IntArray *mem = thr->GetVM()->GetDefaultMemory();
  ArrayWrapperData *data = (ArrayWrapperData *)obj->object_specific_.get();
  IntArray *arr = data->int_array_;
  uint64_t length = arr->GetLength();
  // Mem addr
  int mem_addr_step = arr->GetDataWidth().GetWidth() / 8;
  uint64_t mem_addr = args[0].num_.GetValue();
  // Count
  int count = length;
  if (args.size() >= 2) {
    count = args[1].num_.GetValue() + 1;
  }
  // Start
  uint64_t array_addr = 0;
  if (args.size() >= 3) {
    array_addr = args[2].num_.GetValue();
  }
  // Do the copy.
  for (int i = 0; i < count; ++i) {
    if (is_load) {
      arr->Write(array_addr, mem->ReadWide(mem_addr, mem_addr_step));
    } else {
      mem->WriteWide(mem_addr, arr->Read(array_addr));
    }
    mem_addr += mem_addr_step;
    ++array_addr;
    array_addr %= length;
  }
}

void ArrayWrapper::InstallMethods(VM *vm, Object *obj) {
  vector<RegisterType> rets;
  Method *m =
    Method::InstallNativeMethod(vm, obj, "load", &ArrayWrapper::Load, rets);
  m->SetSynthName(synth::kLoad);
  m = Method::InstallNativeMethod(vm, obj, "store", &ArrayWrapper::Store, rets);
  m->SetSynthName(synth::kStore);
}

}  // namespace vm
