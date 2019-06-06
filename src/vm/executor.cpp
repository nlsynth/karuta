#include "vm/executor.h"

#include "base/annotation.h"
#include "base/dump_stream.h"
#include "base/status.h"
#include "compiler/compiler.h"
#include "vm/distance_wrapper.h"
#include "fe/fe.h"
#include "fe/expr.h"
#include "fe/stmt.h"
#include "fe/nodecode.h"
#include "fe/var_decl.h"
#include "numeric/numeric_op.h"  // from iroha
#include "vm/array_wrapper.h"
#include "vm/channel_wrapper.h"
#include "vm/decl_annotator.h"
#include "vm/insn.h"
#include "vm/insn_annotator.h"
#include "vm/int_array.h"
#include "vm/string_wrapper.h"
#include "vm/thread.h"
#include "vm/thread_wrapper.h"
#include "vm/tls_wrapper.h"
#include "vm/mailbox_wrapper.h"
#include "vm/method.h"
#include "vm/numeric_object.h"
#include "vm/object.h"
#include "vm/opcode.h"
#include "vm/vm.h"

namespace vm {

Executor::Executor(Thread *thread) : thr_(thread) {
}

Object *Executor::CreateMemoryObject(const iroha::NumericWidth &width,
				     fe::ArrayShape *shape,
				     fe::ArrayInitializer *array_initializer,
				     Annotation *an) {
  vector<uint64_t> s;
  for (auto i : shape->length) {
    s.push_back(i);
  }
  Object *obj = ArrayWrapper::NewIntArrayWrapper(thr_->GetVM(),
						 s, width, an);
  IntArray *memory = ArrayWrapper::GetIntArray(obj);
  InitializeArray(memory, array_initializer);
  return obj;
}

Object *Executor::CreateObjectArray(fe::ArrayShape *shape) {
  return ArrayWrapper::NewObjectArrayWrapper(thr_->GetVM(), shape->length[0]);
}

bool Executor::ExecInsn(Method *method, MethodFrame *frame, Insn *insn) {
  bool need_suspend = false;
  switch (insn->op_) {
  case OP_NUM:
    {
      int dst = insn->dst_regs_[0]->id_;
      frame->reg_values_[dst].num_ = insn->src_regs_[0]->initial_num_;
      if (method->IsTopLevel()) {
	frame->reg_values_[dst].type_ = Value::NUM;
	frame->reg_values_[dst].num_.type_ =
	  method->method_regs_[dst]->type_.width_;
      }
    }
    break;
  case OP_STR:
    ExecStr(method, frame, insn);
    break;
  case OP_ADD_MAY_WITH_TYPE:
  case OP_SUB_MAY_WITH_TYPE:
  case OP_MUL_MAY_WITH_TYPE:
  case OP_DIV_MAY_WITH_TYPE:
    if (MayExecuteCustomOp(method, frame, insn)) {
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
    ExecBinop(method, frame, insn);
    break;
  case OP_FUNCALL:
    need_suspend = ExecFuncall(frame, insn);
    if (!thr_->IsRunnable()) {
      return true;
    }
    break;
  case OP_FUNCALL_DONE:
    ExecFuncallDone(method, frame, insn);
    break;
  case OP_LOAD_OBJ:
    ExecLoadObj(frame, insn);
    break;
  case OP_IF:
    ExecIf(frame, insn);
    // do not increment pc.
    return false;
  case OP_GOTO:
    {
      bool v = ExecGoto(frame, insn);
      // do not increment pc.
      return v;
    }
  case OP_NOP:
    break;
  case OP_PRE_INC:
  case OP_PRE_DEC:
    ExecIncDec(frame, insn);
    break;
  case OP_ARRAY_READ:
    ExecArrayRead(method, frame, insn);
    break;
  case OP_ARRAY_WRITE:
    ExecArrayWrite(method, frame, insn);
    break;
  case OP_LOGIC_INV:
    ExecLogicInv(frame, insn);
    break;
  case OP_BIT_INV:
  case OP_PLUS:
  case OP_MINUS:
    ExecNumUniop(frame, insn);
    break;
  case OP_MEMBER_READ:
  case OP_MEMBER_WRITE:
    ExecMemberAccess(method, frame, insn);
    break;
  case OP_BIT_RANGE:
    ExecBitRange(method, frame, insn);
    break;
  case OP_FUNCDECL:
    ExecFuncdecl(method, frame, insn);
    break;
  case OP_VARDECL:
    ExecVardecl(method, frame, insn);
    break;
  case OP_THREAD_DECL:
    ExecThreadDecl(method, frame, insn);
    break;
  case OP_CHANNEL_DECL:
    ExecChannelDecl(method, frame, insn);
    break;
  case OP_MAILBOX_DECL:
    ExecMailboxDecl(method, frame, insn);
    break;
  case OP_IMPORT:
    ExecImport(frame, insn);
    need_suspend = true;
    break;
  case OP_MEMBER_READ_WITH_CHECK:
    ExecMemberReadWithCheck(method, frame, insn);
    break;
  case OP_ARRAY_WRITE_WITH_CHECK:
    ExecArrayWriteWithCheck(method, frame, insn);
    break;
  case OP_FUNCALL_WITH_CHECK:
    need_suspend = ExecFuncallWithCheck(frame, insn);
    if (!thr_->IsRunnable()) {
      return true;
    }
    break;
  case OP_FUNCALL_DONE_WITH_CHECK:
    ExecFuncallDoneWithCheck(method, frame, insn);
    break;
  case OP_SET_TYPE_OBJECT:
    ExecSetTypeObject(method, insn);
    break;
  case OP_MAY_WITH_TYPE_DONE:
    ExecMayWithTypeDone(method, frame, insn);
    break;
  default:
    CHECK(false) << "unknown insn:" << vm::OpCodeName(insn->op_);
  }
  ++frame->pc_;
  return need_suspend;
}

void Executor::ExecStr(const Method *method, MethodFrame *frame, Insn *insn) {
  int dst = insn->dst_regs_[0]->id_;
  frame->reg_values_[dst].object_ =
    StringWrapper::NewStringWrapper(thr_->GetVM(), InsnOpUtils::Str(insn));
  if (method->IsTopLevel()) {
    frame->reg_values_[dst].type_ = Value::OBJECT;
  }
}

void Executor::ExecBinop(const Method *method, MethodFrame *frame,
			 Insn *insn) {
  int dst = insn->dst_regs_[0]->id_;
  if (method->method_regs_[dst]->type_.value_type_ != Value::NUM) {
    if (method->method_regs_[dst]->type_.value_type_ == Value::NONE) {
      RetryBinopWithType(method, frame, insn);
    } else {
      ExecNonNumResultBinop(method, frame, insn);
    }
    return;
  }
  int lhs = insn->src_regs_[0]->id_;
  int rhs = insn->src_regs_[1]->id_;
  if (method->IsTopLevel()) {
    if (InsnType::IsNumCalculation(insn->op_)) {
      InsnAnnotator::AnnotateNumCalculationOp(insn);
    }
    if (insn->op_ == OP_LSHIFT || insn->op_ == OP_RSHIFT) {
      frame->reg_values_[dst].num_.type_ =
	frame->method_->method_regs_[lhs]->type_.width_;
    }
  }
  switch (insn->op_) {
  case OP_ADD:
  case OP_ADD_MAY_WITH_TYPE:
    iroha::Op::Add(frame->reg_values_[lhs].num_,
		   frame->reg_values_[rhs].num_,
		   &frame->reg_values_[dst].num_);
    iroha::Op::FixupWidth(frame->method_->method_regs_[dst]->type_.width_,
			  &frame->reg_values_[dst].num_);
    break;
  case OP_SUB:
  case OP_SUB_MAY_WITH_TYPE:
    iroha::Op::Sub(frame->reg_values_[lhs].num_,
		   frame->reg_values_[rhs].num_,
		   &frame->reg_values_[dst].num_);
    iroha::Op::FixupWidth(frame->method_->method_regs_[dst]->type_.width_,
			  &frame->reg_values_[dst].num_);
    break;
  case OP_MUL:
  case OP_MUL_MAY_WITH_TYPE:
    iroha::Op::CalcBinOp(iroha::BINOP_MUL,
			 frame->reg_values_[lhs].num_,
			 frame->reg_values_[rhs].num_,
			 &frame->reg_values_[dst].num_);
    iroha::Op::FixupWidth(frame->method_->method_regs_[dst]->type_.width_,
			  &frame->reg_values_[dst].num_);
    break;
  case OP_DIV:
  case OP_DIV_MAY_WITH_TYPE:
    iroha::Op::CalcBinOp(iroha::BINOP_DIV,
			 frame->reg_values_[lhs].num_,
			 frame->reg_values_[rhs].num_,
			 &frame->reg_values_[dst].num_);
    iroha::Op::FixupWidth(frame->method_->method_regs_[dst]->type_.width_,
			  &frame->reg_values_[dst].num_);
    break;
  case OP_ASSIGN:
    iroha::Numeric::CopyValueWithWidth(frame->reg_values_[rhs].num_.GetArray(),
				       frame->reg_values_[rhs].num_.type_,
				       frame->method_->method_regs_[dst]->type_.width_,
				       nullptr,
				       frame->reg_values_[dst].num_.GetMutableArray());
    iroha::Op::FixupWidth(frame->method_->method_regs_[dst]->type_.width_,
			  &frame->reg_values_[dst].num_);
    if (method->IsTopLevel() &&
	!frame->method_->method_regs_[dst]->GetIsDeclaredType()) {
      frame->method_->method_regs_[dst]->type_ =
	frame->method_->method_regs_[rhs]->type_;
    }
    break;
  case OP_AND:
    iroha::Op::CalcBinOp(iroha::BINOP_AND,
			 frame->reg_values_[lhs].num_,
			 frame->reg_values_[rhs].num_,
			 &frame->reg_values_[dst].num_);
    break;
  case OP_OR:
    iroha::Op::CalcBinOp(iroha::BINOP_OR,
			 frame->reg_values_[lhs].num_,
			 frame->reg_values_[rhs].num_,
			 &frame->reg_values_[dst].num_);
    break;
  case OP_XOR:
    iroha::Op::CalcBinOp(iroha::BINOP_XOR,
			 frame->reg_values_[lhs].num_,
			 frame->reg_values_[rhs].num_,
			 &frame->reg_values_[dst].num_);
    break;
  case OP_CONCAT:
    {
      iroha::Numeric l = frame->reg_values_[lhs].num_;
      iroha::Numeric r = frame->reg_values_[rhs].num_;
      l.type_ = frame->method_->method_regs_[lhs]->type_.width_;
      r.type_ =	frame->method_->method_regs_[rhs]->type_.width_;
      iroha::Op::Concat(l, r,
			&frame->reg_values_[dst].num_);
    }
    break;
  case OP_LSHIFT:
    iroha::Op::CalcBinOp(iroha::BINOP_LSHIFT,
			 frame->reg_values_[lhs].num_,
			 frame->reg_values_[rhs].num_,
			 &frame->reg_values_[dst].num_);
    iroha::Op::FixupWidth(frame->method_->method_regs_[dst]->type_.width_,
			  &frame->reg_values_[dst].num_);
    break;
  case OP_RSHIFT:
    iroha::Op::CalcBinOp(iroha::BINOP_RSHIFT,
			 frame->reg_values_[lhs].num_,
			 frame->reg_values_[rhs].num_,
			 &frame->reg_values_[dst].num_);
    iroha::Op::FixupWidth(frame->method_->method_regs_[dst]->type_.width_,
			  &frame->reg_values_[dst].num_);
    break;
  default:
    CHECK(false) << "unknown binop:" << vm::OpCodeName(insn->op_);
  }
}

void Executor::RetryBinopWithType(const Method *method, MethodFrame *frame, Insn *insn) {
  if (insn->op_ == OP_CONCAT) {
    InsnAnnotator::AnnotateConcatInsn(insn);
    // TODO: Annotate other types of insns.
  } else {
    CHECK(insn->op_ == OP_ADD_MAY_WITH_TYPE ||
	  insn->op_ == OP_SUB_MAY_WITH_TYPE ||
	  insn->op_ == OP_MUL_MAY_WITH_TYPE ||
	  insn->op_ == OP_DIV_MAY_WITH_TYPE);
  }
  int lhs = insn->src_regs_[0]->id_;
  int rhs = insn->src_regs_[1]->id_;
  CHECK(method->method_regs_[lhs]->type_.value_type_ ==
	method->method_regs_[rhs]->type_.value_type_);
  int dst = insn->dst_regs_[0]->id_;
  if (method->method_regs_[lhs]->type_.value_type_ == Value::NUM) {
    method->method_regs_[dst]->type_.value_type_ = Value::NUM;
  } else if (method->method_regs_[lhs]->type_.value_type_ == Value::OBJECT) {
    method->method_regs_[dst]->type_.value_type_ = Value::OBJECT;
  }
  ExecBinop(method, frame, insn);
}

void Executor::ExecArrayRead(const Method *method, MethodFrame *frame,
			     Insn *insn) {
  CHECK(insn->obj_reg_ != nullptr);
  Object *array_obj = frame->reg_values_[insn->obj_reg_->id_].object_;
  CHECK(array_obj);
  Value &lhs_value = frame->reg_values_[insn->dst_regs_[0]->id_];
  auto *dst_reg = insn->dst_regs_[0];
  if (ArrayWrapper::IsIntArray(array_obj)) {
    IntArray *array = ArrayWrapper::GetIntArray(array_obj);
    vector<uint64_t> indexes;
    PopulateArrayIndexes(frame, insn, 0, &indexes);
    lhs_value.num_ = array->Read(indexes);
    if (method->IsTopLevel()) {
      dst_reg->type_.value_type_ = Value::NUM;
      dst_reg->type_.width_ = array->GetDataWidth();
    }
  } else {
    CHECK(ArrayWrapper::IsObjectArray(array_obj));
    int index = frame->reg_values_[insn->src_regs_[0]->id_].num_.GetValue0();
    lhs_value.type_ = Value::OBJECT;
    lhs_value.object_ = ArrayWrapper::Get(array_obj, index);
    if (method->IsTopLevel()) {
      dst_reg->type_.value_type_ = Value::OBJECT;
    }
  }
}

void Executor::ExecArrayWrite(Method *method, MethodFrame *frame, Insn *insn) {
  CHECK(insn->obj_reg_ != nullptr);
  Object *array_obj = frame->reg_values_[insn->obj_reg_->id_].object_;
  CHECK(array_obj);
  if (ArrayWrapper::IsIntArray(array_obj)) {
    IntArray *array = ArrayWrapper::GetIntArray(array_obj);
    vector<uint64_t> indexes;
    PopulateArrayIndexes(frame, insn, 1, &indexes);
    array->Write(indexes,
		 frame->reg_values_[insn->src_regs_[0]->id_].num_);
  } else {
    CHECK(ArrayWrapper::IsObjectArray(array_obj));
    CHECK(method->method_regs_[insn->src_regs_[0]->id_]->type_.value_type_
	  == Value::OBJECT);
    int index = frame->reg_values_[insn->src_regs_[1]->id_].num_.GetValue0();
    ArrayWrapper::Set(array_obj, index,
		      frame->reg_values_[insn->src_regs_[0]->id_].object_);
  }
}

void Executor::PopulateArrayIndexes(MethodFrame *frame, Insn *insn, int start,
				    vector<uint64_t> *indexes) {
  for (int i = start; i < insn->src_regs_.size(); ++i) {
    uint64_t v = frame->reg_values_[insn->src_regs_[i]->id_].num_.GetValue0();
    indexes->push_back(v);
  }
}

void Executor::ExecLogicInv(MethodFrame *frame, Insn *insn) {
  int val = 1;
  Value &value = frame->reg_values_[insn->src_regs_[0]->id_];
  if (value.type_ == Value::ENUM_ITEM) {
    if (value.enum_val_.val != 0) {
      val = 0;
    }
  } else if (value.type_ == Value::NUM) {
    if (!iroha::Op::IsZero(value.num_)) {
      val = 0;
    }
  }
  Value &dst_value = frame->reg_values_[insn->dst_regs_[0]->id_];
  dst_value.enum_val_.val = val;
}

void Executor::ExecNumUniop(MethodFrame *frame, Insn *insn) {
  Value &value = frame->reg_values_[insn->src_regs_[0]->id_];
  Value &dst_value = frame->reg_values_[insn->dst_regs_[0]->id_];
  if (value.type_ == Value::ENUM_ITEM) {
    CHECK(insn->op_ == OP_BIT_INV);
    if (value.enum_val_.val) {
      dst_value.enum_val_.val = 0;
    } else {
      dst_value.enum_val_.val = 1;
    }
    return;
  }
  iroha::Numeric res;
  switch (insn->op_) {
  case OP_BIT_INV:
    iroha::Op::BitInv(value.num_, &res);
    break;
  case OP_PLUS:
    res = value.num_;
    break;
  case OP_MINUS:
    iroha::Op::Minus(value.num_, &res);
    break;
  default:
    CHECK(false);
    break;
  }
  int dst_id = insn->dst_regs_[0]->id_;
  iroha::Op::FixupWidth(frame->method_->method_regs_[dst_id]->type_.width_,
			&res);
  dst_value.num_ = res;
}

void Executor::ExecLoadObj(MethodFrame *frame, Insn *insn) {
  Value &dst_value = frame->reg_values_[insn->dst_regs_[0]->id_];
  Value *obj_value;
  if (insn->label_) {
    Object *src_obj;
    if (insn->obj_reg_) {
      src_obj = frame->reg_values_[insn->obj_reg_->id_].object_;
    } else {
      src_obj = frame->obj_;
    }
    obj_value = src_obj->LookupValue(insn->label_, false);
    CHECK(obj_value) << "Failed to LoadObj: " << sym_cstr(insn->label_);
    CHECK(obj_value->IsObjectType()) << " is not a object";
    dst_value.object_ = obj_value->object_;
    dst_value.type_ = obj_value->type_;
  } else {
    dst_value.object_ = frame->obj_;
    dst_value.type_ = Value::OBJECT;
  }
}

void Executor::ExecIncDec(MethodFrame *frame, Insn *insn) {
  int target = insn->dst_regs_[0]->id_;
  iroha::Numeric n1;
  iroha::Op::MakeConst(1, &n1);
  iroha::Numeric res;
  if (insn->op_ == OP_PRE_INC) {
    iroha::Op::Add(frame->reg_values_[target].num_, n1, &res);
  } else {
    iroha::Op::Sub(frame->reg_values_[target].num_, n1, &res);
  }
  iroha::Op::FixupWidth(frame->method_->method_regs_[target]->type_.width_, &res);
  res.type_ = frame->method_->method_regs_[target]->type_.width_;
  frame->reg_values_[target].num_ = res;
}

void Executor::ExecNonNumResultBinop(const Method *method, MethodFrame *frame,
				     Insn *insn) {
  int dst = insn->dst_regs_[0]->id_;
  int lhs = insn->src_regs_[0]->id_;
  int rhs = insn->src_regs_[1]->id_;
  switch (insn->op_) {
  case OP_ASSIGN:
    frame->reg_values_[lhs] = frame->reg_values_[rhs];
    frame->reg_values_[dst] = frame->reg_values_[rhs];
    break;
  case OP_LAND:
    frame->reg_values_[dst].enum_val_.val =
      frame->reg_values_[lhs].enum_val_.val &&
      frame->reg_values_[rhs].enum_val_.val;
    break;
  case OP_LOR:
    frame->reg_values_[dst].enum_val_.val =
      frame->reg_values_[lhs].enum_val_.val ||
      frame->reg_values_[rhs].enum_val_.val;
    break;
  case OP_GT:
  case OP_LT:
  case OP_GTE:
  case OP_LTE:
    {
      // fall through.
      CHECK(method->method_regs_[lhs]->type_.value_type_ == Value::NUM &&
	    method->method_regs_[rhs]->type_.value_type_ == Value::NUM);
    }
  case OP_EQ:
  case OP_NE:
    {
      bool r;
      if (method->method_regs_[rhs]->type_.value_type_ == Value::NUM) {
	iroha::CompareOp op;
	switch (insn->op_) {
	case OP_LT:
	case OP_GTE:
	  op = iroha::COMPARE_LT;
	  break;
	case OP_GT:
	case OP_LTE:
	  op = iroha::COMPARE_GT;
	  break;
	case OP_EQ:
	case OP_NE:
	  op = iroha::COMPARE_EQ;
	  break;
	default:
	  op = iroha::COMPARE_EQ;
	  CHECK(false);
	  break;
	}
	r = iroha::Op::Compare(op, frame->reg_values_[lhs].num_,
			       frame->reg_values_[rhs].num_);
      } else if (method->method_regs_[rhs]->type_.value_type_ == Value::ENUM_ITEM) {
	r = (frame->reg_values_[lhs].enum_val_.val ==
	     frame->reg_values_[rhs].enum_val_.val);
      } else {
	r = frame->reg_values_[lhs].object_->Compare(frame->reg_values_[rhs].object_);
      }
      if (insn->op_ == OP_NE || insn->op_ == OP_GTE ||
	  insn->op_ == OP_LTE) {
	r = !r;
      }
      frame->reg_values_[dst].SetBool(r);
    }
    break;
  case OP_ADD:
  case OP_ADD_MAY_WITH_TYPE:
    {
      CHECK(method->method_regs_[lhs]->type_.value_type_ ==
	    method->method_regs_[rhs]->type_.value_type_);
      CHECK(method->method_regs_[lhs]->type_.value_type_ == Value::OBJECT);
      string r = frame->reg_values_[lhs].object_->ToString() +
	frame->reg_values_[rhs].object_->ToString();
      frame->reg_values_[dst].object_ =
	StringWrapper::NewStringWrapper(thr_->GetVM(), r);
    }
    break;
  default:
    CHECK(false) << "unknown non num binop:" << vm::OpCodeName(insn->op_);
  }
}

bool Executor::ExecGoto(MethodFrame *frame, Insn *insn) {
  frame->pc_ = insn->jump_target_;
  return thr_->OnJump();
}

void Executor::ExecIf(MethodFrame *frame, Insn *insn) {
  int cond = insn->src_regs_[0]->id_;
  Value &cond_val = frame->reg_values_[cond];
  CHECK(cond_val.type_ == Value::ENUM_ITEM);
  if (cond_val.enum_val_.val) {
    ++frame->pc_;
  } else {
    frame->pc_ = insn->jump_target_;
  }
}

bool Executor::ExecFuncall(MethodFrame *frame,
			   Insn *insn) {
  Object *obj;
  Method *callee_method = LookupCompiledMethod(frame, insn, &obj);
  if (callee_method == nullptr) {
    return true;
  }
  vector<Value> args;
  for (size_t i = 0; i < insn->src_regs_.size(); ++i) {
    args.push_back(frame->reg_values_[insn->src_regs_[i]->id_]);
  }
  auto fn = callee_method->GetMethodFunc();
  if (fn != nullptr) {
    // Native method call (implementation in C++).
    // Copy types of argument values too, since (most of) native methods
    // don't assume argument types.
    for (size_t i = 0; i < insn->src_regs_.size(); ++i) {
      args[i].type_ = insn->src_regs_[i]->type_.value_type_;
      args[i].num_.type_ = insn->src_regs_[i]->type_.width_;
    }
    fn(thr_, obj, args);
    if (!thr_->IsRunnable()) {
      return true;
    }
  } else {
    // Karuta method.
    SetupCalleeFrame(obj, callee_method, args);
    return true;
  }
  return false;
}

Method *Executor::LookupCompiledMethod(MethodFrame *frame, Insn *insn,
				       Object **obj) {
  Method *method = LookupMethod(frame, insn, obj);
  if (method == nullptr) {
    return nullptr;
  }
  compiler::Compiler::CompileMethod(thr_->GetVM(), *obj, method);
  if (method->IsCompileFailure()) {
    return nullptr;
  }
  return method;
}

Method *Executor::LookupMethod(MethodFrame *frame, Insn *insn,
			       Object **obj) {
  Value &obj_value = frame->reg_values_[insn->obj_reg_->id_];
  CHECK(obj_value.IsObjectType());
  *obj = obj_value.object_;
  Value *value = (*obj)->LookupValue(insn->label_, false);
  if (!value) {
    Status::os(Status::USER_ERROR) << "method not found: "
				   << sym_cstr(insn->label_);
    thr_->UserError();
    return nullptr;
  }
  CHECK(value->type_ == Value::METHOD);
  return value->method_;
}

void Executor::ExecFuncallDone(const Method *method,
			       MethodFrame *frame,
			       Insn *insn) {
  for (size_t i = 0; i < insn->dst_regs_.size() &&
	 i < frame->returns_.size(); ++i) {
    frame->reg_values_[insn->dst_regs_[i]->id_] = frame->returns_[i];
  }
  frame->returns_.clear();
}

void Executor::SetupCalleeFrame(Object *obj, Method *callee_method,
				const vector<Value> &args) {
  MethodFrame *frame = thr_->PushMethodFrame(obj, callee_method);
  for (size_t i = 0; i < args.size(); ++i) {
    frame->reg_values_[i] = args[i];
    const iroha::NumericWidth &width = callee_method->GetNthArgWidth(i);
    frame->reg_values_[i].num_.type_ = width;
  }
}

void Executor::ExecMemberAccess(Method *method, MethodFrame *frame,
				const Insn *insn) {
  Object *obj;
  if (insn->op_ == OP_MEMBER_READ || insn->op_ == OP_MEMBER_READ_WITH_CHECK) {
    obj = frame->reg_values_[insn->src_regs_[0]->id_].object_;
  } else {
    obj = frame->reg_values_[insn->src_regs_[1]->id_].object_;
  }
  Value *member = obj->LookupValue(insn->label_, false);
  if (member == nullptr) {
    Status::os(Status::USER_ERROR) << "member not found: "
				   << sym_cstr(insn->label_);
    thr_->UserError();
    return;
  }
  if (TlsWrapper::IsTlsValue(member)) {
    member = TlsWrapper::GetValue(member->object_, thr_);
  }
  if (insn->op_ == OP_MEMBER_READ || insn->op_ == OP_MEMBER_READ_WITH_CHECK) {
    frame->reg_values_[insn->dst_regs_[0]->id_].CopyDataFrom(*member);
    if (method->IsTopLevel()) {
      // Copies data type to the method.
      auto *dst_reg = insn->dst_regs_[0];
      dst_reg->type_.value_type_ = member->type_;
      dst_reg->type_.width_ = member->num_.type_;
      dst_reg->type_.object_name_ = member->type_object_name_;
    }
  } else {
    // OP_MEMBER_WRITE
    CHECK(insn->src_regs_.size() == 2);
    CHECK(insn->src_regs_[0]->id_ == insn->dst_regs_[0]->id_);
    // src: value, obj
    Value &src = frame->reg_values_[insn->src_regs_[0]->id_];
    member->CopyDataFrom(src);
    member->type_ =
      method->method_regs_[insn->src_regs_[0]->id_]->type_.value_type_;
  }
}

void Executor::ExecBitRange(const Method *method, MethodFrame *frame,
			    Insn *insn) {
  int dst = insn->dst_regs_[0]->id_;
  if (method->method_regs_[dst]->type_.value_type_ == Value::NONE) {
    InsnAnnotator::AnnotateBitRangeInsn(insn);
  }
  int h = frame->reg_values_[insn->src_regs_[1]->id_].num_.GetValue0();
  int l = frame->reg_values_[insn->src_regs_[2]->id_].num_.GetValue0();
  Value &value = frame->reg_values_[insn->src_regs_[0]->id_];
  Value &res = frame->reg_values_[dst];
  iroha::Op::SelectBits(value.num_, h, l, &res.num_);
}

void Executor::InitializeArray(IntArray *array,
			       fe::ArrayInitializer *array_initializer) {
  if (array_initializer) {
    for (size_t i = 0; i < array_initializer->num_.size(); ++i) {
      iroha::Numeric num;
      iroha::Op::MakeConst(array_initializer->num_[i], &num);
      array->WriteSingle(i, num);
    }
  }
}

void Executor::ExecVardecl(const Method *method, MethodFrame *frame,
			   Insn *insn) {
  fe::VarDecl *decl = insn->insn_stmt_->GetVarDecl();
  Annotation *an = decl->GetAnnotation();
  Object *obj = frame->reg_values_[insn->obj_reg_->id_].object_;
  CHECK(obj);
  sym_t name = decl->GetNameExpr()->GetSym();
  Value *value = obj->LookupValue(name, true);
  DeclAnnotator::AnnotateValueType(thr_->GetVM(), decl, value);
  if (value->type_ == Value::NUM) {
    iroha::Op::MakeConst(0, &value->num_);
  }
  if (value->type_ == Value::OBJECT && an != nullptr) {
    DistanceWrapper::MaySetDistanceAnnotation(name, an, thr_->GetVM(), obj);
  }
  if (value->type_ == Value::INT_ARRAY) {
    value->object_ = CreateMemoryObject(decl->GetWidth(),
					decl->GetArrayShape(),
					decl->GetArrayInitializer(),
					decl->GetAnnotation());
  }
  if (value->type_ == Value::OBJECT_ARRAY) {
    value->object_ = CreateObjectArray(decl->GetArrayShape());
  }
  if (an != nullptr && an->IsThreadLocal()) {
    TlsWrapper::InjectTlsWrapper(thr_->GetVM(), value);
  }
}

void Executor::ExecThreadDecl(const Method *method, MethodFrame *frame,
			      Insn *insn) {
  Object *callee_obj;
  Method *callee_method = LookupMethod(frame, insn, &callee_obj);
  CHECK(callee_method) << "no method";
  sym_t method_name = insn->label_;
  Object *thread_obj =
    ThreadWrapper::NewThreadWrapper(thr_->GetVM(), method_name, false, 0);

  CHECK(callee_obj == frame->reg_values_[insn->obj_reg_->id_].object_);
  sym_t member_name = insn->insn_stmt_->GetExpr()->GetLhs()->GetSym();
  Value *value = callee_obj->LookupValue(member_name, true);
  value->type_ = Value::OBJECT;
  value->object_ = thread_obj;
}

void Executor::ExecChannelDecl(const Method *method,
			       MethodFrame *frame, Insn *insn) {
  int width = insn->insn_stmt_->GetWidth().GetWidth();
  Annotation *an = insn->insn_stmt_->GetAnnotation();
  CHECK(an == nullptr || !an->IsThreadLocal());
  Object *channel_obj =
    ChannelWrapper::NewChannel(thr_->GetVM(), width, insn->label_, an);

  Object *obj = frame->reg_values_[insn->obj_reg_->id_].object_;
  CHECK(obj);
  Value *value = obj->LookupValue(insn->label_, true);
  value->type_ = Value::OBJECT;
  value->object_ = channel_obj;
}

void Executor::ExecMailboxDecl(const Method *method,
			       MethodFrame *frame, Insn *insn) {
  Annotation *an = insn->insn_stmt_->GetAnnotation();
  int width = insn->insn_stmt_->GetWidth().GetWidth();
  Object *mailbox_obj =
    MailboxWrapper::NewMailbox(thr_->GetVM(), width, insn->label_, an);
  Object *obj = frame->reg_values_[insn->obj_reg_->id_].object_;
  CHECK(obj);
  Value *value = obj->LookupValue(insn->label_, true);
  value->type_ = Value::OBJECT;
  value->object_ = mailbox_obj;
}

void Executor::ExecImport(MethodFrame *frame, Insn *insn) {
  const string &fn = insn->insn_stmt_->GetString();
  VM *vm = thr_->GetVM();
  vm::Object *thr_obj = vm->kernel_object_->Clone();
  compiler::CompileOptions opts;
  Method *method = fe::FE::CompileFile(fn, false, false, false, vm, thr_obj);
  if (method == nullptr) {
    Status::os(Status::USER_ERROR) << "Failed to import: " << fn;
    thr_->UserError();
    return;
  }
  vm->AddThreadFromMethod(thr_, thr_obj, method, 0);
  thr_->Suspend();

  if (insn->dst_regs_.size() > 0) {
    // import "foo.karuta" as v
    int dst_id = insn->dst_regs_[0]->id_;
    frame->reg_values_[dst_id].object_ = thr_obj;
    frame->reg_values_[dst_id].type_ = Value::OBJECT;
  }
}

void Executor::ExecFuncdecl(const Method *method, MethodFrame *frame,
			    Insn *insn) {
  Object *obj = frame->reg_values_[insn->obj_reg_->id_].object_;
  if (!obj) {
    Status::os(Status::USER_ERROR) << "Can't find object";
    thr_->UserError();
    return;
  }

  Value *value = obj->LookupValue(insn->label_, true);
  value->type_ = Value::METHOD;
  Method *new_method = thr_->GetVM()->NewMethod(false /* not toplevel */);
  new_method->SetParseTree(insn->insn_stmt_->GetMethodDef());
  value->method_ = new_method;

  ClearThreadEntry(frame, insn);
  bool is_soft_thread = false;
  bool is_thread_entry = false;
  string thr_name;
  Annotation *an = new_method->GetAnnotation();
  if (an != nullptr) {
    thr_name = an->GetName();
    is_thread_entry = an->IsThreadEntry();
    is_soft_thread = an->IsSoftThreadEntry();
  }
  if (sym_str(insn->label_) == "main") {
    is_thread_entry = true;
  }
  if (thr_name.empty()) {
    thr_name = "$thr_" + sym_str(insn->label_);
  }
  if (is_thread_entry || is_soft_thread) {
    int num = 1;
    if (an != nullptr) {
      num = an->GetNum();
    }
    AddThreadEntry(frame, insn, thr_name, num, is_soft_thread);
  }
  if (an != nullptr && an->IsDataFlowEntry()) {
    AddThreadEntry(frame, insn, thr_name, 1, false);
  }
}

void Executor::AddThreadEntry(MethodFrame *frame, Insn *insn,
				      const string &name, int num,
				      bool is_soft) {
  Object *callee_obj;
  Object *obj = frame->reg_values_[insn->obj_reg_->id_].object_;
  for (int i = 0; i < num; ++i) {
    Object *thread_obj =
      ThreadWrapper::NewThreadWrapper(thr_->GetVM(), insn->label_, is_soft, i);
    string thr_name = name;
    if (num > 1) {
      char buf[20];
      sprintf(buf, "$%dof%d", i, num);
      thr_name += string(buf);
    }
    Value *value = obj->LookupValue(sym_lookup(thr_name.c_str()), true);
    value->type_ = Value::OBJECT;
    value->object_ = thread_obj;
  }
}

void Executor::ClearThreadEntry(MethodFrame *frame, Insn *insn) {
  Object *obj = frame->reg_values_[insn->obj_reg_->id_].object_;
  ThreadWrapper::DeleteThreadByMethodName(obj, sym_str(insn->label_));
}

void Executor::ExecMemberReadWithCheck(Method *method,
				       MethodFrame *frame,
				       const Insn *insn) {
  Executor::ExecMemberAccess(method, frame, insn);
  // Annotate the type of the results now.
  CHECK(insn->op_ == OP_MEMBER_READ_WITH_CHECK);
  Value &obj_value = frame->reg_values_[insn->src_regs_[0]->id_];
  CHECK(obj_value.type_ == Value::OBJECT);
  Object *obj = obj_value.object_;
  Value *member = obj->LookupValue(insn->label_, false);
  int dst_id = insn->dst_regs_[0]->id_;
  Register *dst_reg = method->method_regs_[dst_id];
  dst_reg->type_.value_type_ = member->type_;
  dst_reg->type_.object_name_ = member->type_object_name_;
  dst_reg->type_object_ = NumericObject::Get(thr_->GetVM(),
					     member->type_object_name_);
}

bool Executor::ExecFuncallWithCheck(MethodFrame *frame, Insn *insn) {
  Object *obj;
  Method *callee_method = LookupMethod(frame, insn, &obj);
  if (callee_method == nullptr) {
    return true;
  }
  if (callee_method->GetParseTree() != nullptr) {
    // non native
    if (insn->src_regs_.size() != callee_method->GetNumArgRegisters()) {
      CHECK(false) << "number of arguments doesn't match";
    }
  }
  return Executor::ExecFuncall(frame, insn);
}

void Executor::ExecFuncallDoneWithCheck(const Method *method,
					MethodFrame *frame,
					Insn *insn) {
  Object *obj;
  Method *callee_method = LookupMethod(frame, insn, &obj);
  CHECK(callee_method);
  int num_returns = callee_method->GetNumReturnRegisters();
  int num_dsts = insn->dst_regs_.size();
  // Annotates return values.
  CHECK(num_dsts == 1 || num_dsts == num_returns);
  for (int i = 0; i < num_dsts && i < num_returns; ++i) {
    insn->dst_regs_[i]->type_ = callee_method->return_types_[i];
  }
  Executor::ExecFuncallDone(method, frame, insn);
}

void Executor::ExecArrayWriteWithCheck(Method *method,
				       MethodFrame *frame,
				       Insn *insn) {
  if (insn->obj_reg_) {
    // Annotates the result value.
    // e.g. result = (a[i] = v)
    Object *array_obj = frame->reg_values_[insn->obj_reg_->id_].object_;
    if (ArrayWrapper::IsIntArray(array_obj)) {
      IntArray *array = ArrayWrapper::GetIntArray(array_obj);

      int dst_id = insn->dst_regs_[0]->id_;
      method->method_regs_[dst_id]->type_.width_ = array->GetDataWidth();
      method->method_regs_[dst_id]->type_.value_type_ = Value::NUM;
    } else {
      CHECK(ArrayWrapper::IsObjectArray(array_obj));
      int dst_id = insn->dst_regs_[0]->id_;
      method->method_regs_[dst_id]->type_.value_type_ = Value::OBJECT;
    }
  }
  Executor::ExecArrayWrite(method, frame, insn);
}

void Executor::ExecSetTypeObject(Method *method, Insn *insn) {
  int dst_id = insn->dst_regs_[0]->id_;
  Register *reg = method->method_regs_[dst_id];
  reg->type_object_ = NumericObject::Get(thr_->GetVM(),
					 reg->type_.object_name_);
  if (reg->type_object_ == nullptr) {
    Status::os(Status::USER_ERROR) << "Can't find numeric type: "
				   << sym_cstr(reg->type_.object_name_);
    thr_->UserError();
  }
}

bool Executor::MayExecuteCustomOp(const Method *method, MethodFrame *frame,
				  Insn *insn) {
  int lhs = insn->src_regs_[0]->id_;
  int rhs = insn->src_regs_[1]->id_;
  if (method->method_regs_[lhs]->type_.value_type_ != Value::NUM ||
      method->method_regs_[rhs]->type_.value_type_ != Value::NUM) {
    return false;
  }
  if (IsCustomOpCall(method, insn)) {
    return ExecCustomOp(method, frame, insn);
  }
  return false;
}

bool Executor::ExecCustomOp(const Method *method, MethodFrame *frame,
			    Insn *insn) {
  int lhs = insn->src_regs_[0]->id_;
  Object *type_obj = method->method_regs_[lhs]->type_object_;
  sym_t s = NumericObject::GetMethodName(type_obj, insn->op_);
  CHECK(s);
  Value *value = type_obj->LookupValue(s, false);
  CHECK(value != nullptr && value->type_ == Value::METHOD &&
	value->method_ != nullptr);
  Method *op_method = value->method_;
  compiler::Compiler::CompileMethod(thr_->GetVM(), type_obj, op_method);
  CHECK(!method->IsCompileFailure());
  vector<Value> args;
  for (size_t i = 0; i < insn->src_regs_.size(); ++i) {
    args.push_back(frame->reg_values_[insn->src_regs_[i]->id_]);
  }
  auto fn = op_method->GetMethodFunc();
  CHECK(fn == nullptr);
  SetupCalleeFrame(type_obj, op_method, args);
  return true;
}


void Executor::ExecMayWithTypeDone(const Method *method,
				   MethodFrame *frame, Insn *insn) {
  if (IsCustomOpCall(method, insn)) {
    insn->dst_regs_[0]->type_ = insn->src_regs_[0]->type_;
    Executor::ExecFuncallDone(method, frame, insn);
  }
}

bool Executor::IsCustomOpCall(const Method *method, Insn *insn) {
  int lhs = insn->src_regs_[0]->id_;
  int rhs = insn->src_regs_[1]->id_;
  if (method->method_regs_[rhs]->type_object_ != nullptr &&
      method->method_regs_[lhs]->type_object_ ==
      method->method_regs_[rhs]->type_object_) {
    return true;
  }
  return false;
}

}  // namespace vm

