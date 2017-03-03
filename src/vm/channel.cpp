#include "vm/channel.h"

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

Object *Channel::NewChannel(VM *vm, int width, sym_t name) {
  Object *pipe = vm->root_object_->Clone(vm);
  vector<RegisterType> rets;
  Method::InstallNativeMethod(vm, pipe, "write", &Channel::WriteMethod, rets);
  rets.push_back(Method::IntType(width));
  Method::InstallNativeMethod(vm, pipe, "read", &Channel::ReadMethod, rets);

  pipe->object_specific_.reset(new ChannelData(width, name));

  return pipe;
}

bool Channel::IsChannel(Object *obj) {
  return (obj->ObjectTypeKey() == kChannelObjectKey);
}

const string &Channel::ChannelName(Object *obj) {
  CHECK(IsChannel(obj));
  ChannelData *pipe_data = (ChannelData *)obj->object_specific_.get();
  return pipe_data->name_;
}

int Channel::ChannelWidth(Object *obj) {
  CHECK(IsChannel(obj));
  ChannelData *pipe_data = (ChannelData *)obj->object_specific_.get();
  return pipe_data->width_;
}

void Channel::ReadMethod(Thread *thr, Object *obj,
			  const vector<Value> &args) {
  Value value;
  if (!ReadValue(thr, obj, &value)) {
    return;
  }

  NativeMethods::SetReturnValue(thr, value);
}

bool Channel::ReadValue(Thread *thr, Object *obj, Value *value) {
  ChannelData *pipe_data = (ChannelData *)obj->object_specific_.get();
  if (pipe_data->values_.size() == 0) {
    BlockOnThis(thr, obj);
    thr->Suspend();
    return false;
  }

  value->type_ = Value::NUM;
  int64_t v = *(pipe_data->values_.begin());
  pipe_data->values_.pop_front();
  numeric::Numeric::MakeConst(v, 0, &value->num_);
  value->num_.type = numeric::Width::MakeInt(false, pipe_data->width_, 0);
  return true;
}

void Channel::WriteMethod(Thread *thr, Object *obj, const vector<Value> &args) {
  CHECK(args.size() == 1 && args[0].type_ == Value::NUM);
  WriteValue(args[0], obj);
}

void Channel::WriteValue(const Value &value, Object *obj) {
  int64_t v = numeric::Numeric::GetInt(value.num_);
  ChannelData *pipe_data = (ChannelData *)obj->object_specific_.get();
  pipe_data->values_.push_back(v);
  if (pipe_data->blocking_thread_) {
    pipe_data->blocking_thread_->Resume();
    pipe_data->blocking_thread_ = nullptr;
  }
}

void Channel::BlockOnThis(Thread *thr, Object *obj) {
  ChannelData *pipe_data = (ChannelData *)obj->object_specific_.get();
  CHECK(pipe_data->blocking_thread_ == nullptr);
  pipe_data->blocking_thread_ = thr;
}

}  // namespace vm
