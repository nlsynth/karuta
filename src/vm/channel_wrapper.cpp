#include "vm/channel_wrapper.h"

#include "base/annotation.h"
#include "base/status.h"
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
  ChannelData(int width, sym_t name, Annotation *an)
    : width_(width), name_(sym_cstr(name)), an_(an) {};
  virtual ~ChannelData() {};

  virtual const char *ObjectTypeKey() {
    return kChannelObjectKey;
  }

  int width_;
  string name_;
  list<iroha::NumericValue> values_;

  set<Thread *> read_waiters_;
  Annotation *an_;
};

Object *ChannelWrapper::NewChannel(VM *vm, int width, sym_t name,
				   Annotation *an) {
  Object *pipe = vm->root_object_->Clone();
  vector<RegisterType> rets;
  Method *m = Method::InstallNativeMethod(vm, pipe, "write",
					  &ChannelWrapper::WriteMethod, rets);
  m->SetSynthName(synth::kChannelWrite);
  m = Method::InstallNativeMethod(vm, pipe, "writeFast",
				  &ChannelWrapper::WriteMethod, rets);
  m->SetSynthName(synth::kChannelNoWaitWrite);
  rets.push_back(Method::IntType(width));
  m = Method::InstallNativeMethod(vm, pipe, "read",
				  &ChannelWrapper::ReadMethod, rets);
  m->SetSynthName(synth::kChannelRead);

  pipe->object_specific_.reset(new ChannelData(width, name, an));

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

int ChannelWrapper::ChannelDepth(Object *obj) {
  CHECK(IsChannel(obj));
  ChannelData *pipe_data = (ChannelData *)obj->object_specific_.get();
  if (pipe_data->an_ != nullptr) {
    return pipe_data->an_->GetDepth();
  }
  return 1;
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
  iroha::NumericValue v = *(pipe_data->values_.begin());
  *(value->num_.GetMutableArray()) = v;
  value->num_.type_ = iroha::NumericWidth(false, pipe_data->width_);
  pipe_data->values_.pop_front();
  return true;
}

void ChannelWrapper::WriteMethod(Thread *thr, Object *obj,
				 const vector<Value> &args) {
  if (args.size() != 1 || args[0].type_ != Value::NUM) {
    Status::os(Status::USER_ERROR) << "Channel.write takes one value argument";
    thr->UserError();
    return;
  }
  WriteValue(args[0], obj);
}

void ChannelWrapper::WriteValue(const Value &value, Object *obj) {
  const iroha::NumericValue &v = value.num_.GetArray();
  ChannelData *pipe_data = (ChannelData *)obj->object_specific_.get();
  pipe_data->values_.push_back(v);
  for (Thread *t : pipe_data->read_waiters_) {
    t->Resume();
  }
  pipe_data->read_waiters_.clear();
}

void ChannelWrapper::BlockOnThis(Thread *thr, Object *obj) {
  ChannelData *pipe_data = (ChannelData *)obj->object_specific_.get();
  pipe_data->read_waiters_.insert(thr);
}

}  // namespace vm
