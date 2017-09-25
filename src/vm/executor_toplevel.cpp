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
#include "vm/channel.h"
#include "vm/insn.h"
#include "vm/insn_annotator.h"
#include "vm/mailbox_wrapper.h"
#include "vm/numeric_object.h"
#include "vm/thread_wrapper.h"
#include "vm/int_array.h"
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
  case OP_SPAWN:
    ExecSpawn(frame, insn);
    break;
  case OP_GENERIC_READ:
    need_suspend = ExecGenericRead(frame, insn);
    if (need_suspend) {
      return true;
    }
    break;
  case OP_GENERIC_WRITE:
    ExecGenericWrite(method, frame, insn);
    break;
  case OP_MEMBER_READ:
  case OP_MEMBER_WRITE:
    ExecutorToplevel::ExecMemberAccess(method, frame, insn);
    break;
  case OP_ARRAY_WRITE:
    ExecutorToplevel::ExecArrayWrite(method, frame, insn);
    break;
  case OP_FUNCALL:
    need_suspend = ExecutorToplevel::ExecFuncall(frame, insn);
    if (!thr_->IsRunnable()) {
      return true;
    }
    break;
  case OP_FUNCALL_DONE:
    ExecutorToplevel::ExecFuncallDone(method, frame, insn);
    break;
  case OP_SET_TYPE_OBJECT:
    ExecSetTypeObject(method, insn);
    break;
  case OP_ADD:
  case OP_SUB:
  case OP_MUL:
    if (MayExecuteCustomOp(method, frame, insn)) {
      break;
    }
    return Executor::ExecInsn(method, frame, insn);
  default:
    return Executor::ExecInsn(method, frame, insn);
  }
  ++frame->pc_;
  return need_suspend;
}

void ExecutorToplevel::ExecVardecl(const Method *method, MethodFrame *frame,
				   Insn *insn) {
  fe::VarDecl *decl = insn->insn_stmt_->decl_;
  Object *obj = frame->reg_values_[insn->obj_reg_->id_].object_;
  CHECK(obj);
  sym_t name = decl->GetNameExpr()->sym_;
  Value *value = obj->LookupValue(name, true);
  InsnAnnotator::AnnotateValueType(thr_->GetVM(), decl, value);
  if (decl->IsPtr()) {
    int aw = thr_->GetVM()->GetAddressSpaceWidth(obj);
    int dw = value->num_.type_.GetWidth();
    value->num_.type_ = iroha::NumericWidth(false, aw);
    value->pointee_width_ = dw;
  }
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
}

void ExecutorToplevel::ExecThreadDecl(const Method *method, MethodFrame *frame,
				      Insn *insn) {
  Object *callee_obj;
  Method *callee_method = LookupMethod(frame, insn, &callee_obj);
  CHECK(callee_method) << "no method";
  sym_t method_name = insn->label_;
  Object *thread_obj =
    ThreadWrapper::NewThreadWrapper(thr_->GetVM(), method_name, callee_method);

  CHECK(callee_obj == frame->reg_values_[insn->obj_reg_->id_].object_);
  sym_t member_name = insn->insn_stmt_->expr_->lhs_->sym_;
  Value *value = callee_obj->LookupValue(member_name, true);
  value->type_ = Value::OBJECT;
  value->object_ = thread_obj;
}

void ExecutorToplevel::ExecChannelDecl(const Method *method,
				       MethodFrame *frame, Insn *insn) {
  int width = insn->insn_stmt_->width_.GetWidth();
  Object *channel_obj =
    Channel::NewChannel(thr_->GetVM(), width, insn->label_);

  Object *obj = frame->reg_values_[insn->obj_reg_->id_].object_;
  CHECK(obj);
  Value *value = obj->LookupValue(insn->label_, true);
  value->type_ = Value::OBJECT;
  value->object_ = channel_obj;
}

void ExecutorToplevel::ExecMailboxDecl(const Method *method,
				       MethodFrame *frame, Insn *insn) {
  int width = insn->insn_stmt_->width_.GetWidth();
  Object *mailbox_obj =
    MailboxWrapper::NewMailbox(thr_->GetVM(), width, insn->label_);
  Object *obj = frame->reg_values_[insn->obj_reg_->id_].object_;
  CHECK(obj);
  Value *value = obj->LookupValue(insn->label_, true);
  value->type_ = Value::OBJECT;
  value->object_ = mailbox_obj;
}

void ExecutorToplevel::ExecImport(Insn *insn) {
  const string &fn = insn->insn_stmt_->str_;
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

void ExecutorToplevel::ExecSpawn(MethodFrame *frame, Insn *insn) {
  VM *vm = thr_->GetVM();
  Object *obj;
  Method *method = LookupMethod(frame, insn, &obj);
  CHECK(method) << "no method";
  vm->AddThreadFromMethod(nullptr, obj, method);
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
  new_method->parse_tree_ = insn->insn_stmt_->method_def_;
  value->method_ = new_method;
  Annotation *an = new_method->GetAnnotation();
  if (an != nullptr) {
    string name = an->GetName();
    if (name.empty()) {
      name = "$thr_" + sym_str(insn->label_);
    }
    if (an->IsThreadEntry()) {
      AddThreadEntry(frame, insn, name);
    }
    if (an->IsDataFlowEntry()) {
      AddThreadEntry(frame, insn, name);
    }
  }
}

void ExecutorToplevel::AddThreadEntry(MethodFrame *frame, Insn *insn,
				      const string &name) {
  Object *callee_obj;
  Method *callee_method = LookupMethod(frame, insn, &callee_obj);
  Object *thread_obj =
    ThreadWrapper::NewThreadWrapper(thr_->GetVM(),
				    insn->label_, callee_method);
  Object *obj = frame->reg_values_[insn->obj_reg_->id_].object_;
  Value *value = obj->LookupValue(sym_lookup(name.c_str()), true);
  value->type_ = Value::OBJECT;
  value->object_ = thread_obj;
}

void ExecutorToplevel::ExecMemberAccess(Method *method, MethodFrame *frame,
					const Insn *insn) {
  Executor::ExecMemberAccess(frame, insn);
  // Annotate the type now.
  if (insn->op_ == OP_MEMBER_READ) {
    Value &obj_value = frame->reg_values_[insn->src_regs_[0]->id_];
    CHECK(obj_value.type_ == Value::OBJECT);
    Object *obj = obj_value.object_;
    Value *member = obj->LookupValue(insn->label_, false);
    int dst_id = insn->dst_regs_[0]->id_;
    method->method_regs_[dst_id]->type_.value_type_ = member->type_;
  }
}

bool ExecutorToplevel::ExecGenericRead(MethodFrame *frame, Insn *insn) {
  if (insn->src_regs_.size()) {
    ExecMemoryRead(frame, insn);
  } else {
    return ExecChannelRead(frame, insn);
  }
  return false;
}

bool ExecutorToplevel::ExecFuncall(MethodFrame *frame, Insn *insn) {
  Object *obj;
  Method *callee_method = LookupMethod(frame, insn, &obj);
  if (callee_method == nullptr) {
    return true;
  }
  if (callee_method->parse_tree_ != nullptr) {
    // non native
    if (insn->src_regs_.size() != callee_method->GetNumArgRegisters()) {
      CHECK(false) << "number of arguments doesn't match";
    }
  }
  return Executor::ExecFuncall(frame, insn);
}

void ExecutorToplevel::ExecFuncallDone(const Method *method,
				       MethodFrame *frame,
				       Insn *insn) {
  Object *obj;
  Method *callee_method = LookupMethod(frame, insn, &obj);
  CHECK(callee_method);
  int num_returns = callee_method->GetNumReturnRegisters();
  int num_dsts = insn->dst_regs_.size();
  // annotate return values.
  CHECK(num_dsts == 1 || num_dsts == num_returns);
  for (int i = 0; i < num_dsts && i < num_returns; ++i) {
    insn->dst_regs_[i]->type_ = callee_method->return_types_[i];
  }
  Executor::ExecFuncallDone(method, frame, insn);
}

void ExecutorToplevel::ExecArrayWrite(Method *method, MethodFrame *frame,
				      Insn *insn) {
  if (insn->obj_reg_) {
    // Member array.
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

void ExecutorToplevel::ExecGenericWrite(const Method *method,
					MethodFrame *frame,
					Insn *insn) {
  if (insn->src_regs_.size() == 2) {
    // address, value.
    ExecMemoryWrite(method, frame, insn);
  } else if (insn->src_regs_.size() == 1) {
    // (obj: channel) value
    ExecChannelWrite(method, frame, insn);
  } else {
    CHECK(false);
  }
}

void ExecutorToplevel::ExecSetTypeObject(Method *method, Insn *insn) {
  int dst_id = insn->dst_regs_[0]->id_;
  Register *reg = method->method_regs_[dst_id];
  reg->type_object_ = NumericObject::Get(thr_->GetVM(),
					 reg->type_.object_name_);
}

bool ExecutorToplevel::MayExecuteCustomOp(const Method *method, MethodFrame *frame, Insn *insn) {
  int lhs = insn->src_regs_[0]->id_;
  int rhs = insn->src_regs_[1]->id_;
  if (frame->reg_values_[lhs].type_ != Value::NUM ||
      frame->reg_values_[rhs].type_ != Value::NUM) {
    return false;
  }
  if (method->method_regs_[rhs]->type_object_ != nullptr &&
      method->method_regs_[lhs]->type_object_ ==
      method->method_regs_[rhs]->type_object_) {
    CHECK(false) << "Custom op is not allowed from top level";
    return false;
  }
  return false;
}

}  // namespace vm
