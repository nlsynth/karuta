// ssa
#include "opt/ssa.h"

#include <stdio.h>

#include "dfg/dfg.h"
#include "dfg/dfg_util.h"
#include "opt/opt.h"
#include "opt/basic_block.h"
#include "opt/dfc.h"
#include "opt/ssa_converter.h"
#include "opt/ssa_cleaner.h"
#include "opt/misc.h"
#include "sym.h"

namespace opt {

void SSA::Init() {
}

void SSA::Perform(DGraph *graph) {
  SSAConverter converter(graph);
  converter.Perform();
}

void SSA::Cleanup(DGraph *graph) {
  SSACleaner cleaner(graph);
  cleaner.Perform();
}

void SSAUtil::CollectSingularRegister(DataFlowCollector *dfc,
				      BasicBlockSet *bset,
				      set<DRegister *> *singular_regs) {
  map<DRegister *, set<DInsn *> > define_insns;
  for (BasicBlock *bb : bset->bbs_) {
    set<DefInfo *> reaches;
    dfc->GetReachDefs(bb, &reaches);
    map<DRegister *, set<DInsn *> > local_define_insns;
    // fill initial value by reaching assignments.
    for (DefInfo *di : reaches) {
      local_define_insns[di->output_reg].insert(di->insn);
    }
    for (size_t i = 0; i < bb->states.size(); ++i) {
      DState *st = bb->states[i];
      for (list<DInsn *>::iterator jt = st->insns_.begin();
	   jt != st->insns_.end(); ++jt) {
	DInsn *insn = *jt;
	for (vector<DRegister *>::iterator kt = insn->inputs_.begin();
	     kt != insn->inputs_.end();
	     ++kt) {
	  set<DInsn *> &s = local_define_insns[*kt];
	  for (set<DInsn *>::iterator lt = s.begin(); lt != s.end(); ++lt) {
	    define_insns[*kt].insert(*lt);
	  }
	}
      }
      // update write insns.
      for (list<DInsn *>::iterator jt = st->insns_.begin();
	   jt != st->insns_.end(); ++jt) {
	DInsn *insn = *jt;
	for (vector<DRegister *>::iterator kt = insn->outputs_.begin();
	     kt != insn->outputs_.end();
	     ++kt) {
	  // overwrite by this 1 assignment insn.
	  set<DInsn *> s;
	  s.insert(insn);
	  local_define_insns[*kt] = s;
	}
      }
    }
  }
  for (map<DRegister *, set<DInsn *> >::iterator it = define_insns.begin();
       it != define_insns.end(); ++it) {
    set<DInsn *> &s = it->second;
    DRegister *reg = it->first;
    if (s.size() == 1 && reg->reg_type_ == DRegister::REG_NORMAL) {
      //cout << "singular " << DFG::RegisterName(reg) << "\n";
      singular_regs->insert(reg);
    }
  }
}

void SSAUtil::CopyRegisterList(vector<DRegister *> &src,
			       vector<DRegister *> *dst) {
  for (vector<DRegister *>::iterator it = src.begin(); it != src.end(); ++it) {
    dst->push_back(*it);
  }
}

void SSAUtil::PrependState(DGraph *graph, DState *st) {
  DState *second_state = DStateUtil::GetNextState(graph, st);
  DState *new_state = DGraphUtil::AllocStateNext(graph, st);
  DStateUtil::SetNextState(graph, st, new_state);
  if (second_state == st) {
    // terminal state.
    // (st)
    // new_state -> new_state
    DStateUtil::SetNextState(graph, new_state, new_state);
  } else {
    DStateUtil::SetNextState(graph, new_state, second_state);
  }
  // move insns from st to new_state
  DResource *br = DGraphUtil::FindResource(graph, sym_branch, true);
  while (st->insns_.size() > 1) {
    for (DInsn *insn : st->insns_) {
      if (insn->resource_ != br) {
	DStateUtil::MoveInsn(insn, st, new_state);
	break;
      }
    }
  }
}

DefInfo *SSAUtil::GetDefInfo(multimap<DInsn *, DefInfo *> &def_info_map, DInsn *insn,
			     DRegister *output_reg) {
  size_t count = def_info_map.count(insn);
  if (count == 0) {
    return NULL;
  }
  multimap<DInsn *, DefInfo *>::iterator it = def_info_map.find(insn);
  for (size_t i = 0; i < count; ++i) {
    DefInfo *di = it->second;
    if (di->output_reg == output_reg) {
      return di;
    }
    ++it;
  }
  return NULL;
}


class SSAOpt : public OptimizationPhase {
public:
  virtual bool Perform(const char *phase, DGraph *graph, const char *note) {
    if (!strcmp(phase, "opt_ssa")) {
      SSA::Perform(graph);
    } else if (!strcmp(phase, "opt_ssa_cleanup")) {
      SSA::Cleanup(graph);
    }
    return false;
  }
  static OptimizationPhase *Create(const char *phase) {
    return new SSAOpt;
  }
};

///Optimizer: SSA Converter
///Optimizer: Un-SSA Converter
static void register_ssa() {
  OptimizationPhase::registerPhase("opt_ssa", &SSAOpt::Create, NULL);
  OptimizationPhase::registerPhase("opt_ssa_cleanup", &SSAOpt::Create, NULL);
}

STATIC_INITIALIZER(ssa, register_ssa());

}  // namespace opt
