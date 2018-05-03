#include "vm/executor.h"

#include "base/dump_stream.h"
#include "base/status.h"
#include "compiler/compiler.h"
#include "fe/fe.h"
#include "fe/expr.h"
#include "fe/stmt.h"
#include "fe/nodecode.h"
#include "fe/var_decl.h"
#include "numeric/numeric_op.h"  // from iroha
#include "vm/array_wrapper.h"
#include "vm/insn.h"
#include "vm/int_array.h"
#include "vm/string_wrapper.h"
#include "vm/thread.h"
#include "vm/tls_wrapper.h"
#include "vm/method.h"
#include "vm/object.h"
#include "vm/opcode.h"
#include "vm/vm.h"

namespace vm {

Executor::Executor(Thread *thread) : thr_(thread) {
}

Executor::~Executor() {
}

Object *Executor::CreateMemoryObject(const iroha::NumericWidth &width,
				     int array_length,
				     fe::ArrayInitializer *array_initializer,
				     Annotation *an) {
  Object *obj = ArrayWrapper::NewIntArrayWrapper(thr_->GetVM(),
						 array_length, width,
						 an);
  IntArray *memory = ArrayWrapper::GetIntArray(obj);
  InitializeArray(memory, array_initializer);
  return obj;
}

Object *Executor::CreateObjectArray(int array_length) {
  return ArrayWrapper::NewObjectArrayWrapper(thr_->GetVM(), array_length);
}

IntArray *Executor::CreateIntArray(const iroha::NumericWidth &width,
				   int array_length,
				   fe::ArrayInitializer *array_initializer) {
  IntArray *array = IntArray::Create(width, array_length);
  InitializeArray(array, array_initializer);
  return array;
}

bool Executor::ExecInsn(Method *method, MethodFrame *frame, Insn *insn) {
  bool need_suspend = false;
  switch (insn->op_) {
  case OP_NUM:
    {
      int dst = insn->dst_regs_[0]->id_;
      frame->reg_values_[dst].num_ = insn->src_regs_[0]->initial_num_;
      frame->reg_values_[dst].num_.type_ = method->method_regs_[dst]->type_.width_;
    }
    break;
  case OP_STR:
    ExecStr(frame, insn);
    break;
  case OP_ADD:
  case OP_SUB:
  case OP_MUL:
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
    ExecGoto(frame, insn);
    // do not increment pc.
    return false;
  case OP_NOP:
    break;
  case OP_PRE_INC:
  case OP_PRE_DEC:
    ExecIncDec(frame, insn);
    break;
  case OP_ARRAY_READ:
    ExecArrayRead(frame, insn);
    break;
  case OP_ARRAY_WRITE:
    ExecArrayWrite(frame, insn);
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
    ExecMemberAccess(frame, insn);
    break;
  case OP_BIT_RANGE:
    ExecBitRange(frame, insn);
    break;
  default:
    CHECK(false) << "unknown insn:" << vm::OpCodeName(insn->op_);
  }
  ++frame->pc_;
  return need_suspend;
}

void Executor::ExecStr(MethodFrame *frame, Insn *insn) {
  int dst = insn->dst_regs_[0]->id_;
  frame->reg_values_[dst].object_ =
    StringWrapper::NewStringWrapper(thr_->GetVM(), InsnOpUtils::Str(insn));
}

void Executor::ExecBinop(const Method *method, MethodFrame *frame,
			 Insn *insn) {
  int dst = insn->dst_regs_[0]->id_;
  if (frame->reg_values_[dst].type_ != Value::NUM) {
    ExecNonNumResultBinop(method, frame, insn);
    return;
  }
  int lhs = insn->src_regs_[0]->id_;
  int rhs = insn->src_regs_[1]->id_;
  switch (insn->op_) {
  case OP_ADD:
    iroha::Op::Add(frame->reg_values_[lhs].num_,
		   frame->reg_values_[rhs].num_,
		   &frame->reg_values_[dst].num_);
    iroha::Op::FixupWidth(frame->method_->method_regs_[dst]->type_.width_,
			  &frame->reg_values_[dst].num_);
    break;
  case OP_SUB:
    iroha::Op::Sub(frame->reg_values_[lhs].num_,
		   frame->reg_values_[rhs].num_,
		   &frame->reg_values_[dst].num_);
    iroha::Op::FixupWidth(frame->method_->method_regs_[dst]->type_.width_,
			  &frame->reg_values_[dst].num_);
    break;
  case OP_MUL:
    iroha::Op::CalcBinOp(iroha::BINOP_MUL,
			 frame->reg_values_[lhs].num_,
			 frame->reg_values_[rhs].num_,
			 &frame->reg_values_[dst].num_);
    iroha::Op::FixupWidth(frame->method_->method_regs_[dst]->type_.width_,
			  &frame->reg_values_[dst].num_);
    break;
  case OP_ASSIGN:
    frame->reg_values_[dst].num_ = frame->reg_values_[rhs].num_;
    iroha::Op::FixupWidth(frame->method_->method_regs_[dst]->type_.width_,
			  &frame->reg_values_[dst].num_);
    frame->reg_values_[dst].num_.type_ = frame->method_->method_regs_[dst]->type_.width_;

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
    iroha::Op::Concat(frame->reg_values_[lhs].num_,
		      frame->reg_values_[rhs].num_,
		      &frame->reg_values_[dst].num_);
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

void Executor::ExecArrayRead(MethodFrame *frame, Insn *insn) {
  int index = frame->reg_values_[insn->src_regs_[0]->id_].num_.GetValue0();
  CHECK(insn->obj_reg_ != nullptr);
  Object *array_obj = frame->reg_values_[insn->obj_reg_->id_].object_;
  CHECK(array_obj);
  Value &lhs = frame->reg_values_[insn->dst_regs_[0]->id_];
  if (ArrayWrapper::IsIntArray(array_obj)) {
    IntArray *array = ArrayWrapper::GetIntArray(array_obj);
    lhs.num_ = array->Read(index);
    lhs.num_.type_ = array->GetDataWidth();
  } else {
    CHECK(ArrayWrapper::IsObjectArray(array_obj));
    lhs.object_ = ArrayWrapper::Get(array_obj, index);
    lhs.type_ = Value::OBJECT;
  }
}

void Executor::ExecArrayWrite(MethodFrame *frame, Insn *insn) {
  int index = frame->reg_values_[insn->src_regs_[0]->id_].num_.GetValue0();
  CHECK(insn->obj_reg_ != nullptr);
  Object *array_obj = frame->reg_values_[insn->obj_reg_->id_].object_;
  CHECK(array_obj);
  if (ArrayWrapper::IsIntArray(array_obj)) {
    IntArray *array = ArrayWrapper::GetIntArray(array_obj);
    array->Write(index,
		 frame->reg_values_[insn->src_regs_[1]->id_].num_);
  } else {
    CHECK(ArrayWrapper::IsObjectArray(array_obj));
    CHECK(frame->reg_values_[insn->src_regs_[1]->id_].type_ == Value::OBJECT);
    ArrayWrapper::Set(array_obj, index,
		      frame->reg_values_[insn->src_regs_[1]->id_].object_);
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
  iroha::Op::FixupWidth(frame->method_->method_regs_[dst_id]->type_.width_, &res);
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
      CHECK(frame->reg_values_[lhs].type_ == Value::NUM &&
	    frame->reg_values_[rhs].type_ == Value::NUM);
    }
  case OP_EQ:
  case OP_NE:
    {
      bool r;
      if (frame->reg_values_[rhs].type_ == Value::NUM) {
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
      } else if (frame->reg_values_[rhs].type_ == Value::ENUM_ITEM) {
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
    {
      CHECK(frame->reg_values_[lhs].type_ == Value::OBJECT);
      CHECK(frame->reg_values_[rhs].type_ == Value::OBJECT);
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

void Executor::ExecGoto(MethodFrame *frame, Insn *insn) {
  frame->pc_ = insn->jump_target_;
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
    // native
    fn(thr_, obj, args);
    if (!thr_->IsRunnable()) {
      return true;
    }
  } else {
    SetupCallee(obj, callee_method, args);
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

void Executor::SetupCallee(Object *obj, Method *callee_method,
			   const vector<Value> &args) {
  MethodFrame *frame = thr_->PushMethodFrame(obj, callee_method);
  for (size_t i = 0; i < args.size(); ++i) {
    frame->reg_values_[i] = args[i];
    const iroha::NumericWidth &width = callee_method->GetNthArgWidth(i);
    frame->reg_values_[i].num_.type_ = width;
  }
}

void Executor::MemoryWrite(uint64_t addr, int data_width,
			   const iroha::Numeric &data) {
  iroha::Numeric d = data;
  d.type_.SetWidth(data_width);
  IntArray *mem = thr_->GetVM()->GetDefaultMemory();
  mem->WriteWide(addr, d);
}

void Executor::MemoryRead(int addr, int data_width, iroha::Numeric *res) {
  IntArray *mem = thr_->GetVM()->GetDefaultMemory();
  *res = mem->ReadWide(addr, data_width);
}

void Executor::ExecMemberAccess(MethodFrame *frame, const Insn *insn) {
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
  } else {
    // OP_MEMBER_WRITE
    CHECK(insn->src_regs_.size() == 2);
    CHECK(insn->src_regs_[0]->id_ == insn->dst_regs_[0]->id_);
    // src: value, obj
    Value &src = frame->reg_values_[insn->src_regs_[0]->id_];
    member->CopyDataFrom(src);
  }
}

void Executor::ExecBitRange(MethodFrame *frame, Insn *insn) {
  int h = frame->reg_values_[insn->src_regs_[1]->id_].num_.GetValue0();
  int l = frame->reg_values_[insn->src_regs_[2]->id_].num_.GetValue0();
  Value &value = frame->reg_values_[insn->src_regs_[0]->id_];
  Value &res = frame->reg_values_[insn->dst_regs_[0]->id_];
  iroha::Op::SelectBits(value.num_, h, l, &res.num_);
}

void Executor::InitializeArray(IntArray *array, fe::ArrayInitializer *array_initializer) {
  if (array_initializer) {
    for (size_t i = 0; i < array_initializer->num_.size(); ++i) {
      iroha::Numeric num;
      iroha::Op::MakeConst(array_initializer->num_[i], &num);
      array->Write(i, num);
    }
  }
}

}  // namespace vm

