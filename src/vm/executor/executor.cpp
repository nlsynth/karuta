#include "vm/executor/executor.h"

#include "vm/thread.h"

namespace vm {
namespace executor {

bool Executor::ExecInsn(Insn *insn) {
  insn_ = insn;
  bool need_suspend = false;
  switch (op()) {
  case OP_NUM:
    ExecNum();
    break;
  case OP_STR:
    ExecStr();
    break;
  case OP_ADD_MAY_WITH_TYPE:
  case OP_SUB_MAY_WITH_TYPE:
  case OP_MUL_MAY_WITH_TYPE:
  case OP_DIV_MAY_WITH_TYPE:
    if (MayExecuteCustomOp()) {
      need_suspend = true;
      if (!thr_->IsRunnable()) {
	return true;
      }
      break;
    }
    // fall through.
  case OP_ADD:
  case OP_SUB:
  case OP_MUL:
  case OP_DIV:
  case OP_ASSIGN:
  case OP_GT:
  case OP_LT:
  case OP_GTE:
  case OP_LTE:
  case OP_EQ:
  case OP_NE:
  case OP_LAND:
  case OP_LOR:
  case OP_AND:
  case OP_OR:
  case OP_XOR:
  case OP_CONCAT:
  case OP_LSHIFT:
  case OP_RSHIFT:
    ExecBinop();
    break;
  case OP_FUNCALL:
    need_suspend = ExecFuncall();
    if (!thr_->IsRunnable()) {
      return true;
    }
    break;
  case OP_FUNCALL_DONE:
    ExecFuncallDone();
    break;
  case OP_LOAD_OBJ:
    ExecLoadObj();
    break;
  case OP_IF:
    {
      bool v = ExecIf();
      // do not increment pc.
      return v;
    }
  case OP_GOTO:
    {
      bool v = ExecGoto();
      // do not increment pc.
      return v;
    }
  case OP_NOP:
    break;
  case OP_YIELD:
    need_suspend = ExecYield();
    break;
  case OP_PRE_INC:
  case OP_PRE_DEC:
    ExecIncDec();
    break;
  case OP_ARRAY_READ:
    ExecArrayRead();
    break;
  case OP_ARRAY_WRITE:
    ExecArrayWrite();
    break;
  case OP_LOGIC_INV:
    ExecLogicInv();
    break;
  case OP_BIT_INV:
  case OP_PLUS:
  case OP_MINUS:
    ExecNumUniop();
    break;
  case OP_MEMBER_READ:
  case OP_MEMBER_WRITE:
    ExecMemberAccess();
    break;
  case OP_BIT_RANGE:
    ExecBitRange();
    break;
  case OP_FUNCDECL:
    ExecFuncdecl();
    break;
  case OP_VARDECL:
    ExecVardecl();
    break;
  case OP_THREAD_DECL:
    ExecThreadDecl();
    break;
  case OP_CHANNEL_DECL:
    ExecChannelDecl();
    break;
  case OP_MAILBOX_DECL:
    ExecMailboxDecl();
    break;
  case OP_IMPORT:
    ExecImport();
    need_suspend = true;
    break;
  case OP_MEMBER_READ_WITH_CHECK:
    ExecMemberReadWithCheck();
    break;
  case OP_ARRAY_WRITE_WITH_CHECK:
    ExecArrayWriteWithCheck();
    break;
  case OP_FUNCALL_WITH_CHECK:
    need_suspend = ExecFuncallWithCheck();
    if (!thr_->IsRunnable()) {
      return true;
    }
    break;
  case OP_FUNCALL_DONE_WITH_CHECK:
    ExecFuncallDoneWithCheck();
    break;
  case OP_SET_TYPE_OBJECT:
    ExecSetTypeObject();
    break;
  case OP_PUSH_CURRENT_OBJECT:
    frame_->objs_.push_back(frame_->obj_);
    frame_->obj_ = VAL(oreg()).object_;
    break;
  case OP_POP_CURRENT_OBJECT:
    frame_->obj_ = *(frame_->objs_.rbegin());
    frame_->objs_.pop_back();
    break;
  case OP_MAY_WITH_TYPE_DONE:
    ExecMayWithTypeDone();
    break;
  default:
    CHECK(false) << "unknown insn:" << vm::OpCodeName(op());
  }
  ++frame_->pc_;
  return need_suspend;
}

}  // namespace executor
}  // namespace vm
