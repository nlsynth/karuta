// -*- C++ -*-
#ifndef _dfg_d_module_h_
#define _dfg_d_module_h_

#include "nli.h"

namespace opt {
class OptimizeContext;
}  // namespace opt

namespace dfg {

class DChannel;
class DGraph;

// A FSM and its subsidiary resource modules and interfaces.
class DModule {
public:
  enum ModuleType {
    MODULE_NONE,
    // Contains thread modules and task modules.
    MODULE_CONTAINER,
    // Runs permanently.
    MODULE_THREAD,
    // Kicked by external request.
    MODULE_TASK,
  };

  DModule(const char *name, enum ModuleType type, DModule *parent);
  ~DModule();

  string module_name_;
  enum ModuleType module_type_;
  DGraph *graph_;
  DModule *parent_mod_;
  vector<DModule *> sub_modules_;
  vector<DChannel *> channels_;

  opt::OptimizeContext *GetOptimizeContext();

private:
  std::unique_ptr<opt::OptimizeContext> optimize_context_;
};

class DModuleUtil {
public:
  static DModule *Create(DModule *parent, const char *name);
  static void ClearAnnotation(DModule *mod);
  static DChannel *CreateChannel(DModule *mod);
};

}  // namespace dfg

#endif  // _dfg_d_module_h_
