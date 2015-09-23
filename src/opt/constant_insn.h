// -*- C++ -*-
#ifndef _opt_constant_insn_h_
#define _opt_constant_insn_h_

#include "opt/opt_phase.h"

namespace opt {

class ConstantInsnElimination : public OptimizationPhase {
public:
  virtual bool Perform(const char *phase, DGraph *graph, const char *note);
  static OptimizationPhase *Create(const char *phase) {
    return new ConstantInsnElimination;
  }

private:
  static bool ModifyConstantInsn(DGraph *graph, DState *st, DInsn *insn);
  static bool IsConstantInputInsn(DInsn *insn);
  static DRegister *CalcConstantInputResult(DGraph *g, DInsn *insn);
  static DRegister *CalcMaybeConstantResult(DGraph *g, DInsn *insn);

  static uint64_t CalcBitConcat(DInsn *insn, int *width);
};

}  // namespace opt

#endif  // _opt_constant_insn_h_
