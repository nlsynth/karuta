#include "synth/thread_synth.h"

#include "base/status.h"
#include "compiler/compiler.h"
#include "iroha/iroha.h"
#include "karuta/annotation.h"
#include "synth/design_synth.h"
#include "synth/method_expander.h"
#include "synth/method_scanner.h"
#include "synth/method_synth.h"
#include "synth/object_attr_names.h"
#include "synth/object_synth.h"
#include "synth/resource_set.h"
#include "synth/resource_synth.h"
#include "synth/shared_resource_set.h"
#include "synth/tool.h"
#include "vm/array_wrapper.h"
#include "vm/io_wrapper.h"
#include "vm/mailbox_wrapper.h"
#include "vm/vm_method.h"
#include "vm/object.h"
#include "vm/object_util.h"

namespace synth {

ThreadSynth::ThreadSynth(ObjectSynth *obj_synth, const string &thread_name,
                         const string &entry_method_name,
                         vm::Object *thread_obj, int index)
    : obj_synth_(obj_synth),
      thread_name_(thread_name),
      entry_method_name_(entry_method_name),
      is_primary_thread_(false),
      thread_obj_(thread_obj),
      index_(index),
      tab_(nullptr),
      is_task_(false),
      reg_name_index_(0) {}

ThreadSynth::~ThreadSynth() {
  for (auto &per_obj : obj_methods_) {
    for (auto &m : per_obj.second.methods_) {
      delete m.second;
    }
  }
}

bool ThreadSynth::HasExtVisibleResource(vm::Object *obj) {
  map<sym_t, vm::Object *> member_objs;
  obj->GetAllMemberObjs(&member_objs);
  for (auto it : member_objs) {
    vm::Object *member_obj = it.second;
    if (obj == member_obj) {
      continue;
    }
    if (vm::ArrayWrapper::IsIntArray(member_obj)) {
      Annotation *a = vm::ArrayWrapper::GetAnnotation(member_obj);
      if (a != nullptr &&
          (a->IsAxiMaster() || a->IsAxiSlave() || a->IsExportSramIf())) {
        return true;
      }
    }
  }
  map<sym_t, vm::Method *> member_methods;
  obj->GetAllMemberMethods(&member_methods);
  for (auto it : member_methods) {
    vm::Method *method = it.second;
    if (method->GetAnnotation()->IsExtIO()) {
      return true;
    }
  }
  return false;
}

bool ThreadSynth::Scan() {
  tab_ = new ITable(obj_synth_->GetIModule());
  tab_->SetName(thread_name_);
  resource_.reset(new ResourceSet(tab_));
  rsynth_.reset(new ResourceSynth(resource_.get(), this));
  // Entry method of this thread.
  RequestMethod(obj_synth_->GetObject(), entry_method_name_);
  int num_scan;
  map<vm::Object *, set<string>> scanned;
  do {
    num_scan = 0;
    // Every object in this thread.
    for (auto &it : obj_methods_) {
      vm::Object *obj = it.first;
      map<string, MethodSynth *> &methods = it.second.methods_;
      for (auto jt : methods) {
        auto &name = jt.first;
        auto &m = scanned[obj];
        if (m.find(name) != m.end()) {
          continue;
        }
        ++num_scan;
        MethodScanner ms(this, obj, name);
        if (!ms.Scan()) {
          Status::os(Status::USER_ERROR)
              << "Failed to scan thread: " << thread_name_ << "."
              << entry_method_name_;
          MessageFlush::Get(Status::USER_ERROR);
          return false;
        }
        scanned[obj].insert(name);
      }
    }
  } while (num_scan > 0);

  return true;
}

bool ThreadSynth::Synth() {
  // Prepares MethodSynth objects for all methods.
  for (auto &it : obj_methods_) {
    vm::Object *obj = it.first;
    for (auto jt : it.second.methods_) {
      auto &name = jt.first;
      auto *ms = new MethodSynth(this, obj, name, tab_, rsynth_.get(),
                                 resource_.get());
      obj_methods_[obj].methods_[name] = ms;
    }
  }
  MethodSynth *root_method =
      obj_methods_[obj_synth_->GetObject()].methods_[entry_method_name_];
  root_method->SetRoot(index_);
  if (is_task_) {
    root_method->SetTaskEntry();
  }
  // Actually synthesize all.
  for (auto &it : obj_methods_) {
    for (auto jt : it.second.methods_) {
      if (!jt.second->Synth()) {
        Status::os(Status::USER_ERROR)
            << "Failed to synthesize thread: " << thread_name_ << "."
            << entry_method_name_;
        MessageFlush::Get(Status::USER_ERROR);
        return false;
      }
    }
  }

  MethodExpander expander(root_method->GetContext(), this, &table_calls_);
  expander.Expand();

  obj_synth_->GetIModule()->tables_.push_back(tab_);
  return true;
}

void ThreadSynth::SetPrimary() { is_primary_thread_ = true; }

bool ThreadSynth::IsPrimary() { return is_primary_thread_; }

void ThreadSynth::CollectUnclaimedMembers() {
  CollectUnclaimedMemberObjects();
  CollectUnclaimedMemberMethods();
}

void ThreadSynth::CollectUnclaimedMemberObjects() {
  DesignSynth *ds = obj_synth_->GetDesignSynth();
  SharedResourceSet *sres = ds->GetSharedResourceSet();
  vm::Object *obj = obj_synth_->GetObject();
  map<sym_t, vm::Object *> member_objs;
  obj->GetAllMemberObjs(&member_objs);
  for (auto it : member_objs) {
    vm::Object *member_obj = it.second;
    if (member_obj == obj) {
      continue;
    }
    if (vm::ArrayWrapper::IsIntArray(member_obj)) {
      if (sres->HasAccessor(member_obj, nullptr)) {
        continue;
      }
      rsynth_->MayAddAxiMasterPort(obj, member_obj);
      rsynth_->MayAddAxiSlavePort(obj, member_obj);
      rsynth_->MayAddSramIfPort(obj, member_obj);
      rsynth_->MayAddExternalSram(member_obj);
    }
    if (vm::MailboxWrapper::IsMailbox(member_obj)) {
      if (sres->HasAccessor(member_obj, nullptr)) {
        continue;
      }
      rsynth_->MayAddSharedRegExtWriter(member_obj);
    }
    if (vm::IOWrapper::IsIO(member_obj)) {
      if (sres->HasAccessor(member_obj, nullptr)) {
        continue;
      }
      rsynth_->MayAddIO(member_obj, true);
    }
    // Named Memory member should be kept.
    string n = vm::ObjectUtil::GetStringMember(member_obj, kSramName);
    if (!n.empty()) {
      resource_->GetExternalArrayResource(member_obj);
    }
  }
}

void ThreadSynth::CollectUnclaimedMemberMethods() {
  vm::Object *obj = obj_synth_->GetObject();
  map<sym_t, vm::Method *> member_methods;
  obj->GetAllMemberMethods(&member_methods);
  for (auto it : member_methods) {
    vm::Method *method = it.second;
    auto *an = method->GetAnnotation();
    if (an->IsExtIO()) {
      compiler::Compiler::CompileMethod(obj_synth_->GetVM(), obj, method);
      if (method->IsCompileFailure()) {
        continue;
      }
      if (an->IsExtInput()) {
        MayGenerateExtIOMethod(method, /* !output */ false);
      }
      if (an->IsExtOutput()) {
        MayGenerateExtIOMethod(method, /* output */ true);
      }
    }
    if (an->IsExtMethodStub()) {
      string name(sym_str(it.first));
      if (!obj_synth_->IsUsedStub(name)) {
        AddExtStubResource(name);
      }
    }
  }
}

void ThreadSynth::MayGenerateExtIOMethod(vm::Method *method, bool is_output) {
  DesignSynth *ds = obj_synth_->GetDesignSynth();
  SharedResourceSet *sres = ds->GetSharedResourceSet();
  if (sres->HasExtIOAccessor(method)) {
    return;
  }
  rsynth_->MayAddExtIO(method, is_output);
}

void ThreadSynth::SetIsTask(bool is_task) { is_task_ = is_task; }

void ThreadSynth::RequestMethod(vm::Object *obj, const string &m) {
  obj_methods_[obj].methods_[m] = nullptr;
}

MethodContext *ThreadSynth::GetMethodContext(vm::Object *obj, const string &m) {
  return obj_methods_[obj].methods_[m]->GetContext();
}

ResourceSet *ThreadSynth::GetResourceSet() { return resource_.get(); }

ObjectSynth *ThreadSynth::GetObjectSynth() { return obj_synth_; }

ITable *ThreadSynth::GetITable() { return tab_; }

vm::Object *ThreadSynth::GetThreadObject() { return thread_obj_; }

void ThreadSynth::AddName(const string &n) { used_reg_names_.insert(n); }

IRegister *ThreadSynth::AllocRegister(const string &prefix) {
  string n;
  do {
    char buf[10];
    sprintf(buf, "_%d", reg_name_index_);
    n = prefix + string(buf);
    ++reg_name_index_;
  } while (used_reg_names_.find(n) != used_reg_names_.end());
  used_reg_names_.insert(n);
  return new IRegister(tab_, n);
}

vector<TableCall> &ThreadSynth::GetTableCalls() { return table_calls_; }

const string &ThreadSynth::GetEntryMethodName() { return entry_method_name_; }

int ThreadSynth::GetIndex() const { return index_; }

IInsn *ThreadSynth::InjectSubModuleCall(IState *st, IInsn *pseudo_call_insn,
                                        ITable *callee_tab) {
  ITable *caller_tab = st->GetTable();
  IResource *call_res =
      Tool::FindOrCreateTaskCallResource(caller_tab, callee_tab);
  if (call_res == nullptr) {
    return nullptr;
  }
  // Argument values.
  IInsn *iinsn = new IInsn(call_res);
  st->insns_.push_back(iinsn);
  for (IRegister *reg : pseudo_call_insn->inputs_) {
    iinsn->inputs_.push_back(reg);
  }
  // Return values.
  if (pseudo_call_insn->outputs_.size() == 0) {
    return iinsn;
  }
  // State allocated for funcall_done to inject return.
  IState *next_st = Tool::GetNextState(st);
  CHECK(next_st);
  IResource *ret =
      Tool::FindOrCreateTaskReturnValueResource(caller_tab, callee_tab);
  if (ret == nullptr) {
    // TODO: This shouldn't happen. Put CHECK(false) here.
    // outputs_.size() == 1 in case of void return due to the default
    // return reg.
    return iinsn;
  }
  IInsn *ret_insn = new IInsn(ret);
  ret_insn->depending_insns_.push_back(iinsn);
  ret_insn->SetOperand(iroha::operand::kGetMailbox);
  next_st->insns_.push_back(ret_insn);
  for (IRegister *reg : pseudo_call_insn->outputs_) {
    ret_insn->outputs_.push_back(reg);
  }
  return ret_insn;
}

IInsn *ThreadSynth::InjectDataFlowCall(ThreadSynth *thr, IState *st,
                                       IInsn *pseudo_call_insn,
                                       ITable *callee_tab, bool no_wait) {
  vector<IResource *> df;
  DesignUtil::FindResourceByClassName(callee_tab, resource::kDataFlowIn, &df);
  CHECK(df.size() == 1);
  IResource *sreg = df[0]->GetParentResource();
  ITable *caller_tab = st->GetTable();
  IResource *w = Tool::FindOrCreateDataFlowCaller(caller_tab, sreg);
  IInsn *iinsn = new IInsn(w);
  st->insns_.push_back(iinsn);
  for (IRegister *reg : pseudo_call_insn->inputs_) {
    iinsn->inputs_.push_back(reg);
  }
  if (pseudo_call_insn->inputs_.size() == 0) {
    // Adds a dummy argument.
    IRegister *reg = thr->AllocRegister("df_arg");
    reg->value_type_.SetWidth(1);
    iroha::Numeric iv;
    iv.SetValue0(0);
    reg->SetInitialValue(iv);
    iinsn->inputs_.push_back(reg);
    thr->GetITable()->registers_.push_back(reg);
  }
  if (no_wait) {
    iinsn->SetOperand(iroha::operand::kNoWait);
  }
  return iinsn;
}

IInsn *ThreadSynth::InjectExtStubCall(IState *st, IInsn *pseudo_call_insn,
                                      const string &name, bool is_flow) {
  // ext-task-call or ext-flow-call
  ITable *caller_tab = st->GetTable();
  IResource *call =
      Tool::FindOrCreateExtStubCallResource(caller_tab, name, is_flow);
  IInsn *insn = new IInsn(call);
  st->insns_.push_back(insn);
  bool need_width =
      pseudo_call_insn->inputs_.size() > call->input_types_.size();
  for (IRegister *reg : pseudo_call_insn->inputs_) {
    insn->inputs_.push_back(reg);
    if (need_width) {
      call->input_types_.push_back(reg->value_type_);
    }
  }
  // ext-task-wait or ext-flow-result.
  IState *next_st = Tool::GetNextState(st);
  IResource *wait =
      Tool::FindOrCreateExtStubWaitResource(caller_tab, name, is_flow);
  IInsn *wait_insn = new IInsn(wait);
  wait_insn->depending_insns_.push_back(insn);
  next_st->insns_.push_back(wait_insn);
  need_width = pseudo_call_insn->outputs_.size() > wait->output_types_.size();
  for (IRegister *reg : pseudo_call_insn->outputs_) {
    wait_insn->outputs_.push_back(reg);
    if (need_width) {
      wait->output_types_.push_back(reg->value_type_);
    }
  }
  return wait_insn;
}

void ThreadSynth::AddExtStubResource(const string &name) {
  (void)Tool::FindOrCreateExtStubCallResource(tab_, name, false);
  (void)Tool::FindOrCreateExtStubWaitResource(tab_, name, false);
}

}  // namespace synth
