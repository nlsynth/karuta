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
  IResource *res = DesignTool::CreateTaskCallResource(caller, callee);
  IInsn *task_entry = DesignUtil::FindTaskEntryInsn(callee);
  IResource *entry = task_entry->GetResource();
  // copy arg types
  for (auto &iv : entry->output_types_) {
    res->input_types_.push_back(iv);
  }
  return res;
}

IResource *Tool::FindOrCreateTaskReturnValueResource(ITable *caller,
						     ITable *callee) {
  // Find the return value writer.
  IState *return_st = callee->states_[callee->states_.size() - 1];
  IResource *writer = nullptr;
  for (IInsn *insn : return_st->insns_) {
    if (resource::IsSharedRegWriter(*insn->GetResource()->GetClass())) {
      writer = insn->GetResource();
    }
  }
  if (writer == nullptr) {
    return nullptr;
  }
  IResource *return_reg = writer->GetParentResource();
  for (IResource *res : caller->resources_) {
    if (res->GetParentResource() == return_reg) {
      return res;
    }
  }
  IResource *res = DesignTool::CreateSharedRegReaderResource(caller,
							     return_reg);
  return res;
}

IInsn *Tool::FindArgInsn(ITable *tab, IResource *arg_res) {
  for (size_t i = 0; i < tab->states_.size(); ++i) {
    IState *st = tab->states_[i];
    for (IInsn *insn : st->insns_) {
      if (insn->GetResource() == arg_res) {
	return insn;
      }
    }
  }
  return nullptr;
}

IResource *Tool::FindOrCreateDataFlowCaller(ITable *caller,
					    IResource *sreg) {
  for (IResource *res : caller->resources_) {
    if (res->GetParentResource() == sreg) {
      return res;
    }
  }
  IResource *res = DesignTool::CreateSharedRegWriterResource(caller,
							     sreg);
  return res;
}

IResource *Tool::FindOrCreateExtStubCallResource(ITable *caller,
						 const string &name) {
  for (IResource *res : caller->resources_) {
    if (resource::IsExtTaskCall(*res->GetClass())) {
      if (res->GetParams()->GetExtTaskName() == name) {
	return res;
      }
    }
  }
  IResourceClass *rc =
    DesignUtil::FindResourceClass(caller->GetModule()->GetDesign(),
				  resource::kExtTaskCall);
  IResource *call = new IResource(caller, rc);
  caller->resources_.push_back(call);
  call->GetParams()->SetExtTaskName(name);
  return call;
}

IResource *Tool::FindOrCreateExtStubWaitResource(ITable *caller,
						 const string &name) {
  for (IResource *res : caller->resources_) {
    if (resource::IsExtTaskWait(*res->GetClass())) {
      if (res->GetParentResource()->GetParams()->GetExtTaskName() == name) {
	return res;
      }
    }
  }
  IResource *call = FindOrCreateExtStubCallResource(caller, name);
  IResourceClass *rc =
    DesignUtil::FindResourceClass(caller->GetModule()->GetDesign(),
				  resource::kExtTaskWait);
  IResource *wait = new IResource(caller, rc);
  caller->resources_.push_back(wait);
  wait->SetParentResource(call);
  return wait;
}

}  // namespace synth
