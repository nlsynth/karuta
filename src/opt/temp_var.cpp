#include "opt/temp_var.h"

#include "opt/opt.h"
#include "opt/opt_context.h"
#include "opt/basic_block.h"

namespace opt {

PureTempVarElimination::~PureTempVarElimination() {
  STLDeleteSecondElements(&per_register_map_);
}

bool PureTempVarElimination::Perform(const char *phase, DGraph *graph,
				     const char *msg) {
  GraphOptimizeStat::SetupStateAnnotation(graph);
  BasicBlockSet bbs;
  BasicBlockCollector bbc(graph, &bbs);
  dfg::DGraphAnnotation an;
  bbc.CollectBBAll(&an);

  // Collect all BBs assign to the register.
  CollectAssigns(graph);
  // Block local temp var elimination.
  MarkBlockLocals();
  for (BasicBlock * bb : bbs.bbs_) {
    KillTempRegsInBB(graph, bb);
  }

  OptimizeContext *ctx = graph->owner_module_->GetOptimizeContext();
  ctx->DumpIntermediateGraph(graph, &an, "temp_var");
  return true;
}

void PureTempVarElimination::MarkBlockLocals() {
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
}

void PureTempVarElimination::CollectAssigns(DGraph *graph) {
  // Collect all BBs assign to the register.
  DResource *as = DGraphUtil::FindResource(graph, sym_assign, true);
  for (DState *st : graph->states_) {
    StateAnnotation *sa = StateAnnotation::Get(st);
    BasicBlock *bb = sa->bb_;
    for (DInsn *insn : st->insns_) {
      for (DRegister *reg : insn->inputs_) {
	PerRegister *pr = GetPerRegister(reg);
	pr->using_bbs.insert(bb);
      }
      for (DRegister *reg : insn->outputs_) {
	PerRegister *pr = GetPerRegister(reg);
	pr->using_bbs.insert(bb);
	pr->writer_states.insert(st);
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
    for (DInsn *insn : st->insns_) {
      for (vector<DRegister *>::iterator it = insn->inputs_.begin();
	   it != insn->inputs_.end(); ++it) {
	DRegister *reg = *it;
	map<DRegister *, DRegister *>::iterator jt = equiv_regs.find(reg);
	if (jt != equiv_regs.end()) {
	  // update this input to the equivalent register.
	  *it = jt->second;
	}
      }
      if (insn->resource_ == as) {
	DRegister *input = *(insn->inputs_.begin());
	DRegister *output = *(insn->outputs_.begin());
	if (IsRedundantAssign(st, insn)) {
	  // assign: @output <- @input
	  // @output can be replaced with @input.
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

bool PureTempVarElimination::IsRedundantAssign(DState *st, DInsn *insn) {
  DRegister *output = *(insn->outputs_.begin());
  PerRegister *pr_output = GetPerRegister(output);
  DRegister *input = *(insn->inputs_.begin());
  if (input->reg_type_ != DRegister::REG_NORMAL ||
      !pr_output->is_block_local) {
    return false;
  }
  PerRegister *pr_input = GetPerRegister(input);
  StateAnnotation *cur_sa = StateAnnotation::Get(st);
  for (DState *writer_state : pr_input->writer_states) {
    StateAnnotation *writer_sa = StateAnnotation::Get(writer_state);
    if (writer_sa->bb_ == cur_sa->bb_) {
      // @input might be over written in this block. so don't kill.
      // (this can be more precise by checking whether @input is over
      //  written between the read of @input and use of @output)
      return false;
    }
  }
  return true;
}

PureTempVarElimination::PerRegister *
PureTempVarElimination::GetPerRegister(DRegister *reg) {
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
