// -*- C++ -*-
#ifndef _vm_array_wrapper_h_
#define _vm_array_wrapper_h_

#include "vm/common.h"

namespace vm {

class ArrayWrapper {
public:
  static bool IsObjectArray(Object *obj);
  static bool IsIntArray(Object *obj);
  static string ToString(Object *obj);

  static Object *NewObjectArrayWrapper(VM *vm, int size);
  static Object *NewIntArrayWrapper(VM *vm, uint64_t size,
				    const iroha::NumericWidth &width,
				    Annotation *an);
  static Object *Copy(VM *vm, Object *obj);

  static Object *Get(Object *obj, int nth);
  static void Set(Object *obj, int nth, Object *elem);
  static IntArray *GetIntArray(Object *obj);
  static Annotation *GetAnnotation(Object *obj);
  static int GetDataWidth(Object *obj);
  static void InstallSramIfMethods(VM *vm ,Object *obj);

private:
  static void AxiLoad(Thread *thr, Object *obj, const vector<Value> &args);
  static void AxiStore(Thread *thr, Object *obj, const vector<Value> &args);
  static void Wait(Thread *thr, Object *obj, const vector<Value> &args);
  static void Read(Thread *thr, Object *obj, const vector<Value> &args);
  static void Write(Thread *thr, Object *obj, const vector<Value> &args);
  static void MemBurstAccess(Thread *thr, Object *obj,
			     const vector<Value> &args, bool is_load);
  static void InstallMethods(VM *vm ,Object *obj);
  static void MayNotifyWaiters(Object *obj);
};

}  // namespace vm

#endif // _vm_array_wrapper_h_
