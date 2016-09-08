// -*- C++ -*-
#ifndef _isynth_method_expander_h_
#define _isynth_method_expander_h_

#include "isynth/common.h"

#include <map>

using namespace std;

namespace isynth {

class CalleeInfo {
public:
  IState *initial;
  IState *final;
  vector<IRegister *> args;
  vector<IRegister *> rets;
};

class MethodExpander {
public:
  MethodExpander(MethodContext *root, ThreadSynth *thread_synth);

  bool Expand();

private:
  CalleeInfo ExpandMethod(MethodContext *method);
  void CopyState(IState *ost, map<IState *, IState *> &st_map,
		 map<IRegister *, IRegister *> &reg_map,
		 IState *nst);
  IInsn *CopyInsn(IInsn *oinsn, map<IState *, IState *> &st_map,
		  map<IRegister *, IRegister *> &reg_map);
  void BuildInsnRegCopy(IInsn *insn, map<IRegister *, IRegister *> &reg_map);
  void BuildRegCopy(IRegister *reg, map<IRegister *, IRegister *> &reg_map);
  string GetName(const string &name);
  void ExpandStates(MethodContext *method, map<IState *, IState *> &st_map,
		    map<IRegister *, IRegister *> &reg_map);

  MethodContext *root_method_;
  ThreadSynth *thread_;
  ITable *tab_;
  int reg_name_index_;
  set<string> used_reg_names_;
};

}  // namespace isynth

#endif  // _isynth_method_expander_h_
