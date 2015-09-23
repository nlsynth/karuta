#include "opt/ssa_assorted.h"

#include "opt/constant_insn.h"
#include "opt/misc.h"
#include "opt/opt.h"
#include "opt/opt_context.h"
#include "opt/ssa_misc.h"

namespace opt {

bool AssortedSSAOptimization::Perform(const char *phase, DGraph *graph,
				      const char *note) {
  dfg::DGraphAnnotation an;
  OptimizeContext *ctx = graph->owner_module_->GetOptimizeContext();
  ctx->DumpIntermediateGraph(graph, &an, "ssa_assorted");

  for (int i = 0; i < 8; ++i) {
    CopyPropagation cp(false);
    cp.Perform(phase, graph, note);

    ConstantInsnElimination cie;
    cie.Perform(phase, graph, note);

    UnusedOutputElimination uoe;
    uoe.Perform(phase, graph, note);

    char buf[20];
    sprintf(buf, "ssa_assorted_%d", i);
    ctx->DumpIntermediateGraph(graph, &an, buf);
  }

  return true;
}

static void register_assorted() {
  OptimizationPhase::registerPhase("opt_ssa_assorted",
				   &AssortedSSAOptimization::Create, NULL);
}

STATIC_INITIALIZER(ssa_assorted, register_assorted());

}  // namespace opt
