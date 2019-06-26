#include "vm/thread.h"

#include "base/dump_stream.h"
#include "base/status.h"
#include "fe/method.h"
#include "fe/var_decl.h"
#include "karuta/env.h"
#include "vm/value.h"
#include "vm/executor.h"
#include "vm/insn.h"
#include "vm/method.h"
#include "vm/object.h"
#include "vm/profile.h"
#include "vm/vm.h"

namespace vm {

string Thread::dbg_bytecode_;

Thread::Thread(VM *vm, Thread *parent, Object *obj, Method *method, int index)
  : vm_(vm), parent_thread_(parent),
    in_yield_(false), index_(index), busy_counter_(0) {
  stat_ = RUNNABLE;
  PushMethodFrame(obj, method);
  MaySetThreadIndex();
  busy_counter_limit_ = Env::GetDuration();
}

Thread::~Thread() {
  while (method_stack_.size() > 0) {
    PopMethodFrame();
  }
}

void Thread::SetByteCodeDebug(string flags) {
  dbg_bytecode_ = flags;
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
  Executor executor(this, frame);
  Profile *profile = vm_->GetProfile();
  bool profile_enabled = profile->IsEnabled();
  while (frame->pc_ < method->insns_.size()) {
    if (profile_enabled) {
      profile->Mark(method, frame->pc_);
    }
    Insn *insn = method->insns_[frame->pc_];
    bool need_suspend = executor.ExecInsn(insn);
    if (need_suspend) {
      return;
    }
  }
  PassReturnValues();
  if (ByteCodeDebugMode::IsEnabled(dbg_bytecode_)) {
    // debug run time annotating.
    if (method->IsTopLevel()) {
      DumpStream ds(cout);
      ds.os << "--post toplevel execution.\n";
      method->Dump(ds);
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
  MayBlock();
  stat_ = SUSPENDED;
}

void Thread::Exit() {
  stat_ = DONE;
}

void Thread::Resume() {
  CHECK(stat_ == SUSPENDED);
  stat_ = RUNNABLE;
}

void Thread::SetInYield(bool in_yield) {
  in_yield_ = in_yield;
}

bool Thread::GetInYield() {
  return in_yield_;
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

bool Thread::OnJump() {
  busy_counter_++;
  if (busy_counter_limit_ > 0 && busy_counter_ > busy_counter_limit_) {
    Status::os(Status::USER_ERROR)
      << "Busy loop detected. Killing the thread. "
      << "Increase the limit by --duration option, if necessary.";
    UserError();
    Exit();
    // true to suspend the Executor.
    return true;
  }
  return false;
}

void Thread::MayBlock() {
  busy_counter_ = 0;
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
    local_val.num_type_ = reg->type_.width_;
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
  auto *parse_tree = frame->method_->GetParseTree();
  fe::VarDeclSet *args = parse_tree->GetArgs();
  fe::VarDeclSet *returns = parse_tree->GetReturns();
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

void Thread::MaySetThreadIndex() {
  MethodFrame *frame = CurrentMethodFrame();
  CHECK(frame->method_->GetNumArgRegisters() <= 1)
    << "Too many arguments for a thread entry method";
  if (frame->method_->GetNumArgRegisters() == 1) {
    frame->reg_values_[0].num_.SetValue0(index_);
  }
}

}  // namespace vm
