#include "vm/executor.h"

#include "base/dump_stream.h"
#include "base/status.h"
#include "compiler/compiler.h"
#include "fe/fe.h"
#include "fe/expr.h"
#include "fe/stmt.h"
#include "fe/nodecode.h"
#include "fe/var_decl.h"
#include "vm/array_wrapper.h"
#include "vm/channel.h"
#include "vm/insn.h"
#include "vm/int_array.h"
#include "vm/string_wrapper.h"
#include "vm/thread.h"
#include "vm/method.h"
#include "vm/object.h"
#include "vm/opcode.h"
#include "vm/vm.h"

namespace vm {

MethodFrame::~MethodFrame() {
  for (size_t i = 0; i < reg_values_.size(); ++i) {
    Value &val = reg_values_[i];
    if (val.local_int_array_) {
      delete val.local_int_array_;
    }
  }
}

Executor::Executor(Thread *thread) : thr_(thread) {
}

Executor::~Executor() {
}

Object *Executor::CreateMemoryObject(const numeric::Width *width,
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

IntArray *Executor::CreateIntArray(const numeric::Width *width,
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
      const numeric::Width *width =
	method->method_regs_[dst]->type_.width_;
      frame->reg_values_[dst].num_ = insn->src_regs_[0]->initial_num_;
      frame->reg_values_[dst].num_.type = width;
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
  case OP_CHANNEL_READ:
    need_suspend = ExecChannelRead(frame, insn);
    if (need_suspend) {
      return true;
    }
    break;
  case OP_MEMORY_READ:
    ExecMemoryRead(frame, insn);
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
  case OP_CHANNEL_WRITE:
    ExecChannelWrite(method, frame, insn);
    break;
  case OP_MEMORY_WRITE:
    ExecMemoryWrite(method, frame, insn);
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
    numeric::Numeric::Add(frame->reg_values_[lhs].num_,
			  frame->reg_values_[rhs].num_,
			  &frame->reg_values_[dst].num_);
    break;
  case OP_SUB:
    numeric::Numeric::Sub(frame->reg_values_[lhs].num_,
			  frame->reg_values_[rhs].num_,
			  &frame->reg_values_[dst].num_);
    break;
  case OP_MUL:
    numeric::Numeric::CalcBinOp(numeric::BINOP_MUL,
				frame->reg_values_[lhs].num_,
				frame->reg_values_[rhs].num_,
				&frame->reg_values_[dst].num_);
    break;
  case OP_ASSIGN:
    frame->reg_values_[dst].num_ = frame->reg_values_[rhs].num_;
    numeric::Numeric::FixupWidth(frame->method_->method_regs_[dst]->type_.width_,
				 &frame->reg_values_[dst].num_);
    break;
  case OP_AND:
    numeric::Numeric::CalcBinOp(numeric::BINOP_AND,
				frame->reg_values_[lhs].num_,
				frame->reg_values_[rhs].num_,
				&frame->reg_values_[dst].num_);
    break;
  case OP_OR:
    numeric::Numeric::CalcBinOp(numeric::BINOP_OR,
				frame->reg_values_[lhs].num_,
				frame->reg_values_[rhs].num_,
				&frame->reg_values_[dst].num_);
    break;
  case OP_XOR:
    numeric::Numeric::CalcBinOp(numeric::BINOP_XOR,
				frame->reg_values_[lhs].num_,
				frame->reg_values_[rhs].num_,
				&frame->reg_values_[dst].num_);
    break;
  case OP_CONCAT:
    numeric::Numeric::Concat(frame->reg_values_[lhs].num_,
			     frame->reg_values_[rhs].num_,
			     &frame->reg_values_[dst].num_);
    break;
  case OP_LSHIFT:
    numeric::Numeric::CalcBinOp(numeric::BINOP_LSHIFT,
				frame->reg_values_[lhs].num_,
				frame->reg_values_[rhs].num_,
				&frame->reg_values_[dst].num_);
    break;
  case OP_RSHIFT:
    numeric::Numeric::CalcBinOp(numeric::BINOP_RSHIFT,
				frame->reg_values_[lhs].num_,
				frame->reg_values_[rhs].num_,
				&frame->reg_values_[dst].num_);
    break;
  default:
    CHECK(false) << "unknown binop:" << vm::OpCodeName(insn->op_);
  }
}

void Executor::ExecChannelWrite(const Method *method, MethodFrame *frame,
				Insn *insn) {
  CHECK(insn->obj_reg_);
  Value &dst_value = frame->reg_values_[insn->obj_reg_->id_];
  Value &src_value = frame->reg_values_[insn->src_regs_[insn->src_regs_.size() - 1]->id_];
  CHECK(dst_value.type_ == Value::OBJECT);
  CHECK(Channel::IsChannel(dst_value.object_));
  Channel::WriteValue(src_value, dst_value.object_);
}

void Executor::ExecMemoryWrite(const Method *method, MethodFrame *frame,
			       Insn *insn) {
  Value &src_value = frame->reg_values_[insn->src_regs_[1]->id_];
  Value &dst_value = frame->reg_values_[insn->src_regs_[0]->id_];
  CHECK(dst_value.type_ == Value::NUM);
  int addr = dst_value.num_.int_part;
  MemoryWrite(addr, src_value.num_);
}

void Executor::ExecArrayRead(MethodFrame *frame, Insn *insn) {
  int index = frame->reg_values_[insn->src_regs_[0]->id_].num_.int_part;
  if (insn->obj_reg_) {
    Object *array_obj = frame->reg_values_[insn->obj_reg_->id_].object_;
    CHECK(array_obj);
    Value &lhs = frame->reg_values_[insn->dst_regs_[0]->id_];
    if (ArrayWrapper::IsIntArray(array_obj)) {
      IntArray *array = ArrayWrapper::GetIntArray(array_obj);
      lhs.num_ = array->Read(index);
      lhs.num_.type = array->GetWidth();
    } else {
      CHECK(ArrayWrapper::IsObjectArray(array_obj));
      lhs.object_ = ArrayWrapper::Get(array_obj, index);
      lhs.type_ = Value::OBJECT;
    }
  } else {
    // local array.
    CHECK(insn->src_regs_.size() == 2);
    Value &array = frame->reg_values_[insn->src_regs_[1]->id_];
    Value &index = frame->reg_values_[insn->src_regs_[0]->id_];
    
    frame->reg_values_[insn->dst_regs_[0]->id_].num_ =
      array.local_int_array_->Read(numeric::Numeric::GetInt(index.num_));
    frame->reg_values_[insn->dst_regs_[0]->id_].type_ = Value::NUM;
  }
}

void Executor::ExecArrayWrite(MethodFrame *frame, Insn *insn) {
  int index = frame->reg_values_[insn->src_regs_[0]->id_].num_.int_part;
  if (insn->obj_reg_) {
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
  } else {
    // local array.
    CHECK(insn->src_regs_.size() == 3);
    Value &array = frame->reg_values_[insn->src_regs_[2]->id_];
    
    array.local_int_array_->Write(index,
				  frame->reg_values_[insn->src_regs_[1]->id_].num_);
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
    if (!numeric::Numeric::IsZero(value.num_)) {
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
  numeric::Number res;
  switch (insn->op_) {
  case OP_BIT_INV:
    numeric::Numeric::BitInv(value.num_, &res);
    break;
  case OP_PLUS:
    res = value.num_;
    break;
  case OP_MINUS:
    numeric::Numeric::Minus(value.num_, &res);
    break;
  default:
    CHECK(false);
    break;
  }
  int dst_id = insn->dst_regs_[0]->id_;
  numeric::Numeric::FixupWidth(frame->method_->method_regs_[dst_id]->type_.width_, &res);
  dst_value.num_ = res;
}

void Executor::ExecMemoryRead(MethodFrame *frame, Insn *insn) {
  Value &addr_value = frame->reg_values_[insn->src_regs_[0]->id_];
  CHECK(addr_value.type_ == Value::NUM);
  Value &dst_value = frame->reg_values_[insn->dst_regs_[0]->id_];
  int addr = addr_value.num_.int_part;
  MemoryRead(addr, &dst_value.num_);
  dst_value.type_ = Value::NUM;
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

bool Executor::ExecChannelRead(MethodFrame *frame, Insn *insn) {
  Value &addr_value = frame->reg_values_[insn->obj_reg_->id_];
  CHECK(addr_value.type_ == Value::OBJECT);
  Value &dst_value = frame->reg_values_[insn->dst_regs_[0]->id_];
  if (!Channel::ReadValue(thr_, addr_value.object_, &dst_value)) {
    return true;
  }
  return false;
}

void Executor::ExecIncDec(MethodFrame *frame, Insn *insn) {
  int target = insn->dst_regs_[0]->id_;
  numeric::Number n1;
  numeric::Numeric::MakeConst(1, &n1);
  numeric::Number res;
  if (insn->op_ == OP_PRE_INC) {
    numeric::Numeric::Add(frame->reg_values_[target].num_, n1, &res);
  } else {
    numeric::Numeric::Sub(frame->reg_values_[target].num_, n1, &res);
  }
  numeric::Numeric::FixupWidth(frame->method_->method_regs_[target]->type_.width_, &res);
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
	numeric::CompareOp op;
	switch (insn->op_) {
	case OP_LT:
	case OP_GTE:
	  op = numeric::COMPARE_LT;
	  break;
	case OP_GT:
	case OP_LTE:
	  op = numeric::COMPARE_GT;
	  break;
	case OP_EQ:
	case OP_NE:
	  op = numeric::COMPARE_EQ;
	  break;
	default:
	  op = numeric::COMPARE_EQ;
	  CHECK(false);
	  break;
	}
	r = numeric::Numeric::Compare(op, frame->reg_values_[lhs].num_,
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
  Method *callee_method = LookupMethod(frame, insn, &obj);
  if (!callee_method) {
    return true;
  }
  CHECK(callee_method);
  vector<Value> args;
  for (size_t i = 0; i < insn->src_regs_.size(); ++i) {
    args.push_back(frame->reg_values_[insn->src_regs_[i]->id_]);
  }
  if (callee_method->method_fn_) {
    // native
    callee_method->method_fn_(thr_, obj, args);
    if (!thr_->IsRunnable()) {
      return true;
    }
  } else {
    SetupCallee(obj, callee_method, args);
    return true;
  }
  return false;
}

Method *Executor::LookupMethod(MethodFrame *frame, Insn *insn,
			       Object **obj) {
  Value &obj_value = frame->reg_values_[insn->obj_reg_->id_];
  CHECK(obj_value.IsObjectType());
  *obj = obj_value.object_;
  Value *value = (*obj)->LookupValue(insn->label_, false);
  if (!value) {
    Status::os(Status::USER) << "method not found: "
			       << sym_cstr(insn->label_);
    Status::Check(Status::USER);
    thr_->UserError();
    return nullptr;
  }
  CHECK(value->type_ == Value::METHOD);
  value->method_ =
    compiler::Compiler::CompileMethod(thr_->GetVM(), *obj,
				      value->method_->parse_tree_,
				      value->method_);
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
    const numeric::Width *width = callee_method->GetNthArgWidth(i);
    if (width) {
      frame->reg_values_[i].num_.type = width;
    }
  }
}

void Executor::MemoryWrite(int addr, const numeric::Number &data) {
  IntArray *mem = thr_->GetVM()->GetDefaultMemory();
  mem->Write(addr, data);
}

void Executor::MemoryRead(int addr, numeric::Number *res) {
  IntArray *mem = thr_->GetVM()->GetDefaultMemory();
  *res = mem->Read(addr);
}

void Executor::ExecMemberAccess(MethodFrame *frame, const Insn *insn) {
  Object *obj;
  if (insn->op_ == OP_MEMBER_READ) {
    obj = frame->reg_values_[insn->src_regs_[0]->id_].object_;
  } else {
    obj = frame->reg_values_[insn->src_regs_[1]->id_].object_;
  }
  Value *member = obj->LookupValue(insn->label_, false);
  CHECK(member) << sym_cstr(insn->label_);
  if (insn->op_ == OP_MEMBER_READ) {
    frame->reg_values_[insn->dst_regs_[0]->id_] = *member;
  } else {
    // OP_MEMBER_WRITE
    CHECK(insn->src_regs_.size() == 2);
    CHECK(insn->src_regs_[0]->id_ == insn->dst_regs_[0]->id_);
    // src: value, obj
    Value &src = frame->reg_values_[insn->src_regs_[0]->id_];
    *member = src;
  }
}

void Executor::ExecBitRange(MethodFrame *frame, Insn *insn) {
  int h = numeric::Numeric::GetInt(frame->reg_values_[insn->src_regs_[1]->id_].num_);
  int l = numeric::Numeric::GetInt(frame->reg_values_[insn->src_regs_[2]->id_].num_);
  Value &value = frame->reg_values_[insn->src_regs_[0]->id_];
  Value &res = frame->reg_values_[insn->dst_regs_[0]->id_];
  numeric::Numeric::SelectBits(value.num_, h, l, &res.num_);
}

void Executor::InitializeArray(IntArray *array, fe::ArrayInitializer *array_initializer) {
  if (array_initializer) {
    for (size_t i = 0; i < array_initializer->num_.size(); ++i) {
      numeric::Number num;
      numeric::Numeric::MakeConst(array_initializer->num_[i], &num);
      array->Write(i, num);
    }
  }
}

}  // namespace vm

