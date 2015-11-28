// -*- C++ -*-
#ifndef _opt_opt_h_
#define _opt_opt_h_

#include <string.h>
#include <set>
#include "nli.h"
#include "dfg/dfg.h"
#include "opt/constants.h"

using std::set;

namespace opt {

class BasicBlock;
class OptimizationPhase;

class GraphOptimizeStat {
public:
  static void SetupStateAnnotation(DGraph *graph);

  static void PerformPhase(const char *phase, OptimizationPhase *opt,
			   const char *note, DGraph *graph);
  static void PerformPhaseByName(const char *phase, const char *note,
				 DGraph *graph);

private:
  static void CollectTransitionInfo(DGraph *graph, set<DState *> &reachable);
};

class ModuleOptimizeStat {
public:
  // Public interface to optimization.
  static void Optimize(DModule *mod, const string &phase, const char *note);

private:
  static void CollectGraphs(DModule *mod,
			    list<DGraph *> *targets);
  static void ApplyOptimization(list<DGraph *> *targets, DModule *mod,
				const string &phase, const char *note);
};

class StateAnnotation : public DAnnotation {
public:
  StateAnnotation(DState *state);
  virtual ~StateAnnotation() {};

  static StateAnnotation *Get(DState *ds);
  virtual void Output(ostream &os);

  // Number of previous state. This doesn't include
  // reset state for initial state.
  int nr_join_;
  int nr_branch_;

  // a state can belong to more than 3 basic blocks, but
  // index should not conflict.
  int nth_state_;
  // basic blocks this state belong to
  BasicBlock *bb_;
  // transitions
  list<StateAnnotation *> prev_states_;
  list<StateAnnotation *> next_states_;

  // registers written in this state
  set<DRegister *> written_regs_;
  set<DRegister *> read_regs_;

  // this state
  DState *state_;
};

class Profiler {
public:
  static void SetInsnPassCount(DInsn *insn, int count);
};

}  // namespace opt

#endif  // _opt_opt_h_
