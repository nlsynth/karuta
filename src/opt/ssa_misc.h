// -*- C++ -*-
#ifndef _opt_opt_ssa_misc_h_
#define _opt_opt_ssa_misc_h_

#include "opt/opt_phase.h"

#include <set>

using std::set;

namespace opt {

class UnusedOutputElimination : public OptimizationPhase {
public:
  virtual bool Perform(const char *phase, DGraph *graph, const char *note);
  static OptimizationPhase *Create(const char *phase) {
    return new UnusedOutputElimination;
  }
private:
  set<DRegister *> used_regs_;
  set<DInsn *> unused_insn_;

  void CollectUsedInput(DGraph *graph, DState *state, DInsn *insn, DRegister *reg, bool is_input);
  void CollectUnusedInsn(DGraph *graph, DState *state, DInsn *insn);

  void ReapInsn(DGraph *graph, DState *state);
};

}  // namespace opt

#endif  // _opt_opt_ssa_misc_h_

