#include "vm/executor_toplevel.h"

#include "base/annotation.h"
#include "base/dump_stream.h"
#include "base/status.h"
#include "compiler/compiler.h"
#include "fe/fe.h"
#include "fe/expr.h"
#include "fe/method.h"
#include "fe/stmt.h"
#include "fe/var_decl.h"
#include "numeric/numeric_op.h"  // from iroha
#include "vm/array_wrapper.h"
#include "vm/method.h"
#include "vm/channel_wrapper.h"
#include "vm/insn.h"
#include "vm/insn_annotator.h"
#include "vm/int_array.h"
#include "vm/mailbox_wrapper.h"
#include "vm/numeric_object.h"
#include "vm/thread_wrapper.h"
#include "vm/tls_wrapper.h"
#include "vm/object.h"
#include "vm/opcode.h"
#include "vm/thread.h"
#include "vm/vm.h"

namespace vm {

ExecutorToplevel::ExecutorToplevel(Thread *thr) : Executor(thr) {
}

bool ExecutorToplevel::ExecInsn(Method *method, MethodFrame *frame,
				Insn *insn) {
  bool need_suspend = false;
  switch (insn->op_) {
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
    ExecImport(insn);
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
  case OP_ADD_MAY_WITH_TYPE:
  case OP_SUB_MAY_WITH_TYPE:
  case OP_MUL_MAY_WITH_TYPE:
    if (MayExecuteCustomOp(method, frame, insn)) {
      need_suspend = true;
      if (!thr_->IsRunnable()) {
	return true;
      }
      break;
    }
    return Executor::ExecInsn(method, frame, insn);
  case OP_MAY_WITH_TYPE_DONE:
    ExecMayWithTypeDone(method, frame, insn);
    break;
    // Just a sanity check. Can be removed later.
  case OP_ADD: case OP_SUB: case OP_MUL:
  case OP_MEMBER_READ: case OP_FUNCALL: case OP_FUNCALL_DONE:
    CHECK(false);
    break;
  default:
    return Executor::ExecInsn(method, frame, insn);
  }
  ++frame->pc_;
  return need_suspend;
}

void ExecutorToplevel::ExecVardecl(const Method *method, MethodFrame *frame,
				   Insn *insn) {
  fe::VarDecl *decl = insn->insn_stmt_->GetVarDecl();
  Annotation *an = decl->GetAnnotation();
  Object *obj = frame->reg_values_[insn->obj_reg_->id_].object_;
  CHECK(obj);
  sym_t name = decl->GetNameExpr()->GetSym();
  Value *value = obj->LookupValue(name, true);
  InsnAnnotator::AnnotateValueType(thr_->GetVM(), decl, value);
  if (value->type_ == Value::NUM) {
    iroha::Op::MakeConst(0, &value->num_);
  }
  if (value->type_ == Value::INT_ARRAY) {
    value->object_ = CreateMemoryObject(decl->GetWidth(),
					decl->GetArrayLength(),
					decl->GetArrayInitializer(),
					decl->GetAnnotation());
  }
  if (value->type_ == Value::OBJECT_ARRAY) {
    value->object_ = CreateObjectArray(decl->GetArrayLength());
  }
  if (an != nullptr && an->IsThreadLocal()) {
    TlsWrapper::InjectTlsWrapper(thr_->GetVM(), value);
  }
}

void ExecutorToplevel::ExecThreadDecl(const Method *method, MethodFrame *frame,
				      Insn *insn) {
  Object *callee_obj;
  Method *callee_method = LookupMethod(frame, insn, &callee_obj);
  CHECK(callee_method) << "no method";
  sym_t method_name = insn->label_;
  Object *thread_obj =
    ThreadWrapper::NewThreadWrapper(thr_->GetVM(), method_name, false);

  CHECK(callee_obj == frame->reg_values_[insn->obj_reg_->id_].object_);
  sym_t member_name = insn->insn_stmt_->GetExpr()->GetLhs()->GetSym();
  Value *value = callee_obj->LookupValue(member_name, true);
  value->type_ = Value::OBJECT;
  value->object_ = thread_obj;
}

void ExecutorToplevel::ExecChannelDecl(const Method *method,
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

void ExecutorToplevel::ExecMailboxDecl(const Method *method,
				       MethodFrame *frame, Insn *insn) {
  int width = insn->insn_stmt_->GetWidth().GetWidth();
  Object *mailbox_obj =
    MailboxWrapper::NewMailbox(thr_->GetVM(), width, insn->label_);
  Object *obj = frame->reg_values_[insn->obj_reg_->id_].object_;
  CHECK(obj);
  Value *value = obj->LookupValue(insn->label_, true);
  value->type_ = Value::OBJECT;
  value->object_ = mailbox_obj;
}

void ExecutorToplevel::ExecImport(Insn *insn) {
  const string &fn = insn->insn_stmt_->GetString();
  VM *vm = thr_->GetVM();
  Method *method = fe::FE::CompileFile(fn, false, vm);
  if (!method) {
    Status::os(Status::USER_ERROR) << "Failed to import: " << fn;
    thr_->UserError();
    return;
  }
  vm->AddThreadFromMethod(thr_, vm->kernel_object_, method);
  thr_->Suspend();
}

void ExecutorToplevel::ExecFuncdecl(const Method *method, MethodFrame *frame,
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
      an->GetNum();
    }
    AddThreadEntry(frame, insn, thr_name, num, is_soft_thread);
  }
  if (an != nullptr && an->IsDataFlowEntry()) {
    AddThreadEntry(frame, insn, thr_name, 1, false);
  }
}

void ExecutorToplevel::AddThreadEntry(MethodFrame *frame, Insn *insn,
				      const string &name, int num,
				      bool is_soft) {
  Object *callee_obj;
  Object *obj = frame->reg_values_[insn->obj_reg_->id_].object_;
  for (int i = 0; i < num; ++i) {
    Object *thread_obj =
      ThreadWrapper::NewThreadWrapper(thr_->GetVM(), insn->label_, is_soft);
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

void ExecutorToplevel::ClearThreadEntry(MethodFrame *frame, Insn *insn) {
  Object *obj = frame->reg_values_[insn->obj_reg_->id_].object_;
  ThreadWrapper::DeleteThreadByMethodName(obj, sym_str(insn->label_));
}

void ExecutorToplevel::ExecMemberReadWithCheck(Method *method,
					       MethodFrame *frame,
					       const Insn *insn) {
  Executor::ExecMemberAccess(frame, insn);
  // Annotate the type of the results now.
  CHECK(insn->op_ == OP_MEMBER_READ_WITH_CHECK);
  Value &obj_value = frame->reg_values_[insn->src_regs_[0]->id_];
  CHECK(obj_value.type_ == Value::OBJECT);
  Object *obj = obj_value.object_;
  Value *member = obj->LookupValue(insn->label_, false);
  int dst_id = insn->dst_regs_[0]->id_;
  method->method_regs_[dst_id]->type_.value_type_ = member->type_;
}

bool ExecutorToplevel::ExecFuncallWithCheck(MethodFrame *frame, Insn *insn) {
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

void ExecutorToplevel::ExecFuncallDoneWithCheck(const Method *method,
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

void ExecutorToplevel::ExecArrayWriteWithCheck(Method *method,
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
    } else {
      CHECK(ArrayWrapper::IsObjectArray(array_obj));
      int dst_id = insn->dst_regs_[0]->id_;
      method->method_regs_[dst_id]->type_.value_type_ = Value::OBJECT;
    }
  }
  Executor::ExecArrayWrite(frame, insn);
}

void ExecutorToplevel::ExecSetTypeObject(Method *method, Insn *insn) {
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

bool ExecutorToplevel::MayExecuteCustomOp(const Method *method, MethodFrame *frame, Insn *insn) {
  int lhs = insn->src_regs_[0]->id_;
  int rhs = insn->src_regs_[1]->id_;
  if (frame->reg_values_[lhs].type_ != Value::NUM ||
      frame->reg_values_[rhs].type_ != Value::NUM) {
    return false;
  }
  if (IsCustomOpCall(method, insn)) {
    return ExecCustomOp(method, frame, insn);
  }
  return false;
}

bool ExecutorToplevel::ExecCustomOp(const Method *method, MethodFrame *frame,
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
  SetupCallee(type_obj, op_method, args);
  return true;
}


void ExecutorToplevel::ExecMayWithTypeDone(const Method *method,
					   MethodFrame *frame, Insn *insn) {
  int lhs = insn->src_regs_[0]->id_;
  int rhs = insn->src_regs_[1]->id_;
  if (IsCustomOpCall(method, insn)) {
    insn->dst_regs_[0]->type_ = insn->src_regs_[0]->type_;
    Executor::ExecFuncallDone(method, frame, insn);
  }
}

bool ExecutorToplevel::IsCustomOpCall(const Method *method, Insn *insn) {
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
