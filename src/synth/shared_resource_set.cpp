#include "synth/shared_resource_set.h"

#include "base/stl_util.h"
#include "base/status.h"
#include "iroha/iroha.h"
#include "synth/design_synth.h"
#include "synth/object_method_names.h"
#include "synth/object_synth.h"
#include "synth/thread_synth.h"
#include "vm/insn.h"

namespace synth {

SharedResource::SharedResource()
  : owner_thr_(nullptr), owner_obj_(nullptr), i_res_(nullptr) {
}

SharedResource::~SharedResource() {
}

void SharedResource::SetOwnerIResource(IResource *res) {
  i_res_ = res;
}

void SharedResource::AddAccessorResource(IResource *res, ThreadSynth *acc_thr) {
  vm::Object *object = acc_thr->GetObjectSynth()->GetObject();
  accessor_resources_[res] = object;
}

SharedResourceSet::~SharedResourceSet() {
  STLDeleteSecondElements(&obj_resources_);
  STLDeleteSecondElements(&value_resources_);
}

void SharedResourceSet::DetermineOwnerThreadAll() {
  for (auto it : obj_resources_) {
    DetermineOwnerThread(it.second);
  }
  for (auto it : value_resources_) {
    DetermineOwnerThread(it.second);
  }
}

void SharedResourceSet::ResolveResourceAccessors() {
  for (auto it : obj_resources_) {
    ResolveSharedResourceAccessor(it.second);
  }
  for (auto it : value_resources_) {
    ResolveSharedResourceAccessor(it.second);
  }
}

void SharedResourceSet::ResolveAccessorDistanceAll(DesignSynth *design_synth) {
  for (auto it : obj_resources_) {
    ResolveAccessorDistance(design_synth, it.second);
  }
  for (auto it : value_resources_) {
    ResolveAccessorDistance(design_synth, it.second);
  }
}

void SharedResourceSet::ResolveAccessorDistance(DesignSynth *design_synth,
						SharedResource *sres) {
  for (auto it : sres->accessor_resources_) {
    IResource *res = it.first;
    int d = 0;
    d = design_synth->GetObjectDistance(it.second, sres->owner_obj_);
    if (d > 0) {
      res->GetParams()->SetDistance(d);
    }
  }
}

void SharedResourceSet::DetermineOwnerThread(SharedResource *res) {
  if (res->axi_ctrl_thrs_.size() > 1) {
    Status::os(Status::USER_ERROR)
      << "AXI memory can't have multiple accessor threads";
    return;
  }
  if (res->axi_ctrl_thrs_.size() == 1) {
    res->owner_thr_ = *(res->axi_ctrl_thrs_.begin());
    return;
  }
  // Prefers threads belong to the same object of the resource.
  ThreadSynth *first_thr = nullptr;
  ThreadSynth *first_same_owner_thr = nullptr;
  for (ThreadSynth *thr : res->ordered_accessors_) {
    if (first_thr == nullptr) {
      first_thr = thr;
    }
    if (first_same_owner_thr == nullptr &&
	thr->GetObjectSynth()->GetObject() == res->owner_obj_) {
      first_same_owner_thr = thr;
    }
  }
  if (first_same_owner_thr != nullptr) {
    res->owner_thr_ = first_same_owner_thr;
  } else {
    res->owner_thr_ = first_thr;
  }
}

void SharedResourceSet::ResolveSharedResourceAccessor(SharedResource *sres) {
  for (auto it : sres->accessor_resources_) {
    IResource *res = it.first;
    res->SetParentResource(sres->i_res_);
  }
}

void SharedResourceSet::AddMemberAccessor(ThreadSynth *thr,
					  vm::Object *owner_obj, sym_t name,
					  vm::Insn *insn, bool is_tls) {
  ThreadSynth *tls_thr = nullptr;
  if (is_tls) {
    tls_thr = thr;
  }
  SharedResource *res = GetBySlotName(owner_obj, tls_thr, name);
  res->owner_obj_ = owner_obj;
  res->ordered_accessors_.push_back(thr);
  res->accessors_.insert(thr);
  if (insn->op_ == vm::OP_MEMBER_READ) {
    res->readers_.insert(thr);
  }
  if (insn->op_ == vm::OP_MEMBER_WRITE) {
    res->writers_.insert(thr);
  }
}

void SharedResourceSet::AddObjectAccessor(ThreadSynth *thr,
					  vm::Object *owner_obj,
					  vm::Object *obj,
					  vm::Insn *insn,
					  const string &synth_name,
					  bool is_tls) {
  ThreadSynth *tls_thr = nullptr;
  if (is_tls) {
    tls_thr = thr;
  }
  SharedResource *res = GetByObj(obj, tls_thr);
  res->owner_obj_ = owner_obj;
  res->ordered_accessors_.push_back(thr);
  res->accessors_.insert(thr);
  if (insn->op_ == vm::OP_ARRAY_READ) {
    res->readers_.insert(thr);
  }
  if (insn->op_ == vm::OP_ARRAY_WRITE) {
    res->writers_.insert(thr);
  }
  if (insn->op_ == vm::OP_FUNCALL) {
    if (synth_name == kAxiLoad || synth_name == kAxiStore) {
      res->axi_ctrl_thrs_.insert(thr);
    }
    if (synth_name == kMailboxGet || synth_name == kMailboxPut) {
    }
  }
}

bool SharedResourceSet::AddExtIOMethodAccessor(ThreadSynth *thr,
					       vm::Method *method) {
  auto it = ext_io_methods_.find(method);
  if (it == ext_io_methods_.end()) {
    ext_io_methods_[method] = thr;
    return true;
  } else {
    if (it->second != thr) {
      // Claimed by other thread.
      return false;
    }
  }
  return true;
}

SharedResource *SharedResourceSet::GetBySlotName(vm::Object *obj,
						 ThreadSynth *thr,
						 sym_t name) {
  auto key = std::make_tuple(obj, thr, name);
  auto it = value_resources_.find(key);
  if (it != value_resources_.end()) {
    return it->second;
  }
  SharedResource *res = new SharedResource();
  value_resources_[key] = res;
  return res;
}

SharedResource *SharedResourceSet::GetByObj(vm::Object *obj,
					    ThreadSynth *thr) {
  auto key = std::make_tuple(obj, thr);
  auto it = obj_resources_.find(key);
  if (it != obj_resources_.end()) {
    return it->second;
  }
  SharedResource *res = new SharedResource();
  obj_resources_[key] = res;
  return res;
}

bool SharedResourceSet::HasAccessor(vm::Object *obj, ThreadSynth *thr) {
  auto key = std::make_tuple(obj, thr);
  return (obj_resources_.find(key) != obj_resources_.end());
}

bool SharedResourceSet::HasExtIOAccessor(vm::Method *method) {
  auto it = ext_io_methods_.find(method);
  if (it == ext_io_methods_.end()) {
    return false;
  }
  return true;
}

}  // namespace synth
