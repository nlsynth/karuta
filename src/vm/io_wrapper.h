// -*- C++ -*-
#ifndef _vm_io_wrapper_h_
#define _vm_io_wrapper_h_

#include "vm/common.h"

namespace vm {

class IOWrapper {
public:
  static bool IsIO(Object *obj);
  static Object *NewIOWrapper(VM *vm, const string &name, bool is_output,
			      const iroha::NumericWidth &width, int distance);
  static bool IsOutput(Object *obj);
  static const string &GetName(Object *obj);
  static int GetDistance(Object *obj);
  static int GetWidth(Object *obj);

private:
  static void InstallMethods(VM* vm, Object *obj, bool is_output,
			     const iroha::NumericWidth &width);

  static void Peek(Thread *thr, Object *obj, const vector<Value> &args);
  static void Read(Thread *thr, Object *obj, const vector<Value> &args);
  static void Write(Thread *thr, Object *obj, const vector<Value> &args);
};

}  // namespace vm

#endif  // _vm_io_wrapper_h_
