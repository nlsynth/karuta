// -*- C++ -*-
#ifndef _vm_thread_h_
#define _vm_thread_h_

#include "vm/common.h"

namespace vm {

class Thread {
public:
  Thread(VM *vm, Thread *parent, Object *obj, Method *method);
  ~Thread();

  void Run();
  void Dump(DumpStream &ds) const;
  bool IsRunnable() const;
  bool IsDone() const;
  void Suspend();
  void Exit();
  void Resume();
  void SetInYield(bool in_yield);
  bool GetInYield();

  VM *GetVM();
  static void SetByteCodeDebug(bool enable);

  MethodFrame *PushMethodFrame(Object *obj, Method *method);

  void SetReturnValueFromNativeMethod(const Value &value);
  bool IsRootThread() const;

  // For GC.
  vector<MethodFrame*> &MethodStack();

  void UserError();

private:
  enum Stat {
    RUNNABLE, SUSPENDED, DONE
  };

  void RunMethod();
  void PassReturnValues();
  void PopMethodFrame();
  MethodFrame *CurrentMethodFrame() const;
  MethodFrame *ParentMethodFrame() const;

  static bool dbg_bytecode_;

  VM *vm_;
  Stat stat_;
  Thread *parent_thread_;

  std::unique_ptr<Executor> executor_;

  vector<MethodFrame*> method_stack_;
  bool in_yield_;
};

}  // namespace vm

#endif  // _vm_thread_h_
