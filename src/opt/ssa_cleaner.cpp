#include "opt/ssa_cleaner.h"

#include "dfg/dfg.h"
#include "opt/opt.h"
#include "opt/opt_context.h"
#include "opt/basic_block.h"
#include "opt/ssa.h"
#include "opt/dfc.h"

namespace opt {

SSACleaner::SSACleaner(DGraph *graph) : graph_(graph) {
  assign_res_ = DGraphUtil::FindResource(graph_, sym_assign, true);
  phi_res_ = DGraphUtil::FindResource(graph_, sym_lookup("phi"), true);
  selector_res_ = DGraphUtil::FindResource(graph_, sym_lookup("selector"), true);
}

void SSACleaner::Perform() {
  GraphOptimizeStat::SetupStateAnnotation(graph_);

  dfg::DGraphAnnotation ssa_clean;

  bset_.reset(new BasicBlockSet);
  BasicBlockCollector bbc(graph_, bset_.get());
  bbc.CollectBBAll(&ssa_clean);

  dfc_.reset(new DataFlowCollector(graph_, bset_.get(), &ssa_clean));
  dfc_->Perform();

  set<DefInfo *> all_defs;
  dfc_->GetAllDefs(&all_defs);
  for (set<DefInfo *>::iterator it = all_defs.begin();
       it != all_defs.end(); ++it) {
    DefInfo *di = *it;
    def_info_map_.insert(std::make_pair(di->insn, di));
  }

  for (set<BasicBlock *>::iterator it = bset_->bbs_.begin();
       it != bset_->bbs_.end(); ++it) {
    ProcessBB(*it);
  }

  OptimizeContext *ctx = graph_->owner_module_->GetOptimizeContext();
  ctx->DumpIntermediateGraph(graph_, &ssa_clean, "ssa_cleaner");

  GraphOptimizeStat::PerformPhaseByName("opt_constant_propagation",
					"", graph_);
}

void SSACleaner::ProcessBB(BasicBlock *bb) {
  set<DefInfo *> reaches;
  dfc_->GetReachDefs(bb, &reaches);
  map<DRegister *, DefInfo *> last_defs;
  for (set<DefInfo *>::iterator it = reaches.begin(); it != reaches.end();
       ++it) {
    DefInfo *di = *it;
    last_defs[di->output_reg] = di;
  }
  for (vector<DState *>::iterator it = bb->states.begin();
       it != bb->states.end(); ++it) {
    DState *st = *it;
    // copy this list to allow ProcessInsn() to modify the list.
    list<DInsn *> copied_insns = st->insns_;
    for (list<DInsn *>::iterator jt = copied_insns.begin();
	 jt != copied_insns.end(); ++jt) {
      ProcessInsn(&last_defs, st, *jt);
    }
  }
}

void SSACleaner::ProcessInsn(map<DRegister *, DefInfo *> *last_defs,
			     DState *st, DInsn *insn) {
  for (vector<DRegister *>::iterator it = insn->outputs_.begin();
       it != insn->outputs_.end(); ++it) {
    DefInfo *di = SSAUtil::GetDefInfo(def_info_map_, insn, *it);
    (*last_defs)[*it] = di;
  }
  if (insn->resource_ != phi_res_) {
    return;
  }
  if (insn->inputs_.size() == 1) {
    DInsn *assign_insn = DGraphUtil::InsnNew(graph_, assign_res_);
    SSAUtil::CopyRegisterList(insn->inputs_, &assign_insn->inputs_);
    SSAUtil::CopyRegisterList(insn->outputs_, &assign_insn->outputs_);
    st->insns_.push_back(assign_insn);
    // remove the phi.
    DStateUtil::EraseInsn(st, insn);
  } else if (insn->inputs_.size() == 2) {
    EmitSelector(last_defs, st, insn);
    // remove the phi.
    DStateUtil::EraseInsn(st, insn);
  }
}

void SSACleaner::EmitSelector(map<DRegister *, DefInfo *> *last_defs,
			      DState *st, DInsn *insn) {
  // emit conditions for both.
  DRegister *cond_reg = DGraphUtil::AllocTmpReg(graph_,
						DTypeUtil::GetBoolType());
  int nth = 0;
  for (vector<DRegister *>::iterator it = insn->inputs_.begin();
       it != insn->inputs_.end(); ++it) {
    DRegister *phi_input = *it;
    DInsn *assign_insn = DGraphUtil::InsnNew(graph_, assign_res_);
    assign_insn->outputs_.push_back(cond_reg);
    DRegister *reg_val =
      DGraphUtil::FindEnum(graph_, "", DTypeUtil::GetBoolType(), nth);
    assign_insn->inputs_.push_back(reg_val);
    DefInfo *di = (*last_defs)[phi_input];
    di->st->insns_.push_back(assign_insn);
    ++nth;
  }
  // emit a selector.
  DInsn *sel_insn = DGraphUtil::InsnNew(graph_, selector_res_);
  SSAUtil::CopyRegisterList(insn->inputs_, &sel_insn->inputs_);
  sel_insn->inputs_.push_back(cond_reg);
  DRegister *output_reg = *(insn->outputs_.begin());
  sel_insn->outputs_.push_back(output_reg);
  st->insns_.push_back(sel_insn);
}

}  // namespace opt
