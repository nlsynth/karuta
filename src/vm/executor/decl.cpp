#include "vm/executor/decl.h"

#include "base/status.h"
#include "compiler/compiler.h"
#include "fe/expr.h"
#include "fe/fe.h"
#include "fe/stmt.h"
#include "fe/var_decl.h"
#include "iroha/numeric.h"
#include "karuta/annotation.h"
#include "vm/array_wrapper.h"
#include "vm/channel_wrapper.h"
#include "vm/decl_annotator.h"
#include "vm/distance_wrapper.h"
#include "vm/int_array.h"
#include "vm/mailbox_wrapper.h"
#include "vm/object.h"
#include "vm/thread.h"
#include "vm/thread_wrapper.h"
#include "vm/tls_wrapper.h"
#include "vm/vm.h"

namespace vm {
namespace executor {

void Decl::ExecVardecl() {
  fe::VarDecl *decl = insn_->insn_stmt_->GetVarDecl();
  Annotation *an = decl->GetAnnotation();
  Object *obj = VAL(oreg()).object_;
  if (obj == nullptr) {
    Status::os(Status::USER_ERROR) << "Can't find object";
    thr_->UserError();
    return;
  }
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

void Decl::ExecThreadDecl() {
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

void Decl::ExecChannelDecl() {
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

void Decl::ExecMailboxDecl() {
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

void Decl::ExecFuncdecl() {
  Object *obj = VAL(oreg()).object_;
  if (obj == nullptr) {
    Status::os(Status::USER_ERROR) << "Can't find object to add function "
				   << sym_cstr(insn_->label_);
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
    is_soft_thread = an->IsSoftThreadEntry();
  }
  is_thread_entry = new_method->IsThreadEntry();
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

void Decl::PushCurrentObject() {
  vm::Object *obj = VAL(oreg()).object_;
  // (a) Uses the object if the label is not speficied (local var).
  // (b) Looks up a member object if label is specified (member var).
  // (c) Uses the module name from the file name if (b) fails (file object).
  if (insn_->label_ != sym_null) {
    Value *value = obj->LookupValue(insn_->label_, false);
    if (value != nullptr) {
      obj = value->object_;
    } else {
      if (sym_str(insn_->label_) != thr_->GetModuleName()) {
	Status::os(Status::USER_ERROR)
	  << "Failed to get object: "
	  << sym_str(insn_->label_) << " "
	  << insn_->insn_expr_->GetPos().Format();
	thr_->UserError();
	return;
      }
    }
  }
  Value *value = obj->LookupValue(sym_parent, true);
  value->type_ = Value::OBJECT;
  value->object_ = frame_->obj_;

  frame_->objs_.push_back(frame_->obj_);
  frame_->obj_ = obj;
}

void Decl::PopCurrentObject() {
  frame_->obj_ = *(frame_->objs_.rbegin());
  frame_->objs_.pop_back();
}

void Decl::AddThreadEntry(const string &name, int num, bool is_soft) {
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

void Decl::ClearThreadEntry() {
  Object *obj = VAL(oreg()).object_;
  ThreadWrapper::DeleteThreadByMethodName(obj, sym_str(insn_->label_));
}

void Decl::ExecImport() {
  const string &fn = insn_->insn_stmt_->GetString();
  VM *vm = thr_->GetVM();
  vm::Object *thr_obj = vm->kernel_object_->Clone();
  compiler::CompileOptions opts;
  Method *method = fe::FE::ImportFile(fn, vm, thr_obj);
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

void Decl::InitializeArray(IntArray *array,
			   fe::ArrayInitializer *array_initializer) {
  if (array_initializer != nullptr) {
    for (size_t i = 0; i < array_initializer->num_.size(); ++i) {
      iroha::Numeric num;
      iroha::Op::MakeConst0(array_initializer->num_[i], num.GetMutableArray());
      array->WriteSingle(i, num.type_, num.GetArray());
    }
  }
}

Object *Decl::CreateMemoryObject(const iroha::NumericWidth &width,
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

Object *Decl::CreateObjectArray(fe::ArrayShape *shape) {
  return ArrayWrapper::NewObjectArrayWrapper(thr_->GetVM(), shape->length[0]);
}

}  // namespace executor
}  // namespace vm

