#include "vm/native_methods.h"

#include <stdlib.h>

#include "base/pool.h"
#include "base/status.h"
#include "iroha/numeric.h"
#include "karuta/annotation.h"
#include "karuta/annotation_builder.h"
#include "synth/synth.h"
#include "synth/object_attr_names.h"
#include "synth/object_method_names.h"
#include "vm/method.h"
#include "vm/object.h"
#include "vm/object_util.h"
#include "vm/profile.h"
#include "vm/string_wrapper.h"
#include "vm/thread.h"
#include "vm/thread_wrapper.h"
#include "vm/value.h"
#include "vm/vm.h"

namespace vm {

void NativeMethods::Assert(Thread *thr, Object *obj,
			   const vector<Value> &args) {
  CHECK(args.size() == 1) << "Assert got " << args.size() << "args.";
  const Value &arg = args[0];
  VM *vm = thr->GetVM();
  CHECK(arg.type_ == Value::ENUM_ITEM) << "Assert argument is not an enum item";
  CHECK(arg.enum_val_.enum_type == vm->bool_type_);
  if (arg.enum_val_.val == 0) {
    cout << "ASSERTION FAILURE\n";
  }
}

void NativeMethods::Clone(Thread *thr, Object *obj,
			  const vector<Value> &args) {
  Value value;
  value.type_ = Value::OBJECT;
  value.object_ = obj->Clone();
  SetReturnValue(thr, value);
}

void NativeMethods::Dump(Thread *thr, Object *obj,
			 const vector<Value> &args) {
  obj->Dump();
}

void NativeMethods::Exit(Thread *thr, Object *obj,
			 const vector<Value> &args) {
  thr->Exit();
}

void NativeMethods::GetTickCount(Thread *thr, Object *obj,
				 const vector<Value> &args) {
  Value value;
  value.type_ = Value::NUM;
  iroha::Op::MakeConst0(thr->GetVM()->GetTickCount(), &value.num_);
  SetReturnValue(thr, value);
}

void NativeMethods::Main(Thread *thr, Object *obj,
			 const vector<Value> &args) {
  // do nothing.
}

void NativeMethods::New(Thread *thr, Object *obj,
			const vector<Value> &args) {
  // Saved in default-isynth.karuta
  Value *v = thr->GetVM()->kernel_object_
    ->LookupValue(sym_lookup("Kernel_"), true);
  Value value;
  value.type_ = Value::OBJECT;
  value.object_ = v->object_->Clone();
  SetReturnValue(thr, value);
}

void NativeMethods::Print(Thread *thr, Object *obj,
			  const vector<Value> &args) {
  cout << "print: ";
  for (size_t i = 0; i < args.size(); ++i) {
    args[i].Dump(cout);
    cout << "\n";
  }
}


void NativeMethods::Run(Thread *thr, Object *obj,
			const vector<Value> &args) {
  ThreadWrapper::Run(thr->GetVM(), obj);
}

void NativeMethods::SetDump(Thread *thr, Object *obj,
			    const vector<Value> &args) {
  SetMemberString(thr, synth::kDumpFileName, obj, args);
}

void NativeMethods::SetIROutput(Thread *thr, Object *obj,
				const vector<Value> &args) {
  SetMemberString(thr, synth::kIrFileName, obj, args);
}

void NativeMethods::SetIrohaPath(Thread *thr, Object *obj,
				 const vector<Value> &args) {
  if (Env::IsSandboxMode()) {
    Status::os(Status::USER_ERROR)
      << "SetIrohaPath() is not allowed on sandbox mode";
    thr->UserError();
    return;
  }
  SetMemberString(thr, synth::kIrohaPath, obj, args);
}

void NativeMethods::RunIroha(Thread *thr, Object *obj,
			     const vector<Value> &args) {
  if (Env::IsSandboxMode()) {
    Status::os(Status::USER_ERROR)
      << "RunIroha() is not allowed on sandbox mode";
    thr->UserError();
    return;
  }
  if (args.size() != 1 || args[0].type_ != Value::OBJECT ||
      !StringWrapper::IsString(args[0].object_)) {
    Status::os(Status::USER_ERROR) << "Missing argument for runIroha()";
    thr->UserError();
    return;
  }
  int res =
    synth::Synth::RunIroha(obj, StringWrapper::String(args[0].object_));
  if (res != 0) {
    Status::os(Status::USER_ERROR) << "runIroha() failed: " << res;
    thr->UserError();
  }
}

void NativeMethods::Synth(Thread *thr, Object *obj,
			   const vector<Value> &args) {
  if (args.size() != 1 || args[0].type_ != Value::OBJECT ||
      !StringWrapper::IsString(args[0].object_)) {
  }
  synth::Synth::Synthesize(thr->GetVM(), obj,
			   StringWrapper::String(args[0].object_));
}

void NativeMethods::SetMemberString(Thread *thr, const char *name,
				    Object *obj,
				    const vector<Value> &args) {
  if (args.size() == 1 && args[0].type_ == Value::OBJECT &&
      StringWrapper::IsString(args[0].object_)) {
    const string &str = StringWrapper::String(args[0].object_);
    ObjectUtil::SetStringMember(obj, name, str);
  }
}

void NativeMethods::Compile(Thread *thr, Object *obj,
			    const vector<Value> &args) {
  string phase;
  if (args.size() == 1) {
    CHECK(StringWrapper::IsString(args[0].object_));
    phase = StringWrapper::String(args[0].object_);
  }
  if (phase.empty()) {
    bool ok = synth::Synth::Synthesize(thr->GetVM(), obj,
				       synth::Synth::IrPath(obj));
    if (!ok) {
      Status::os(Status::USER_ERROR) << "Failed to synthesize the design.";
      thr->UserError();
    }
  } else {
    int res = synth::Synth::RunIrohaOpt(phase, obj);
    if (res > 0) {
      Status::os(Status::USER_ERROR) << "compile(" << phase << ") failed.";
      thr->UserError();
    }
  }
}

void NativeMethods::SetSynthParam(Thread *thr, Object *obj,
				  const vector<Value> &args) {
  if (args.size() != 2 ||
      (args[0].type_ != Value::OBJECT ||
       !StringWrapper::IsString(args[0].object_))) {
    Status::os(Status::USER_ERROR)
      << "setSynthParam() requires 2 arguments and 1st argument should be a string.";
    thr->UserError();
    return;
  }
  if ((args[1].type_ != Value::OBJECT ||
       !StringWrapper::IsString(args[1].object_)) &&
      args[1].type_ != Value::NUM) {
    Status::os(Status::USER_ERROR) << "setSynthParam() requires a string or integer value.";
    thr->UserError();
    return;
  }
  sym_t synth_params = sym_lookup(synth::kSynthParams);
  Value *value = obj->LookupValue(synth_params, true);
  if (value->type_ == Value::NONE) {
    value->type_ = Value::ANNOTATION;
    value->annotation_ = AnnotationBuilder::Build(synth_params, nullptr);
  }
  string key = StringWrapper::String(args[0].object_);
  if (args[1].type_ == Value::NUM) {
    value->annotation_->AddIntParam(key, args[1].num_.GetValue0());
  } else {
    value->annotation_->AddStrParam(key,
				    StringWrapper::String(args[1].object_));
  }
}

void NativeMethods::WidthOf(Thread *thr, Object *obj,
			    const vector<Value> &args) {
  if (args.size() != 1 || args[0].type_ != Value::NUM) {
    Status::os(Status::USER_ERROR) << "Invalid argument to widthof()";
    MessageFlush::Get(Status::USER_ERROR);
    thr->UserError();
    return;
  }
  Value value;
  value.type_ = Value::NUM;
  iroha::Op::MakeConst0(args[0].num_type_.GetWidth(),
			&value.num_);
  SetReturnValue(thr, value);
}

void NativeMethods::Wait(Thread *thr, Object *obj,
			 const vector<Value> &args) {
}

void NativeMethods::WriteHdl(Thread *thr, Object *obj,
			     const vector<Value> &args) {
  CHECK(args.size() == 1);
  const Value& arg = args[0];
  CHECK(StringWrapper::IsString(arg.object_));
  synth::Synth::WriteHdl(StringWrapper::String(arg.object_), obj);
}

void NativeMethods::Yield(Thread *thr, Object *obj,
			  const vector<Value> &args) {
  thr->Yield();
}

void NativeMethods::IsMain(Thread *thr, Object *obj,
			   const vector<Value> &args) {
  Value value;
  value.type_ = Value::ENUM_ITEM;
  value.enum_val_.enum_type = thr->GetVM()->bool_type_;
  value.enum_val_.val = thr->IsRootThread() ? 1 : 0;
  SetReturnValue(thr, value);
}

void NativeMethods::GC(Thread *thr, Object *obj,
		       const vector<Value> &args) {
  thr->GetVM()->GC();
}

void NativeMethods::ClearProfile(Thread *thr, Object *obj,
				 const vector<Value> &args) {
  thr->GetVM()->GetProfile()->Clear();
}

void NativeMethods::EnableProfile(Thread *thr, Object *obj,
				  const vector<Value> &args) {
  thr->GetVM()->GetProfile()->SetEnable(true);
}

void NativeMethods::DisableProfile(Thread *thr, Object *obj,
				   const vector<Value> &args) {
  thr->GetVM()->GetProfile()->SetEnable(false);
}

void NativeMethods::GetTicker(Thread *thr, Object *obj,
			      const vector<Value> &args) {
  Value value;
  value.type_ = Value::OBJECT;
  // WIP.
  value.object_ = obj->Clone();
  SetReturnValue(thr, value);
}

void NativeMethods::SetReturnValue(Thread *thr, const Value &value) {
  thr->SetReturnValueFromNativeMethod(value);
}

}  // namespace vm
