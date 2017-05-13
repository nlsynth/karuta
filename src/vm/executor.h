// -*- C++ -*-
#ifndef _vm_executor_h_
#define _vm_executor_h_

#include "vm/common.h"
#include "vm/value.h"

namespace vm {

class MethodFrame {
public:
  ~MethodFrame();

  Method *method_;
  size_t pc_;
  Object *obj_;
  vector<Value> reg_values_;
  // callee writes here.
  vector<Value> returns_;
};

class Executor {
public:
  Executor(Thread *thread);
  virtual ~Executor();

  virtual bool ExecInsn(Method *method, MethodFrame *frame, Insn *insn);

  Object *CreateMemoryObject(const numeric::Width *width,
			     int array_length,
			     fe::ArrayInitializer *array_initializer,
			     Annotation *an);
  Object *CreateObjectArray(int array_length);

  static IntArray *CreateIntArray(const numeric::Width *width,
				  int array_length,
				  fe::ArrayInitializer *array_initializer);

protected:
  void ExecMemberAccess(MethodFrame *frame, const Insn *insn);
  void ExecFuncallDone(const Method *method, MethodFrame *frame, Insn *insn);
  Method *LookupMethod(MethodFrame *frame, Insn *insn, Object **obj);
  void ExecLoadObj(MethodFrame *frame, Insn *insn);

  void ExecArrayWrite(MethodFrame *frame, Insn *insn);
  bool ExecChannelRead(MethodFrame *frame, Insn *insn);
  void ExecChannelWrite(const Method *method, MethodFrame *frame, Insn *insn);
  void ExecMemoryRead(MethodFrame *frame, Insn *insn);
  void ExecMemoryWrite(const Method *method, MethodFrame *frame, Insn *insn);

  void MemoryWrite(int addr, const numeric::Number &data);

  Thread *thr_;
private:
  void ExecStr(MethodFrame *frame, Insn *insn);
  void ExecBinop(const Method *method, MethodFrame *frame, Insn *insn);
  void ExecIncDec(MethodFrame *frame, Insn *insn);
  void ExecArrayRead(MethodFrame *frame, Insn *insn);
  void ExecNumUniop(MethodFrame *frame, Insn *insn);
  void ExecLogicInv(MethodFrame *frame, Insn *insn);
  void ExecNonNumResultBinop(const Method *method, MethodFrame *frame,
			     Insn *insn);
  bool ExecFuncall(MethodFrame *frame, Insn *insn);
  void ExecIf(MethodFrame *frame, Insn *insn);
  void ExecGoto(MethodFrame *frame, Insn *insn);
  void ExecBitRange(MethodFrame *frame, Insn *insn);
  void SetupCallee(Object *obj, Method *callee_method,
		   const vector<Value> &args);

  void MemoryRead(int addr, numeric::Number *res);

  static void InitializeArray(IntArray *array, fe::ArrayInitializer *array_initializer);
};

}  // namespace vm

#endif  // _vm_executor_h_
