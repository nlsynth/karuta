#include "vm/thread.h"

#include "base/dump_stream.h"
#include "fe/method.h"
#include "fe/var_decl.h"
#include "base/status.h"
#include "vm/value.h"
#include "vm/executor.h"
#include "vm/executor_toplevel.h"
#include "vm/insn.h"
#include "vm/method.h"
#include "vm/object.h"
#include "vm/vm.h"

namespace vm {

bool Thread::dbg_bytecode_;

Thread::Thread(VM *vm, Thread *parent, Object *obj, Method *method)
  : vm_(vm), parent_thread_(parent),
    executor_(new Executor(this)),
    executor_toplevel_(new ExecutorToplevel(this)) {
  stat_ = RUNNABLE;
  PushMethodFrame(obj, method);
}

Thread::~Thread() {
  while (method_stack_.size() > 0) {
    PopMethodFrame();
  }
}

void Thread::SetByteCodeDebug(bool enable) {
  dbg_bytecode_ = enable;
}

void Thread::Run() {
  while (method_stack_.size() > 0) {
    RunMethod();
    if (!IsRunnable()) {
      return;
    }
  }
  if (parent_thread_) {
    parent_thread_->Resume();
  }
  stat_ = DONE;
}

void Thread::RunMethod() {
  MethodFrame *frame = CurrentMethodFrame();
  Method *method = frame->method_;
  Executor *executor;
  if (method->IsTopLevel()) {
    executor = executor_toplevel_.get();
  } else {
    executor = executor_.get();
  }
  while (frame->pc_ < method->insns_.size()) {
    Insn *insn = method->insns_[frame->pc_];
    bool need_suspend = executor->ExecInsn(method, frame, insn);
    if (need_suspend) {
      return;
    }
  }
  PassReturnValues();
  if (dbg_bytecode_) {
    // debug run time annotating.
    if (method->IsTopLevel()) {
      DumpStream ds(cout);
      ds.os << "--post toplevel execution.\n";
      method->Dump();
    }
  }
  PopMethodFrame();
}

void Thread::Dump(DumpStream &ds) const {
}

bool Thread::IsRunnable() const {
  return (stat_ == RUNNABLE);
}

bool Thread::IsDone() const {
  return (stat_ == DONE);
}

void Thread::Suspend() {
  stat_ = SUSPENDED;
}

void Thread::Exit() {
  stat_ = DONE;
}

void Thread::Resume() {
  CHECK(stat_ == SUSPENDED);
  stat_ = RUNNABLE;
}

VM *Thread::GetVM() {
  return vm_;
}

void Thread::SetReturnValueFromNativeMethod(const Value &value) {
  MethodFrame *frame = CurrentMethodFrame();
  frame->returns_.push_back(value);
}

bool Thread::IsRootThread() const {
  return (parent_thread_ == nullptr);
}

vector<MethodFrame*> &Thread::MethodStack() {
  return method_stack_;
}

void Thread::UserError() {
  Status::Check(Status::USER_ERROR, true);
  MethodFrame *frame = CurrentMethodFrame();
  Method *method = frame->method_;
  frame->pc_ = method->insns_.size();
  stat_ = DONE;
}

MethodFrame *Thread::PushMethodFrame(Object *obj, Method *method) {
  MethodFrame *frame = new MethodFrame;
  frame->method_ = method;
  frame->pc_ = 0;
  frame->obj_ = obj;
  frame->reg_values_.resize(method->method_regs_.size());
  for (size_t i = 0; i < method->method_regs_.size(); ++i) {
    Value &local_val = frame->reg_values_[i];
    Register *reg = method->method_regs_[i];
    local_val.type_ = reg->type_.value_type_;
    local_val.enum_val_.enum_type = reg->type_.enum_type_;
    if (local_val.type_ == Value::INT_ARRAY) {
      local_val.local_int_array_ =
	Executor::CreateIntArray(reg->type_.width_,
				 reg->GetArrayLength(),
				 reg->GetArrayInitializer());
    }
    local_val.num_.type_ = reg->type_.width_;
  }
  method_stack_.push_back(frame);
  return frame;
}

void Thread::PassReturnValues() {
  MethodFrame *parent_frame = ParentMethodFrame();
  if (!parent_frame) {
    return;
  }
  MethodFrame *frame = CurrentMethodFrame();
  fe::VarDeclSet *args = frame->method_->parse_tree_->args_;
  fe::VarDeclSet *returns = frame->method_->parse_tree_->returns_;
  int base = 0;
  if (args) {
    base = args->decls.size();
  }
  if (!returns) {
    return;
  }
  for (size_t i = 0; i < returns->decls.size(); ++i) {
    Value &value = frame->reg_values_[base + i];
    parent_frame->returns_.push_back(value);
  }
}

void Thread::PopMethodFrame() {
  CHECK(method_stack_.size() > 0) << "attempting to pop from empty method stack.";
  MethodFrame *frame = CurrentMethodFrame();
  method_stack_.pop_back();
  delete frame;
}

MethodFrame *Thread::CurrentMethodFrame() const {
  return method_stack_[method_stack_.size() - 1];
}

MethodFrame *Thread::ParentMethodFrame() const {
  if (method_stack_.size() < 2) {
    return nullptr;
  }
  return method_stack_[method_stack_.size() - 2];
}

}  // namespace vm
