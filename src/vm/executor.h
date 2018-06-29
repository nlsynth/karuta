// -*- C++ -*-
#ifndef _vm_executor_h_
#define _vm_executor_h_

#include "vm/common.h"
#include "vm/value.h"

namespace vm {

class MethodFrame {
public:
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

  bool ExecInsn(Method *method, MethodFrame *frame, Insn *insn);

private:
  void ExecMemberAccess(Method *method, MethodFrame *frame, const Insn *insn);
  bool ExecFuncall(MethodFrame *frame, Insn *insn);
  void ExecFuncallDone(const Method *method, MethodFrame *frame, Insn *insn);
  Method *LookupMethod(MethodFrame *frame, Insn *insn, Object **obj);
  Method *LookupCompiledMethod(MethodFrame *frame, Insn *insn, Object **obj);
  void ExecLoadObj(MethodFrame *frame, Insn *insn);
  void ExecArrayWrite(Method *method, MethodFrame *frame, Insn *insn);
  void SetupCallee(Object *obj, Method *callee_method,
		   const vector<Value> &args);
  void ExecStr(MethodFrame *frame, Insn *insn);
  void ExecBinop(const Method *method, MethodFrame *frame, Insn *insn);
  void ExecIncDec(MethodFrame *frame, Insn *insn);
  void ExecArrayRead(MethodFrame *frame, Insn *insn);
  void ExecNumUniop(MethodFrame *frame, Insn *insn);
  void ExecLogicInv(MethodFrame *frame, Insn *insn);
  void ExecNonNumResultBinop(const Method *method, MethodFrame *frame,
			     Insn *insn);
  void ExecIf(MethodFrame *frame, Insn *insn);
  void ExecGoto(MethodFrame *frame, Insn *insn);
  void ExecBitRange(const Method *method, MethodFrame *frame, Insn *insn);

  void MemoryRead(int addr, int data_width, iroha::Numeric *res);
  void MemoryWrite(uint64_t addr, int data_width, const iroha::Numeric &data);

  // for toplevel
  void ExecVardecl(const Method *method, MethodFrame *frame, Insn *insn);
  void ExecThreadDecl(const Method *method, MethodFrame *frame, Insn *insn);
  void ExecChannelDecl(const Method *method, MethodFrame *frame, Insn *insn);
  void ExecMailboxDecl(const Method *method, MethodFrame *frame, Insn *insn);
  
  void ExecImport(Insn *insn);
  void ExecFuncdecl(const Method *method, MethodFrame *frame, Insn *insn);
  void ExecMemberReadWithCheck(Method *method, MethodFrame *frame,
			       const Insn *insn);
  bool ExecFuncallWithCheck(MethodFrame *frame, Insn *insn);
  void ExecFuncallDoneWithCheck(const Method *method, MethodFrame *frame, Insn *insn);
  void ExecArrayWriteWithCheck(Method *method, MethodFrame *frame, Insn *insn);
  void ExecSetTypeObject(Method *method, Insn *insn);
  bool MayExecuteCustomOp(const Method *method, MethodFrame *frame, Insn *insn);
  void ExecMayWithTypeDone(const Method *method, MethodFrame *frame, Insn *insn);
  bool ExecCustomOp(const Method *method, MethodFrame *frame, Insn *insn);
  void RetryBinopWithType(const Method *method, MethodFrame *frame, Insn *insn);

  void AddThreadEntry(MethodFrame *frame, Insn *insn, const string &name,
		      int num, bool is_soft);
  void ClearThreadEntry(MethodFrame *frame, Insn *insn);
  bool IsCustomOpCall(const Method *method, Insn *insn);
  Object *CreateMemoryObject(const iroha::NumericWidth &width,
			     int array_length,
			     fe::ArrayInitializer *array_initializer,
			     Annotation *an);
  Object *CreateObjectArray(int array_length);
  IntArray *CreateIntArray(const iroha::NumericWidth &width,
			   int array_length,
			   fe::ArrayInitializer *array_initializer);
  void InitializeArray(IntArray *array,
		       fe::ArrayInitializer *array_initializer);


  Thread *thr_;
};

}  // namespace vm

#endif  // _vm_executor_h_
