#include "opt/opt_phase.h"

#include "opt/constants.h"
#include "opt/opt_context.h"
#include "synth/interface.h"

namespace opt {
  
map<string, OptimizationPhase::PhaseInfo> OptimizationPhase::phases_;

class Nop : public OptimizationPhase {
public:
  virtual bool Perform(const char *phase, DGraph *graph, const char *note) {
    dfg::DGraphAnnotation an;
    dfg::DModuleUtil::ClearAnnotation(graph->owner_module_);
    OptimizeContext *ctx = graph->owner_module_->GetOptimizeContext();
    if (note) {
      ostream &os = an.SummaryAnnotation();
      os << "note:" << note << "<br>";
      an.Flush();
    }
    ctx->DumpIntermediateGraph(graph, &an, kOptNop);
    return true;
  }
  static OptimizationPhase *Create(const char *phase) {
    return new Nop;
  }
};

class OptInterface : public OptimizationPhase {
public:
  virtual bool Perform(const char *phase, DGraph *graph, const char *note) {
    synth::InterfaceCompiler ic;
    ic.CompileGraph(graph);
    return true;
  }
  static OptimizationPhase *Create(const char *phase) {
    return new OptInterface;
  }
};

OptimizationPhase *OptimizationPhase::getPhase(const char *name) {
  map<string, PhaseInfo>::iterator it = phases_.find(string(name));
  if (it == phases_.end()) {
    return NULL;
  }
  PhaseInfo &pi = it->second;
  return pi.factory(name);
}

void OptimizationPhase::registerPhase(const char *name, OptimizationPhaseFactory factory,
				      PhaseCondition *cond) {
  PhaseInfo pi;
  pi.factory = factory;
  pi.cond = cond;
  phases_[name] = pi;
}

void OptimizationPhase::releasePhases() {
  for (auto it = phases_.begin(); it != phases_.end(); ++it) {
    PhaseInfo &pi = it->second;
    if (pi.cond) {
      delete pi.cond;
    }
  }
}

static void register_main() {
  OptimizationPhase::registerPhase(kOptNop,
				   &Nop::Create, NULL);
  OptimizationPhase::registerPhase(kOptInterface,
				   &OptInterface::Create, NULL);
}

static void release_phases() {
  OptimizationPhase::releasePhases();
}

STATIC_INITIALIZER(opt_main, register_main());
STATIC_FINALIZER(opt_main, release_phases());

}  // namespace opt
