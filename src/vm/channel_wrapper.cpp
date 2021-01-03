#include "vm/channel_wrapper.h"

#include <list>

#include "base/status.h"
#include "iroha/numeric.h"
#include "karuta/annotation.h"
#include "synth/object_method_names.h"
#include "vm/method.h"
#include "vm/native_methods.h"
#include "vm/native_objects.h"
#include "vm/object.h"
#include "vm/thread.h"
#include "vm/thread_queue.h"
#include "vm/vm.h"

using std::list;

namespace vm {

static const char *kChannelObjectKey = "channel";

class ChannelData : public ObjectSpecificData {
 public:
  ChannelData(int width, sym_t name, Annotation *an)
      : width_(width), name_(sym_cstr(name)), an_(an) {
    if (an == nullptr) {
      depth_ = 1;
    } else {
      depth_ = an_->GetDepth();
    }
  };
  virtual ~ChannelData(){};

  virtual const char *ObjectTypeKey() { return kChannelObjectKey; }

  int width_;
  string name_;
  list<iroha::NumericValue> values_;
  int depth_;

  ThreadQueue read_waiters_;
  ThreadQueue write_waiters_;
  Annotation *an_;
};

Object *ChannelWrapper::NewChannel(VM *vm, int width, sym_t name,
                                   Annotation *an) {
  Object *pipe = vm->root_object_->Clone();
  vector<RegisterType> rets;
  Method *m = NativeObjects::InstallNativeMethod(
      vm, pipe, "write", &ChannelWrapper::WriteMethod, rets);
  m->SetSynthName(synth::kChannelWrite);
  m = NativeObjects::InstallNativeMethod(vm, pipe, "writeFast",
                                         &ChannelWrapper::WriteMethod, rets);
  m->SetSynthName(synth::kChannelNoWaitWrite);
  rets.push_back(NativeObjects::IntType(width));
  m = NativeObjects::InstallNativeMethod(vm, pipe, "read",
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
  return pipe_data->depth_;
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
    BlockOnRead(thr, obj);
    return false;
  }

  value->type_ = Value::NUM;
  iroha::NumericValue v = *(pipe_data->values_.begin());
  value->num_value_ = v;
  value->num_width_ = iroha::NumericWidth(false, pipe_data->width_);
  pipe_data->values_.pop_front();
  // Wake writers.
  pipe_data->write_waiters_.ResumeAll();
  return true;
}

void ChannelWrapper::WriteMethod(Thread *thr, Object *obj,
                                 const vector<Value> &args) {
  if (args.size() != 1 || args[0].type_ != Value::NUM) {
    Status::os(Status::USER_ERROR) << "Channel.write takes one value argument";
    thr->UserError();
    return;
  }
  WriteValue(args[0], thr, obj);
}

void ChannelWrapper::WriteValue(const Value &value, Thread *thr, Object *obj) {
  ChannelData *pipe_data = (ChannelData *)obj->object_specific_.get();
  if (pipe_data->values_.size() == pipe_data->depth_) {
    BlockOnWrite(thr, obj);
    return;
  }
  const iroha::NumericValue &v = value.num_value_;
  pipe_data->values_.push_back(v);
  // Wake readers.
  pipe_data->read_waiters_.ResumeAll();
}

void ChannelWrapper::BlockOnRead(Thread *thr, Object *obj) {
  ChannelData *pipe_data = (ChannelData *)obj->object_specific_.get();
  pipe_data->read_waiters_.AddThread(thr);
}

void ChannelWrapper::BlockOnWrite(Thread *thr, Object *obj) {
  ChannelData *pipe_data = (ChannelData *)obj->object_specific_.get();
  pipe_data->write_waiters_.AddThread(thr);
}

}  // namespace vm
