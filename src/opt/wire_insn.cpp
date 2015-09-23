// Copyright (C) Yusuke Tabata 2012
// Combine instructions in multiple cycles into a cycle.

#include "opt/wire_insn.h"

#include "dfg/dfg_util.h"
#include "opt/basic_block.h"
#include "opt/dfc.h"
#include "opt/opt.h"
#include "opt/opt_context.h"
#include "stl_util.h"

namespace opt {

// Helper class for WireInsn.
class BranchMover {
public:
  BranchMover(DGraph *graph, BasicBlock *bb);
  void Perform();

private:
  DInsn *FindBranchInsn();
  void FindSourceWire();
  size_t GetLastNonEmptyState();
  int GetConditionDefStateIndex();

  DGraph *graph_;
  BasicBlock *bb_;
  DResource *assign_res_;
  DResource *branch_res_;

  // Original branch state and insn.
  DInsn *br_insn_;

  DRegister *cond_reg_;
  DRegister *source_wire_;
  int source_wire_idx_;
};

BranchMover::BranchMover(DGraph *graph, BasicBlock *bb)
  : graph_(graph), bb_(bb) {
  assign_res_ = DGraphUtil::FindResource(graph_, sym_assign, true);
  branch_res_ = DGraphUtil::FindResource(graph_, sym_branch, true);

  br_insn_ = NULL;

  cond_reg_ = NULL;
  source_wire_ = NULL;
  source_wire_idx_ = -1;
}

void BranchMover::Perform() {
  // Find the branch insn in this BB.
  br_insn_ = FindBranchInsn();
  if (!br_insn_) {
    // no branch in this bb. (terminal or infinite loop)
    return;
  }
  cond_reg_ = *(br_insn_->inputs_.begin());

  // Finds the insn which defines the condition.
  int def_st_idx = GetConditionDefStateIndex();
  if (def_st_idx < 0) {
    // condition is not defined in this bb.
    return;
  }
  FindSourceWire();

  int last_non_empty_state_idx = GetLastNonEmptyState();
  // max(state which define the condition, last non empty state)
  int branch_idx = (def_st_idx > last_non_empty_state_idx) ?
    def_st_idx : last_non_empty_state_idx;
  // if it is the last state. don't move.
  if (branch_idx == (int)bb_->states.size() - 1) {
    return;
  }
  DState *new_br_st = bb_->states[branch_idx];
  DInsn *new_br_insn = DStateUtil::FindInsnByResource(new_br_st, branch_res_);
  new_br_insn->targets_ = br_insn_->targets_;
  if (branch_idx == source_wire_idx_) {
    CHECK(source_wire_ != NULL);
    new_br_insn->inputs_.push_back(source_wire_);
  } else {
    new_br_insn->inputs_.push_back(cond_reg_);
  }
}

int BranchMover::GetConditionDefStateIndex() {
  int def_st_idx = -1;
  for (size_t idx = 0; idx < bb_->states.size(); ++idx) {
    DState *cur_st = bb_->states[idx];
    for (list<DInsn *>::iterator it = cur_st->insns_.begin();
	 it != cur_st->insns_.end(); ++it) {
      DInsn *insn = *it;
      for (vector<DRegister *>::iterator jt = insn->outputs_.begin();
	   jt != insn->outputs_.end(); ++jt) {
	if (*jt == cond_reg_) {
	  def_st_idx = idx;
	}
      }
    }
  }
  return def_st_idx;
}

void BranchMover::FindSourceWire() {
  for (size_t idx = 0; idx < bb_->states.size(); ++idx) {
    DState *cur_st = bb_->states[idx];
    for (list<DInsn *>::iterator it = cur_st->insns_.begin();
	 it != cur_st->insns_.end(); ++it) {
      DInsn *insn = *it;
      if (insn->resource_ == assign_res_ &&
	  (*insn->outputs_.begin()) == cond_reg_) {
	source_wire_ = *(insn->inputs_.begin());
	source_wire_idx_ = idx;
      }
    }
  }
}

DInsn *BranchMover::FindBranchInsn() {
  DInsn *insn = NULL;
  for (size_t idx = 0; idx < bb_->states.size(); ++idx) {
    DState *cur_st = bb_->states[idx];
    insn = DStateUtil::FindInsnByResource(cur_st, branch_res_);
    if (insn->targets_.size() > 1) {
      return insn;
    }
  }
  return NULL;
}

size_t BranchMover::GetLastNonEmptyState() {
  size_t last_non_empty_state_idx = -1;
  for (size_t idx = 0; idx < bb_->states.size(); ++idx) {
    DState *cur_st = bb_->states[idx];
    if (cur_st->insns_.size() > 1) {
      // this state has other than branch insn.
      last_non_empty_state_idx = idx;
    }
  }
  return last_non_empty_state_idx;
}

WireInsn::~WireInsn() {
  STLDeleteSecondElements(&per_insn_map_);
}

bool WireInsn::Perform(const char *phase, DGraph *graph, const char *note) {
  graph_ = graph;
  assign_res_ = DGraphUtil::FindResource(graph_, sym_assign, true);
  branch_res_ = DGraphUtil::FindResource(graph_, sym_branch, true);
  memory_res_ = DGraphUtil::FindResource(graph_, sym_memory, true);
  sram_res_ = DGraphUtil::FindResource(graph_, sym_sram_if, true);
  read_channel_res_ = DGraphUtil::FindResource(graph_, sym_read_channel, true);

  GraphOptimizeStat::SetupStateAnnotation(graph);
  bset_.reset(new BasicBlockSet);
  BasicBlockCollector bbc(graph, bset_.get());
  dfg::DGraphAnnotation an;
  bbc.CollectBBAll(&an);
  dfc_.reset(new DataFlowCollector(graph, bset_.get(), &an));
  dfc_->Perform();

  CollectReachingRegisters();

  OptimizeContext *ctx = graph->owner_module_->GetOptimizeContext();
  ctx->DumpIntermediateGraph(graph, &an, "pre_wire_insn");

  for (set<BasicBlock *>::iterator it = bset_->bbs_.begin();
       it != bset_->bbs_.end(); ++it) {
    BuildDependency(*it);
  }
  ModifyGraph();
  InjectWireToRegisterAssignments();
  for (set<BasicBlock *>::iterator it = bset_->bbs_.begin();
       it != bset_->bbs_.end(); ++it) {
    ScanBBToMoveBranchInsn(*it);
  }

  GraphOptimizeStat::PerformPhaseByName("opt_unreachable_state_elimination",
					"", graph);

  ctx->DumpIntermediateGraph(graph, &an, "wire_insn");
  return true;
}

void WireInsn::CollectReachingRegisters() {
  CollectUsedRegsForBB();
  // collect active_defs: defs which reach some bb.
  set<DefInfo *> active_defs;
  for (set<BasicBlock *>::iterator it = bset_->bbs_.begin();
       it != bset_->bbs_.end(); ++it) {
    BasicBlock *bb = *it;
    set<DefInfo *> reach_defs;
    dfc_->GetReachDefs(bb, &reach_defs);
    set<DRegister *> &regs_in_bb = used_regs_for_bb_[bb];
    for (set<DefInfo *>::iterator it = reach_defs.begin();
	 it != reach_defs.end(); ++it) {
      DefInfo *di = *it;
      if (regs_in_bb.find(di->output_reg) != regs_in_bb.end()) {
	active_defs.insert(di);
      }
    }
  }

  // find active outputs of each defining insn.
  for (set<DefInfo *>::iterator it = active_defs.begin();
       it != active_defs.end(); ++it) {
    DefInfo *di = *it;
    PerInsn *pi = GetPerInsn(di->insn);
    for (vector<DRegister *>::iterator jt = di->insn->outputs_.begin();
	 jt != di->insn->outputs_.end(); jt++) {
      DRegister *output = *jt;
      // TODO(yusuke): should be reach && used.
      // now this just checks only the reachability.
      if (output == di->output_reg) {
	pi->output_reach_to_other_bb_.insert(output);
      }
    }
  }
}

void WireInsn::CollectUsedRegsForBB() {
  DGraphWalker<WireInsn>
    register_walker(this, NULL, NULL, &WireInsn::TraverseRegisterToCollectUse);
  register_walker.Traverse(graph_);
}

void WireInsn::TraverseRegisterToCollectUse(DGraph *graph, DState *state,
					    DInsn *insn,
					    DRegister *reg, bool is_input) {
  if (is_input) {
    BasicBlock *bb = bset_->state_bb_mapping_[state];
    used_regs_for_bb_[bb].insert(reg);
  }
}

void WireInsn::ModifyGraph() {
  for (set<BasicBlock *>::iterator it = bset_->bbs_.begin();
       it != bset_->bbs_.end(); ++it) {
    BasicBlock *bb = *it;
    SplitInsnOutputBB(bb);
    ScanBBToMoveInsn(bb);
  }
}

void WireInsn::BuildDependency(BasicBlock *bb) {
  map<DRegister *, DInsn *> last_def_insn;
  map<DRegister *, DInsn *> last_read_insn;
  int nth_state = 0;
  for (vector<DState *>::iterator it = bb->states.begin();
       it != bb->states.end(); it++, nth_state++) {
    DState *st = *it;
    for (list<DInsn *>::iterator jt = st->insns_.begin();
	 jt != st->insns_.end(); jt++) {
      DInsn *insn = *jt;
      PerInsn *pi = GetPerInsn(insn);
      pi->nth_state = nth_state;
      // WRITE -> READ dependency.
      for (vector<DRegister *>::iterator kt = insn->inputs_.begin();
	   kt != insn->inputs_.end(); kt++) {
	BuildRWDependencyPair(insn, *kt, last_def_insn);
      }
      // READ -> WRITE dependency.
      for (vector<DRegister *>::iterator kt = insn->outputs_.begin();
	   kt != insn->outputs_.end(); kt++) {
	BuildRWDependencyPair(insn, *kt, last_read_insn);
      }
      // update last write
      for (vector<DRegister *>::iterator kt = insn->outputs_.begin();
	   kt != insn->outputs_.end(); kt++) {
	last_def_insn[*kt] = insn;
      }
      // update last read
      for (vector<DRegister *>::iterator kt = insn->inputs_.begin();
	   kt != insn->inputs_.end(); kt++) {
	last_read_insn[*kt] = insn;
      }
    }
  }
}

void WireInsn::BuildRWDependencyPair(DInsn *insn, DRegister *reg,
				     map<DRegister *, DInsn *> &dep_map) {
  DRegister *input = reg;
  DInsn *def_insn = dep_map[input];
  if (!def_insn) {
    // not written/read in this block.
    return;
  }
  PerInsn *pi = GetPerInsn(insn);
  pi->depending_insn_[input] = def_insn;
  // adds reverse mapping too.
  PerInsn *def_insn_pi = GetPerInsn(def_insn);
  def_insn_pi->using_insns_[input].insert(insn);
}

void WireInsn::InjectWireToRegisterAssignments() {
  DGraphWalker<WireInsn> state_walker(this, &WireInsn::TraverseState, NULL, NULL);
  state_walker.Traverse(graph_);
}

void WireInsn::TraverseState(DGraph *graph, DState *state) {
  vector<DInsn *> new_assign_insn;
  for (list<DInsn *>::iterator it = state->insns_.begin();
       it != state->insns_.end(); ++it) {
    DInsn *insn = *it;
    PerInsn *pi = GetPerInsn(insn);
    for (vector<DRegister *>::iterator jt = insn->outputs_.begin();
	 jt != insn->outputs_.end(); ++jt) {
      DRegister *maybe_wire = *jt;
      DRegister *orig_reg = pi->wire_to_register_[maybe_wire];
      if (orig_reg) {
	const bool used_later = IsUsedLaterInThisBB(insn, orig_reg);
	const bool reach_to_other_bb =
	  pi->output_reach_to_other_bb_.find(orig_reg) !=
	  pi->output_reach_to_other_bb_.end();
	if (used_later || reach_to_other_bb) {
	  DInsn *assign_insn = DGraphUtil::InsnNew(graph_, assign_res_);
	  assign_insn->inputs_.push_back(maybe_wire);
	  assign_insn->outputs_.push_back(orig_reg);
	  new_assign_insn.push_back(assign_insn);
	}
      }
    }
  }
  for (vector<DInsn *>::iterator it = new_assign_insn.begin();
       it != new_assign_insn.end(); ++it) {
    state->insns_.push_back(*it);
  }
}

bool WireInsn::IsUsedLaterInThisBB(DInsn *insn, DRegister *output) {
  PerInsn *pi = GetPerInsn(insn);
  map<DRegister *, set<DInsn *> >::iterator it = pi->using_insns_.find(output);
  if (it == pi->using_insns_.end()) {
    return false;
  }
  set<DInsn *> &users = it->second;
  for (set<DInsn *>::iterator jt = users.begin(); jt != users.end(); ++jt) {
    PerInsn *user_pi = GetPerInsn(*jt);
    if (user_pi->nth_state > pi->nth_state) {
      return true;
    }
  }
  return false;
}

void WireInsn::SplitInsnOutputBB(BasicBlock *bb) {
  for (vector<DState *>::iterator it = bb->states.begin();
       it != bb->states.end(); it++) {
    DState *st = *it;
    for (list<DInsn *>::iterator jt = st->insns_.begin();
	 jt != st->insns_.end(); jt++) {
      DInsn *insn = *jt;
      if (IsIsolatedInsn(insn)) {
	// ignore multi cycles insns like memory ops.
	continue;
      }
      if (insn->resource_ == assign_res_) {
	PerInsn *pi = GetPerInsn(insn);
	pi->is_assign = true;
      } else {
	SplitInsnOutput(insn);
      }
    }
  }
}

void WireInsn::SplitInsnOutput(DInsn *insn) {
  for (vector<DRegister *>::iterator it = insn->outputs_.begin();
       it != insn->outputs_.end(); ++it) {
    DRegister *reg = *it;
    if (reg->reg_type_ != DRegister::REG_NORMAL) {
      continue;
    }
    DRegister *wire_reg = DGraphUtil::AllocWireReg(graph_, reg->data_type_);
    AddWireToRegMapping(insn, wire_reg, *it);
    *it = wire_reg;
  }
}

void WireInsn::ScanBBToMoveInsn(BasicBlock *bb) {
  for (size_t target = 0; target < bb->states.size() - 1; ++target) {
    if (IsIsolatedState(bb->states[target])) {
      continue;
    }
    for (size_t pos = target + 1; pos < bb->states.size(); ++pos) {
      vector<DInsn *> movable_insns;
      DState *src_st = bb->states[pos];
      if (IsIsolatedState(src_st)) {
	continue;
      }
      for (list<DInsn *>::iterator it = src_st->insns_.begin();
	   it != src_st->insns_.end(); ++it) {
	DInsn *insn = *it;
	if (CanMoveInsn(insn, bb, target)) {
	  movable_insns.push_back(insn);
	}
      }
      for (vector<DInsn *>::iterator it = movable_insns.begin();
	   it != movable_insns.end(); ++it) {
	MoveInsn(*it, bb, target);
      }
    }
  }
}

void WireInsn::ScanBBToMoveBranchInsn(BasicBlock *bb) {
  BranchMover bm(graph_, bb);
  bm.Perform();
}

bool WireInsn::CanMoveInsn(DInsn *insn, BasicBlock *bb, int target_pos) {
  if (insn->resource_ == branch_res_) {
    return false;
  }
  if (IsIsolatedInsn(insn)) {
    return false;
  }
  DState *target_st = bb->states[target_pos];
  if (!CanUseResourceInState(target_st, insn->resource_) &&
      !CanAllocateResourceInState(target_st, insn->resource_)) {
    return false;
  }
  PerInsn *pi = GetPerInsn(insn);
  int max_pos = 0;
  // check input dependency
  for (map<DRegister *, DInsn *>::iterator it = pi->depending_insn_.begin();
       it != pi->depending_insn_.end(); ++it) {
    PerInsn *src_pi = GetPerInsn(it->second);
    if (src_pi->nth_state > max_pos) {
      max_pos = src_pi->nth_state;
    }
  }
  if (max_pos <= target_pos) {
    return true;
  }
  return false;
}

bool WireInsn::CanUseResourceInState(DState *st, DResource *resource) {
  for (list<DInsn *>::iterator it = st->insns_.begin();
       it != st->insns_.end(); ++it) {
    DInsn *target_insn = *it;
    if (resource->opr_->is_exclusive_ &&
	resource == target_insn->resource_) {
      return false;
    }
  }
  return true;
}

bool WireInsn::CanAllocateResourceInState(DState *st, DResource *resource) {
  return false;
}

bool WireInsn::IsIsolatedState(DState *st) {
  for (list<DInsn *>::iterator it = st->insns_.begin();
       it != st->insns_.end(); ++it) {
    DInsn *insn = *it;
    if (IsIsolatedInsn(insn)) {
      return true;
    }
  }
  return false;
}

bool WireInsn::IsIsolatedInsn(DInsn *insn) {
  if (insn->resource_ == memory_res_ ||
      insn->resource_ == sram_res_ ||
      insn->resource_ == read_channel_res_) {
    return true;
  }
  return false;
}

void WireInsn::MoveInsn(DInsn *insn, BasicBlock *bb, int target_pos) {
  PerInsn *pi = GetPerInsn(insn);
  DState *src_st = bb->states[pi->nth_state];
  DState *dst_st = bb->states[target_pos];
  DResource *res = GetResourceInMovedState(dst_st, insn);
  if (!res) {
    LOG(FATAL) << "This resource seems not available. :"
	       << sym_cstr(insn->resource_->opr_->type_);
  }
  insn->resource_ = res;
  DStateUtil::MoveInsn(insn, src_st, dst_st);
  pi->nth_state = target_pos;
  for (vector<DRegister *>::iterator it = insn->inputs_.begin();
       it != insn->inputs_.end(); it++) {
    DRegister *input = *it;
    DInsn *src_insn = pi->depending_insn_[input];
    if (!src_insn) {
      continue;
    }
    PerInsn *src_pi = GetPerInsn(src_insn);
    if (src_pi->nth_state < target_pos) {
      // This register was an output in previous state,
      // so the wire is not avaialble.
      continue;
    }
    DRegister *alt_input = src_pi->register_to_wire_[input];
    if (!alt_input && src_pi->is_assign) {
      alt_input = *(src_insn->inputs_.begin());
    }
    if (alt_input) {
      *it = alt_input;
    }
  }
}

DResource *WireInsn::GetResourceInMovedState(DState *st, DInsn *insn) {
  if (!CanUseResourceInState(st, insn->resource_)) {
    return NULL;
  }
  return insn->resource_;
}

void WireInsn::AddWireToRegMapping(DInsn *insn, DRegister *wire, DRegister *reg) {
  PerInsn *pi = GetPerInsn(insn);
  pi->wire_to_register_[wire] = reg;
  pi->register_to_wire_[reg] = wire;
}

WireInsn::PerInsn *WireInsn::GetPerInsn(DInsn *insn) {
  PerInsn *pi;
  map<DInsn *, PerInsn *>::iterator it = per_insn_map_.find(insn);
  if (it == per_insn_map_.end()) {
    pi = new PerInsn;
    per_insn_map_.insert(std::make_pair(insn, pi));
  } else {
    pi = it->second;
  }
  return pi;
}

DRegister *WireInsn::GetOutputWire(DInsn *insn, DRegister *reg) {
  PerInsn *pi = GetPerInsn(insn);
  return pi->register_to_wire_[reg];
}

///Optimizer: Wire instuction
// This processes only within a block for now.

static void register_wire_insn() {
  OptimizationPhase::registerPhase("opt_wire_insn",
				   &WireInsn::Create, NULL);
}

STATIC_INITIALIZER(wire_insn, register_wire_insn());

}  // namespace opt
