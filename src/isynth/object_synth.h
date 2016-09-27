// -*- C++ -*-
#ifndef _isynth_object_synth_h_
#define _isynth_object_synth_h_

#include "isynth/common.h"

namespace isynth {

class ObjectSynth {
public:
  ObjectSynth(vm::VM *vm, vm::Object *obj, const char *object_name,
	      const vector<string> &task_entries,
	      IDesign *design, ChannelSynth *channel);
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
  IDesign *design_;
  ChannelSynth *channel_;
  IModule *mod_;
  vector<ThreadSynth *> threads_;
  vector<ObjectSynth *> member_objs_;
};

}  // namespace isynth

#endif  // _isynth_object_synth_h_
