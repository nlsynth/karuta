#include "vm/channel_wrapper.h"

#include "numeric/numeric_op.h"  // from iroha
#include "synth/object_method_names.h"
#include "vm/object.h"
#include "vm/thread.h"
#include "vm/method.h"
#include "vm/native_methods.h"
#include "vm/vm.h"

#include <list>

using std::list;

namespace vm {

static const char *kChannelObjectKey = "channel";

class ChannelData : public ObjectSpecificData {
public:
  ChannelData(int width, sym_t name) : width_(width), name_(sym_cstr(name)),
				       blocking_thread_(nullptr) {};
  virtual ~ChannelData() {};

  virtual const char *ObjectTypeKey() {
    return kChannelObjectKey;
  }

  int width_;
  string name_;
  list<uint64_t> values_;

  Thread *blocking_thread_;
};

Object *ChannelWrapper::NewChannel(VM *vm, int width, sym_t name) {
  Object *pipe = vm->root_object_->Clone(vm);
  vector<RegisterType> rets;
  Method *m = Method::InstallNativeMethod(vm, pipe, "write",
					  &ChannelWrapper::WriteMethod, rets);
  m->SetSynthName(synth::kChannelWrite);
  rets.push_back(Method::IntType(width));
  m = Method::InstallNativeMethod(vm, pipe, "read",
				  &ChannelWrapper::ReadMethod, rets);
  m->SetSynthName(synth::kChannelRead);

  pipe->object_specific_.reset(new ChannelData(width, name));

  return pipe;
}

bool ChannelWrapper::IsChannel(Object *obj) {
  return (obj->ObjectTypeKey() == kChannelObjectKey);
}

const string &ChannelWrapper::ChannelName(Object *obj) {
  CHECK(IsChannel(obj));
  ChannelData *pipe_data = (ChannelData *)obj->object_specific_.get();
  return pipe_data->name_;
}

int ChannelWrapper::ChannelWidth(Object *obj) {
  CHECK(IsChannel(obj));
  ChannelData *pipe_data = (ChannelData *)obj->object_specific_.get();
  return pipe_data->width_;
}

void ChannelWrapper::ReadMethod(Thread *thr, Object *obj,
				const vector<Value> &args) {
  Value value;
  if (!ReadValue(thr, obj, &value)) {
    return;
  }

  NativeMethods::SetReturnValue(thr, value);
}

bool ChannelWrapper::ReadValue(Thread *thr, Object *obj, Value *value) {
  ChannelData *pipe_data = (ChannelData *)obj->object_specific_.get();
  if (pipe_data->values_.size() == 0) {
    BlockOnThis(thr, obj);
    thr->Suspend();
    return false;
  }

  value->type_ = Value::NUM;
  int64_t v = *(pipe_data->values_.begin());
  pipe_data->values_.pop_front();
  iroha::Op::MakeConst(v, &value->num_);
  value->num_.type_ = iroha::NumericWidth(false, pipe_data->width_);
  return true;
}

void ChannelWrapper::WriteMethod(Thread *thr, Object *obj,
				 const vector<Value> &args) {
  CHECK(args.size() == 1 && args[0].type_ == Value::NUM);
  WriteValue(args[0], obj);
}

void ChannelWrapper::WriteValue(const Value &value, Object *obj) {
  int64_t v = value.num_.GetValue();
  ChannelData *pipe_data = (ChannelData *)obj->object_specific_.get();
  pipe_data->values_.push_back(v);
  if (pipe_data->blocking_thread_) {
    pipe_data->blocking_thread_->Resume();
    pipe_data->blocking_thread_ = nullptr;
  }
}

void ChannelWrapper::BlockOnThis(Thread *thr, Object *obj) {
  ChannelData *pipe_data = (ChannelData *)obj->object_specific_.get();
  CHECK(pipe_data->blocking_thread_ == nullptr);
  pipe_data->blocking_thread_ = thr;
}

}  // namespace vm
