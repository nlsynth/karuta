// -*- C++ -*-
#ifndef _vm_mailbox_wrapper_h_
#define _vm_mailbox_wrapper_h_

#include "vm/common.h"

namespace vm {

class MailboxData;

class MailboxWrapper {
 public:
  static Object *NewMailbox(VM *vm, int width, sym_t name, Annotation *an);
  static bool IsMailbox(Object *obj);
  static int GetWidth(Object *obj);
  static Annotation *GetAnnotation(Object *obj);

 private:
  static void InstallMethods(VM *vm, Object *obj, int width);
  static void Width(Thread *thr, Object *obj, const vector<Value> &args);
  static void Put(Thread *thr, Object *obj, const vector<Value> &args);
  static void Get(Thread *thr, Object *obj, const vector<Value> &args);
  static void Notify(Thread *thr, Object *obj, const vector<Value> &args);
  static void Wait(Thread *thr, Object *obj, const vector<Value> &args);

  static void WakeOne(bool wake_put, MailboxData *data);
};

}  // namespace vm

#endif  // _vm_mailbox_wrapper_h_
