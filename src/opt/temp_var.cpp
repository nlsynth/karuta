#include "opt/temp_var.h"

#include "opt/opt.h"
#include "opt/opt_context.h"
#include "opt/basic_block.h"

namespace opt {

PureTempVarElimination::~PureTempVarElimination() {
  STLDeleteSecondElements(&per_register_map_);
}

bool PureTempVarElimination::Perform(const char *phase, DGraph *graph, const char *msg) {
  GraphOptimizeStat::SetupStateAnnotation(graph);
  BasicBlockSet bbs;
  BasicBlockCollector bbc(graph, &bbs);
  dfg::DGraphAnnotation an;
  bbc.CollectBBAll(&an);

  // Collect all BBs assign to the register.
  CollectAssigns(graph);
  // block local temp var elimination.
  for (map<DRegister *, PerRegister *>::iterator it = per_register_map_.begin();
       it != per_register_map_.end(); ++it) {
    // this register is used only in a block.
    PerRegister *pr = it->second;
    if (pr->using_bbs.size() == 1 &&
	it->first->reg_type_ == DRegister::REG_NORMAL &&
	!it->first->has_initial_) {
      pr->is_block_local = true;
    }
  }
  for (set<BasicBlock *>::iterator it = bbs.bbs_.begin(); it != bbs.bbs_.end(); ++it) {
    KillTempRegsInBB(graph, *it);
  }

  // process one time assign
  set<DInsn *> assign_once;
  map<DRegister *, DRegister *> equiv_regs;
  for (map<DRegister *, PerRegister *>::iterator it = per_register_map_.begin();
       it != per_register_map_.end(); ++it) {
    PerRegister *pr = it->second;
    DRegister *output = it->first;
    if (pr->insns_assign_to_this.size() == 1 &&
	output->reg_type_ == DRegister::REG_NORMAL &&
	!output->has_initial_) {
      DInsn *insn = *(pr->insns_assign_to_this.begin());
      DRegister *input = *(insn->inputs_.begin());
      if (input->reg_type_ == DRegister::REG_NORMAL) {
	assign_once.insert(insn);
	equiv_regs[output] = input;
      }
    }
  }
  UpdateEquiv(equiv_regs, graph);
  RemoveInsns(assign_once, graph);
  OptimizeContext *ctx = graph->owner_module_->GetOptimizeContext();
  ctx->DumpIntermediateGraph(graph, &an, "temp_var");
  return true;
}

void PureTempVarElimination::CollectAssigns(DGraph *graph) {
  // Collect all BBs assign to the register.
  DResource *as = DGraphUtil::FindResource(graph, sym_assign, true);
  for (list<DState *>::iterator it = graph->states_.begin();
       it != graph->states_.end(); it++) {
    DState *st = *it;
    StateAnnotation *sa = StateAnnotation::Get(st);
    BasicBlock *bb = sa->bb_;
    for (list<DInsn *>::iterator jt = st->insns_.begin();
	 jt != st->insns_.end(); jt++) {
      DInsn *insn = *jt;
      for (vector<DRegister *>::iterator kt = insn->inputs_.begin(); kt != insn->inputs_.end();
	   ++kt) {
	PerRegister *pr = GetPerRegister(*kt);
	pr->using_bbs.insert(bb);
      }
      for (vector<DRegister *>::iterator kt = insn->outputs_.begin(); kt != insn->outputs_.end();
	   ++kt) {
	PerRegister *pr = GetPerRegister(*kt);
	pr->using_bbs.insert(bb);
	if (insn->resource_ == as) {
	  CHECK(insn->inputs_.size() == 1);
	  pr->insns_assign_to_this.insert(insn);
	}
      }
    }
  }
}

void PureTempVarElimination::KillTempRegsInBB(DGraph *graph,
					      BasicBlock *bb) {
  map<DRegister *, DRegister *> equiv_regs;
  map<DInsn *, DState *> tmp_insns;
  DResource *as = DGraphUtil::FindResource(graph, sym_assign, true);
  for (size_t i = 0; i < bb->states.size(); ++i) {
    DState *st = bb->states[i];
    for (list<DInsn *>::iterator jt = st->insns_.begin();
	 jt != st->insns_.end(); jt++) {
      DInsn *insn = *jt;
      for (vector<DRegister *>::iterator kt = insn->inputs_.begin(); kt != insn->inputs_.end();
	   ++kt) {
	DRegister *reg = *kt;
	map<DRegister *, DRegister *>::iterator lt = equiv_regs.find(reg);
	if (lt != equiv_regs.end()) {
	  // update this input to the equivalent register.
	  *kt = lt->second;
	}
      }
      if (insn->resource_ == as) {
	DRegister *input = *(insn->inputs_.begin());
	DRegister *output = *(insn->outputs_.begin());
	PerRegister *pr = GetPerRegister(output);
	if (input->reg_type_ == DRegister::REG_NORMAL &&
	    pr->is_block_local) {
	  // assign: @output <- @input
	  // where @output is only used in this block, so all @output should be
	  // replaced with @input.
	  equiv_regs[output] = input;
	  // this insn is useless
	  tmp_insns[insn] = st;
	}
      } else {
	for (vector<DRegister *>::iterator kt = insn->outputs_.begin();
	     kt != insn->outputs_.end(); ++kt) {
	  map<DRegister *, DRegister *>::iterator lt = equiv_regs.find(*kt);
	  if (lt != equiv_regs.end()) {
	    // overwritten by non assign insn.
	    equiv_regs.erase(lt);
	  }
	}
      }
    }
  }
  while (tmp_insns.size() > 0) {
    map<DInsn *, DState *>::iterator it = tmp_insns.begin();
    LOG(INFO) << "Removing insn id:" << it->first->insn_id_;
    DStateUtil::EraseInsn(it->second, it->first);
    tmp_insns.erase(it);
  }
}

void PureTempVarElimination::UpdateEquiv(map<DRegister *, DRegister *>& equiv_map,
					 DGraph *graph) {
  for (list<DState *>::iterator it = graph->states_.begin();
       it != graph->states_.end(); it++) {
    DState *st = *it;
    for (list<DInsn *>::iterator jt = st->insns_.begin();
	 jt != st->insns_.end(); jt++) {
      DInsn *insn = *jt;
      for (vector<DRegister *>::iterator kt = insn->inputs_.begin(); kt != insn->inputs_.end();
	   ++kt) {
	DRegister *reg = equiv_map[*kt];
	if (reg) {
	  *kt = reg;
	}
      }
      for (vector<DRegister *>::iterator kt = insn->outputs_.begin(); kt != insn->outputs_.end();
	   ++kt) {
	DRegister *reg = equiv_map[*kt];
	if (reg) {
	  *kt = reg;
	}
      }
    }
  }
}

void PureTempVarElimination::RemoveInsns(set<DInsn *> &insns, DGraph *graph) {
  map<DInsn *, DState *> live_insns;
  for (list<DState *>::iterator it = graph->states_.begin();
       it != graph->states_.end(); it++) {
    DState *st = *it;
    for (list<DInsn *>::iterator jt = st->insns_.begin();
	 jt != st->insns_.end(); jt++) {
      DInsn *insn = *jt;
      if (insns.find(insn) != insns.end()) {
	live_insns[insn] = st;
      }
    }
  }

  while (live_insns.size() > 0) {
    map<DInsn *, DState *>::iterator it = live_insns.begin();
    DStateUtil::EraseInsn(it->second, it->first);
    LOG(INFO) << "Removing insn id:" << it->first->insn_id_;
    live_insns.erase(it);
  }
}

PureTempVarElimination::PerRegister *PureTempVarElimination::GetPerRegister(DRegister *reg) {
  PerRegister *pr;
  map<DRegister *, PerRegister *>::iterator it = per_register_map_.find(reg);
  if (it == per_register_map_.end()) {
    pr = new PerRegister;
    pr->is_block_local = false;
    per_register_map_.insert(std::make_pair(reg, pr));
  } else {
    pr = it->second;
  }
  return pr;
}

///Optimizer: Pure Temp Variable elimination
static void register_temp_var() {
  OptimizationPhase::registerPhase("opt_pure_temp_variable_elimination",
				   &PureTempVarElimination::Create, NULL);
}

STATIC_INITIALIZER(opt_temp_var, register_temp_var());

}  // namespace opt
