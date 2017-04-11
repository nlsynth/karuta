#include "synth/tool.h"

#include "iroha/iroha.h"
#include "synth/resource_set.h"

namespace synth {

void Tool::SetNextState(IState *cur, IState *next) {
  IInsn *tr_insn = DesignUtil::GetTransitionInsn(cur);
  tr_insn->target_states_.clear();
  DesignTool::AddNextState(cur, next);
}

IState *Tool::GetNextState(IState *st) {
  IInsn *insn = DesignUtil::FindTransitionInsn(st);
  if (insn == nullptr) {
    return nullptr;
  }
  if (insn->target_states_.size() != 1) {
    return nullptr;
  }
  return insn->target_states_[0];
}

IResource *Tool::FindOrCreateTaskCallResource(ITable *caller,
					      ITable *callee) {
  for (IResource *res : caller->resources_) {
    if (resource::IsTaskCall(*res->GetClass()) &&
	res->GetCalleeTable() == callee) {
      return res;
    }
  }
  return DesignTool::CreateTaskCallResource(caller, callee);
}

void Tool::InjectDataFlowIn(IState *initialSt, ResourceSet *rset) {
  ITable *tab = initialSt->GetTable();
  IInsn *wait_insn = nullptr;
  IState *wait_st = nullptr;
  int insn_idx;
  for (int i = 0; i < tab->states_.size(); ++i) {
    IState *st = tab->states_[i];
    int idx = 0;
    for (IInsn *insn : st->insns_) {
      if (insn->GetOperand() == iroha::operand::kWaitNotify) {
	wait_insn = insn;
	wait_st = st;
	insn_idx = idx;
      }
      ++idx;
    }
    if (wait_insn != nullptr) {
      break;
    }
  }
  // Replace wait_insn with new DataFlowIn resource.
  CHECK(wait_insn);
  wait_st->insns_.erase(wait_st->insns_.begin() + insn_idx);
  IResource *res = rset->GetDataFlowInResource();
  res->SetParentResource(wait_insn->GetResource()->GetParentResource());
  IInsn *insn = new IInsn(res);
  initialSt->insns_.push_back(insn);
  for (IRegister *reg : wait_insn->outputs_) {
    insn->outputs_.push_back(reg);
  }
}

}  // namespace synth
