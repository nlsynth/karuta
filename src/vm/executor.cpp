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

void Executor::ExecNum() {
  Register *d = dreg(0);
  if (IsTopLevel()) {
    d->type_.value_type_ = Value::NUM;
    d->type_.width_ = sreg(0)->initial_num_.type_;
  }
  iroha::Numeric::CopyValueWithWidth(sreg(0)->initial_num_.GetArray(),
				     sreg(0)->initial_num_.type_,
				     d->type_.width_,
				     nullptr,
				     &VAL(d).num_);
}

void Executor::ExecStr() {
  Value &v = VAL(dreg(0));
  v.object_ =
    StringWrapper::NewStringWrapper(thr_->GetVM(), InsnOpUtils::Str(insn_));
  if (IsTopLevel()) {
    v.type_ = Value::OBJECT;
  }
}

void Executor::ExecBinop() {
  Register *dst = dreg(0);
  Register *lhs = sreg(0);
  Register *rhs = sreg(1);
  if (dst->type_.value_type_ != Value::NUM) {
    if (dst->type_.value_type_ == Value::NONE) {
      CHECK(IsTopLevel());
      RetryBinopWithType();
    } else {
      ExecNonNumResultBinop();
    }
    return;
  }
  if (IsTopLevel()) {
    if (InsnType::IsNumCalculation(op())) {
      InsnAnnotator::AnnotateNumCalculationOp(insn_);
    }
    if (op() == OP_LSHIFT || op() == OP_RSHIFT) {
      dst->type_.width_ = lhs->type_.width_;
    }
  }
  switch (op()) {
  case OP_ADD:
  case OP_ADD_MAY_WITH_TYPE:
    iroha::Op::Add0(VAL(lhs).num_, VAL(rhs).num_,
		    &VAL(dst).num_);
    iroha::Op::FixupValueWidth(dst->type_.width_,
			       &VAL(dst).num_);
    break;
  case OP_SUB:
  case OP_SUB_MAY_WITH_TYPE:
    iroha::Op::Sub0(VAL(lhs).num_, VAL(rhs).num_,
		    &VAL(dst).num_);
    iroha::Op::FixupValueWidth(dst->type_.width_,
			       &VAL(dst).num_);
    break;
  case OP_MUL:
  case OP_MUL_MAY_WITH_TYPE:
    iroha::Op::CalcBinOp(iroha::BINOP_MUL,
			 VAL(lhs).num_, VAL(rhs).num_,
			 rhs->type_.width_,
			 &VAL(dst).num_);
    iroha::Op::FixupValueWidth(dst->type_.width_,
			       &VAL(dst).num_);
    break;
  case OP_DIV:
  case OP_DIV_MAY_WITH_TYPE:
    iroha::Op::CalcBinOp(iroha::BINOP_DIV,
			 VAL(lhs).num_, VAL(rhs).num_,
			 rhs->type_.width_,
			 &VAL(dst).num_);
    iroha::Op::FixupValueWidth(dst->type_.width_,
			       &VAL(dst).num_);
    break;
  case OP_ASSIGN:
    iroha::Numeric::CopyValueWithWidth(VAL(rhs).num_,
				       rhs->type_.width_,
				       dst->type_.width_,
				       nullptr,
				       &VAL(dst).num_);
    iroha::Op::FixupValueWidth(dst->type_.width_,
			       &VAL(dst).num_);
    if (IsTopLevel() &&
	!dst->GetIsDeclaredType()) {
      dst->type_ = rhs->type_;
    }
    break;
  case OP_AND:
    iroha::Op::CalcBinOp(iroha::BINOP_AND,
			 VAL(lhs).num_, VAL(rhs).num_,
			 lhs->type_.width_,
			 &VAL(dst).num_);
    break;
  case OP_OR:
    iroha::Op::CalcBinOp(iroha::BINOP_OR,
			 VAL(lhs).num_, VAL(rhs).num_,
			 lhs->type_.width_,
			 &VAL(dst).num_);
    break;
  case OP_XOR:
    iroha::Op::CalcBinOp(iroha::BINOP_XOR,
			 VAL(lhs).num_, VAL(rhs).num_,
			 lhs->type_.width_,
			 &VAL(dst).num_);
    break;
  case OP_CONCAT:
    {
      iroha::NumericWidth &lt = lhs->type_.width_;
      iroha::NumericWidth &rt = rhs->type_.width_;
      iroha::Op::Concat(VAL(lhs).num_, lt,
			VAL(rhs).num_, rt,
			&VAL(dst).num_, nullptr);
    }
    break;
  case OP_LSHIFT:
    iroha::Op::CalcBinOp(iroha::BINOP_LSHIFT,
			 VAL(lhs).num_, VAL(rhs).num_,
			 lhs->type_.width_,
			 &VAL(dst).num_);
    iroha::Op::FixupValueWidth(dst->type_.width_,
			       &VAL(dst).num_);
    break;
  case OP_RSHIFT:
    iroha::Op::CalcBinOp(iroha::BINOP_RSHIFT,
			 VAL(lhs).num_, VAL(rhs).num_,
			 lhs->type_.width_,
			 &VAL(dst).num_);
    iroha::Op::FixupValueWidth(dst->type_.width_,
			       &VAL(dst).num_);
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
  Register *lhs = sreg(0);
  Register *rhs = sreg(1);
  CHECK(lhs->type_.value_type_ == rhs->type_.value_type_);
  Register *dst = dreg(0);
  if (lhs->type_.value_type_ == Value::NUM) {
    dst->type_.value_type_ = Value::NUM;
  } else if (lhs->type_.value_type_ == Value::OBJECT) {
    dst->type_.value_type_ = Value::OBJECT;
  }
  ExecBinop();
}

void Executor::ExecArrayRead() {
  CHECK(oreg() != nullptr);
  Object *array_obj = VAL(oreg()).object_;
  CHECK(array_obj);
  Value &lhs_value = VAL(dreg(0));
  auto *dst_reg = dreg(0);
  if (ArrayWrapper::IsIntArray(array_obj)) {
    IntArray *array = ArrayWrapper::GetIntArray(array_obj);
    vector<uint64_t> indexes;
    PopulateArrayIndexes(0, &indexes);
    lhs_value.num_ = array->Read(indexes);
    if (IsTopLevel()) {
      dst_reg->type_.value_type_ = Value::NUM;
      dst_reg->type_.width_ = array->GetDataWidth();
    }
  } else {
    CHECK(ArrayWrapper::IsObjectArray(array_obj));
    int index = VAL(sreg(0)).num_.GetValue0();
    lhs_value.type_ = Value::OBJECT;
    lhs_value.object_ = ArrayWrapper::Get(array_obj, index);
    if (IsTopLevel()) {
      dst_reg->type_.value_type_ = Value::OBJECT;
    }
  }
}

void Executor::ExecArrayWrite() {
  CHECK(oreg() != nullptr);
  Object *array_obj = VAL(oreg()).object_;
  CHECK(array_obj);
  if (ArrayWrapper::IsIntArray(array_obj)) {
    IntArray *array = ArrayWrapper::GetIntArray(array_obj);
    vector<uint64_t> indexes;
    PopulateArrayIndexes(1, &indexes);
    iroha::Numeric n(VAL(sreg(0)).num_, sreg(0)->type_.width_);
    array->Write(indexes, n);
  } else {
    CHECK(ArrayWrapper::IsObjectArray(array_obj));
    Register *vobj = sreg(0);
    CHECK(vobj->type_.value_type_ == Value::OBJECT);
    int index = VAL(sreg(1)).num_.GetValue0();
    ArrayWrapper::Set(array_obj, index,
		      VAL(vobj).object_);
  }
}

void Executor::PopulateArrayIndexes(int start, vector<uint64_t> *indexes) {
  for (int i = start; i < insn_->src_regs_.size(); ++i) {
    uint64_t v = VAL(insn_->src_regs_[i]).num_.GetValue0();
    indexes->push_back(v);
  }
}

void Executor::ExecLogicInv() {
  int v = 1;
  Register *src = sreg(0);
  Value &value = VAL(src);
  if (src->type_.value_type_ == Value::ENUM_ITEM) {
    if (value.enum_val_.val != 0) {
      v = 0;
    }
  } else if (src->type_.value_type_ == Value::NUM) {
    if (!iroha::Op::IsZero(src->type_.width_, value.num_)) {
      v = 0;
    }
  }
  Value &dst_value = VAL(dreg(0));
  dst_value.enum_val_.val = v;
}

void Executor::ExecNumUniop() {
  Value &value = VAL(sreg(0));
  Value &dst_value = VAL(dreg(0));
  if (value.type_ == Value::ENUM_ITEM) {
    CHECK(op() == OP_BIT_INV);
    if (value.enum_val_.val) {
      dst_value.enum_val_.val = 0;
    } else {
      dst_value.enum_val_.val = 1;
    }
    return;
  }
  iroha::NumericValue res;
  switch (op()) {
  case OP_BIT_INV:
    iroha::Op::BitInv0(value.num_, &res);
    break;
  case OP_PLUS:
    res = value.num_;
    break;
  case OP_MINUS:
    iroha::Op::Minus0(value.num_, &res);
    break;
  default:
    CHECK(false);
    break;
  }
  iroha::Op::FixupValueWidth(dreg(0)->type_.width_, &res);
  dst_value.num_ = res;
}

void Executor::ExecLoadObj() {
  Value &dst_value = VAL(dreg(0));
  Value *obj_value;
  if (insn_->label_) {
    Object *src_obj;
    if (oreg()) {
      src_obj = VAL(oreg()).object_;
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
  if (IsTopLevel()) {
    dreg(0)->type_.value_type_ = Value::OBJECT;
  }
}

void Executor::ExecIncDec() {
  Register *target = dreg(0);
  iroha::NumericValue n1;
  n1.SetValue0(1);
  iroha::NumericValue res;
  if (op() == OP_PRE_INC) {
    iroha::Op::Add0(VAL(target).num_, n1, &res);
  } else {
    iroha::Op::Sub0(VAL(target).num_, n1, &res);
  }
  iroha::Op::FixupValueWidth(target->type_.width_, &res);
  VAL(target).num_ = res;
}

void Executor::ExecNonNumResultBinop() {
  Register *dst = dreg(0);
  Register *lhs = sreg(0);
  Register *rhs = sreg(1);
  switch (op()) {
  case OP_ASSIGN:
    VAL(lhs) = VAL(rhs);
    VAL(dst) = VAL(rhs);
    break;
  case OP_LAND:
    VAL(dst).enum_val_.val =
      VAL(lhs).enum_val_.val &&
      VAL(rhs).enum_val_.val;
    break;
  case OP_LOR:
    VAL(dst).enum_val_.val =
      VAL(lhs).enum_val_.val ||
      VAL(rhs).enum_val_.val;
    break;
  case OP_GT:
  case OP_LT:
  case OP_GTE:
  case OP_LTE:
    {
      // fall through.
      CHECK(lhs->type_.value_type_ == Value::NUM &&
	    rhs->type_.value_type_ == Value::NUM);
    }
  case OP_EQ:
  case OP_NE:
    {
      bool r;
      if (rhs->type_.value_type_ == Value::NUM) {
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
	r = iroha::Op::Compare0(cmp_op, VAL(lhs).num_,
				VAL(rhs).num_);
      } else if (rhs->type_.value_type_ ==
		 Value::ENUM_ITEM) {
	r = (VAL(lhs).enum_val_.val ==
	     VAL(rhs).enum_val_.val);
      } else {
	r = VAL(lhs).object_->Compare(VAL(rhs).object_);
      }
      if (op() == OP_NE || op() == OP_GTE ||
	  op() == OP_LTE) {
	r = !r;
      }
      VAL(dst).SetBool(r);
    }
    break;
  case OP_ADD:
  case OP_ADD_MAY_WITH_TYPE:
    {
      CHECK(lhs->type_.value_type_ == rhs->type_.value_type_);
      CHECK(lhs->type_.value_type_ == Value::OBJECT);
      string r = VAL(lhs).object_->ToString() +
	VAL(rhs).object_->ToString();
      VAL(dst).object_ =
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
  Register *cond = sreg(0);
  Value &cond_val = VAL(cond);
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
    args.push_back(VAL(insn_->src_regs_[i]));
  }
  auto fn = callee_method->GetMethodFunc();
  if (fn != nullptr) {
    // Native method call (implementation in C++).
    // Copy types of argument values too, since (most of) native methods
    // don't assume argument types.
    for (size_t i = 0; i < insn_->src_regs_.size(); ++i) {
      args[i].type_ = sreg(i)->type_.value_type_;
      args[i].num_type_ = sreg(i)->type_.width_;
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
  Value &obj_value = VAL(oreg());
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
    VAL(insn_->dst_regs_[i]) = frame_->returns_[i];
  }
  frame_->returns_.clear();
}

void Executor::SetupCalleeFrame(Object *obj, Method *callee_method,
				const vector<Value> &args) {
  MethodFrame *callee_frame = thr_->PushMethodFrame(obj, callee_method);
  for (size_t i = 0; i < args.size(); ++i) {
    callee_frame->reg_values_[i] = args[i];
  }
}

void Executor::ExecMemberAccess() {
  Object *obj;
  if (op() == OP_MEMBER_READ || op() == OP_MEMBER_READ_WITH_CHECK) {
    obj = VAL(sreg(0)).object_;
  } else {
    obj = VAL(sreg(1)).object_;
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
    VAL(dreg(0)).CopyDataFrom(*member, member->num_type_);
    if (IsTopLevel()) {
      // Copies data type to the method.
      auto *dst_reg = dreg(0);
      dst_reg->type_.value_type_ = member->type_;
      dst_reg->type_.width_ = member->num_type_;
      dst_reg->type_.object_name_ = member->type_object_name_;
    }
  } else {
    // OP_MEMBER_WRITE
    CHECK(insn_->src_regs_.size() == 2);
    CHECK(sreg(0)->id_ == dreg(0)->id_);
    // src: value, obj
    Register *src_reg = sreg(0);
    Value &src = VAL(src_reg);
    member->CopyDataFrom(src, src_reg->type_.width_);
    member->type_ = src_reg->type_.value_type_;
  }
}

void Executor::ExecBitRange() {
  Register *dst = dreg(0);
  if (dst->type_.value_type_ == Value::NONE) {
    InsnAnnotator::AnnotateBitRangeInsn(insn_);
  }
  int h = VAL(sreg(1)).num_.GetValue0();
  int l = VAL(sreg(2)).num_.GetValue0();
  Value &value = VAL(sreg(0));
  Value &res = VAL(dst);
  iroha::Op::SelectBits(value.num_, value.num_type_,
			h, l, &res.num_, nullptr);
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
  Object *obj = VAL(oreg()).object_;
  CHECK(obj);
  sym_t name = decl->GetNameExpr()->GetSym();
  Value *value = obj->LookupValue(name, true);
  DeclAnnotator::AnnotateValueType(thr_->GetVM(), decl, value);
  if (value->type_ == Value::NUM) {
    iroha::Numeric::MayPopulateStorage(value->num_type_,
				       nullptr, &value->num_);
    iroha::Op::MakeConst0(0, &value->num_);
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

  CHECK(callee_obj == VAL(oreg()).object_);
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

  Object *obj = VAL(oreg()).object_;
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
  Object *obj = VAL(oreg()).object_;
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
    Register *dst = dreg(0);
    VAL(dst).object_ = thr_obj;
    dst->type_.value_type_ = Value::OBJECT;
  }
}

void Executor::ExecFuncdecl() {
  Object *obj = VAL(oreg()).object_;
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
  Object *obj = VAL(oreg()).object_;
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
  Object *obj = VAL(oreg()).object_;
  ThreadWrapper::DeleteThreadByMethodName(obj, sym_str(insn_->label_));
}

void Executor::ExecMemberReadWithCheck() {
  ExecMemberAccess();
  // Annotate the type of the results now.
  CHECK(op() == OP_MEMBER_READ_WITH_CHECK);
  Value &obj_value = VAL(sreg(0));
  CHECK(sreg(0)->type_.value_type_ == Value::OBJECT);
  Object *obj = obj_value.object_;
  Value *member = obj->LookupValue(insn_->label_, false);
  Register *dst_reg = dreg(0);
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
    Object *array_obj = VAL(oreg()).object_;
    Register *dst_reg = dreg(0);
    if (ArrayWrapper::IsIntArray(array_obj)) {
      IntArray *array = ArrayWrapper::GetIntArray(array_obj);

      dst_reg->type_.width_ = array->GetDataWidth();
      dst_reg->type_.value_type_ = Value::NUM;
    } else {
      CHECK(ArrayWrapper::IsObjectArray(array_obj));
      dst_reg->type_.value_type_ = Value::OBJECT;
    }
  }
  ExecArrayWrite();
}

void Executor::ExecSetTypeObject() {
  Register *reg = dreg(0);
  reg->type_object_ = NumericObject::Get(thr_->GetVM(),
					 reg->type_.object_name_);
  if (reg->type_object_ == nullptr) {
    Status::os(Status::USER_ERROR) << "Can't find numeric type: "
				   << sym_cstr(reg->type_.object_name_);
    thr_->UserError();
  }
}

bool Executor::MayExecuteCustomOp() {
  Register *lhs = sreg(0);
  Register *rhs = sreg(1);
  if (lhs->type_.value_type_ != Value::NUM ||
      rhs->type_.value_type_ != Value::NUM) {
    return false;
  }
  if (IsCustomOpCall()) {
    return ExecCustomOp();
  }
  return false;
}

bool Executor::ExecCustomOp() {
  Register *lhs = sreg(0);
  Object *type_obj = lhs->type_object_;
  sym_t s = NumericObject::GetMethodName(type_obj, op());
  CHECK(s);
  Value *value = type_obj->LookupValue(s, false);
  CHECK(value != nullptr && value->type_ == Value::METHOD &&
	value->method_ != nullptr);
  Method *op_method = value->method_;
  compiler::Compiler::CompileMethod(thr_->GetVM(), type_obj, op_method);
  CHECK(!op_method->IsCompileFailure());
  vector<Value> args;
  for (size_t i = 0; i < insn_->src_regs_.size(); ++i) {
    args.push_back(VAL(insn_->src_regs_[i]));
  }
  auto fn = op_method->GetMethodFunc();
  CHECK(fn == nullptr);
  SetupCalleeFrame(type_obj, op_method, args);
  return true;
}


void Executor::ExecMayWithTypeDone() {
  if (IsCustomOpCall()) {
    dreg(0)->type_ = sreg(0)->type_;
    ExecFuncallDone();
  }
}

bool Executor::IsCustomOpCall() {
  Register *lhs = sreg(0);
  Register *rhs = sreg(1);
  if (rhs->type_object_ != nullptr &&
      lhs->type_object_ == rhs->type_object_) {
    return true;
  }
  return false;
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

}  // namespace vm
