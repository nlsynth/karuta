// -*- C++ -*-
#ifndef _synth_shared_resource_set_h_
#define _synth_shared_resource_set_h_

#include <map>
#include <set>
#include <tuple>

#include "synth/common.h"

using std::map;
using std::set;
using std::tuple;

namespace synth {

// This represents a shared resource and its accessors.
// SharedResource is key-ed by an Object or member name.
class SharedResource {
 public:
  SharedResource();
  ~SharedResource();

  void SetOwnerIResource(IResource *res);
  void AddAccessorResource(IResource *res, ThreadSynth *acc_thr);

  set<ThreadSynth *> readers_;
  set<ThreadSynth *> writers_;
  set<ThreadSynth *> axi_ctrl_thrs_;
  vector<ThreadSynth *> ordered_accessors_;
  set<ThreadSynth *> accessors_;
  ThreadSynth *owner_thr_;
  // Owner object of this (either object or sym) member.
  vm::Object *owner_obj_;
  map<IResource *, vm::Object *> accessor_resources_;
  // Actual resource for this instance.
  IResource *i_res_;
};

// Per DesignSynth object to manage every shared resources.
class SharedResourceSet {
 public:
  ~SharedResourceSet();

  // Called between pass 1 and 2.
  // Determines an owner thread (ThreadSynth).
  void DetermineOwnerThreadAll();
  // Called after pass 2. Sets the foreign resource for IResource.
  void ResolveResourceAccessors();
  void ResolveAccessorDistanceAll(DesignSynth *design_synth);

  // Declares @thr accesses this.name/obj.
  // NUM
  void AddMemberAccessor(ThreadSynth *thr, vm::Object *owner_obj, sym_t name,
                         vm::Insn *insn, bool is_tls);
  // OBJECT, INT_ARRAY, OBJECT_ARRAY
  void AddObjectAccessor(ThreadSynth *thr, vm::Object *owner_obj,
                         vm::Object *obj, vm::Insn *insn,
                         const string &synth_name, bool is_tls);
  // ExtIO is not shareable, so this keeps track of the accessor thread.
  bool AddExtIOMethodAccessor(ThreadSynth *thr, vm::Method *method);

  // ThreadSynth to specify thread local storage. nullptr is specified for
  // normal variables.
  SharedResource *GetBySlotName(vm::Object *obj, ThreadSynth *thr, sym_t name);
  SharedResource *GetByObj(vm::Object *obj, ThreadSynth *thr);
  bool HasAccessor(vm::Object *obj, ThreadSynth *thr);
  bool HasExtIOAccessor(vm::Method *method);

 private:
  void DetermineOwnerThread(SharedResource *res);
  void ResolveSharedResourceAccessor(SharedResource *sres);
  void ResolveAccessorDistance(DesignSynth *design_synth, SharedResource *sres);

  // ThreadSynth is nullptr for non TLS object for {obj,value}_resources_.
  map<tuple<vm::Object *, ThreadSynth *>, SharedResource *> obj_resources_;
  map<tuple<vm::Object *, ThreadSynth *, sym_t>, SharedResource *>
      value_resources_;
  map<vm::Method *, ThreadSynth *> ext_io_methods_;
};

}  // namespace synth

#endif  // _synth_shared_resource_set_h_
