// -*- C++ -*-
#ifndef _opt_opt_phase_h_
#define _opt_opt_phase_h_

#include "dfg/dfg.h"
#include "nli.h"

#include <map>

using std::map;

namespace opt {

class OptimizeContext;
class OptimizationPhase;

typedef OptimizationPhase *(*OptimizationPhaseFactory)(const char *phase);
class PhaseCondition {
public:
  bool (*CanPerform)(OptimizeContext *oc);
};

class OptimizationPhase {
public:
  virtual ~OptimizationPhase() {};
  virtual bool Perform(const char *phase, dfg::DGraph *graph,
		       const char *note) = 0;

  static OptimizationPhase *getPhase(const char *name);
  static void registerPhase(const char *name, OptimizationPhaseFactory,
			    PhaseCondition *cond);
  static void releasePhases();

private:
  struct PhaseInfo {
    OptimizationPhaseFactory factory;
    PhaseCondition *cond;
  };
  static map<string, PhaseInfo> phases_;
};

}  // namespace opt

#endif  // _opt_opt_phase_h_
