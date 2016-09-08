// -*- C++ -*-
#ifndef _isynth_thread_synth_h_
#define _isynth_thread_synth_h_

#include "isynth/common.h"

#include <map>

using std::map;

namespace isynth {

class ThreadSynth {
public:
  ThreadSynth(ObjectSynth *obj_synth,
	      const char *method_name, IModule *mod);
  virtual ~ThreadSynth();

  bool Synth();
  ObjectSynth *GetObjectSynth();
  void RequestMethod(const string &m);
  MethodContext *GetMethodContext(const string &m);
  ResourceSet *GetResourceSet();
  ITable *GetITable();

private:
  ObjectSynth *obj_synth_;
  const string method_name_;
  IModule *mod_;
  ITable *tab_;
  std::unique_ptr<ResourceSet> resource_;
  map<string, MethodSynth *> methods_;
};

}  // namespace isynth

#endif  // _isynth_thread_synth_h_
