// -*- C++ -*-
#ifndef _opt_opt_temp_var_h_
#define _opt_opt_temp_var_h_

#include "opt/opt_phase.h"

namespace opt {

class BasicBlock;

class PureTempVarElimination : public OptimizationPhase {
public:
  virtual ~PureTempVarElimination();
  static OptimizationPhase *Create(const char *phase) {
    return new PureTempVarElimination;
  };
  virtual bool Perform(const char *phase, DGraph *graph, const char *msg);

private:
  struct PerRegister {
    // use mean both read or write.
    set<BasicBlock *> using_bbs;
    // assign insn, not other insns' output.
    set<DInsn *> insns_assign_to_this;
    bool is_block_local;
    set<DState *> writer_states;
  };

  void CollectAssigns(DGraph *graph);
  void MarkBlockLocals();
  void KillTempRegsInBB(DGraph *graph, BasicBlock *bb);
  bool IsRedundantAssign(DState *st, DInsn *insn);
  map<DRegister *, PerRegister *> per_register_map_;
  PerRegister *GetPerRegister(DRegister *reg);
};

}  // namespace opt

#endif // _opt_opt_temp_var_h_
