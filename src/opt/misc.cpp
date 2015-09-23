#include "opt/misc.h"

#include <map>
#include "opt/opt.h"
#include "opt/opt_context.h"
#include "opt/basic_block.h"
#include "opt/reg_share.h"
#include "dfg/dfg.h"
#include "dfg/dfg_util.h"

namespace opt {

void UnreachableStateElimination::Perform(DGraph *graph) {
  set<DState *> reachable;
  DStateUtil::CollectReachable(graph, graph->initial_state_, &reachable);

  list<DState *>::iterator it;
 again:
  for (it = graph->states_.begin(); it != graph->states_.end(); it++) {
    if (reachable.find(*it) == reachable.end()) {
      graph->states_.erase(it);
      goto again;
    }
  }
}

DeadStateElimination::DeadStateElimination(bool is_strong) : is_strong_(is_strong) {
}

void DeadStateElimination::Perform(DGraph *graph) {
  map<DState *, dead_state_entry> dead_states;
  DResource *br = DGraphUtil::FindResource(graph, sym_branch, true);

  // collect number of join
  for (DState *st : graph->states_) {
    DInsn *insn = DStateUtil::FindInsnByResource(st, br);
    if (!insn) {
      continue;
    }
    for (vector<DState *>::iterator jt = insn->targets_.begin();
	 jt != insn->targets_.end(); jt++) {
      ++join_count_[*jt];
    }
  }

  // collect dead states
  for (DState *st : graph->states_) {
    if (IsDeadState(st)) {
      dead_state_entry ds;
      ds.state = st;
      ds.target_state = FindTransitionTargetState(st);
      dead_states[st] = ds;
    }
  }

  // update transitions
  for (DState *st : graph->states_) {
    DInsn *insn = DStateUtil::FindInsnByResource(st, br);
    if (!insn) {
      continue;
    }
    for (vector<DState *>::iterator jt = insn->targets_.begin();
	 jt != insn->targets_.end(); jt++) {
      map<DState *, dead_state_entry >::iterator kt;
      kt = dead_states.find(*jt);
      if (kt == dead_states.end()) {
	continue;
      }
      *jt = kt->second.target_state;
    }
  }

  // kill states
 again:
  for (auto it = graph->states_.begin(); it != graph->states_.end(); it++) {
    map<DState *, dead_state_entry >::iterator kt;
    kt = dead_states.find(*it);
    if (kt != dead_states.end()) {
      if ((*it) == graph->initial_state_) {
	graph->initial_state_ = FindTransitionTargetState(*it);
	graph->initial_state_->text_annotation_ = "initial";
      }
      graph->states_.erase(it);
      goto again;
    }
  }
}

bool DeadStateElimination::IsDeadState(DState *ds) {
  if (ds->insns_.size() != 1) {
    // this state has branch insn.
    return false;
  }
  DInsn *insn = *(ds->insns_.begin());
  if (insn->resource_->opr_->type_ != sym_branch) {
    return false;
  }
  if (insn->targets_.size() != 1) {
    return false;
  }
  if (!is_strong_ &&
      join_count_[ds] > 1) {
    return false;
  }
  if (*(insn->targets_.begin()) == ds) {
    // terminal state
    return false;
  }
  // ok, this state do nothing.
  return true;
}

// Skips chain of live states. Dead -> Dead .. Dead -> Live (find!)
DState *DeadStateElimination::FindTransitionTargetState(DState *ds) {
  while (IsDeadState(ds)) {
    // get branch insn, this is the only one insn in this state
    DInsn *insn = *(ds->insns_.begin());
    // this is the un-conditional transition target
    ds = *(insn->targets_.begin());
  }
  return ds;
}

void DeadResourceElimination::Perform(DGraph *graph) {
  set<DResource *> res_set;
  // scan
  for (list<DState *>::iterator it = graph->states_.begin();
       it != graph->states_.end(); it++) {
    list<DInsn *>::iterator jt;
    DState *s = *it;
    for (jt = s->insns_.begin(); jt != s->insns_.end(); jt++) {
      DInsn *insn = *jt;
      res_set.insert(insn->resource_);
    }
  }
  // kill unused resource
 again:
  for (list<DResource *>::iterator kt = graph->resources_.begin();
       kt != graph->resources_.end(); kt++) {
    DResource *r = *kt;
    if (res_set.find(r) == res_set.end()) {
      graph->resources_.erase(kt);
      goto again;
    }
  }
}

void DeadVariableElimination::Perform(DGraph *graph) {
  DGraphWalker<DeadVariableElimination>
    walker(this, NULL, NULL,
	   &DeadVariableElimination::WalkRegister);
  walker.Traverse(graph);
 again:
   for (list<DRegister *>::iterator it = graph->registers_.begin(); it != graph->registers_.end();
       ++it) {
    if (used_regs_.find(*it) == used_regs_.end()) {
      graph->registers_.erase(it);
      goto again;
    }
  }
}

void DeadVariableElimination::WalkRegister(DGraph *graph, DState *state, DInsn *insn,
					   DRegister *reg, bool is_input) {
  used_regs_.insert(reg);
}

ConstantBranchElimination::ConstantBranchElimination(DGraph *graph) : graph_(graph) {
  branch_res_ = DGraphUtil::FindResource(graph_, sym_branch, true);
}

void ConstantBranchElimination::Perform() {
  DGraphWalker<ConstantBranchElimination>
    walker(this, NULL,
	   &ConstantBranchElimination::WalkInsn, NULL);
  walker.Traverse(graph_);
}

void ConstantBranchElimination::WalkInsn(DGraph *graph, DState *state, DInsn *insn) {
  if (insn->resource_ != branch_res_) {
    return;
  }
  if (insn->inputs_.size() == 0) {
    return;
  }
  DRegister *cond = *(insn->inputs_.begin());
  if (cond->reg_type_ != DRegister::REG_CONST) {
    return;
  }
  if (cond->num_ == 0) {
    // pop_front
    vector<DState*> states;
    for (size_t i = 1; i < insn->targets_.size(); ++i) {
      states.push_back(insn->targets_[i]);
    }
    //insn->targets_.pop_front();
    insn->targets_ = states;
  } else {
    insn->targets_.pop_back();
  }
  insn->inputs_.pop_back();
}

class MiscOpt : public OptimizationPhase {
public:
  MiscOpt();
  static OptimizationPhase *Create(const char *phase) {
    return new MiscOpt;
  };

  sym_t bbs_;
  sym_t urse_;
  sym_t cbe_;

  bool Perform(const char *phase, DGraph *graph, const char *note);
private:
  void DoBasicBlockShrink(DGraph *graph);
};

MiscOpt::MiscOpt() {
  bbs_ = sym_lookup("opt_basic_block_shrink");
  urse_ = sym_lookup("opt_unreachable_state_elimination");
  cbe_ = sym_lookup("opt_constant_branch_elimination");
}

void MiscOpt::DoBasicBlockShrink(DGraph *graph) {
  dfg::DGraphAnnotation an;
  GraphOptimizeStat::SetupStateAnnotation(graph);
  BasicBlockSet bset;
  BasicBlockCollector bbc(graph, &bset);
  bbc.CollectBBAll(&an);
  //
  BasicBlockShrinker bbs(graph);
  bbs.Perform(&bset.bbs_, &an);
  OptimizeContext *ctx = graph->owner_module_->GetOptimizeContext();
  ctx->DumpIntermediateGraph(graph, &an, "bb_shrink");
}

bool MiscOpt::Perform(const char *phase, DGraph *graph, const char *note) {
  sym_t phase_sym = sym_lookup(phase);
  if (phase_sym == bbs_) {
    DoBasicBlockShrink(graph);
  } else if (phase_sym == urse_) {
    UnreachableStateElimination::Perform(graph);
  } else if (phase_sym == cbe_) {
    ConstantBranchElimination cbe(graph);
    cbe.Perform();
  }
  return true;
}

class OptCleaner : public OptimizationPhase {
public:
  OptCleaner();
  virtual bool Perform(const char *phase, DGraph *graph, const char *note);
  static OptimizationPhase *Create(const char *phase) {
    return new OptCleaner;
  }
public:
  sym_t weak_;
  sym_t normal_;
};

OptCleaner::OptCleaner() {
  weak_ = sym_lookup("opt_clean_graph_weak");
  normal_ = sym_lookup("opt_clean_graph");
}

bool OptCleaner::Perform(const char *phase, DGraph *graph, const char *note) {
  bool is_strong = true;
  if (sym_lookup(phase) == weak_) {
    is_strong = false;
  }
  DeadStateElimination dse(is_strong);
  dse.Perform(graph);
  DeadVariableElimination dve;
  dve.Perform(graph);
  DeadResourceElimination::Perform(graph);
  return true;
}

CopyPropagation::CopyPropagation(bool do_dump) : do_dump_(do_dump) {
}

bool CopyPropagation::Perform(const char *phase, DGraph *graph, const char *note) {
  phi_res_ = DGraphUtil::FindResource(graph, sym_lookup("phi"), true);

  DGraphWalker<CopyPropagation>
    constant_finder(this, NULL, &CopyPropagation::ConstantAssignFinder, NULL);
  constant_finder.Traverse(graph);

  DGraphWalker<CopyPropagation>
    constant_updator(this, NULL, &CopyPropagation::UpdateConstant, NULL);
  constant_updator.Traverse(graph);

  DGraphUtil::ClearAnnotation(graph);
  if (do_dump_) {
    OptimizeContext *ctx = graph->owner_module_->GetOptimizeContext();
    ctx->DumpIntermediateGraph(graph, NULL, "constant_propagation");
  }
  return true;
}

void CopyPropagation::ConstantAssignFinder(DGraph *graph, DState *state,
					   DInsn *insn) {
  DResource *as = DGraphUtil::FindResource(graph, sym_assign, true);
  if (insn->resource_ != as) {
    return;
  }
  DRegister *input = *(insn->inputs_.begin());
  DRegister *output = *(insn->outputs_.begin());
  if (constant_map_.find(output) != constant_map_.end()) {
    // assigned more than twice.
    non_single_regs_.insert(output);
  }
  constant_map_[output] = input;
}

void CopyPropagation::UpdateConstant(DGraph *graph, DState *state, DInsn *insn) {
  if (insn->resource_ == phi_res_) {
    // skip phi for now not to lost the location. it will be processed later.
    return;
  }
  for (vector<DRegister *>::iterator it = insn->inputs_.begin();
       it != insn->inputs_.end(); ++it) {
    DRegister *assignee_reg = *it;
    if (non_single_regs_.find(assignee_reg) != non_single_regs_.end()) {
      continue;
    }
    map<DRegister *, DRegister *>::iterator jt = constant_map_.find(assignee_reg);
    if (jt == constant_map_.end()) {
      continue;
    }
    DRegister *constant_reg = jt->second;
    if (constant_reg->data_type_ != assignee_reg->data_type_) {
      CHECK(assignee_reg->data_type_->type_ != DType::ENUM)
	<< " insn->id_=" << insn->insn_id_;
      // change the width to the previous width.
      constant_reg = DGraphUtil::FindWidthNum(graph, constant_reg->num_,
					      assignee_reg->data_type_->size_);
    }
    *it = constant_reg;
  }
}

///Optimizer: Basic block shrink
///Optimizer: Unreachable state elimination
static void register_misc() {
  OptimizationPhase::registerPhase("opt_basic_block_shrink",
				   &MiscOpt::Create, NULL);
  OptimizationPhase::registerPhase("opt_unreachable_state_elimination",
				   &MiscOpt::Create, NULL);
  OptimizationPhase::registerPhase("opt_constant_branch_elimination",
				   &MiscOpt::Create, NULL);


  OptimizationPhase::registerPhase("opt_clean_graph_weak",
				   &OptCleaner::Create, NULL);
  OptimizationPhase::registerPhase("opt_clean_graph",
				   &OptCleaner::Create, NULL);
  OptimizationPhase::registerPhase("opt_copy_propagation",
				   &CopyPropagation::Create, NULL);
}

STATIC_INITIALIZER(opt_misc, register_misc());

}  // namespace opt
