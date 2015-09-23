#include "vm/executor_toplevel.h"

#include "dump_stream.h"
#include "messages.h"
#include "compiler/compiler.h"
#include "fe/fe.h"
#include "fe/expr.h"
#include "fe/stmt.h"
#include "fe/var_decl.h"
#include "vm/array_wrapper.h"
#include "vm/method.h"
#include "vm/channel.h"
#include "vm/insn.h"
#include "vm/insn_annotator.h"
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
  case OP_FUNCALL_DONE:
    ExecutorToplevel::ExecFuncallDone(method, frame, insn);
    break;
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
  sym_t name = decl->name_expr->sym_;
  Value *value = obj->LookupValue(name, true);
  InsnAnnotator::AnnotateValueType(decl, value);
  if (value->type_ == Value::NUM) {
    Numeric::MakeConst(0, 0, &value->num_);
  }
  if (value->type_ == Value::INT_ARRAY) {
    value->object_ = CreateMemoryObject(decl->width, decl->array_length,
					decl->array_initializer);
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
  Object *channel_obj =
    Channel::NewChannel(thr_->GetVM(), 32, insn->label_);

  Object *obj = frame->reg_values_[insn->obj_reg_->id_].object_;
  CHECK(obj);
  Value *value = obj->LookupValue(insn->label_, true);
  value->type_ = Value::OBJECT;
  value->object_ = channel_obj;
}

void ExecutorToplevel::ExecImport(Insn *insn) {
  const string &fn = insn->insn_stmt_->str_;
  VM *vm = thr_->GetVM();
  Method *method = fe::FE::CompileFile(fn, false, vm);
  if (!method) {
    thr_->UserError("Failed to import");
    return;
  }
  vm->AddThreadFromMethod(thr_, method);
  thr_->Suspend();
}

void ExecutorToplevel::ExecSpawn(MethodFrame *frame, Insn *insn) {
  VM *vm = thr_->GetVM();
  Object *obj;
  Method *method = LookupMethod(frame, insn, &obj);
  CHECK(method) << "no method";
  vm->AddThreadFromMethod(NULL, method);
}

void ExecutorToplevel::ExecFuncdecl(const Method *method, MethodFrame *frame,
				    Insn *insn) {
  Object *obj = frame->reg_values_[insn->obj_reg_->id_].object_;
  if (!obj) {
    thr_->UserError("can't find object");
    return;
  }

  Value *value = obj->LookupValue(insn->label_, true);
  value->type_ = Value::METHOD;
  Method *new_method = thr_->GetVM()->NewMethod(false /* not toplevel */);
  new_method->parse_tree_ = insn->insn_stmt_->method_def_;
  value->method_ = new_method;
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
    CHECK(ArrayWrapper::IsIntArray(array_obj));
    IntArray *array = ArrayWrapper::GetIntArray(array_obj);

    const NumberWidth *width = array->GetWidth();
    int dst_id = insn->dst_regs_[0]->id_;
    method->method_regs_[dst_id]->type_.width_ = width;
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

}  // namespace vm
