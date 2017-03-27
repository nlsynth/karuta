#include "vm/mailbox_wrapper.h"

#include "numeric/numeric.h"
#include "synth/object_method_names.h"
#include "vm/method.h"
#include "vm/object.h"
#include "vm/thread.h"
#include "vm/vm.h"

namespace vm {

static const char *kMailboxObjectKey = "mailbox";

class MailboxData : public ObjectSpecificData {
public:
  MailboxData(int width, sym_t name) : width_(width), name_(sym_cstr(name)) {
    number_.type = numeric::Width::MakeInt(false, width);
    has_value_ = false;
  }

  virtual const char *ObjectTypeKey() {
    return kMailboxObjectKey;
  }

  int width_;
  string name_;
  set<Thread *> put_waiters_;
  set<Thread *> get_waiters_;
  numeric::Number number_;
  bool has_value_;
};

Object *MailboxWrapper::NewMailbox(VM *vm, int width, sym_t name) {
  Object *mailbox_obj = vm->root_object_->Clone(vm);
  mailbox_obj->object_specific_.reset(new MailboxData(width, name));
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

void MailboxWrapper::InstallMethods(VM *vm ,Object *obj, int width) {
  vector<RegisterType> rets;
  rets.push_back(Method::IntType(32));
  Method *m =
    Method::InstallNativeMethod(vm, obj, "width", &MailboxWrapper::Width, rets);
  m->SetSynthName(synth::kMailboxWidth);
  m = Method::InstallNativeMethod(vm, obj, "put", &MailboxWrapper::Put, rets);
  m->SetSynthName(synth::kMailboxPut);
  rets[0] = Method::IntType(width);
  m = Method::InstallNativeMethod(vm, obj, "get", &MailboxWrapper::Get, rets);
  m->SetSynthName(synth::kMailboxGet);
}

void MailboxWrapper::Width(Thread *thr, Object *obj,
			   const vector<Value> &args) {
  Value value;
  value.type_ = Value::NUM;
  value.num_.int_part = GetWidth(obj);
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
    Wake(true, data);
  } else {
    data->get_waiters_.insert(thr);
    thr->Suspend();
  }
}

void MailboxWrapper::Put(Thread *thr, Object *obj,
			 const vector<Value> &args) {
  MailboxData *data = (MailboxData *)obj->object_specific_.get();
  if (data->has_value_) {
    data->get_waiters_.insert(thr);
    thr->Suspend();
  } else {
    data->has_value_ = true;
    data->number_ = args[0].num_;
    Wake(false, data);
  }
}

void MailboxWrapper::Wake(bool wake_put, MailboxData *data) {
  set<Thread *> *s;
  if (wake_put) {
    s = &data->put_waiters_;
  } else {
    s = &data->get_waiters_;
  }
  if (s->size() == 0) {
    return;
  }
  Thread *t = *(s->begin());
  s->erase(t);
  t->Resume();
}

}  // namespace vm
