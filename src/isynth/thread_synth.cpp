#include "isynth/thread_synth.h"

#include "isynth/method_expander.h"
#include "isynth/method_synth.h"
#include "iroha/i_design.h"
#include "isynth/resource_set.h"
#include "status.h"

namespace isynth {

ThreadSynth::ThreadSynth(ObjectSynth *obj_synth,
			 const char *method_name, IModule *mod)
  : obj_synth_(obj_synth), method_name_(method_name), mod_(mod), tab_(nullptr) {
}

ThreadSynth::~ThreadSynth() {
  STLDeleteSecondElements(&methods_);
}

bool ThreadSynth::Synth() {
  tab_ = new ITable(mod_);
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
				 << method_name_;
	MessageFlush::Get(Status::USER);
	return false;
      }
      methods_[it.first] = m;
    }
  } while (num_synth > 0);

  MethodSynth *root_method = methods_[method_name_];
  MethodExpander expander(root_method->GetContext(), this);
  expander.Expand();

  mod_->tables_.push_back(tab_);
  return true;
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

}  // namespace isynth
