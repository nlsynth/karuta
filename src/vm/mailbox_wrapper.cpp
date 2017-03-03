#include "vm/mailbox_wrapper.h"

#include "vm/method.h"
#include "vm/object.h"
#include "vm/thread.h"
#include "vm/vm.h"

namespace vm {

static const char *kMailboxObjectKey = "mailbox";

class MailboxData : public ObjectSpecificData {
public:
  MailboxData(int width) : width_(width) {
  }

  int width_;
};

Object *MailboxWrapper::NewMailbox(VM *vm, int width, sym_t name) {
  Object *mailbox_obj = vm->root_object_->Clone(vm);
  InstallMethods(vm, mailbox_obj);
  mailbox_obj->object_specific_.reset(new MailboxData(width));
  return mailbox_obj;
}

bool MailboxWrapper::IsMailbox(Object *obj) {
  return (obj->ObjectTypeKey() == kMailboxObjectKey);
}

void MailboxWrapper::InstallMethods(VM *vm ,Object *obj) {
  vector<RegisterType> rets;
  rets.push_back(Method::IntType(32));
  Method::InstallNativeMethod(vm, obj, "width", &MailboxWrapper::Width, rets);
}

void MailboxWrapper::Width(Thread *thr, Object *obj,
			   const vector<Value> &args) {
  Value value;
  value.type_ = Value::NUM;
  MailboxData *data = (MailboxData *)obj->object_specific_.get();
  value.num_.int_part = data->width_;
  thr->SetReturnValueFromNativeMethod(value);
}

}  // namespace vm
