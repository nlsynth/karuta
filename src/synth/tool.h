// -*- C++ -*-
#ifndef _synth_tool_h_
#define _synth_tool_h_

#include "synth/common.h"

namespace synth {

// Some of methods might be moved to DesignTool.
class Tool {
 public:
  static void SetNextState(IState *cur, IState *next);
  static IState *GetNextState(IState *st);
  static IResource *FindOrCreateTaskCallResource(ITable *caller,
                                                 ITable *callee);
  static IResource *FindOrCreateTaskReturnValueResource(ITable *caller,
                                                        ITable *callee);
  static IResource *FindOrCreateDataFlowCaller(ITable *caller, IResource *sreg);
  static IResource *FindOrCreateExtStubCallResource(ITable *caller,
                                                    const string &name,
                                                    bool is_flow);
  static IResource *FindOrCreateExtStubWaitResource(ITable *caller,
                                                    const string &name,
                                                    bool is_flow);

 private:
  static IInsn *FindArgInsn(ITable *tab, IResource *arg_res);
};

}  // namespace synth

#endif  // _synth_method_context_h_
