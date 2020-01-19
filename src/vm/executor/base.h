// -*- C++ -*-
#ifndef _vm_executor_base_h_
#define _vm_executor_base_h_

#include "vm/common.h"

// Mostly for inline methods.
#include "vm/common.h"
#include "vm/insn.h"
#include "vm/method.h"
#include "vm/method_frame.h"
#include "vm/opcode.h"
#include "vm/value.h"

namespace vm {
namespace executor {

class Base {
public:
  Base(Thread *thread, MethodFrame *frame) : thr_(thread), frame_(frame) {
  }
  
protected:
  void ExecMemberAccess();
  bool ExecFuncall();
  void ExecFuncallDone();
  Method *LookupMethod(Object **obj);
  Method *LookupCompiledMethod(Object **obj);
  void ExecLoadObj();
  void SetupCalleeFrame(Object *obj, Method *callee_method,
			const vector<Value> &args);
  void ExecStr();
  void ExecNum();
  void ExecBinop();
  void ExecIncDec();
  void ExecArrayRead();
  void ExecArrayWrite();
  void ExecNumUniop();
  void ExecLogicInv();
  void ExecNonNumResultBinop();
  bool ExecIf();
  bool ExecGoto();
  void ExecBitRange();
  
  void ExecMemberReadWithCheck();
  bool ExecFuncallWithCheck();
  void ExecFuncallDoneWithCheck();
  void ExecArrayWriteWithCheck();
  void ExecSetTypeObject();
  bool MayExecuteCustomOp();
  void ExecMayWithTypeDone();
  bool ExecCustomOp();
  void RetryBinopWithType();

  bool IsCustomOpCall();

  void PopulateArrayIndexes(int start, vector<uint64_t> *indexes);

  bool IsTopLevel() const {
    return frame_->method_->IsTopLevel();
  }
  enum OpCode op() const {
    return insn_->op_;
  }
  Value &VAL(Register *reg) const {
    return frame_->reg_values_[reg->id_];
  }
  Register *sreg(int idx) {
    return insn_->src_regs_[idx];
  }
  Register *dreg(int idx) {
    return insn_->dst_regs_[idx];
  }
  Register *oreg() {
    return insn_->obj_reg_;
  }

  // Set in ExecInsn().
  Insn *insn_;
  // Given from the constructor.
  Thread *thr_;
  MethodFrame *frame_;
};

}  // namespace executor
}  // namespace vm

#endif  // _vm_executor_base_h_
