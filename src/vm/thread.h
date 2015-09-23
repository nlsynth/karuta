// -*- C++ -*-
#ifndef _vm_thread_h_
#define _vm_thread_h_

#include "nli.h"

class DumpStream;

namespace vm {

class Executor;
class ExecutorToplevel;
class Insn;
class Method;
class MethodFrame;
class Object;
class Value;
class VM;

class Thread {
public:
  Thread(VM *vm, Thread *parent, Method *method);
  ~Thread();

  void Run();
  void Dump(DumpStream &ds) const;
  bool IsRunnable() const;
  bool IsDone() const;
  void Suspend();
  void Exit();
  void Resume();

  VM *GetVM();
  static void SetByteCodeDebug(bool enable);

  MethodFrame *PushMethodFrame(Object *obj, Method *method);

  void SetReturnValueFromNativeMethod(const Value &value);
  bool IsRootThread() const;

  void UserError(const char *msg);

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
  std::unique_ptr<ExecutorToplevel> executor_toplevel_;

  vector<MethodFrame*> method_stack_;
};

}  // namespace vm

#endif  // _vm_thread_h_
