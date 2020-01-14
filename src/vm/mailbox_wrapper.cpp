#include "vm/mailbox_wrapper.h"

#include "base/status.h"
#include "synth/object_method_names.h"
#include "vm/method.h"
#include "vm/native_objects.h"
#include "vm/object.h"
#include "vm/thread.h"
#include "vm/vm.h"

namespace vm {

static const char *kMailboxObjectKey = "mailbox";

struct WaitQueue {
  set<Thread *> waiters;

  void AddThread(Thread *thr) {
    waiters.insert(thr);
  }

  void ResumeOne() {
    if (waiters.size() == 0) {
      return;
    }
    Thread *t = *(waiters.begin());
    waiters.erase(t);
    t->Resume();
  }

  void ResumeAll(set<Thread *> *resumed) {
    for (Thread *t : waiters) {
      t->Resume();
      resumed->insert(t);
    }
    waiters.clear();
  }
};

class MailboxData : public ObjectSpecificData {
public:
  MailboxData(int width, sym_t name, Annotation *an)
    : width_(width), name_(sym_cstr(name)), an_(an) {
    has_value_ = false;
  }

  virtual const char *ObjectTypeKey() {
    return kMailboxObjectKey;
  }

  int width_;
  string name_;
  WaitQueue put_waiters_;
  WaitQueue get_waiters_;
  WaitQueue notify_waiters_;
  set<Thread *> notified_threads_;
  iroha::NumericValue number_;
  bool has_value_;
  Annotation *an_;
};

Object *MailboxWrapper::NewMailbox(VM *vm, int width, sym_t name,
				   Annotation *an) {
  Object *mailbox_obj = vm->root_object_->Clone();
  mailbox_obj->object_specific_.reset(new MailboxData(width, name, an));
  InstallMethods(vm, mailbox_obj, width);
  return mailbox_obj;
}

bool MailboxWrapper::IsMailbox(Object *obj) {
  return (obj->ObjectTypeKey() == kMailboxObjectKey);
}

int MailboxWrapper::GetWidth(Object *obj) {
  CHECK(IsMailbox(obj));
  MailboxData *data = (MailboxData *)obj->object_specific_.get();
  return data->width_;
}

Annotation *MailboxWrapper::GetAnnotation(Object *obj) {
  MailboxData *data = (MailboxData *)obj->object_specific_.get();
  return data->an_;
}

void MailboxWrapper::InstallMethods(VM *vm ,Object *obj, int width) {
  vector<RegisterType> rets;
  rets.push_back(NativeObjects::IntType(32));
  // width
  Method *m =
    NativeObjects::InstallNativeMethod(vm, obj, "width",
				       &MailboxWrapper::Width, rets);
  m->SetSynthName(synth::kMailboxWidth);
  // put
  m = NativeObjects::InstallNativeMethod(vm, obj, "put",
					 &MailboxWrapper::Put, rets);
  m->SetSynthName(synth::kMailboxPut);
  // notify
  m = NativeObjects::InstallNativeMethod(vm, obj, "notify",
					 &MailboxWrapper::Notify, rets);
  m->SetSynthName(synth::kMailboxNotify);
  // get
  rets[0] = NativeObjects::IntType(width);
  m = NativeObjects::InstallNativeMethod(vm, obj, "get",
					 &MailboxWrapper::Get, rets);
  m->SetSynthName(synth::kMailboxGet);
  // wait
  m = NativeObjects::InstallNativeMethod(vm, obj, "wait",
					 &MailboxWrapper::Wait, rets);
  m->SetSynthName(synth::kMailboxWait);
}

void MailboxWrapper::Width(Thread *thr, Object *obj,
			   const vector<Value> &args) {
  Value value;
  value.type_ = Value::NUM;
  value.num_.SetValue0(GetWidth(obj));
  thr->SetReturnValueFromNativeMethod(value);
}

void MailboxWrapper::Get(Thread *thr, Object *obj,
			 const vector<Value> &args) {
  MailboxData *data = (MailboxData *)obj->object_specific_.get();
  if (data->has_value_) {
    data->has_value_ = false;
    Value value;
    value.type_ = Value::NUM;
    value.num_ = data->number_;
    thr->SetReturnValueFromNativeMethod(value);
    WakeOne(true, data);
  } else {
    data->get_waiters_.AddThread(thr);
    thr->Suspend();
  }
}

void MailboxWrapper::Put(Thread *thr, Object *obj,
			 const vector<Value> &args) {
  MailboxData *data = (MailboxData *)obj->object_specific_.get();
  if (data->has_value_) {
    data->put_waiters_.AddThread(thr);
    thr->Suspend();
  } else {
    data->has_value_ = true;
    data->number_ = args[0].num_;
    WakeOne(false, data);
  }
}

void MailboxWrapper::Notify(Thread *thr, Object *obj,
			    const vector<Value> &args) {
  if (args.size() != 1 || args[0].type_ != Value::NUM) {
    Status::os(Status::USER_ERROR) << "Mailbox.write takes one value argument";
    thr->UserError();
    return;
  }
  MailboxData *data = (MailboxData *)obj->object_specific_.get();
  data->number_ = args[0].num_;
  data->notify_waiters_.ResumeAll(&data->notified_threads_);
}

void MailboxWrapper::Wait(Thread *thr, Object *obj, const vector<Value> &args) {
  MailboxData *data = (MailboxData *)obj->object_specific_.get();
  if (data->notified_threads_.find(thr) != data->notified_threads_.end()) {
    // Already notified at the same time (in execution event order).
    data->notified_threads_.erase(thr);
    Value value;
    value.type_ = Value::NUM;
    value.num_ = data->number_;
    thr->SetReturnValueFromNativeMethod(value);
  } else {
    data->notify_waiters_.AddThread(thr);
    thr->Suspend();
  }
}

void MailboxWrapper::WakeOne(bool wake_put, MailboxData *data) {
  WaitQueue *q;
  if (wake_put) {
    q = &data->put_waiters_;
  } else {
    q = &data->get_waiters_;
  }
  q->ResumeOne();
}

}  // namespace vm
