// -*- C++ -*-
#ifndef _opt_resource_alloc_h_
#define _opt_resource_alloc_h_

#include "opt/opt_phase.h"
#include "opt/wire_insn.h"

namespace opt {

class ResourceAlloc : public WireInsn {
public:
  virtual ~ResourceAlloc() {};
  virtual bool Perform(const char *phase, DGraph *graph, const char *note);
  static OptimizationPhase *Create(const char *phase) {
    return new ResourceAlloc;
  }

private:
  virtual DResource *GetResourceInMovedState(DState *st, DInsn *insn);
  virtual bool CanAllocateResourceInState(DState *st, DResource *resource);
  DResource *FindEquivalentResource(DState *st, DResource *res);
};

}  // namespace opt

#endif  // _opt_resource_alloc_h_
