#include "opt/ssa_misc.h"

#include "dfg/dfg_util.h"
#include "opt/ssa.h"

namespace opt {

bool UnusedOutputElimination::Perform(const char *phase, DGraph *graph, const char *note) {
  DGraphWalker<UnusedOutputElimination>
    input_walker(this,
		 NULL, NULL, &UnusedOutputElimination::CollectUsedInput);
  input_walker.Traverse(graph);
  DGraphWalker<UnusedOutputElimination>
    insn_walker(this, NULL, &UnusedOutputElimination::CollectUnusedInsn, NULL);
  insn_walker.Traverse(graph);

  DGraphWalker<UnusedOutputElimination>
    state_walker(this, &UnusedOutputElimination::ReapInsn, NULL, NULL);
  state_walker.Traverse(graph);

  return true;
}

void UnusedOutputElimination::CollectUsedInput(DGraph *graph, DState *state,
					       DInsn *insn, DRegister *reg,
					       bool is_input) {
  if (is_input) {
    used_regs_.insert(reg);
  }
}

void UnusedOutputElimination::CollectUnusedInsn(DGraph *graph, DState *state, DInsn *insn) {
  if (DInsnUtil::HasSideEffect(insn)) {
    return;
  }
  bool unused = true;
  for (vector<DRegister *>::iterator it = insn->outputs_.begin(); it != insn->outputs_.end(); ++it) {
    DRegister *reg = *it;
    if (used_regs_.find(reg) != used_regs_.end()) {
      unused = false;
    }
  }
  if (unused) {
    unused_insn_.insert(insn);
  }
}

void UnusedOutputElimination::ReapInsn(DGraph *graph, DState *state) {
  list<DInsn *> insns = state->insns_;
  for (list<DInsn *>::iterator it = insns.begin(); it != insns.end(); ++it) {
    DInsn *insn = *it;
    if (unused_insn_.find(insn) != unused_insn_.end()) {
      DStateUtil::EraseInsn(state, insn);
    }
  }
}

static void register_misc() {
  OptimizationPhase::registerPhase("opt_unused_output_elimination",
				   &UnusedOutputElimination::Create, NULL);
}

STATIC_INITIALIZER(ssa_misc, register_misc());

}  // namespace opt
