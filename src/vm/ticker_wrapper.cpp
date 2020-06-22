#include "vm/ticker_wrapper.h"

#include "synth/object_method_names.h"
#include "vm/method.h"
#include "vm/native_methods.h"
#include "vm/native_objects.h"
#include "vm/object.h"
#include "vm/vm.h"

namespace vm {

Object *TickerWrapper::NewTicker(VM *vm) {
  Object *obj = vm->root_object_->Clone();
  vector<RegisterType> rets;
  rets.push_back(NativeObjects::IntType(32));
  Method *m = NativeObjects::InstallNativeMethod(vm, obj, "getTickCount",
						 &TickerWrapper::GetTickCount,
						 rets);
  m->SetSynthName(synth::kGetTickCount);
  return obj;
}

void TickerWrapper::GetTickCount(Thread *thr, Object *obj,
				 const vector<Value> &args) {
  Value value;
  value.type_ = Value::NUM;
  iroha::Op::MakeConst0(0, &value.num_);
  NativeMethods::SetReturnValue(thr, value);
}

}  // namespace vm
