// -*- C++ -*-
#ifndef _synth_shared_resource_set_h_
#define _synth_shared_resource_set_h_

#include "synth/common.h"

#include <set>
#include <map>

using std::map;
using std::set;

namespace synth {

class SharedResource {
public:
  SharedResource();
  ~SharedResource();

  set<ThreadSynth *> readers_;
  set<ThreadSynth *> writers_;
  vector<ThreadSynth *> ordered_accessors_;
  set<ThreadSynth *> accessors_;
  ThreadSynth *owner_;
};

class SharedResourceSet {
public:
  ~SharedResourceSet();

  void ResolveResourceTypes();

  // NUM
  void AddMemberAccessor(ThreadSynth *thr, sym_t name, vm::Insn *insn);
  // OBJECT, INT_ARRAY, OBJECT_ARRAY
  void AddObjectAccessor(ThreadSynth *thr, vm::Object *obj, vm::Insn *insn);

  SharedResource *GetBySlotName(vm::Object *obj, sym_t name);
  SharedResource *GetByObj(vm::Object *obj);

private:
  void ResolveSharedResource(SharedResource *res);

  map<vm::Object *, SharedResource *> obj_resources_;
  map<vm::Object *, map<sym_t, SharedResource *> > value_resources_;
};

}  // namespace synth

#endif  // _synth_shared_resource_set_h_
