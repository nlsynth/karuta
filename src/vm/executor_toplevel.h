// -*- C++ -*-
#ifndef _vm_executor_toplevel_h_
#define _vm_executor_toplevel_h_

#include "vm/executor.h"

namespace vm {

class ExecutorToplevel : public Executor {
public:
  ExecutorToplevel(Thread *thr);

  virtual bool ExecInsn(Method *method, MethodFrame *frame, Insn *insn);

  void ExecVardecl(const Method *method, MethodFrame *frame, Insn *insn);
  void ExecThreadDecl(const Method *method, MethodFrame *frame, Insn *insn);
  void ExecChannelDecl(const Method *method, MethodFrame *frame, Insn *insn);
  void ExecMailboxDecl(const Method *method, MethodFrame *frame, Insn *insn);
  
  void ExecImport(Insn *insn);
  void ExecSpawn(MethodFrame *frame, Insn *insn);
  void ExecFuncdecl(const Method *method, MethodFrame *frame, Insn *insn);
  void ExecMemberAccess(Method *method, MethodFrame *frame, const Insn *insn);
  void ExecFuncallDone(const Method *method, MethodFrame *frame, Insn *insn);
  void ExecArrayWrite(Method *method, MethodFrame *frame, Insn *insn);
  bool ExecGenericRead(MethodFrame *frame, Insn *insn);
  void ExecGenericWrite(const Method *method, MethodFrame *frame, Insn *insn);
};

}  // namespace vm

#endif // _vm_executor_toplevel_h_
