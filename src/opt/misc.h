// -*- C++ -*-
#ifndef _opt_misc_h_
#define _opt_misc_h_

#include <list>
#include <map>
#include <set>
#include <iostream>

#include "nli.h"
#include "opt/opt_phase.h"

using std::list;
using std::set;
using std::map;
using std::ostream;


namespace dfg {
class DGraph;
class DGraphAnnotation;
class DInsn;
class DRegister;
class DResource;
class DState;
}  // namespace dfg
using namespace dfg;

namespace opt {

class BasicBlock;
class StateAnnotation;

class UnreachableStateElimination {
public:
  static void Perform(DGraph *graph);
};

class DeadStateElimination {
public:
  DeadStateElimination(bool is_strong);
  void Perform(DGraph *graph);
private:
  // dead state does nothing but go next
  struct dead_state_entry {
    DState *state;
    DState *target_state;
  };
  DState *FindTransitionTargetState(DState *ds);
  bool IsDeadState(DState *ds);

  bool is_strong_;
  map<DState *, int> join_count_;
};

class DeadResourceElimination {
public:
  static void Perform(DGraph *graph);
};

class DeadVariableElimination {
public:
  void Perform(DGraph *graph);
private:
  void WalkRegister(DGraph *graph, DState *state, DInsn *insn,
		    DRegister *reg, bool is_input);

  set<DRegister *> used_regs_;
};

class ConstantBranchElimination {
public:
  ConstantBranchElimination(DGraph *graph);
  void Perform();
private:
  void WalkInsn(DGraph *graph, DState *state, DInsn *insn);

  DGraph *graph_;
  DResource *branch_res_;
};

class CopyPropagation : public OptimizationPhase {
public:
  CopyPropagation(bool dump_graph);
  virtual ~CopyPropagation() {
  }
  virtual bool Perform(const char *phase, DGraph *graph, const char *note);
  static OptimizationPhase *Create(const char *phase) {
    return new CopyPropagation(true);
  }
private:
  void ConstantAssignFinder(DGraph *graph, DState *state, DInsn *insn);
  void UpdateConstant(DGraph *graph, DState *state, DInsn *insn);

  bool do_dump_;
  map<DRegister *, DRegister *> constant_map_;
  set<DRegister *> non_single_regs_;
  DResource *phi_res_;
};

}  // namespace opt

#endif  // _opt_misc_h_
