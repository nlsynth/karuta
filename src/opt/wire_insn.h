// -*- C++ -*-
#ifndef _opt_opt_wire_insn_h_
#define _opt_opt_wire_insn_h_

#include "opt/opt_phase.h"

#include <vector>

using std::vector;

namespace dfg {
class DResource;
}  // namespace dfg
using namespace dfg;

namespace opt {

class BasicBlock;
class BasicBlockSet;
class DataFlowCollector;

// Basic class to wire instructions in a cycle.
// Performs conservative wiring and no additional resource allocation.
// Currently, ResourceAlloc(resource_alloc.cpp) inherits this class
// and does more aggresive optimization.
class WireInsn : public OptimizationPhase {
public:
  virtual ~WireInsn();
  virtual bool Perform(const char *phase, DGraph *graph, const char *note);
  static OptimizationPhase *Create(const char *phase) {
    return new WireInsn;
  }

protected:
  virtual DResource *GetResourceInMovedState(DState *st, DInsn *insn);
  virtual bool CanAllocateResourceInState(DState *st, DResource *resource);

private:
  // populates pi->reach_to_other_bb_;
  void CollectReachingRegisters();
  void ModifyGraph();
  void BuildDependency(BasicBlock *bb);
  void BuildRWDependencyPair(DInsn *insn, DRegister *reg,
			     map<DRegister *, DInsn *> &dep_map);
  void InjectWireToRegisterAssignments();
  void TraverseState(DGraph *graph, DState *state);
  bool IsUsedLaterInThisBB(DInsn *insn, DRegister *output);

  void SplitInsnOutputBB(BasicBlock *bb);
  void SplitInsnOutput(DInsn *insn);

  void ScanBBToMoveInsn(BasicBlock *bb);
  void ScanBBToMoveBranchInsn(BasicBlock *bb);
  bool CanMoveInsn(DInsn *insn, BasicBlock *bb, int target_pos);
  bool CanUseResourceInState(DState *st, DResource *resource);
  void MoveInsn(DInsn *insn, BasicBlock *bb, int target_pos);
  void AddWireToRegMapping(DInsn *insn, DRegister *wire, DRegister *reg);
  DRegister *GetOutputWire(DInsn *insn, DRegister *reg);
  bool IsIsolatedState(DState *st);
  bool IsIsolatedInsn(DInsn *insn);

protected:
  DGraph *graph_;

private:
  DResource *assign_res_;
  DResource *branch_res_;
  DResource *memory_res_;
  DResource *sram_res_;
  DResource *read_channel_res_;
  std::unique_ptr<BasicBlockSet> bset_;
  std::unique_ptr<DataFlowCollector> dfc_;
  struct PerInsn {
    PerInsn() {
      is_assign = false;
    }
    bool is_assign;
    // Adds assignment instruction (normal <- wire), if the result is
    // used later or in other BBs.
    // {insn, wire register} -> normal register.
    map<DRegister *, DRegister *> wire_to_register_;
    // reverse mapping of above to rewrite inputs.
    map<DRegister *, DRegister *> register_to_wire_;
    // source of each input. non existent, if it comes from other bb.
    map<DRegister *, DInsn *> depending_insn_;
    // users of each output.
    map<DRegister *, set<DInsn *> > using_insns_;
    // nth, up to date.
    int nth_state;
    // output reach to other bb
    set<DRegister *> output_reach_to_other_bb_;
  };
  map<DInsn *, PerInsn *> per_insn_map_;
  PerInsn *GetPerInsn(DInsn *insn);

  map<BasicBlock *, set<DRegister *> > used_regs_for_bb_;
  // output will be stored into used_regs_
  void CollectUsedRegsForBB();
  void TraverseRegisterToCollectUse(DGraph *graph, DState *state, DInsn *insn,
				    DRegister *reg, bool is_input);
};

}  // namespace opt

#endif  // _opt_opt_wire_insn_h_
