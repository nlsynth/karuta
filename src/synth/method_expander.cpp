#include "synth/method_expander.h"

#include "iroha/i_design.h"
#include "iroha/iroha.h"
#include "synth/method_context.h"
#include "synth/object_synth.h"
#include "synth/resource_set.h"
#include "synth/thread_synth.h"
#include "synth/tool.h"
#include "vm/object.h"

namespace synth {

MethodExpander::MethodExpander(MethodContext *root, ThreadSynth *thr_synth,
                               vector<TableCall> *table_calls)
    : root_method_(root),
      thr_synth_(thr_synth),
      tab_(thr_synth->GetITable()),
      table_calls_(table_calls) {}

bool MethodExpander::Expand() {
  for (IRegister *reg : tab_->registers_) {
    thr_synth_->AddName(reg->GetName());
  }
  CalleeInfo ci = ExpandMethod(root_method_);
  tab_->SetInitialState(ci.initial);
  return true;
}

CalleeInfo MethodExpander::ExpandMethod(MethodContext *method) {
  map<IState *, IState *> st_copy_map;
  map<IRegister *, IRegister *> reg_copy_map;
  // Copy registers.
  for (auto &sw : method->states_) {
    IState *ost = sw->state_;
    IState *nst = new IState(ost->GetTable());
    st_copy_map[ost] = nst;
    for (IInsn *insn : ost->insns_) {
      BuildInsnRegCopy(insn, reg_copy_map);
    }
  }
  BuildInsnRegCopy(method->method_signature_insn_, reg_copy_map);
  // Copy states.
  map<IInsn *, IInsn *> insn_copy_map;
  for (StateWrapper *sw : method->states_) {
    IState *st = sw->state_;
    IState *nst = st_copy_map[st];
    tab_->states_.push_back(nst);
    CopyState(st, st_copy_map, reg_copy_map, nst, insn_copy_map);
  }
  CopyDependingInsns(method, insn_copy_map);
  CollectTableCalls(method, st_copy_map);
  ExpandCalleeStates(method, st_copy_map, reg_copy_map);
  // Add registers.
  for (auto it : reg_copy_map) {
    IRegister *nreg = it.second;
    if (!nreg->IsConst()) {
      tab_->registers_.push_back(nreg);
    }
  }
  CalleeInfo p;
  p.initial = st_copy_map[method->states_[0]->state_];
  p.final = st_copy_map[(*(method->states_.rbegin()))->state_];
  for (IRegister *reg : method->method_signature_insn_->inputs_) {
    p.args.push_back(reg_copy_map[reg]);
  }
  for (IRegister *reg : method->method_signature_insn_->outputs_) {
    p.rets.push_back(reg_copy_map[reg]);
  }
  return p;
}

void MethodExpander::CollectTableCalls(MethodContext *method,
                                       map<IState *, IState *> &st_map) {
  // sub obj call resource.
  IResource *pseudo = thr_synth_->GetResourceSet()->PseudoCallResource();
  for (StateWrapper *sw : method->states_) {
    if (!(sw->is_sub_obj_call_ || sw->is_data_flow_call_ ||
          sw->is_ext_stub_call_)) {
      continue;
    }
    TableCall call;
    IState *st = st_map[sw->state_];
    call.call_insn = DesignUtil::FindInsnByResource(st, pseudo);
    call.call_state = st;
    call.caller_thread = thr_synth_;
    call.callee_obj = sw->callee_vm_obj_;
    call.callee_func = sw->callee_func_name_;
    vm::Value *value = call.callee_obj->LookupValue(
        sym_lookup(call.callee_func.c_str()), false);
    CHECK(value && value->type_ == vm::Value::METHOD);
    call.callee_method = value->method_;
    if (sw->is_sub_obj_call_) {
      call.is_sub_obj_call = true;
    } else if (sw->is_data_flow_call_) {
      call.is_data_flow_call = true;
    } else if (sw->is_ext_stub_call_) {
      call.is_ext_stub_call = true;
      call.is_ext_flow_stub_call = sw->is_ext_flow_stub_call_;
    } else {
      CHECK(false);
    }
    table_calls_->push_back(call);
  }
}

void MethodExpander::ExpandCalleeStates(
    MethodContext *method, map<IState *, IState *> &st_map,
    map<IRegister *, IRegister *> &reg_map) {
  // call resource.
  IResource *pseudo = thr_synth_->GetResourceSet()->PseudoCallResource();
  for (StateWrapper *sw : method->states_) {
    if (sw->callee_func_name_.empty()) {
      continue;
    }
    if (sw->is_sub_obj_call_ || sw->is_data_flow_call_ ||
        sw->is_ext_stub_call_) {
      continue;
    }
    MethodContext *callee =
        thr_synth_->GetMethodContext(sw->callee_vm_obj_, sw->callee_func_name_);
    CalleeInfo ci = ExpandMethod(callee);
    IState *rs = Tool::GetNextState(sw->state_);
    Tool::SetNextState(st_map[sw->state_], ci.initial);
    Tool::SetNextState(ci.final, st_map[rs]);
    IInsn *call_insn = DesignUtil::FindInsnByResource(sw->state_, pseudo);
    CHECK(call_insn->inputs_.size() == ci.args.size());
    IResource *assign = thr_synth_->GetResourceSet()->AssignResource();
    // Set up call arguments.
    for (size_t i = 0; i < call_insn->inputs_.size(); ++i) {
      IInsn *assign_insn = new IInsn(assign);
      assign_insn->inputs_.push_back(reg_map[call_insn->inputs_[i]]);
      assign_insn->outputs_.push_back(ci.args[i]);
      st_map[sw->state_]->insns_.push_back(assign_insn);
    }
    // Get return values.
    for (size_t i = 0; i < call_insn->outputs_.size(); ++i) {
      IInsn *assign_insn = new IInsn(assign);
      assign_insn->inputs_.push_back(ci.rets[i]);
      assign_insn->outputs_.push_back(reg_map[call_insn->outputs_[i]]);
      st_map[rs]->insns_.push_back(assign_insn);
    }
  }
}

void MethodExpander::CopyState(IState *ost, map<IState *, IState *> &st_map,
                               map<IRegister *, IRegister *> &reg_map,
                               IState *nst, map<IInsn *, IInsn *> &insn_map) {
  for (IInsn *insn : ost->insns_) {
    IInsn *new_insn = CopyInsn(insn, st_map, reg_map);
    insn_map[insn] = new_insn;
    nst->insns_.push_back(new_insn);
  }
  nst->GetMutableProfile()->valid_ = ost->GetProfile().valid_;
  nst->GetMutableProfile()->raw_count_ = ost->GetProfile().raw_count_;
}

IInsn *MethodExpander::CopyInsn(IInsn *oinsn, map<IState *, IState *> &st_map,
                                map<IRegister *, IRegister *> &reg_map) {
  IInsn *insn = new IInsn(oinsn->GetResource());
  insn->SetOperand(oinsn->GetOperand());
  for (IRegister *reg : oinsn->inputs_) {
    insn->inputs_.push_back(reg_map[reg]);
  }
  for (IRegister *reg : oinsn->outputs_) {
    insn->outputs_.push_back(reg_map[reg]);
  }
  for (IState *st : oinsn->target_states_) {
    insn->target_states_.push_back(st_map[st]);
  }
  return insn;
}

void MethodExpander::CopyDependingInsns(MethodContext *method,
                                        map<IInsn *, IInsn *> &insn_map) {
  for (StateWrapper *sw : method->states_) {
    for (IInsn *insn : sw->state_->insns_) {
      IInsn *new_insn = insn_map[insn];
      CHECK(new_insn);
      for (IInsn *dinsn : insn->depending_insns_) {
        new_insn->depending_insns_.push_back(insn_map[dinsn]);
      }
    }
  }
}

void MethodExpander::BuildInsnRegCopy(IInsn *insn,
                                      map<IRegister *, IRegister *> &reg_map) {
  for (IRegister *reg : insn->inputs_) {
    BuildRegCopy(reg, reg_map);
  }
  for (IRegister *reg : insn->outputs_) {
    BuildRegCopy(reg, reg_map);
  }
}

void MethodExpander::BuildRegCopy(IRegister *reg,
                                  map<IRegister *, IRegister *> &reg_map) {
  if (reg->IsConst()) {
    reg_map[reg] = reg;
    return;
  }
  if (reg_map.find(reg) != reg_map.end()) {
    return;
  }
  IRegister *nreg = thr_synth_->AllocRegister(reg->GetName());
  if (reg->HasInitialValue()) {
    iroha::Numeric v = reg->GetInitialValue();
    nreg->SetInitialValue(v);
  }
  nreg->SetConst(reg->IsConst());
  nreg->SetStateLocal(reg->IsStateLocal());
  nreg->value_type_ = reg->value_type_;
  auto *params = reg->GetMutableParams(false);
  if (params != nullptr) {
    auto *nparams = nreg->GetMutableParams(true);
    nparams->Merge(params);
  }
  reg_map[reg] = nreg;
}

}  // namespace synth
