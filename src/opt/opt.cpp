// Copyright (C) Yusuke Tabata 2007-2015
//
// ModuleOptimizeStat::Optimize() will be called from outside
//
// "dead state" does nothing and just transitions to next state
//

#include "opt.h"

#include <string.h>

#include "dfg/dfg.h"
#include "messages.h"
#include "nli.h"
#include "opt/basic_block.h"
#include "opt/resource_annotation.h"
#include "opt/opt_context.h"
#include "opt/opt_phase.h"

namespace opt {

StateAnnotation::StateAnnotation(DState *state) : nr_join_(0),
						  nr_branch_(0),
						  nth_state_(0),
						  bb_(NULL),
						  state_(state) {
}

void StateAnnotation::Output(ostream &os) {
  os << nr_join_ << "," << nr_branch_ << ":";
  if (bb_) {
    os << bb_->bb_id << ",";
  }
}

StateAnnotation *StateAnnotation::Get(DState *ds) {
  return (StateAnnotation *)ds->annotation_;
}

class InsnAnnotation : public DAnnotation {
public:
  InsnAnnotation();
  virtual ~InsnAnnotation() {};

  virtual void Output(ostream &os);

  // profile count
  int count_;
};

InsnAnnotation::InsnAnnotation() {
  count_ = 0;
}

void InsnAnnotation::Output(ostream &os) {
  os << "(p " << count_ << ")";
}

static InsnAnnotation *get_insn_annotation(DInsn *insn) {
  return (InsnAnnotation *)insn->annotation_;
}

void Profiler::SetInsnPassCount(DInsn *insn, int count) {
  if (!insn->annotation_) {
    insn->annotation_ = new InsnAnnotation();
  }
  InsnAnnotation *an = get_insn_annotation(insn);
  an->count_ = count;
}

void GraphOptimizeStat::PerformPhase(const char *phase,
				     OptimizationPhase *opt, const char *note,
				     DGraph *graph) {
  if (opt) {
    opt->Perform(phase, graph, note);
    DGraphUtil::ClearAnnotation(graph);
  } else {
    Message::os(Message::USER) << "unknown optimization phase:" << phase;
    MessageFlush(Message::USER);
  }
}

void GraphOptimizeStat::PerformPhaseByName(const char *phase, const char *note,
					   DGraph *graph) {
  OptimizationPhase *opt = OptimizationPhase::getPhase(phase);
  if (opt) {
    PerformPhase(phase, opt, note, graph);
    delete opt;
  }
}

void GraphOptimizeStat::SetupStateAnnotation(DGraph *graph) {
  DGraphUtil::ClearAnnotation(graph);
  // Sets annotations for all states
  set<DState *> reachable;
  DStateUtil::CollectReachable(graph, graph->initial_state_, &reachable);

  for (set<DState *>::iterator it = reachable.begin();
       it != reachable.end(); it++) {
    (*it)->annotation_ = new StateAnnotation(*it);
  }
  // Count join and branch for each state
  CollectTransitionInfo(graph, reachable);
}

void GraphOptimizeStat::CollectTransitionInfo(DGraph *graph,
					      set<DState *> &reachable) {
  DResource *br = DGraphUtil::FindResource(graph, sym_branch, true);
  for (set<DState *>::iterator it = reachable.begin();
       it != reachable.end(); it++) {
    StateAnnotation *cur = StateAnnotation::Get(*it);
    DInsn *br_insn = DStateUtil::FindInsnByResource(*it, br);
    // current state
    cur->nr_branch_ = br_insn->targets_.size();
    // target states
    for (vector<DState *>::iterator jt = br_insn->targets_.begin();
	 jt != br_insn->targets_.end(); jt++) {
      StateAnnotation *target = StateAnnotation::Get(*jt);
      target->nr_join_ ++;
      target->prev_states_.push_back(cur);
      cur->next_states_.push_back(target);
    }
  }
}

// top level function for optimizer
void ModuleOptimizeStat::Optimize(DModule *mod, const string &phase,
				  const char *note) {
  if (mod->GetOptimizeContext()->IsSet(OptimizeContext::SynthReady)) {
    LOG(INFO) << "Module is already optimized";
    return;
  }
  if (phase.empty()) {
    return;
  }
  // set up
  list<DGraph *> target_graphs;
  CollectGraphs(mod, &target_graphs);

  ApplyOptimization(&target_graphs, mod, phase, note);

  if (phase == string(kOptSynth)) {
    // performs last steps of optimization
    OptimizeContext *ctx = mod->GetOptimizeContext();
    ctx->DumpIntermediateModule(NULL, "optimized");
    dfg::DModuleUtil::ClearAnnotation(mod);
    // low level optimization
    ApplyOptimization(&target_graphs, mod,
		      kOptCleanGraph, NULL);
    for (list<DGraph *>::iterator it = target_graphs.begin();
	 it != target_graphs.end(); it++) {
      opt::ll_optimize_graph((*it), 1);
    }
    ctx->DumpIntermediateModule(NULL, "ll");
    // clean up
    DModuleUtil::ClearAnnotation(mod);
    mod->GetOptimizeContext()->SetFlag(OptimizeContext::SynthReady);
  }
}

void ModuleOptimizeStat::CollectGraphs(DModule *mod,
				       list<DGraph *> *targets) {
  if (mod->graph_) {
    targets->push_back(mod->graph_);
  }
  for (vector<DModule *>::iterator it = mod->sub_modules_.begin();
       it != mod->sub_modules_.end(); it++) {
    CollectGraphs(*it, targets);
  }
}

void ModuleOptimizeStat::ApplyOptimization(list<DGraph *> *opts,
					   DModule *mod, const string &phase,
					   const char *note) {
  sym_t phase_sym = sym_lookup(phase.c_str());
  LOG(PHASE) << "performing " << phase;
  if (phase == string(kOptSynth)) {
    // kill unused pseudo resource.
    phase_sym = sym_lookup("opt_clean_graph");
  }
  if (phase_sym == sym_lookup("opt_ssa") &&
      mod->GetOptimizeContext()->IsSet(OptimizeContext::RegisterShare)) {
    Message::os(Message::USER)
      << "Can't perform SSA optimization after register sharing";
    MessageFlush(Message::USER);
    return;
  }
  OptimizeContext *ctx = mod->GetOptimizeContext();
  ctx->BeginPhase(phase.c_str());
  for (list<DGraph *>::iterator it = opts->begin();
       it != opts->end(); it++) {
    OptimizationPhase *opt = OptimizationPhase::getPhase(phase.c_str());
    if (opt) {
      GraphOptimizeStat::PerformPhase(phase.c_str(), opt, note, *it);
      delete opt;
    }
  }
  ctx->EndPhase();
  if (phase_sym == sym_lookup("opt_register_share")) {
    mod->GetOptimizeContext()->ClearFlag(OptimizeContext::SSAForm);
    mod->GetOptimizeContext()->SetFlag(OptimizeContext::RegisterShare);
  }
  if (phase_sym == sym_lookup("opt_ssa")) {
    mod->GetOptimizeContext()->SetFlag(OptimizeContext::SSAForm);
  }
}

}  // namespace opt
