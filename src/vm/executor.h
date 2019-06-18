// -*- C++ -*-
#ifndef _vm_executor_h_
#define _vm_executor_h_

#include "vm/common.h"
#include "vm/value.h"
#include "vm/method_frame.h"

namespace vm {

class Executor {
public:
  Executor(Thread *thread, MethodFrame *frame) : thr_(thread), frame_(frame) {
  }

  bool ExecInsn(Insn *insn);

private:
  void ExecMemberAccess(const Insn *insn);
  bool ExecFuncall(Insn *insn);
  void ExecFuncallDone(Insn *insn);
  Method *LookupMethod(Insn *insn, Object **obj);
  Method *LookupCompiledMethod(Insn *insn, Object **obj);
  void ExecLoadObj(Insn *insn);
  void SetupCalleeFrame(Object *obj, Method *callee_method,
			const vector<Value> &args);
  void ExecStr(Insn *insn);
  void ExecNum(Insn *insn);
  void ExecBinop(Insn *insn);
  void ExecIncDec(Insn *insn);
  void ExecArrayRead(Insn *insn);
  void ExecArrayWrite(Insn *insn);
  void ExecNumUniop(Insn *insn);
  void ExecLogicInv(Insn *insn);
  void ExecNonNumResultBinop(Insn *insn);
  void ExecIf(Insn *insn);
  bool ExecGoto(Insn *insn);
  void ExecBitRange(Insn *insn);

  // for toplevel
  void ExecVardecl(Insn *insn);
  void ExecThreadDecl(Insn *insn);
  void ExecChannelDecl(Insn *insn);
  void ExecMailboxDecl(Insn *insn);
  
  void ExecImport(Insn *insn);
  void ExecFuncdecl(Insn *insn);
  void ExecMemberReadWithCheck(const Insn *insn);
  bool ExecFuncallWithCheck(Insn *insn);
  void ExecFuncallDoneWithCheck(Insn *insn);
  void ExecArrayWriteWithCheck(Insn *insn);
  void ExecSetTypeObject(Insn *insn);
  bool MayExecuteCustomOp(Insn *insn);
  void ExecMayWithTypeDone(Insn *insn);
  bool ExecCustomOp(Insn *insn);
  void RetryBinopWithType(Insn *insn);

  void AddThreadEntry(Insn *insn, const string &name,
		      int num, bool is_soft);
  void ClearThreadEntry(Insn *insn);
  bool IsCustomOpCall(const Method *method, Insn *insn);
  Object *CreateMemoryObject(const iroha::NumericWidth &width,
			     fe::ArrayShape *shape,
			     fe::ArrayInitializer *array_initializer,
			     Annotation *an);
  Object *CreateObjectArray(fe::ArrayShape *shape);
  void InitializeArray(IntArray *array,
		       fe::ArrayInitializer *array_initializer);
  void PopulateArrayIndexes(Insn *insn, int start, vector<uint64_t> *indexes);

  Method *m() const {
    return frame_->method_;
  }

  Thread *thr_;
  MethodFrame *frame_;
};

}  // namespace vm

#endif  // _vm_executor_h_
