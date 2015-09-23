// -*- C++ -*-
#ifndef _synth_object_synth_h_
#define _synth_object_synth_h_

#include "nli.h"

#include <map>
#include <set>

using std::map;
using std::set;

namespace dfg {
class DModule;
class DResource;
}  // namespace dfg
using namespace dfg;

namespace vm {
class Object;
class VM;
}  // namespace vm

namespace synth {

class ObjectSynth;
class ThreadSynth;

struct MemberObjectEntryMethod {
  MemberObjectEntryMethod(sym_t name);

  sym_t method_name_;
  DResource *resource_;
};

struct MemberObject {
  MemberObject(vm::Object *vm_obj);
  ~MemberObject();
  MemberObjectEntryMethod *GetMethod(sym_t name);

  vm::Object *vm_obj_;
  DModule *dmodule_;
  ObjectSynth *obj_synth_;
  // Same vm::Objecct can have multiple names.
  set<sym_t> member_name_;

  map<sym_t, MemberObjectEntryMethod *> entry_methods_;
};

class ObjectSynth {
public:
  ObjectSynth(vm::VM *vm, vm::Object *obj,
	      const char *object_name,
	      set<sym_t> entry_method_names,
	      DModule *parent_module);
  virtual ~ObjectSynth();

  bool Synth();
  void ExpandFunctions();

  DModule *GetDModule();

private:
  void CollectThreads();
  void SynthSubModules();
  MemberObject *GetMemberObject(vm::Object *obj);

  vector<ThreadSynth *> threads_;
  map<vm::Object *, MemberObject *> member_objs_;

  vm::VM *vm_;
  vm::Object *obj_;
  DModule *parent_module_;
  set<sym_t> entry_method_names_;
  DModule *this_module_;
};

}  // namespace synth

#endif  // _synth_object_synth_h_
