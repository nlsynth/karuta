// -*- C++ -*-
#ifndef _synth_object_synth_h_
#define _synth_object_synth_h_

#include "synth/common.h"

namespace synth {

class ObjectSynth {
public:
  ObjectSynth(vm::Object *obj, const char *object_name,
	      const vector<string> &task_entries,
	      DesignSynth *design_synth);
  virtual ~ObjectSynth();

  bool Synth();

  vm::VM *GetVM() const;
  vm::Object *GetObject() const;
  ChannelSynth *GetChannelSynth() const;
  IModule *GetIModule();
  ThreadSynth *GetThreadByName(const string &name);

private:
  void CollectThreads(IModule *mod);
  void CollectSubModuleCalls();
  void ResolveSubModuleCalls();

  vm::VM *vm_;
  vm::Object *obj_;
  const string obj_name_;
  vector<string> task_entries_;
  DesignSynth *design_synth_;
  IModule *mod_;
  vector<ThreadSynth *> threads_;
  vector<ObjectSynth *> member_objs_;
};

}  // namespace synth

#endif  // _synth_object_synth_h_
