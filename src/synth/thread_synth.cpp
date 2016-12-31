#include "synth/thread_synth.h"

#include "synth/method_expander.h"
#include "synth/method_scanner.h"
#include "synth/method_synth.h"
#include "iroha/i_design.h"
#include "synth/resource_set.h"
#include "synth/tool.h"
#include "status.h"

namespace synth {

ThreadSynth::ThreadSynth(ObjectSynth *obj_synth,
			 const string &thread_name,
			 const string &method_name, IModule *mod)
  : obj_synth_(obj_synth),
    thread_name_(thread_name), method_name_(method_name), mod_(mod),
    tab_(nullptr),
    is_task_(false),
    reg_name_index_(0) {
}

ThreadSynth::~ThreadSynth() {
  STLDeleteSecondElements(&methods_);
}

bool ThreadSynth::Scan() {
  tab_ = new ITable(mod_);
  tab_->SetName(thread_name_);
  resource_.reset(new ResourceSet(tab_));
  RequestMethod(method_name_);
  int num_scan;
  set<string> scanned;
  do {
    num_scan = 0;
    for (auto &n : method_names_) {
      if (scanned.find(n) != scanned.end()) {
	continue;
      }
      ++num_scan;
      MethodScanner ms(this, n);
      if (!ms.Scan()) {
	Status::os(Status::USER) << "Failed to scan thread: "
				 << thread_name_ << "." << method_name_;
	MessageFlush::Get(Status::USER);
	return false;
      }
      scanned.insert(n);
      break;
    }
  } while (num_scan > 0);

  return true;
}

bool ThreadSynth::Synth() {
  for (const string &s : method_names_) {
    methods_[s] = new MethodSynth(this, s, tab_, resource_.get());
  }
  for (auto it : methods_) {
    if (!it.second->Synth()) {
      Status::os(Status::USER) << "Failed to synthesize thread: "
			       << thread_name_ << "." << method_name_;
      MessageFlush::Get(Status::USER);
      return false;
    }
  }

  MethodSynth *root_method = methods_[method_name_];
  MethodExpander expander(root_method->GetContext(), this, &sub_obj_calls_);
  expander.Expand();
  if (is_task_) {
    root_method->InjectTaskEntry(tab_->GetInitialState());
  }

  mod_->tables_.push_back(tab_);
  return true;
}

void ThreadSynth::SetIsTask(bool is_task) {
  is_task_ = is_task;
}

void ThreadSynth::RequestMethod(const string &m) {
  method_names_.insert(m);
}

MethodContext *ThreadSynth::GetMethodContext(const string &m) {
  return methods_[m]->GetContext();
}

ResourceSet *ThreadSynth::GetResourceSet() {
  return resource_.get();
}

ObjectSynth *ThreadSynth::GetObjectSynth() {
  return obj_synth_;
}

ITable *ThreadSynth::GetITable() {
  return tab_;
}

void ThreadSynth::AddName(const string &n) {
  used_reg_names_.insert(n);
}

IRegister *ThreadSynth::AllocRegister(const string &prefix) {
  string n;
  do {
    char buf[10];
    sprintf(buf, "_%d", reg_name_index_);
    n = prefix + string(buf);
    ++reg_name_index_;
  } while (used_reg_names_.find(n) != used_reg_names_.end());
  used_reg_names_.insert(n);
  IRegister *reg = new IRegister(tab_, n);
  return reg;
}

vector<SubObjCall> &ThreadSynth::GetSubObjCalls() {
  return sub_obj_calls_;
}

const string &ThreadSynth::GetMethodName() {
  return method_name_;
}

void ThreadSynth::InjectSubModuleCall(IState *st, IInsn *insn,
				      ITable *callee_tab) {
  ITable *caller_tab = st->GetTable();
  IResource *call_res = Tool::FindOrCreateTaskCallResource(caller_tab,
							   callee_tab);
  IInsn *iinsn = new IInsn(call_res);
  st->insns_.push_back(iinsn);
}

}  // namespace synth
