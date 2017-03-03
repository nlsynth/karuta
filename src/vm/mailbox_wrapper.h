// -*- C++ -*-
#ifndef _vm_mailbox_wrapper_h_
#define _vm_mailbox_wrapper_h_

#include "vm/common.h"

namespace vm {

class MailboxWrapper {
public:
  static Object *NewMailbox(VM *vm, int width, sym_t name);
  static bool IsMailbox(Object *obj);

private:
  static void InstallMethods(VM *vm ,Object *obj);
  static void Width(Thread *thr, Object *obj, const vector<Value> &args);
};

}  // namespace vm

#endif  // _vm_mailbox_wrapper_h_
