#include "vm/array_wrapper.h"

#include <sstream>

#include "base/status.h"
#include "base/util.h"
#include "karuta/annotation.h"
#include "numeric/numeric_op.h"  // from iroha
#include "synth/object_method_names.h"
#include "vm/int_array.h"
#include "vm/native_objects.h"
#include "vm/method.h"
#include "vm/object.h"
#include "vm/object_util.h"
#include "vm/string_wrapper.h"
#include "vm/thread.h"
#include "vm/thread_queue.h"
#include "vm/vm.h"

namespace vm {

static const char *kObjectArrayKey = "object_array";
static const char *kIntArrayKey = "int_array";

class ArrayWrapperData : public ObjectSpecificData {
public:
  ArrayWrapperData(VM *vm, vector<uint64_t> &shape, bool is_int,
		   const iroha::NumericWidth &width,
		   Annotation *an) {
    uint64_t size = 1;
    for (uint64_t s : shape) {
      uint64_t r = Util::RoundUp2(s);
      shape_.push_back(r);
      size *= r;
    }
    if (is_int) {
      int_array_.reset(IntArray::Create(width, shape));
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

  explicit ArrayWrapperData(ArrayWrapperData *src) {
    objs_ = src->objs_;
    if (src->int_array_.get() != nullptr) {
      int_array_.reset(IntArray::Copy(src->int_array_.get()));
    } else {
      int_array_ = nullptr;
    }
    an_ = src->an_;
    shape_ = src->shape_;
  }

  vector<Object *> objs_;
  std::unique_ptr<IntArray> int_array_;
  Annotation *an_;
  ThreadQueue waiters_;
  vector<uint64_t> shape_;

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
  Object *array_obj = vm->array_prototype_object_->Clone();
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
  vector<uint64_t> shape;
  shape.push_back(size);
  Object *array_obj = vm->array_prototype_object_->Clone();
  InstallMethods(vm, array_obj);
  iroha::NumericWidth dw;
  ArrayWrapperData *data = new ArrayWrapperData(vm, shape, false, dw, nullptr);
  array_obj->object_specific_.reset(data);
  return array_obj;
}

Object *ArrayWrapper::NewIntArrayWrapper(VM *vm, vector<uint64_t> &shape,
					 const iroha::NumericWidth &width,
					 Annotation *an) {
  Object *array_obj = vm->array_prototype_object_->Clone();
  InstallMethods(vm, array_obj);
  ArrayWrapperData *data = new ArrayWrapperData(vm, shape, true, width, an);
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
  return data->int_array_.get();
}

Annotation *ArrayWrapper::GetAnnotation(Object *obj) {
  ArrayWrapperData *data = (ArrayWrapperData *)obj->object_specific_.get();
  return data->an_;
}

int ArrayWrapper::GetDataWidth(Object *obj) {
  IntArray *a = GetIntArray(obj);
  return a->GetDataWidth().GetWidth();
}

void ArrayWrapper::Read(Thread *thr, Object *obj, const vector<Value> &args) {
  CHECK(args.size() > 0) << "read requires an address";
  uint64_t addr = args[0].num_.GetValue0();
  ArrayWrapperData *data = (ArrayWrapperData *)obj->object_specific_.get();
  IntArray *arr = data->int_array_.get();
  Value value;
  value.type_ = Value::NUM;
  iroha::Op::MakeConst0(arr->ReadSingle(addr).GetValue0(),
			&value.num_);
  thr->SetReturnValueFromNativeMethod(value);
}

void ArrayWrapper::Write(Thread *thr, Object *obj, const vector<Value> &args) {
  CHECK(args.size() > 1) << "write requires an address and data";
  uint64_t addr = args[0].num_.GetValue0();
  uint64_t data = args[1].num_.GetValue0();
  ArrayWrapperData *ad = (ArrayWrapperData *)obj->object_specific_.get();
  IntArray *arr = ad->int_array_.get();
  iroha::Numeric num;
  iroha::Op::MakeConst0(data, num.GetMutableArray());
  arr->WriteSingle(addr, num.type_, num.GetArray());
}

void ArrayWrapper::AxiLoad(Thread *thr, Object *obj,
			   const vector<Value> &args) {
  CHECK(args.size() > 0) << "load requires an address";
  MemBurstAccess(thr, obj, args, true);
  MayNotifyWaiters(obj);
}

void ArrayWrapper::AxiStore(Thread *thr, Object *obj,
			    const vector<Value> &args) {
  CHECK(args.size() > 0) << "store requires an address";
  MemBurstAccess(thr, obj, args, false);
  MayNotifyWaiters(obj);
}

void ArrayWrapper::MayNotifyWaiters(Object *obj) {
  ArrayWrapperData *ad = (ArrayWrapperData *)obj->object_specific_.get();
  ad->waiters_.ResumeAll();
}

void ArrayWrapper::WaitAccess(Thread *thr, Object *obj,
			      const vector<Value> &args) {
  ArrayWrapperData *ad = (ArrayWrapperData *)obj->object_specific_.get();
  if (ad->waiters_.ClearIfNotified(thr)) {
    return;
  }
  ad->waiters_.AddThread(thr);
  thr->Suspend();
}

void ArrayWrapper::NotifyAccess(Thread *thr, Object *obj,
				const vector<Value> &args) {
  MayNotifyWaiters(obj);
}

void ArrayWrapper::MemBurstAccess(Thread *thr, Object *obj,
				  const vector<Value> &args,
				  bool is_load) {
  IntArray *mem = thr->GetVM()->GetDefaultMemory();
  ArrayWrapperData *data = (ArrayWrapperData *)obj->object_specific_.get();
  IntArray *arr = data->int_array_.get();
  uint64_t length = arr->GetLength();
  // Mem addr
  int mem_addr_step = arr->GetDataWidth().GetWidth() / 8;
  uint64_t mem_addr = args[0].num_.GetValue0();
  // Count
  int count = length;
  if (args.size() >= 2) {
    count = args[1].num_.GetValue0() + 1;
  }
  // Start
  uint64_t array_addr = 0;
  if (args.size() >= 3) {
    array_addr = args[2].num_.GetValue0();
  }
  // Do the copy.
  for (int i = 0; i < count; ++i) {
    if (is_load) {
      iroha::Numeric n = mem->ReadWide(mem_addr, mem_addr_step * 8);
      arr->WriteSingle(array_addr, n.type_, n.GetArray());
    } else {
      iroha::NumericValue v = arr->ReadSingle(array_addr);
      iroha::NumericWidth w = arr->GetDataWidth();
      mem->WriteWide(mem_addr, w, v);
    }
    mem_addr += mem_addr_step;
    ++array_addr;
    array_addr %= length;
  }
}

void ArrayWrapper::SaveImage(Thread *thr, Object *obj,
			     const vector<Value> &args) {
  ImageIO(true, thr, obj, args);
}

void ArrayWrapper::LoadImage(Thread *thr, Object *obj,
			     const vector<Value> &args) {
  ImageIO(false, thr, obj, args);
}

void ArrayWrapper::ImageIO(bool save, Thread *thr, Object *obj,
			   const vector<Value> &args) {
  CHECK(args.size() > 0) << "save/load image requires a file name";
  const Value& arg = args[0];
  CHECK(StringWrapper::IsString(arg.object_));
  ArrayWrapperData *data = (ArrayWrapperData *)obj->object_specific_.get();
  IntArray *arr = data->int_array_.get();
  string format;
  if (args.size() >= 2) {
    const Value& fmt = args[1];
    CHECK(StringWrapper::IsString(fmt.object_));
    format = StringWrapper::String(fmt.object_);
  }
  arr->ImageIO(StringWrapper::String(arg.object_), format, save);
}

void ArrayWrapper::SetAddressWidth(Thread *thr, Object *obj,
				   const vector<Value> &args) {
  if (args.size() != 1 || args[0].type_ != Value::NUM) {
    Status::os(Status::USER_ERROR) << "Only 1 int argument is allowed";
    thr->UserError();
    return;
  }
  int w = args[0].num_.GetValue0();
  if (w > 0 && w <= 64) {
    ObjectUtil::SetAddressWidth(obj, w);
  } else {
    Status::os(Status::USER_ERROR) << w << " is invalid address width.";
    thr->UserError();
  }
}

void ArrayWrapper::InstallMethods(VM *vm, Object *obj) {
  vector<RegisterType> rets;
  Method *m;
  m = NativeObjects::InstallNativeMethod(vm, obj, "axiLoad",
					 &ArrayWrapper::AxiLoad, rets);
  m->SetSynthName(synth::kAxiLoad);
  m = NativeObjects::InstallNativeMethod(vm, obj, "axiStore",
					 &ArrayWrapper::AxiStore, rets);
  m->SetSynthName(synth::kAxiStore);
  m = NativeObjects::InstallNativeMethod(vm, obj, "waitAccess",
					 &ArrayWrapper::WaitAccess,
					 rets);
  m->SetSynthName(synth::kSlaveWait);
  m = NativeObjects::InstallNativeMethod(vm, obj, "notifyAccess",
					 &ArrayWrapper::NotifyAccess,
					 rets);
  NativeObjects::InstallNativeMethod(vm, obj, "saveImage",
				     &ArrayWrapper::SaveImage, rets);
  NativeObjects::InstallNativeMethod(vm, obj, "loadImage",
				     &ArrayWrapper::LoadImage, rets);
  NativeObjects::InstallNativeMethod(vm, obj, "setAddressWidth",
				     &ArrayWrapper::SetAddressWidth, rets);
}

void ArrayWrapper::InstallSramIfMethods(VM *vm ,Object *obj) {
  vector<RegisterType> rets;
  rets.push_back(NativeObjects::IntType(32));
  Method *m =
    NativeObjects::InstallNativeMethod(vm, obj, "read",
				       &ArrayWrapper::Read, rets);
  m->SetSynthName(synth::kSramRead);
  rets.clear();
  m = NativeObjects::InstallNativeMethod(vm, obj, "write",
					 &ArrayWrapper::Write, rets);
  m->SetSynthName(synth::kSramWrite);
}

}  // namespace vm
