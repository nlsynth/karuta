// -*- C++ -*-
#ifndef _vm_channel_wrapper_h_
#define _vm_channel_wrapper_h_

#include "vm/common.h"

namespace vm {

class ChannelWrapper {
public:
  static Object *NewChannel(VM *vm, int width, sym_t name, Annotation *an);

  static bool IsChannel(Object *obj);
  static const string &ChannelName(Object *obj);
  static int ChannelWidth(Object *obj);
  static int ChannelDepth(Object *obj);

  static void ReadMethod(Thread *thr, Object *obj, const vector<Value> &args);
  static void WriteMethod(Thread *thr, Object *obj, const vector<Value> &args);

  static void WriteValue(const Value &value, Object *obj);
  static bool ReadValue(Thread *thr, Object *obj, Value *value);

private:
  static void BlockOnThis(Thread *thr, Object *obj);
};

}  // namespace vm

#endif  // _vm_channel_wrapper_h_
