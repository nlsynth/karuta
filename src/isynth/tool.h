// -*- C++ -*-
#ifndef _isynth_tool_h_
#define _isynth_tool_h_

#include "isynth/common.h"

namespace isynth {

// Some of methods might be moved to DesignTool.
class Tool {
public:
  static void SetNextState(IState *cur, IState *next);
  static IState *GetNextState(IState *st);
  static IResource *FindOrCreateSubModuleTaskCallResource(ITable *caller,
							  ITable *callee);
};

}  // namespace isynth

#endif  // _isynth_method_context_h_
