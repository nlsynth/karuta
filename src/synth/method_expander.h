// -*- C++ -*-
#ifndef _synth_method_expander_h_
#define _synth_method_expander_h_

#include "synth/common.h"

#include <map>

using std::map;

namespace synth {

class CalleeInfo {
public:
  IState *initial;
  IState *final;
  vector<IRegister *> args;
  vector<IRegister *> rets;
};

class MethodExpander {
public:
  MethodExpander(MethodContext *root, ThreadSynth *thread_synth,
		 vector<SubObjCall> *sub_obj_calls);

  bool Expand();
  IState *GetLastState();
  map<IRegister *, IRegister *> *GetRootRegMap();

private:
  CalleeInfo ExpandMethod(MethodContext *method,
			  map<IRegister *, IRegister *> *reg_map_out);
  void CopyState(IState *ost, map<IState *, IState *> &st_map,
		 map<IRegister *, IRegister *> &reg_map,
		 IState *nst);
  IInsn *CopyInsn(IInsn *oinsn, map<IState *, IState *> &st_map,
		  map<IRegister *, IRegister *> &reg_map);
  void BuildInsnRegCopy(IInsn *insn, map<IRegister *, IRegister *> &reg_map);
  void BuildRegCopy(IRegister *reg, map<IRegister *, IRegister *> &reg_map);
  void ExpandCalleeStates(MethodContext *method,
			  map<IState *, IState *> &st_map,
			  map<IRegister *, IRegister *> &reg_map);
  void CollectSubObjCalls(MethodContext *method,
			  map<IState *, IState *> &st_map);

  MethodContext *root_method_;
  ThreadSynth *thread_;
  ITable *tab_;
  vector<SubObjCall> *sub_obj_calls_;
  IState *last_state_;
  map<IRegister *, IRegister *> root_reg_copy_map_;
};

}  // namespace synth

#endif  // _synth_method_expander_h_
