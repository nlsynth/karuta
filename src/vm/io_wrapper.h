// -*- C++ -*-
#ifndef _vm_io_wrapper_h_
#define _vm_io_wrapper_h_

#include "vm/common.h"

namespace vm {

class IOWrapper {
public:
  static bool IsIO(Object *obj);
  static Object *NewIOWrapper(VM *vm, sym_t name, bool is_output,
			      const iroha::NumericWidth &width);

private:
  static void InstallMethods(VM* vm, Object *obj, bool is_output,
			     const iroha::NumericWidth &width);

  static void Read(Thread *thr, Object *obj, const vector<Value> &args);
  static void Write(Thread *thr, Object *obj, const vector<Value> &args);
};

}  // namespace vm

#endif  // _vm_io_wrapper_h_
