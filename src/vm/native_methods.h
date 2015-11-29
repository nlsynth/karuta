// -*- C++ -*-
#ifndef _vm_native_methods_h_
#define _vm_native_methods_h_

#include "nli.h"
#include "vm/value.h"

namespace vm {

class Object;
class Thread;

class NativeMethods {
public:
  // Kernel.
  static void Assert(Thread *thr, Object *obj, const vector<Value> &args);
  static void Clone(Thread *thr, Object *obj, const vector<Value> &args);
  static void Compile(Thread *thr, Object *obj, const vector<Value> &args);
  static void Dump(Thread *thr, Object *obj, const vector<Value> &args);
  static void Exit(Thread *thr, Object *obj, const vector<Value> &args);
  static void Channel(Thread *thr, Object *obj, const vector<Value> &args);
  static void Print(Thread *thr, Object *obj, const vector<Value> &args);
  static void Run(Thread *thr, Object *obj, const vector<Value> &args);
  static void SetDump(Thread *thr, Object *obj, const vector<Value> &args);
  static void SetSynthParam(Thread *thr, Object *obj,
			    const vector<Value> &args);
  static void WidthOf(Thread *thr, Object *obj, const vector<Value> &args);
  static void WriteHdl(Thread *thr, Object *obj, const vector<Value> &args);

  // Env.
  static void IsMain(Thread *thr, Object *obj, const vector<Value> &args);
  static void GC(Thread *thr, Object *obj, const vector<Value> &args);

  static void SetReturnValue(Thread *thr, const Value &value);
};

}  // namespace vm

#endif  // _vm_native_methods_h_
