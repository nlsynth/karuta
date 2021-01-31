// -*- C++ -*-
#ifndef _vm_thread_h_
#define _vm_thread_h_

#include "vm/common.h"

namespace vm {

class Thread {
 public:
  Thread(VM *vm, Thread *parent, Object *obj, Method *method, int index);
  ~Thread();

  void Run();
  void Dump() const;
  void Dump(DumpStream &ds) const;
  bool IsRunnable() const;
  bool IsDone() const;
  void Suspend();
  void Exit();
  void Resume();
  bool Yield();

  VM *GetVM();
  static void SetByteCodeDebug(string flags);

  MethodFrame *PushMethodFrame(Object *obj, Method *method);

  void SetReturnValueFromNativeMethod(const Value &value);
  bool IsRootThread() const;

  // For GC.
  vector<MethodFrame *> &MethodStack();

  void UserError();

  // Busy look detection.
  // Consecutive jumps without thread suspend are considered to be a busy loop.
  bool OnJump();
  void MayBlock();

  void SetModuleName(const string &n);
  const string &GetModuleName();

 private:
  enum Stat { RUNNABLE, SUSPENDED, DONE };

  void RunMethod();
  void PassReturnValues();
  void PopMethodFrame();
  MethodFrame *CurrentMethodFrame() const;
  MethodFrame *ParentMethodFrame() const;
  void MaySetThreadIndex();

  static string dbg_bytecode_;

  VM *vm_;
  Stat stat_;
  Thread *parent_thread_;

  vector<MethodFrame *> method_stack_;
  bool in_yield_;
  int index_;
  string module_name_;
  long busy_counter_;
  long busy_counter_limit_;
};

}  // namespace vm

#endif  // _vm_thread_h_
