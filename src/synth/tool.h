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
  static IResource *FindOrCreateSubModuleTaskCallResource(ITable *caller,
							  ITable *callee);
};

}  // namespace synth

#endif  // _synth_method_context_h_
