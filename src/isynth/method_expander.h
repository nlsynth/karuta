// -*- C++ -*-
#ifndef _isynth_method_expander_h_
#define _isynth_method_expander_h_

#include "isynth/common.h"

#include <map>

using std::map;

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
  MethodExpander(MethodContext *root, ThreadSynth *thread_synth,
		 vector<SubObjCall> *sub_obj_calls);

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
  void CollectSubObjCalls(MethodContext *method,
			  map<IState *, IState *> &st_map);

  MethodContext *root_method_;
  ThreadSynth *thread_;
  ITable *tab_;
  vector<SubObjCall> *sub_obj_calls_;
};

}  // namespace isynth

#endif  // _isynth_method_expander_h_
