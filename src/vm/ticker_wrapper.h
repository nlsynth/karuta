// -*- C++ -*-
#ifndef _vm_io_wrapper_h_
#define _vm_io_wrapper_h_

#include "vm/common.h"

namespace vm {

class TickerWrapper {
 public:
  static Object *NewTicker(VM *vm);

 private:
  static void GetTickCount(Thread *thr, Object *obj, const vector<Value> &args);
  static void DecrementTick(Thread *thr, Object *obj,
                            const vector<Value> &args);
};

}  // namespace vm

#endif  // _vm_io_wrapper_h_
