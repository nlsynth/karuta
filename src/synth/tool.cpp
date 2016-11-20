#include "synth/tool.h"

#include "iroha/iroha.h"

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

IResource *Tool::FindOrCreateSubModuleTaskCallResource(ITable *caller,
						       ITable *callee) {
  for (IResource *res : caller->resources_) {
    if (resource::IsSubModuleTaskCall(*res->GetClass()) &&
	res->GetCalleeTable() == callee) {
      return res;
    }
  }
  return DesignTool::CreateSubModuleTaskCallResource(caller, callee);
}

}  // namespace synth
