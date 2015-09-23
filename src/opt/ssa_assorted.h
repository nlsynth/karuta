// -*- C++ -*-
#ifndef _opt_ssa_assorted_h_
#define _opt_ssa_assorted_h_

#include "opt/opt_phase.h"

namespace opt {

class AssortedSSAOptimization : public OptimizationPhase {
public:
  virtual bool Perform(const char *phase, DGraph *graph, const char *note);
  static OptimizationPhase *Create(const char *phase) {
    return new AssortedSSAOptimization;
  }
};

}  // namespace opt

#endif  // _opt_ssa_assorted_h_
