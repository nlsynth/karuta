// -*- C++ -*-
#ifndef _synth_thread_synth_h_
#define _synth_thread_synth_h_

#include "synth/common.h"

#include <map>
#include <set>

using std::map;
using std::set;

namespace synth {

class ThreadSynth {
public:
  ThreadSynth(ObjectSynth *obj_synth,
	      const string &thread_name,
	      const string &method_name, IModule *mod);
  virtual ~ThreadSynth();

  bool Synth();
  bool Scan();
  void SetIsTask(bool is_task);
  ObjectSynth *GetObjectSynth();
  void RequestMethod(const string &m);
  void AddName(const string &n);
  IRegister *AllocRegister(const string &prefix);
  MethodContext *GetMethodContext(const string &m);
  ResourceSet *GetResourceSet();
  ITable *GetITable();
  vector<SubObjCall> &GetSubObjCalls();
  const string &GetMethodName();
  static void InjectSubModuleCall(IState *st, IInsn *insn,
				  ITable *callee_tab);

private:
  ObjectSynth *obj_synth_;
  const string thread_name_;
  const string method_name_;
  vector<SubObjCall> sub_obj_calls_;
  IModule *mod_;
  ITable *tab_;
  bool is_task_;
  std::unique_ptr<ResourceSet> resource_;
  map<string, MethodSynth *> methods_;
  set<string> method_names_;
  int reg_name_index_;
  set<string> used_reg_names_;
};

}  // namespace synth

#endif  // _synth_thread_synth_h_
