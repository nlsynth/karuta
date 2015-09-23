#include "opt/resource_alloc.h"

#include "opt/basic_block.h"
#include "opt/dfc.h"

namespace opt {

bool ResourceAlloc::Perform(const char *phase, DGraph *graph, const char *note) {
  return WireInsn::Perform(phase, graph, note);
}

DResource *ResourceAlloc::GetResourceInMovedState(DState *st, DInsn *insn) {
  DResource *res = WireInsn::GetResourceInMovedState(st, insn);
  if (res) {
    return res;
  }
  // insn->resource_ is not available. e.g. already used.
  // (1/2) try to find another resource in the same class.
  res = FindEquivalentResource(st, insn->resource_);
  if (res) {
    return res;
  }
  // (2/2) newly allocate same class resource.
  res = DGraphUtil::CopyResource(graph_, insn->resource_);
  return res;
}

DResource *ResourceAlloc::FindEquivalentResource(DState *st, DResource *src) {
  set<DResource*> used_resources;
  for (list<DInsn *>::iterator it = st->insns_.begin();
       it != st->insns_.end(); ++it) {
    DInsn *insn = *it;
    used_resources.insert(insn->resource_);
  }
  for (DResource *res : graph_->resources_) {
    if (res == src) {
      continue;
    }
    if (used_resources.find(res) != used_resources.end()) {
      continue;
    }
    if (res->opr_ != src->opr_) {
      continue;
    }
    if (DGraphUtil::IsCompatibleResource(res, src)) {
      return res;
    }
  }
  return NULL;
}

bool ResourceAlloc::CanAllocateResourceInState(DState *st, DResource *resource) {
  if (resource->opr_->is_exclusive_ &&
      !resource->opr_->has_side_effect_) {
    return true;
  }
  return false;
}

static void register_resource_alloc() {
  OptimizationPhase::registerPhase("opt_resource_alloc",
				   &ResourceAlloc::Create, NULL);
}

STATIC_INITIALIZER(resource_alloc, register_resource_alloc());

}  // namespace opt
