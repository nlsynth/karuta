#include "vm/executor.h"

#include "base/dump_stream.h"
#include "base/status.h"
#include "compiler/compiler.h"
#include "fe/fe.h"
#include "fe/expr.h"
#include "fe/stmt.h"
#include "fe/nodecode.h"
#include "fe/var_decl.h"
#include "karuta/annotation.h"
#include "numeric/numeric_op.h"  // from iroha
#include "vm/array_wrapper.h"
#include "vm/channel_wrapper.h"
#include "vm/decl_annotator.h"
#include "vm/distance_wrapper.h"
#include "vm/insn.h"
#include "vm/insn_annotator.h"
#include "vm/int_array.h"
#include "vm/mailbox_wrapper.h"
#include "vm/method.h"
#include "vm/numeric_object.h"
#include "vm/object.h"
#include "vm/opcode.h"
#include "vm/string_wrapper.h"
#include "vm/thread.h"
#include "vm/thread_wrapper.h"
#include "vm/tls_wrapper.h"
#include "vm/vm.h"

namespace vm {

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
    ExecIf();
    // do not increment pc.
    return false;
  case OP_GOTO:
    {
      bool v = ExecGoto();
      // do not increment pc.
      return v;
    }
  case OP_NOP:
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
  case OP_MAY_WITH_TYPE_DONE:
    ExecMayWithTypeDone();
    break;
  default:
    CHECK(false) << "unknown insn:" << vm::OpCodeName(op());
  }
  ++frame_->pc_;
  return need_suspend;
}

void Executor::ExecNum() {
  int dst = dreg(0)->id_;
  iroha::Numeric::CopyValueWithWidth(sreg(0)->initial_num_.GetArray(),
				     sreg(0)->initial_num_.type_,
				     mreg(dst)->type_.width_,
				     nullptr,
				     val(dst).num_.GetMutableArray());
  if (frame_->method_->IsTopLevel()) {
    val(dst).type_ = Value::NUM;
    val(dst).num_.type_ = mreg(dst)->type_.width_;
  }
}

void Executor::ExecStr() {
  int dst = dreg(0)->id_;
  val(dst).object_ =
    StringWrapper::NewStringWrapper(thr_->GetVM(), InsnOpUtils::Str(insn_));
  if (frame_->method_->IsTopLevel()) {
    val(dst).type_ = Value::OBJECT;
  }
}

void Executor::ExecBinop() {
  int dst = dreg(0)->id_;
  if (mreg(dst)->type_.value_type_ != Value::NUM) {
    if (mreg(dst)->type_.value_type_ == Value::NONE) {
      RetryBinopWithType();
    } else {
      ExecNonNumResultBinop();
    }
    return;
  }
  int lhs = sreg(0)->id_;
  int rhs = sreg(1)->id_;
  if (m()->IsTopLevel()) {
    if (InsnType::IsNumCalculation(op())) {
      InsnAnnotator::AnnotateNumCalculationOp(insn_);
    }
    if (op() == OP_LSHIFT || op() == OP_RSHIFT) {
      val(dst).num_.type_ = mreg(lhs)->type_.width_;
    }
  }
  switch (op()) {
  case OP_ADD:
  case OP_ADD_MAY_WITH_TYPE:
    iroha::Op::Add0(val(lhs).num_.GetArray(), val(rhs).num_.GetArray(),
		    val(dst).num_.GetMutableArray());
    iroha::Op::FixupWidth(mreg(dst)->type_.width_,
			  &val(dst).num_);
    break;
  case OP_SUB:
  case OP_SUB_MAY_WITH_TYPE:
    iroha::Op::Sub0(val(lhs).num_.GetArray(), val(rhs).num_.GetArray(),
		    val(dst).num_.GetMutableArray());
    iroha::Op::FixupWidth(mreg(dst)->type_.width_,
			  &val(dst).num_);
    break;
  case OP_MUL:
  case OP_MUL_MAY_WITH_TYPE:
    iroha::Op::CalcBinOp(iroha::BINOP_MUL,
			 val(lhs).num_, val(rhs).num_,
			 &val(dst).num_);
    iroha::Op::FixupWidth(mreg(dst)->type_.width_,
			  &val(dst).num_);
    break;
  case OP_DIV:
  case OP_DIV_MAY_WITH_TYPE:
    iroha::Op::CalcBinOp(iroha::BINOP_DIV,
			 val(lhs).num_, val(rhs).num_,
			 &val(dst).num_);
    iroha::Op::FixupWidth(mreg(dst)->type_.width_,
			  &val(dst).num_);
    break;
  case OP_ASSIGN:
    iroha::Numeric::CopyValueWithWidth(val(rhs).num_.GetArray(),
				       val(rhs).num_.type_,
				       mreg(dst)->type_.width_,
				       nullptr,
				       val(dst).num_.GetMutableArray());
    iroha::Op::FixupWidth(mreg(dst)->type_.width_,
			  &val(dst).num_);
    if (m()->IsTopLevel() &&
	!mreg(dst)->GetIsDeclaredType()) {
      mreg(dst)->type_ = mreg(rhs)->type_;
    }
    break;
  case OP_AND:
    iroha::Op::CalcBinOp(iroha::BINOP_AND,
			 val(lhs).num_, val(rhs).num_,
			 &val(dst).num_);
    break;
  case OP_OR:
    iroha::Op::CalcBinOp(iroha::BINOP_OR,
			 val(lhs).num_, val(rhs).num_,
			 &val(dst).num_);
    break;
  case OP_XOR:
    iroha::Op::CalcBinOp(iroha::BINOP_XOR,
			 val(lhs).num_, val(rhs).num_,
			 &val(dst).num_);
    break;
  case OP_CONCAT:
    {
      iroha::Numeric l = val(lhs).num_;
      iroha::Numeric r = val(rhs).num_;
      l.type_ = mreg(lhs)->type_.width_;
      r.type_ =	mreg(rhs)->type_.width_;
      iroha::Op::Concat(l, r,
			&val(dst).num_);
    }
    break;
  case OP_LSHIFT:
    iroha::Op::CalcBinOp(iroha::BINOP_LSHIFT,
			 val(lhs).num_,
			 val(rhs).num_,
			 &val(dst).num_);
    iroha::Op::FixupWidth(mreg(dst)->type_.width_,
			  &val(dst).num_);
    break;
  case OP_RSHIFT:
    iroha::Op::CalcBinOp(iroha::BINOP_RSHIFT,
			 val(lhs).num_,
			 val(rhs).num_,
			 &val(dst).num_);
    iroha::Op::FixupWidth(mreg(dst)->type_.width_,
			  &val(dst).num_);
    break;
  default:
    CHECK(false) << "unknown binop:" << vm::OpCodeName(op());
  }
}

void Executor::RetryBinopWithType() {
  if (op() == OP_CONCAT) {
    InsnAnnotator::AnnotateConcatInsn(insn_);
    // TODO: Annotate other types of insns.
  } else {
    CHECK(op() == OP_ADD_MAY_WITH_TYPE ||
	  op() == OP_SUB_MAY_WITH_TYPE ||
	  op() == OP_MUL_MAY_WITH_TYPE ||
	  op() == OP_DIV_MAY_WITH_TYPE);
  }
  int lhs = sreg(0)->id_;
  int rhs = sreg(1)->id_;
  CHECK(mreg(lhs)->type_.value_type_ ==
	mreg(rhs)->type_.value_type_);
  int dst = dreg(0)->id_;
  if (mreg(lhs)->type_.value_type_ == Value::NUM) {
    mreg(dst)->type_.value_type_ = Value::NUM;
  } else if (mreg(lhs)->type_.value_type_ == Value::OBJECT) {
    mreg(dst)->type_.value_type_ = Value::OBJECT;
  }
  ExecBinop();
}

void Executor::ExecArrayRead() {
  CHECK(oreg() != nullptr);
  Object *array_obj = val(oreg()->id_).object_;
  CHECK(array_obj);
  Value &lhs_value = val(dreg(0)->id_);
  auto *dst_reg = dreg(0);
  if (ArrayWrapper::IsIntArray(array_obj)) {
    IntArray *array = ArrayWrapper::GetIntArray(array_obj);
    vector<uint64_t> indexes;
    PopulateArrayIndexes(0, &indexes);
    *(lhs_value.num_.GetMutableArray()) = array->Read(indexes);
    if (m()->IsTopLevel()) {
      dst_reg->type_.value_type_ = Value::NUM;
      dst_reg->type_.width_ = array->GetDataWidth();
    }
  } else {
    CHECK(ArrayWrapper::IsObjectArray(array_obj));
    int index = val(sreg(0)->id_).num_.GetValue0();
    lhs_value.type_ = Value::OBJECT;
    lhs_value.object_ = ArrayWrapper::Get(array_obj, index);
    if (m()->IsTopLevel()) {
      dst_reg->type_.value_type_ = Value::OBJECT;
    }
  }
}

void Executor::ExecArrayWrite() {
  CHECK(oreg() != nullptr);
  Object *array_obj = val(oreg()->id_).object_;
  CHECK(array_obj);
  if (ArrayWrapper::IsIntArray(array_obj)) {
    IntArray *array = ArrayWrapper::GetIntArray(array_obj);
    vector<uint64_t> indexes;
    PopulateArrayIndexes(1, &indexes);
    array->Write(indexes,
		 val(sreg(0)->id_).num_);
  } else {
    CHECK(ArrayWrapper::IsObjectArray(array_obj));
    CHECK(mreg(sreg(0)->id_)->type_.value_type_
	  == Value::OBJECT);
    int index = val(sreg(1)->id_).num_.GetValue0();
    ArrayWrapper::Set(array_obj, index,
		      val(sreg(0)->id_).object_);
  }
}

void Executor::PopulateArrayIndexes(int start, vector<uint64_t> *indexes) {
  for (int i = start; i < insn_->src_regs_.size(); ++i) {
    uint64_t v = val(insn_->src_regs_[i]->id_).num_.GetValue0();
    indexes->push_back(v);
  }
}

void Executor::ExecLogicInv() {
  int v = 1;
  Value &value = val(sreg(0)->id_);
  if (value.type_ == Value::ENUM_ITEM) {
    if (value.enum_val_.val != 0) {
      v = 0;
    }
  } else if (value.type_ == Value::NUM) {
    if (!iroha::Op::IsZero(value.num_.type_, value.num_.GetArray())) {
      v = 0;
    }
  }
  Value &dst_value = val(dreg(0)->id_);
  dst_value.enum_val_.val = v;
}

void Executor::ExecNumUniop() {
  Value &value = val(sreg(0)->id_);
  Value &dst_value = val(dreg(0)->id_);
  if (value.type_ == Value::ENUM_ITEM) {
    CHECK(op() == OP_BIT_INV);
    if (value.enum_val_.val) {
      dst_value.enum_val_.val = 0;
    } else {
      dst_value.enum_val_.val = 1;
    }
    return;
  }
  iroha::Numeric res;
  switch (op()) {
  case OP_BIT_INV:
    iroha::Op::BitInv0(value.num_.GetArray(), res.GetMutableArray());
    break;
  case OP_PLUS:
    res = value.num_;
    break;
  case OP_MINUS:
    iroha::Op::Minus0(value.num_.GetArray(), res.GetMutableArray());
    break;
  default:
    CHECK(false);
    break;
  }
  int dst_id = dreg(0)->id_;
  iroha::Op::FixupWidth(mreg(dst_id)->type_.width_,
			&res);
  dst_value.num_ = res;
}

void Executor::ExecLoadObj() {
  Value &dst_value = val(dreg(0)->id_);
  Value *obj_value;
  if (insn_->label_) {
    Object *src_obj;
    if (oreg()) {
      src_obj = val(oreg()->id_).object_;
    } else {
      src_obj = frame_->obj_;
    }
    obj_value = src_obj->LookupValue(insn_->label_, false);
    CHECK(obj_value) << "Failed to LoadObj: " << sym_cstr(insn_->label_);
    CHECK(obj_value->IsObjectType()) << " is not a object";
    dst_value.object_ = obj_value->object_;
    dst_value.type_ = obj_value->type_;
  } else {
    dst_value.object_ = frame_->obj_;
    dst_value.type_ = Value::OBJECT;
  }
}

void Executor::ExecIncDec() {
  int target = dreg(0)->id_;
  iroha::NumericValue n1;
  n1.SetValue0(1);
  iroha::Numeric res;
  if (op() == OP_PRE_INC) {
    iroha::Op::Add0(val(target).num_.GetArray(), n1, res.GetMutableArray());
  } else {
    iroha::Op::Sub0(val(target).num_.GetArray(), n1, res.GetMutableArray());
  }
  iroha::Op::FixupWidth(mreg(target)->type_.width_,
			&res);
  res.type_ = mreg(target)->type_.width_;
  val(target).num_ = res;
}

void Executor::ExecNonNumResultBinop() {
  int dst = dreg(0)->id_;
  int lhs = sreg(0)->id_;
  int rhs = sreg(1)->id_;
  switch (op()) {
  case OP_ASSIGN:
    val(lhs) = val(rhs);
    val(dst) = val(rhs);
    break;
  case OP_LAND:
    val(dst).enum_val_.val =
      val(lhs).enum_val_.val &&
      val(rhs).enum_val_.val;
    break;
  case OP_LOR:
    val(dst).enum_val_.val =
      val(lhs).enum_val_.val ||
      val(rhs).enum_val_.val;
    break;
  case OP_GT:
  case OP_LT:
  case OP_GTE:
  case OP_LTE:
    {
      // fall through.
      CHECK(mreg(lhs)->type_.value_type_ == Value::NUM &&
	    mreg(rhs)->type_.value_type_ == Value::NUM);
    }
  case OP_EQ:
  case OP_NE:
    {
      bool r;
      if (mreg(rhs)->type_.value_type_ == Value::NUM) {
	iroha::CompareOp cmp_op;
	switch (op()) {
	case OP_LT:
	case OP_GTE:
	  cmp_op = iroha::COMPARE_LT;
	  break;
	case OP_GT:
	case OP_LTE:
	  cmp_op = iroha::COMPARE_GT;
	  break;
	case OP_EQ:
	case OP_NE:
	  cmp_op = iroha::COMPARE_EQ;
	  break;
	default:
	  cmp_op = iroha::COMPARE_EQ;
	  CHECK(false);
	  break;
	}
	r = iroha::Op::Compare0(cmp_op, val(lhs).num_.GetArray(),
				val(rhs).num_.GetArray());
      } else if (mreg(rhs)->type_.value_type_ ==
		 Value::ENUM_ITEM) {
	r = (val(lhs).enum_val_.val ==
	     val(rhs).enum_val_.val);
      } else {
	r = val(lhs).object_->Compare(val(rhs).object_);
      }
      if (op() == OP_NE || op() == OP_GTE ||
	  op() == OP_LTE) {
	r = !r;
      }
      val(dst).SetBool(r);
    }
    break;
  case OP_ADD:
  case OP_ADD_MAY_WITH_TYPE:
    {
      CHECK(mreg(lhs)->type_.value_type_ ==
	    mreg(rhs)->type_.value_type_);
      CHECK(mreg(lhs)->type_.value_type_ == Value::OBJECT);
      string r = val(lhs).object_->ToString() +
	val(rhs).object_->ToString();
      val(dst).object_ =
	StringWrapper::NewStringWrapper(thr_->GetVM(), r);
    }
    break;
  default:
    CHECK(false) << "unknown non num binop:" << vm::OpCodeName(op());
  }
}

bool Executor::ExecGoto() {
  frame_->pc_ = insn_->jump_target_;
  return thr_->OnJump();
}

void Executor::ExecIf() {
  int cond = sreg(0)->id_;
  Value &cond_val = val(cond);
  CHECK(cond_val.type_ == Value::ENUM_ITEM);
  if (cond_val.enum_val_.val) {
    ++frame_->pc_;
  } else {
    frame_->pc_ = insn_->jump_target_;
  }
}

bool Executor::ExecFuncall() {
  Object *obj;
  Method *callee_method = LookupCompiledMethod(&obj);
  if (callee_method == nullptr) {
    return true;
  }
  vector<Value> args;
  for (size_t i = 0; i < insn_->src_regs_.size(); ++i) {
    args.push_back(val(insn_->src_regs_[i]->id_));
  }
  auto fn = callee_method->GetMethodFunc();
  if (fn != nullptr) {
    // Native method call (implementation in C++).
    // Copy types of argument values too, since (most of) native methods
    // don't assume argument types.
    for (size_t i = 0; i < insn_->src_regs_.size(); ++i) {
      args[i].type_ = insn_->src_regs_[i]->type_.value_type_;
      args[i].num_.type_ = insn_->src_regs_[i]->type_.width_;
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

Method *Executor::LookupCompiledMethod(Object **obj) {
  Method *method = LookupMethod(obj);
  if (method == nullptr) {
    return nullptr;
  }
  compiler::Compiler::CompileMethod(thr_->GetVM(), *obj, method);
  if (method->IsCompileFailure()) {
    return nullptr;
  }
  return method;
}

Method *Executor::LookupMethod(Object **obj) {
  Value &obj_value = val(oreg()->id_);
  CHECK(obj_value.IsObjectType());
  *obj = obj_value.object_;
  Value *value = (*obj)->LookupValue(insn_->label_, false);
  if (!value) {
    Status::os(Status::USER_ERROR) << "method not found: "
				   << sym_cstr(insn_->label_);
    thr_->UserError();
    return nullptr;
  }
  CHECK(value->type_ == Value::METHOD);
  return value->method_;
}

void Executor::ExecFuncallDone() {
  for (size_t i = 0; i < insn_->dst_regs_.size() &&
	 i < frame_->returns_.size(); ++i) {
    val(insn_->dst_regs_[i]->id_) = frame_->returns_[i];
  }
  frame_->returns_.clear();
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

void Executor::ExecMemberAccess() {
  Object *obj;
  if (op() == OP_MEMBER_READ || op() == OP_MEMBER_READ_WITH_CHECK) {
    obj = val(sreg(0)->id_).object_;
  } else {
    obj = val(sreg(1)->id_).object_;
  }
  Value *member = obj->LookupValue(insn_->label_, false);
  if (member == nullptr) {
    Status::os(Status::USER_ERROR) << "member not found: "
				   << sym_cstr(insn_->label_);
    thr_->UserError();
    return;
  }
  if (TlsWrapper::IsTlsValue(member)) {
    member = TlsWrapper::GetValue(member->object_, thr_);
  }
  if (op() == OP_MEMBER_READ || op() == OP_MEMBER_READ_WITH_CHECK) {
    val(dreg(0)->id_).CopyDataFrom(*member,
				   member->num_.type_);
    if (m()->IsTopLevel()) {
      // Copies data type to the method.
      auto *dst_reg = dreg(0);
      dst_reg->type_.value_type_ = member->type_;
      dst_reg->type_.width_ = member->num_.type_;
      dst_reg->type_.object_name_ = member->type_object_name_;
    }
  } else {
    // OP_MEMBER_WRITE
    CHECK(insn_->src_regs_.size() == 2);
    CHECK(sreg(0)->id_ == dreg(0)->id_);
    // src: value, obj
    int id = sreg(0)->id_;
    Value &src = val(id);
    member->CopyDataFrom(src, mreg(id)->type_.width_);
    member->type_ =
      mreg(sreg(0)->id_)->type_.value_type_;
  }
}

void Executor::ExecBitRange() {
  int dst = dreg(0)->id_;
  if (mreg(dst)->type_.value_type_ == Value::NONE) {
    InsnAnnotator::AnnotateBitRangeInsn(insn_);
  }
  int h = val(sreg(1)->id_).num_.GetValue0();
  int l = val(sreg(2)->id_).num_.GetValue0();
  Value &value = val(sreg(0)->id_);
  Value &res = val(dst);
  iroha::Op::SelectBits(value.num_, h, l, res.num_.GetMutableArray(), nullptr);
}

void Executor::InitializeArray(IntArray *array,
			       fe::ArrayInitializer *array_initializer) {
  if (array_initializer) {
    for (size_t i = 0; i < array_initializer->num_.size(); ++i) {
      iroha::Numeric num;
      iroha::Op::MakeConst0(array_initializer->num_[i], num.GetMutableArray());
      array->WriteSingle(i, num.type_, num.GetArray());
    }
  }
}

void Executor::ExecVardecl() {
  fe::VarDecl *decl = insn_->insn_stmt_->GetVarDecl();
  Annotation *an = decl->GetAnnotation();
  Object *obj = val(oreg()->id_).object_;
  CHECK(obj);
  sym_t name = decl->GetNameExpr()->GetSym();
  Value *value = obj->LookupValue(name, true);
  DeclAnnotator::AnnotateValueType(thr_->GetVM(), decl, value);
  if (value->type_ == Value::NUM) {
    iroha::Numeric::MayPopulateStorage(value->num_.type_,
				       nullptr, value->num_.GetMutableArray());
    iroha::Op::MakeConst0(0, value->num_.GetMutableArray());
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

void Executor::ExecThreadDecl() {
  Object *callee_obj;
  Method *callee_method = LookupMethod(&callee_obj);
  CHECK(callee_method) << "no method";
  sym_t method_name = insn_->label_;
  Object *thread_obj =
    ThreadWrapper::NewThreadWrapper(thr_->GetVM(), method_name, false, 0);

  CHECK(callee_obj == val(oreg()->id_).object_);
  sym_t member_name = insn_->insn_stmt_->GetExpr()->GetLhs()->GetSym();
  Value *value = callee_obj->LookupValue(member_name, true);
  value->type_ = Value::OBJECT;
  value->object_ = thread_obj;
}

void Executor::ExecChannelDecl() {
  int width = insn_->insn_stmt_->GetWidth().GetWidth();
  Annotation *an = insn_->insn_stmt_->GetAnnotation();
  CHECK(an == nullptr || !an->IsThreadLocal());
  Object *channel_obj =
    ChannelWrapper::NewChannel(thr_->GetVM(), width, insn_->label_, an);

  Object *obj = val(oreg()->id_).object_;
  CHECK(obj);
  Value *value = obj->LookupValue(insn_->label_, true);
  value->type_ = Value::OBJECT;
  value->object_ = channel_obj;
}

void Executor::ExecMailboxDecl() {
  Annotation *an = insn_->insn_stmt_->GetAnnotation();
  int width = insn_->insn_stmt_->GetWidth().GetWidth();
  Object *mailbox_obj =
    MailboxWrapper::NewMailbox(thr_->GetVM(), width, insn_->label_, an);
  Object *obj = val(oreg()->id_).object_;
  CHECK(obj);
  Value *value = obj->LookupValue(insn_->label_, true);
  value->type_ = Value::OBJECT;
  value->object_ = mailbox_obj;
}

void Executor::ExecImport() {
  const string &fn = insn_->insn_stmt_->GetString();
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

  if (insn_->dst_regs_.size() > 0) {
    // import "foo.karuta" as v
    int dst_id = dreg(0)->id_;
    val(dst_id).object_ = thr_obj;
    val(dst_id).type_ = Value::OBJECT;
  }
}

void Executor::ExecFuncdecl() {
  Object *obj = val(oreg()->id_).object_;
  if (!obj) {
    Status::os(Status::USER_ERROR) << "Can't find object";
    thr_->UserError();
    return;
  }

  Value *value = obj->LookupValue(insn_->label_, true);
  value->type_ = Value::METHOD;
  Method *new_method = thr_->GetVM()->NewMethod(false /* not toplevel */);
  new_method->SetParseTree(insn_->insn_stmt_->GetMethodDef());
  value->method_ = new_method;

  ClearThreadEntry();
  bool is_soft_thread = false;
  bool is_thread_entry = false;
  string thr_name;
  Annotation *an = new_method->GetAnnotation();
  if (an != nullptr) {
    thr_name = an->GetName();
    is_thread_entry = an->IsThreadEntry();
    is_soft_thread = an->IsSoftThreadEntry();
  }
  if (sym_str(insn_->label_) == "main") {
    is_thread_entry = true;
  }
  if (thr_name.empty()) {
    thr_name = "$thr_" + sym_str(insn_->label_);
  }
  if (is_thread_entry || is_soft_thread) {
    int num = 1;
    if (an != nullptr) {
      num = an->GetNum();
    }
    AddThreadEntry(thr_name, num, is_soft_thread);
  }
  if (an != nullptr && an->IsDataFlowEntry()) {
    AddThreadEntry(thr_name, 1, false);
  }
}

void Executor::AddThreadEntry(const string &name, int num, bool is_soft) {
  Object *callee_obj;
  Object *obj = val(oreg()->id_).object_;
  for (int i = 0; i < num; ++i) {
    Object *thread_obj =
      ThreadWrapper::NewThreadWrapper(thr_->GetVM(), insn_->label_, is_soft, i);
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

void Executor::ClearThreadEntry() {
  Object *obj = val(oreg()->id_).object_;
  ThreadWrapper::DeleteThreadByMethodName(obj, sym_str(insn_->label_));
}

void Executor::ExecMemberReadWithCheck() {
  ExecMemberAccess();
  // Annotate the type of the results now.
  CHECK(op() == OP_MEMBER_READ_WITH_CHECK);
  Value &obj_value = val(sreg(0)->id_);
  CHECK(obj_value.type_ == Value::OBJECT);
  Object *obj = obj_value.object_;
  Value *member = obj->LookupValue(insn_->label_, false);
  int dst_id = dreg(0)->id_;
  Register *dst_reg = mreg(dst_id);
  dst_reg->type_.value_type_ = member->type_;
  dst_reg->type_.object_name_ = member->type_object_name_;
  dst_reg->type_object_ = NumericObject::Get(thr_->GetVM(),
					     member->type_object_name_);
}

bool Executor::ExecFuncallWithCheck() {
  Object *obj;
  Method *callee_method = LookupMethod(&obj);
  if (callee_method == nullptr) {
    return true;
  }
  if (callee_method->GetParseTree() != nullptr) {
    // non native
    if (insn_->src_regs_.size() != callee_method->GetNumArgRegisters()) {
      CHECK(false) << "number of arguments doesn't match";
    }
  }
  return ExecFuncall();
}

void Executor::ExecFuncallDoneWithCheck() {
  Object *obj;
  Method *callee_method = LookupMethod(&obj);
  CHECK(callee_method);
  int num_returns = callee_method->GetNumReturnRegisters();
  int num_dsts = insn_->dst_regs_.size();
  // Annotates return values.
  CHECK(num_dsts == 1 || num_dsts == num_returns);
  for (int i = 0; i < num_dsts && i < num_returns; ++i) {
    insn_->dst_regs_[i]->type_ = callee_method->return_types_[i];
  }
  ExecFuncallDone();
}

void Executor::ExecArrayWriteWithCheck() {
  if (oreg()) {
    // Annotates the result value.
    // e.g. result = (a[i] = v)
    Object *array_obj = val(oreg()->id_).object_;
    if (ArrayWrapper::IsIntArray(array_obj)) {
      IntArray *array = ArrayWrapper::GetIntArray(array_obj);

      int dst_id = dreg(0)->id_;
      mreg(dst_id)->type_.width_ = array->GetDataWidth();
      mreg(dst_id)->type_.value_type_ = Value::NUM;
    } else {
      CHECK(ArrayWrapper::IsObjectArray(array_obj));
      int dst_id = dreg(0)->id_;
      mreg(dst_id)->type_.value_type_ = Value::OBJECT;
    }
  }
  ExecArrayWrite();
}

void Executor::ExecSetTypeObject() {
  int dst_id = dreg(0)->id_;
  Register *reg = mreg(dst_id);
  reg->type_object_ = NumericObject::Get(thr_->GetVM(),
					 reg->type_.object_name_);
  if (reg->type_object_ == nullptr) {
    Status::os(Status::USER_ERROR) << "Can't find numeric type: "
				   << sym_cstr(reg->type_.object_name_);
    thr_->UserError();
  }
}

bool Executor::MayExecuteCustomOp() {
  int lhs = sreg(0)->id_;
  int rhs = sreg(1)->id_;
  if (mreg(lhs)->type_.value_type_ != Value::NUM ||
      mreg(rhs)->type_.value_type_ != Value::NUM) {
    return false;
  }
  if (IsCustomOpCall(frame_->method_)) {
    return ExecCustomOp();
  }
  return false;
}

bool Executor::ExecCustomOp() {
  int lhs = sreg(0)->id_;
  Object *type_obj = mreg(lhs)->type_object_;
  sym_t s = NumericObject::GetMethodName(type_obj, op());
  CHECK(s);
  Value *value = type_obj->LookupValue(s, false);
  CHECK(value != nullptr && value->type_ == Value::METHOD &&
	value->method_ != nullptr);
  Method *op_method = value->method_;
  compiler::Compiler::CompileMethod(thr_->GetVM(), type_obj, op_method);
  CHECK(!m()->IsCompileFailure());
  vector<Value> args;
  for (size_t i = 0; i < insn_->src_regs_.size(); ++i) {
    args.push_back(val(insn_->src_regs_[i]->id_));
  }
  auto fn = op_method->GetMethodFunc();
  CHECK(fn == nullptr);
  SetupCalleeFrame(type_obj, op_method, args);
  return true;
}


void Executor::ExecMayWithTypeDone() {
  if (IsCustomOpCall(m())) {
    dreg(0)->type_ = sreg(0)->type_;
    ExecFuncallDone();
  }
}

bool Executor::IsCustomOpCall(const Method *method) {
  int lhs = sreg(0)->id_;
  int rhs = sreg(1)->id_;
  if (method->method_regs_[rhs]->type_object_ != nullptr &&
      method->method_regs_[lhs]->type_object_ ==
      method->method_regs_[rhs]->type_object_) {
    return true;
  }
  return false;
}

}  // namespace vm

