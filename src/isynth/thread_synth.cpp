#include "isynth/thread_synth.h"

#include "isynth/method_expander.h"
#include "isynth/method_synth.h"
#include "iroha/i_design.h"
#include "isynth/resource_set.h"
#include "status.h"

namespace isynth {

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

bool ThreadSynth::Synth() {
  tab_ = new ITable(mod_);
  tab_->SetName(thread_name_);
  resource_.reset(new ResourceSet(tab_));
  RequestMethod(method_name_);
  int num_synth;
  do {
    num_synth = 0;
    for (auto it : methods_) {
      if (it.second != nullptr) {
	continue;
      }
      num_synth++;
      MethodSynth *m =
	new MethodSynth(this, it.first, tab_, resource_.get());
      if (!m->Synth()) {
	Status::os(Status::USER) << "Failed to synthesize thread: "
				 << thread_name_ << "." << method_name_;
	MessageFlush::Get(Status::USER);
	return false;
      }
      methods_[it.first] = m;
      break;
    }
  } while (num_synth > 0);

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
  if (methods_.find(m) != methods_.end()) {
    return;
  }
  methods_[m] = nullptr;
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

}  // namespace isynth
