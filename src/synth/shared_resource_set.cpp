#include "synth/shared_resource_set.h"

#include "iroha/i_design.h"
#include "synth/object_method_names.h"
#include "synth/object_synth.h"
#include "synth/thread_synth.h"
#include "vm/insn.h"

namespace synth {

SharedResource::SharedResource()
  : owner_thr_(nullptr), owner_res_(nullptr) {
}

SharedResource::~SharedResource() {
}

void SharedResource::AddOwnerResource(IResource *res) {
  owner_res_ = res;
}

void SharedResource::AddAccessorResource(IResource *res) {
  accessor_resources_.insert(res);
}

SharedResourceSet::~SharedResourceSet() {
  STLDeleteSecondElements(&obj_resources_);
  for (auto it : value_resources_) {
    auto &m = it.second;
    STLDeleteSecondElements(&m);
  }
}

void SharedResourceSet::DetermineOwnerThreadAll() {
  for (auto it : obj_resources_) {
    DetermineOwnerThread(it.second);
  }
  for (auto it : value_resources_) {
    for (auto jt : it.second) {
      DetermineOwnerThread(jt.second);
    }
  }
}

void SharedResourceSet::ResolveResourceAccessors() {
  for (auto it : obj_resources_) {
    ResolveSharedResourceAccessor(it.second);
  }
  for (auto it : value_resources_) {
    for (auto jt : it.second) {
      ResolveSharedResourceAccessor(jt.second);
    }
  }
}

void SharedResourceSet::DetermineOwnerThread(SharedResource *res) {
  CHECK(res->axi_ctrl_thrs_.size() <= 1);
  if (res->axi_ctrl_thrs_.size() == 1) {
    res->owner_thr_ = *(res->axi_ctrl_thrs_.begin());
  }
  for (ThreadSynth *thr : res->ordered_accessors_) {
    if (res->owner_thr_ == nullptr) {
      // Picks up first one.
      res->owner_thr_ = thr;
    }
  }
}

void SharedResourceSet::ResolveSharedResourceAccessor(SharedResource *sres) {
  for (IResource *res : sres->accessor_resources_) {
    res->SetParentResource(sres->owner_res_);
  }
}

void SharedResourceSet::AddMemberAccessor(ThreadSynth *thr, sym_t name,
					  vm::Insn *insn) {
  SharedResource *res = GetBySlotName(thr->GetObjectSynth()->GetObject(),
				      name);
  res->ordered_accessors_.push_back(thr);
  res->accessors_.insert(thr);
  if (insn->op_ == vm::OP_MEMBER_READ) {
    res->readers_.insert(thr);
  }
  if (insn->op_ == vm::OP_MEMBER_WRITE) {
    res->writers_.insert(thr);
  }
}

void SharedResourceSet::AddObjectAccessor(ThreadSynth *thr, vm::Object *obj,
					  vm::Insn *insn,
					  const string &synth_name) {
  SharedResource *res = GetByObj(obj);
  res->ordered_accessors_.push_back(thr);
  res->accessors_.insert(thr);
  if (insn->op_ == vm::OP_ARRAY_READ) {
    res->readers_.insert(thr);
  }
  if (insn->op_ == vm::OP_ARRAY_WRITE) {
    res->writers_.insert(thr);
  }
  if (insn->op_ == vm::OP_FUNCALL) {
    if (synth_name == kLoad || synth_name == kStore) {
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
						 sym_t name) {
  auto it = value_resources_.find(obj);
  if (it != value_resources_.end()) {
    auto &m = it->second;
    auto jt = m.find(name);
    if (jt != m.end()) {
      return jt->second;
    }
    SharedResource *res = new SharedResource();
    m[name] = res;
    return res;
  }
  SharedResource *res = new SharedResource();
  map<sym_t, SharedResource *> m;
  m[name] = res;
  value_resources_[obj] = m;
  return res;
}

SharedResource *SharedResourceSet::GetByObj(vm::Object *obj) {
  auto it = obj_resources_.find(obj);
  if (it != obj_resources_.end()) {
    return it->second;
  }
  SharedResource *res = new SharedResource();
  obj_resources_[obj] = res;
  return res;
}

bool SharedResourceSet::HasAccessor(vm::Object *obj) {
  return (obj_resources_.find(obj) != obj_resources_.end());
}

bool SharedResourceSet::HasExtIOAccessor(vm::Method *method) {
  auto it = ext_io_methods_.find(method);
  if (it == ext_io_methods_.end()) {
    return false;
  }
  return true;
}

}  // namespace synth
