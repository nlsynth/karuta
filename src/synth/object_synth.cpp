#include "synth/object_synth.h"

#include "dfg/dfg.h"
#include "synth/thread_synth.h"
#include "synth/resource_set.h"
#include "vm/thread_wrapper.h"

namespace synth {

// * 1 entry method:
// * 1 thread:
//     vm::Object ->
//       A toplevel DModule containing a DGraph(FSM).
// * Multiple entry methods or threads:
//     vm::Object ->
//       A toplevel DModule
//         Child DModule for each entry method
//         Child DModule for each thread
//           Topleve DModule for each member vm::Object.
//
// NOTE: This doesn't allow member vm::Object sharing between
// entry points/threads...

MemberObjectEntryMethod::MemberObjectEntryMethod(sym_t name)
  : method_name_(name), resource_(nullptr) {
}
  
MemberObject::MemberObject(vm::Object *vm_obj)
  : vm_obj_(vm_obj), dmodule_(nullptr), obj_synth_(nullptr) {
}

MemberObject::~MemberObject() {
  STLDeleteSecondElements(&entry_methods_);
  delete obj_synth_;
}

MemberObjectEntryMethod *MemberObject::GetMethod(sym_t name) {
  auto it = entry_methods_.find(name);
  if (it != entry_methods_.end()) {
    return it->second;
  }
  MemberObjectEntryMethod *m = new MemberObjectEntryMethod(name);
  entry_methods_[name] = m;
  return m;
}

ObjectSynth::ObjectSynth(vm::VM *vm, vm::Object *obj,
			 const char *object_name,
			 set<sym_t> entry_method_names,
			 DModule *parent_module)
  : vm_(vm), obj_(obj), parent_module_(parent_module),
    entry_method_names_(entry_method_names) {
  this_module_ = DModuleUtil::Create(parent_module_, object_name);
}

ObjectSynth::~ObjectSynth() {
  STLDeleteValues(&threads_);
  STLDeleteSecondElements(&member_objs_);
}

bool ObjectSynth::Synth() {
  CollectThreads();

  for (size_t i = 0; i < threads_.size(); ++i) {
    if (!threads_[i]->Synth()) {
      return false;
    }
  }

  SynthSubModules();
  return true;
}

void ObjectSynth::SynthSubModules() {
  for (size_t i = 0; i < threads_.size(); ++i) {
    ResourceSet *res = threads_[i]->GetResource();
    vector<SubModuleCallEntry> &calls = res->GetSubModuleCalls();
    for (SubModuleCallEntry &entry : calls) {
      MemberObject *mo = GetMemberObject(entry.obj);
      mo->member_name_.insert(entry.orig_obj_name);
      mo->dmodule_ = threads_[i]->GetModule();
      MemberObjectEntryMethod *moe = mo->GetMethod(entry.method_name);
      moe->resource_ = entry.resource;
    } 
  }

  for (auto it : member_objs_) {
    MemberObject *mo = it.second;
    sym_t obj_name = *(mo->member_name_.begin());
    set<sym_t> entry_methods;
    for (auto jt : mo->entry_methods_) {
      entry_methods.insert(jt.first);
    }
    mo->obj_synth_ =
	new ObjectSynth(vm_, mo->vm_obj_,
			sym_cstr(obj_name),
			entry_methods,
			this_module_);
    DModule *child_module = mo->obj_synth_->GetDModule();
    mo->obj_synth_->Synth();
    for (auto jt : mo->entry_methods_) {
      MemberObjectEntryMethod *moe = jt.second;
      moe->resource_->module_ = child_module;
      moe->resource_->name_ = child_module->module_name_;
    }
  }
}

MemberObject *ObjectSynth::GetMemberObject(vm::Object *obj) {
  auto it = member_objs_.find(obj);
  if (it != member_objs_.end()) {
    return it->second;
  }
  MemberObject *m = new MemberObject(obj);
  member_objs_[obj] = m;
  return m;
}

void ObjectSynth::CollectThreads() {
  vector<vm::ThreadWrapper::ThreadEntry> thread_entries;
  vm::ThreadWrapper::GetThreadMethods(obj_, &thread_entries);

  bool is_main = false;
  if (entry_method_names_.size() == 0 &&
      thread_entries.size() == 0) {
    entry_method_names_.insert(sym_lookup("main"));
    is_main = true;
  }

  // If there's only 1 thread or 1 entry, don't create a container.
  if (thread_entries.size() == 0 && entry_method_names_.size() == 1) {
    // main entry.
    if (is_main) {
      this_module_->module_type_ = DModule::MODULE_THREAD;
    } else {
      this_module_->module_type_ = DModule::MODULE_TASK;
    }
    threads_.push_back(new ThreadSynth(vm_, obj_, this_module_,
				       sym_cstr(*(entry_method_names_.begin()))));
  } else if (thread_entries.size() == 1 && entry_method_names_.size() == 0) {
    // main thread.
    this_module_->module_type_ = DModule::MODULE_THREAD;
    const vm::ThreadWrapper::ThreadEntry &entry = thread_entries[0];
    threads_.push_back(new ThreadSynth(vm_, obj_, this_module_,
				       entry.method_name.c_str()));
  } else {
    this_module_->module_type_ = DModule::MODULE_CONTAINER;
    // threads.
    for (size_t i = 0; i < thread_entries.size(); ++i) {
      const vm::ThreadWrapper::ThreadEntry &entry = thread_entries[i];
      const char *thread_name = entry.thread_name.c_str();
      DModule *child_module =
	DModuleUtil::Create(this_module_, thread_name);
      child_module->module_type_ = DModule::MODULE_THREAD;
      const char *method_name = entry.method_name.c_str();
      threads_.push_back(new ThreadSynth(vm_, obj_, child_module,
					 method_name));
    }
    // tasks.
    for (sym_t method_name : entry_method_names_) {
      DModule *child_module =
	DModuleUtil::Create(this_module_, sym_cstr(method_name));
      child_module->module_type_ = DModule::MODULE_TASK;
      threads_.push_back(new ThreadSynth(vm_, obj_, child_module,
					 sym_cstr(method_name)));
    }
  }
}

void ObjectSynth::ExpandFunctions() {
  for (size_t i = 0; i < threads_.size(); ++i) {
    threads_[i]->ExpandFunctions();
  }
  for (auto it : member_objs_) {
    MemberObject *mo = it.second;
    mo->obj_synth_->ExpandFunctions();
  }
}

DModule *ObjectSynth::GetDModule() {
  return this_module_;
}

}  // namespace synth
