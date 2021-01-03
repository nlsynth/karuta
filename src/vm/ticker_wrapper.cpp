#include "vm/ticker_wrapper.h"

#include "synth/object_method_names.h"
#include "vm/method.h"
#include "vm/native_methods.h"
#include "vm/native_objects.h"
#include "vm/object.h"
#include "vm/thread.h"
#include "vm/vm.h"

namespace vm {

static const char *kTickerKey = "ticker_wrapper";

class TickerWrapperData : public ObjectSpecificData {
 public:
  TickerWrapperData() : local_tick_(0) {}

  int local_tick_;

  virtual const char *ObjectTypeKey() { return kTickerKey; }
};

Object *TickerWrapper::NewTicker(VM *vm) {
  Object *obj = vm->root_object_->Clone();
  TickerWrapperData *data = new TickerWrapperData();
  obj->object_specific_.reset(data);
  vector<RegisterType> rets;
  Method *m = NativeObjects::InstallNativeMethod(
      vm, obj, "decrementCount", &TickerWrapper::DecrementTick, rets);
  m->SetSynthName(synth::kDecrementTick);
  rets.push_back(NativeObjects::IntType(32));
  m = NativeObjects::InstallNativeMethod(vm, obj, "getCount",
                                         &TickerWrapper::GetTickCount, rets);
  m->SetSynthName(synth::kGetTickCount);
  return obj;
}

void TickerWrapper::GetTickCount(Thread *thr, Object *obj,
                                 const vector<Value> &args) {
  unsigned int tick = thr->GetVM()->GetGlobalTickCount();
  TickerWrapperData *data = (TickerWrapperData *)obj->object_specific_.get();
  data->local_tick_++;
  tick += data->local_tick_;
  Value value;
  value.type_ = Value::NUM;
  iroha::Op::MakeConst0(tick, &value.num_value_);
  NativeMethods::SetReturnValue(thr, value);
}

void TickerWrapper::DecrementTick(Thread *thr, Object *obj,
                                  const vector<Value> &args) {
  TickerWrapperData *data = (TickerWrapperData *)obj->object_specific_.get();
  if (args.size() == 1 && args[0].type_ == Value::NUM) {
    data->local_tick_ -= args[0].num_value_.GetValue0();
    data->local_tick_++;
  }
}

}  // namespace vm
