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
		 vector<TableCall> *table_calls);

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
  void ExpandCalleeStates(MethodContext *method,
			  map<IState *, IState *> &st_map,
			  map<IRegister *, IRegister *> &reg_map);
  // Fills sub_obj_calls_ or data_flow_calls_
  void CollectTableCalls(MethodContext *method,
			 map<IState *, IState *> &st_map);

  MethodContext *root_method_;
  ThreadSynth *thread_;
  ITable *tab_;
  vector<TableCall> *table_calls_;
};

}  // namespace synth

#endif  // _synth_method_expander_h_
