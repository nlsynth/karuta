#include "opt/ssa_converter.h"

#include <stdio.h>

#include "dfg/dfg.h"
#include "opt/opt.h"
#include "opt/opt_context.h"
#include "opt/basic_block.h"
#include "opt/dfc.h"
#include "opt/dominator.h"
#include "opt/ssa.h"

namespace opt {

class RegisterVersionManager {
public:
  RegisterVersionManager(DGraph *graph) : graph_(graph) {
  }
  ~RegisterVersionManager();

  int GetVersionFromDefInfo(DefInfo *di);
  DRegister *FindVersionedReg(DefInfo *di);
private:
  DGraph *graph_;
  struct PerRegister {
    map<int, DRegister *> versions_;
  };
  map<DRegister *, PerRegister *> reg_info_;
  map<DefInfo *, int> def_versions_;
};

RegisterVersionManager::~RegisterVersionManager() {
  STLDeleteSecondElements(&reg_info_);
}

int RegisterVersionManager::GetVersionFromDefInfo(DefInfo *di) {
  map<DefInfo *, int>::iterator it = def_versions_.find(di);
  if (it == def_versions_.end()) {
    int v = def_versions_.size() + 1;
    def_versions_[di] = v;
    return v;
  }
  return it->second;
}

DRegister *RegisterVersionManager::FindVersionedReg(DefInfo *di) {
  PerRegister *pr = reg_info_[di->output_reg];
  if (!pr) {
    pr = new PerRegister;
    reg_info_[di->output_reg] = pr;
  }
  int version = GetVersionFromDefInfo(di);
  DRegister *reg = pr->versions_[version];
  if (!reg) {
    char buf[12];
    sprintf(buf, "_v%d", version);
    string name = di->output_reg->reg_name_ + string(buf);
    reg = DGraphUtil::FindSym(graph_, name,
			      di->output_reg->data_type_);
    pr->versions_[version] = reg;
  }
  return reg;
}

SSAConverter::SSAConverter(DGraph *graph) : graph_(graph) {
  sym_t sym_phi = sym_lookup("phi");
  phi_res_ = DGraphUtil::FindResource(graph_, sym_phi, true);
  rvm_.reset(new RegisterVersionManager(graph));
}

SSAConverter::~SSAConverter() {
  STLDeleteSecondElements(&reg_phis_map_);
  STLDeleteValues(&phis_);
}

void SSAConverter::Perform() {
  dfg::DGraphAnnotation ssa_prep;
  PreparePHI(&ssa_prep);
  dfg::DGraphAnnotation ssa_calc;
  CalculatePHI(&ssa_calc);
}

void SSAConverter::PreparePHI(dfg::DGraphAnnotation *an) {
  GraphOptimizeStat::SetupStateAnnotation(graph_);
  bset_.reset(new BasicBlockSet);
  BasicBlockCollector bbc(graph_, bset_.get());
  bbc.CollectBBAll(an);

  dfc_.reset(new DataFlowCollector(graph_, bset_.get(), an));
  dfc_->Perform();
  dtb_.reset(new DominatorTreeBuilder(graph_, bset_.get(), an));
  dtb_->Perform();

  SSAUtil::CollectSingularRegister(dfc_.get(),
				   bset_.get(), &singular_regs_);
  for (DRegister *reg : graph_->registers_) {
    if (reg->reg_type_ != DRegister::REG_NORMAL) {
      continue;
    }
    reg_phis_map_[reg] = new PerRegister;
  }

  CollectOriginalDefs();
  PropagatePHIs();
  CommitPHIInsn();

  DumpPerRegister(an);

  OptimizeContext *ctx = graph_->owner_module_->GetOptimizeContext();
  ctx->DumpIntermediateGraph(graph_, an, "ssa_prep");
}

void SSAConverter::CollectOriginalDefs() {
  for (set<BasicBlock *>::iterator it = bset_->bbs_.begin();
       it != bset_->bbs_.end(); ++it) {
    set<DefInfo *> reach_defs;
    dfc_->GetReachDefs(*it, &reach_defs);
    for (set<DefInfo *>::iterator jt = reach_defs.begin();
	 jt != reach_defs.end(); ++jt) {
      DefInfo *di = *jt;
      if (IsSingularReg(di->output_reg)) {
	continue;
      }
      PerRegister *pr = GetPerRegister(di->output_reg);
      pr->original_defs_.insert(di);
    }
  }
}

SSAConverter::PerRegister *SSAConverter::GetPerRegister(DRegister *reg) {
  return reg_phis_map_[reg];
}

bool SSAConverter::IsSingularReg(DRegister *reg) {
  return singular_regs_.find(reg) != singular_regs_.end();
} 

void SSAConverter::DumpPerRegister(dfg::DGraphAnnotation *an) {
  ostream &os = an->SummaryAnnotation();
  os << "per register<br>\n";
  for (map<DRegister *, PerRegister *>::iterator it = reg_phis_map_.begin();
       it != reg_phis_map_.end(); ++it) {
    PerRegister *pr = it->second;
    if (pr->original_defs_.size() == 0) {
      continue;
    }
    os << dfg::DFG::RegisterName(it->first) << "::";
    for (set<DefInfo *>::iterator jt = pr->original_defs_.begin();
	 jt != pr->original_defs_.end(); ++jt) {
      DefInfo *di = *jt;
      os << " " << di->ToString();
    }
    for (set<BasicBlock *>::iterator jt = pr->phi_bbs_.begin();
	 jt != pr->phi_bbs_.end(); ++jt) {
      os << " bb:" << (*jt)->bb_id;
    }
    os << "<br>\n";
  }
  an->Flush();
}

void SSAConverter::PropagatePHIs() {
  for (map<DRegister *, PerRegister *>::iterator it = reg_phis_map_.begin();
       it != reg_phis_map_.end(); ++it) {
    PerRegister *pr = it->second;
    // Step 1. generate phi from original assigns.
    for (set<DefInfo *>::iterator jt = pr->original_defs_.begin();
	 jt != pr->original_defs_.end();
	 ++jt) {
      PropagatePHIforBB(pr, (*jt)->bb);
    }
    // Step 2. generate phi from original assigns.
    size_t num_phis;
    do {
      num_phis = pr->phi_bbs_.size();
      set<BasicBlock *> current_phis = pr->phi_bbs_;
      for (set<BasicBlock *>::iterator it = current_phis.begin();
	   it != current_phis.end(); ++it) {
	PropagatePHIforBB(pr, *it);
      }
    } while (num_phis != pr->phi_bbs_.size());
  }
}

void SSAConverter::PropagatePHIforBB(PerRegister *pr, BasicBlock *bb) {
  vector<BasicBlock *> frontiers;
  dtb_->GetFrontier(bb, &frontiers);
  for (vector<BasicBlock *>::iterator it = frontiers.begin();
       it != frontiers.end(); ++it) {
    pr->phi_bbs_.insert(*it);
  }
}

void SSAConverter::CommitPHIInsn() {
  // allocate states for new insns.
  set<BasicBlock *> bbs;
  for (map<DRegister *, PerRegister *>::iterator it = reg_phis_map_.begin();
       it != reg_phis_map_.end(); ++it) {
    PerRegister *pr = it->second;
    for (set<BasicBlock *>::iterator jt = pr->phi_bbs_.begin();
	 jt != pr->phi_bbs_.end(); ++jt) {
      bbs.insert(*jt);
    }
  }
  for (set<BasicBlock *>::iterator it = bbs.begin(); it != bbs.end(); ++it) {
    BasicBlock *bb = *it;
    SSAUtil::PrependState(graph_, bb->states[0]);
  }
  // allocate insns.
  for (map<DRegister *, PerRegister *>::iterator it = reg_phis_map_.begin();
       it != reg_phis_map_.end(); ++it) {
    PerRegister *pr = it->second;
    for (set<BasicBlock *>::iterator jt = pr->phi_bbs_.begin();
	 jt != pr->phi_bbs_.end(); ++jt) {
      DInsn *insn = DGraphUtil::InsnNew(graph_, phi_res_);
      insn->outputs_.push_back(it->first);
      BasicBlock *bb = *jt;
      bb->states[0]->insns_.push_back(insn);
    }
  }
}

void SSAConverter::CalculatePHI(dfg::DGraphAnnotation *an) {
  // update basic block related objects to catch up graph changes.
  GraphOptimizeStat::SetupStateAnnotation(graph_);
  bset_.reset(new BasicBlockSet);
  BasicBlockCollector bbc(graph_, bset_.get());
  bbc.CollectBBAll(an);

  dfc_.reset(new DataFlowCollector(graph_, bset_.get(), an));
  dfc_->Perform();

  for (set<BasicBlock *>::iterator it = bset_->bbs_.begin(); it != bset_->bbs_.end(); ++it) {
    CalculatePHIInputsforBB(*it);
  }

  for (vector<PHI *>::iterator it = phis_.begin(); it != phis_.end(); ++it) {
    UpdatePHIInputs(*it);
  }

  set<DefInfo *> all_defs;
  dfc_->GetAllDefs(&all_defs);
  for (set<DefInfo *>::iterator it = all_defs.begin(); it != all_defs.end(); ++it) {
    DefInfo *di = *it;
    def_info_map_.insert(std::make_pair(di->insn, di));
  }

  for (set<BasicBlock *>::iterator it = bset_->bbs_.begin(); it != bset_->bbs_.end(); ++it) {
    UpdateVersionsForBB(*it);
  }

  DumpPHIs(an);

  OptimizeContext *ctx = graph_->owner_module_->GetOptimizeContext();
  ctx->DumpIntermediateGraph(graph_, an, "ssa_calc");
}

void SSAConverter::CalculatePHIInputsforBB(BasicBlock *bb) {
  set<DInsn *> phis;
  for (list<DInsn *>::iterator it = bb->states[0]->insns_.begin();
       it != bb->states[0]->insns_.end(); ++it) {
    DInsn *insn = *it;
    if (insn->resource_ == phi_res_) {
      phis.insert(insn);
    }
  }
  set<DefInfo *> reaches;
  dfc_->GetReachDefs(bb, &reaches);
  map<DRegister *, set<DefInfo *> > per_reg_defs;
  for (set<DefInfo *>::iterator it = reaches.begin(); it != reaches.end(); ++it) {
    DefInfo *di = *it;
    per_reg_defs[di->output_reg].insert(di);
  }
  for (set<DInsn *>::iterator it = phis.begin(); it != phis.end(); ++it) {
    DInsn *insn = *it;
    DRegister *reg = *(insn->outputs_.begin());
    set<DefInfo *>& reaching = per_reg_defs[reg];
    PHI *phi = new PHI;
    phi->insn_ = insn;
    phi->defs_ = reaching;
    phis_.push_back(phi);
  }
}

void SSAConverter::UpdatePHIInputs(PHI *phi) {
  for (set<DefInfo *>::iterator it = phi->defs_.begin(); it != phi->defs_.end(); ++it) {
    DefInfo *di = *it;
    DRegister *reg = rvm_->FindVersionedReg(di);
    phi->insn_->inputs_.push_back(reg);
  }
}

void SSAConverter::UpdateVersionsForBB(BasicBlock *bb) {
  set<DefInfo *> reaches;
  dfc_->GetReachDefs(bb, &reaches);
  map<DRegister *, DefInfo *> last_defs;
  for (set<DefInfo *>::iterator it = reaches.begin(); it != reaches.end(); ++it) {
    DefInfo *di = *it;
    last_defs[di->output_reg] = di;
  }
  for (vector<DState *>::iterator it = bb->states.begin(); it != bb->states.end(); ++it) {
    DState *st = *it;
    for (list<DInsn *>::iterator jt = st->insns_.begin(); jt != st->insns_.end(); ++jt) {
      UpdateVersionsForInsn(&last_defs, *jt);
    }
  }
}

void SSAConverter::UpdateVersionsForInsn(map<DRegister *, DefInfo *> *last_defs, DInsn *insn) {
  if (insn->resource_ != phi_res_) {
    for (vector<DRegister *>::iterator it = insn->inputs_.begin(); it != insn->inputs_.end(); ++it) {
      DRegister *reg = *it;
      if (last_defs->find(reg) != last_defs->end()) {
	DefInfo *di = (*last_defs)[reg];
	*it = rvm_->FindVersionedReg(di);
      }
    }
  }
  for (vector<DRegister *>::iterator it = insn->outputs_.begin(); it != insn->outputs_.end(); ++it) {
    DefInfo *di = SSAUtil::GetDefInfo(def_info_map_, insn, *it);
    (*last_defs)[di->output_reg] = di;
    *it = rvm_->FindVersionedReg(di);
  }
}

void SSAConverter::DumpPHIs(dfg::DGraphAnnotation *an) {
  ostream &os = an->SummaryAnnotation();
  os << "per phi<br>\n";
  for (vector<PHI *>::iterator it = phis_.begin(); it != phis_.end(); ++it) {
    PHI *phi = *it;
    os << phi->insn_->insn_id_;
    for (set<DefInfo *>::iterator jt = phi->defs_.begin(); jt != phi->defs_.end(); ++jt) {
      DefInfo *di = *jt;
      os << " " << di->ToString();
    }
    os << "<br>\n";
  }
  an->Flush();
}

}  // namespace opt
