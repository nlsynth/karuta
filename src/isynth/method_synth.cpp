#include "isynth/method_synth.h"

#include "compiler/compiler.h"
#include "dfg/resource_params.h"
#include "fe/expr.h"
#include "fe/method.h"
#include "fe/var_decl.h"
#include "iroha/iroha.h"
#include "iroha/i_design.h"
#include "isynth/channel_synth.h"
#include "isynth/thread_synth.h"
#include "isynth/object_synth.h"
#include "isynth/resource_set.h"
#include "isynth/method_context.h"
#include "status.h"
#include "vm/channel.h"
#include "vm/insn.h"
#include "vm/method.h"
#include "vm/object.h"
#include "vm/register.h"
#include "vm/value.h"

namespace isynth {

MethodSynth::MethodSynth(ThreadSynth *thr_synth,
			 const string &method_name, ITable *tab,
			 ResourceSet *res)
  : thr_synth_(thr_synth), method_name_(method_name), tab_(tab), res_(res) {
  context_.reset(new MethodContext(this));
  vm_ = thr_synth->GetObjectSynth()->GetVM();
  obj_ = thr_synth->GetObjectSynth()->GetObject();
}

MethodSynth::~MethodSynth() {
}

bool MethodSynth::Synth() {
  vm::Value *value = obj_->LookupValue(sym_lookup(method_name_.c_str()), false);
  if (!value || value->type_ != vm::Value::METHOD) {
    Status::os(Status::USER) << "Failed to find method: " << method_name_;
    MessageFlush::Get(Status::USER);
    return false;
  }
  vm::Method *method = value->method_;
  if (!method->parse_tree_) {
    SynthNativeMethod(method);
    return true;
  }
  compiler::Compiler::CompileMethod(vm_, obj_,
				    method->parse_tree_,
				    method);
  EmitEntryInsn(method);
  StateWrapper *last = nullptr;
  // mapping from vm::insn index to state index.
  map<int, int> state_index;
  state_index[0] = context_->states_.size();
  for (size_t i = 0; i < method->insns_.size(); ++i) {
    SynthInsn(method->insns_[i]);
    StateWrapper *lw = context_->LastState();
    if (last == lw) {
      AllocState();
    }
    state_index[i + 1] = context_->states_.size();
    last = context_->LastState();
  }
  for (size_t i = 0; i < method->insns_.size(); ++i) {
    vm_insn_state_map_[i] = context_->states_[state_index[i]];
  }
  AllocState();

  ResolveJumps();
  LinkStates();
  return true;
}

MethodContext *MethodSynth::GetContext() {
  return context_.get();
}

void MethodSynth::SynthNativeMethod(vm::Method *method) {
  sym_t name = sym_lookup(method->AlternativeImplementation());
  vm::Value *value = obj_->LookupValue(name, false);
  CHECK(value && value->type_ == vm::Value::METHOD) << sym_cstr(name);
  vm::Method *alt_method = value->method_;
  CHECK(alt_method->parse_tree_ &&
	alt_method->parse_tree_->imported_resource_ &&
	alt_method->parse_tree_->imported_resource_->IsImportedModule());

  SynthEmbeddedMethod(alt_method);
}

void MethodSynth::SynthEmbeddedMethod(vm::Method *method) {
  EmitEntryInsn(method);
  StateWrapper *sw = AllocState();
  IResource *res = res_->GetImportedResource(method);
  IInsn *iinsn = new IInsn(res);
  iinsn->inputs_ = context_->method_insn_->inputs_;
  iinsn->outputs_ = context_->method_insn_->outputs_;
  sw->state_->insns_.push_back(iinsn);
}

void MethodSynth::LinkStates() {
  for (size_t i = 0; i < context_->states_.size() - 1; ++i) {
    StateWrapper *s0 = context_->states_[i];
    IInsn *tr_insn = DesignUtil::FindTransitionInsn(s0->state_);
    if (tr_insn != nullptr && tr_insn->target_states_.size() > 0) {
      continue;
    }
    StateWrapper *s1 = context_->states_[i + 1];
    DesignTool::AddNextState(s0->state_, s1->state_);
  }
}

void MethodSynth::SynthInsn(vm::Insn *insn) {
  switch (insn->op_) {
  case vm::OP_NOP:
    SynthNop(insn);
    break;
  case vm::OP_NUM:
    SynthNum(insn);
    break;
  case vm::OP_ASSIGN:
    SynthAssign(insn);
    break;
  case vm::OP_FUNCALL:
    SynthFuncall(insn);
    break;
  case vm::OP_FUNCALL_DONE:
    SynthFuncallDone(insn);
    break;
  case vm::OP_LOAD_OBJ:
    SynthLoadObj(insn);
    break;
  case vm::OP_GOTO:
    SynthGoto(insn);
    break;
  case vm::OP_IF:
    SynthIf(insn);
    break;
  case vm::OP_ADD:
  case vm::OP_SUB:
  case vm::OP_MUL:
  case vm::OP_EQ:
  case vm::OP_NE:
  case vm::OP_GT:
  case vm::OP_LT:
  case vm::OP_GTE:
  case vm::OP_LTE:
  case vm::OP_AND:
  case vm::OP_OR:
  case vm::OP_XOR:
  case vm::OP_LAND:
  case vm::OP_LOR:
    SynthBinCalcExpr(insn);
    break;
  case vm::OP_LSHIFT:
  case vm::OP_RSHIFT:
    SynthShiftExpr(insn);
    break;
  case vm::OP_CONCAT:
    SynthConcat(insn);
    break;
  case vm::OP_MEMBER_READ:
    SynthMemberAccess(insn, false);
    break;
  case vm::OP_MEMBER_WRITE:
    SynthMemberAccess(insn, true);
    break;
  case vm::OP_ARRAY_READ:
    SynthArrayAccess(insn, false, false);
    break;
  case vm::OP_ARRAY_WRITE:
    SynthArrayAccess(insn, true, false);
    break;
  case vm::OP_MEMORY_READ:
    SynthArrayAccess(insn, false, true);
    break;
  case vm::OP_MEMORY_WRITE:
    SynthArrayAccess(insn, true, true);
    break;
  case vm::OP_BIT_RANGE:
    SynthBitRange(insn);
    break;
  case vm::OP_CHANNEL_WRITE:
    SynthChannelAccess(insn, true);
    break;
  case vm::OP_CHANNEL_READ:
    SynthChannelAccess(insn, false);
    break;
  default:
    CHECK(false) << "unknown insn:" << vm::OpCodeName(insn->op_);
  }
}

void MethodSynth::SynthNop(vm::Insn *insn) {
}

void MethodSynth::SynthNum(vm::Insn *insn) {
  vm::Register *src_reg = insn->src_regs_[0];
  CHECK(src_reg->type_.value_type_ == vm::Value::NUM);
  vm::Register *dst_reg = insn->dst_regs_[0];
  IRegister *ireg =
    DesignTool::AllocConstNum(tab_,
			      numeric::Width::GetWidth(src_reg->type_.width_),
			      numeric::Numeric::GetInt(src_reg->initial_num_));
  local_reg_map_[dst_reg] = ireg;
}

void MethodSynth::SynthAssign(vm::Insn *insn) {
  IRegister *lhs_reg = FindLocalVarRegister(insn->src_regs_[0]);
  IRegister *rhs_reg = FindLocalVarRegister(insn->src_regs_[1]);
  IResource *assign = res_->AssignResource();
  IInsn *iinsn = new IInsn(assign);
  iinsn->inputs_.push_back(rhs_reg);
  iinsn->outputs_.push_back(lhs_reg);
  StateWrapper *sw = AllocState();
  sw->state_->insns_.push_back(iinsn);
}

void MethodSynth::SynthLoadObj(vm::Insn *insn) {
  if (insn->label_) {
    vm::Value *value = obj_->LookupValue(insn->label_, false);
    // Can be OBJECT, INT_ARRAY, OBJECT_ARRAY.
    vm::Object *member = value->object_;
    CHECK(member);
    member_reg_to_obj_map_[insn->dst_regs_[0]] = member;
    orig_name_map_[insn->dst_regs_[0]] = insn->label_;
  } else {
    // loading "this" obj.
    member_reg_to_obj_map_[insn->dst_regs_[0]] = obj_;
  }
}

void MethodSynth::SynthFuncall(vm::Insn *insn) {
  sym_t func_name = insn->label_;
  vm::Object *callee_obj = nullptr;
  if (insn->obj_reg_) {
    callee_obj = member_reg_to_obj_map_[insn->obj_reg_];
  }
  if (insn->obj_reg_ && callee_obj != obj_) {
    CHECK(false) << "Sub module call is not yet implemented";
  }
  StateWrapper *sw = AllocState();
  sw->func_name_ = string(sym_cstr(func_name));
  thr_synth_->RequestMethod(sw->func_name_);

  IInsn *iinsn = new IInsn(res_->PseudoResource());
  sw->state_->insns_.push_back(iinsn);
  for (vm::Register *arg : insn->src_regs_) {
    IRegister *iarg = FindLocalVarRegister(arg);
    iinsn->inputs_.push_back(iarg);
  }
}

void MethodSynth::SynthFuncallDone(vm::Insn *insn) {
  StateWrapper *sw = context_->LastState();
  CHECK(sw->state_->insns_.size() == 1);
  IInsn *iinsn = sw->state_->insns_[0];
  for (vm::Register *ret : insn->dst_regs_) {
    IRegister *iret = FindLocalVarRegister(ret);
    iinsn->outputs_.push_back(iret);
  }
}

void MethodSynth::SynthIf(vm::Insn *insn) {
  StateWrapper *sw = AllocState();
  sw->vm_insn_ = insn;
  IInsn *iinsn = DesignUtil::GetTransitionInsn(sw->state_);
  IRegister *cond_reg = FindLocalVarRegister(insn->src_regs_[0]);
  iinsn->inputs_.push_back(cond_reg);
}

void MethodSynth::SynthConcat(vm::Insn *insn) {
  IValueType vt;
  IResource *concat = res_->GetOpResource(vm::OP_CONCAT, vt);
  IInsn *iinsn = new IInsn(concat);
  IRegister *lhs = FindLocalVarRegister(insn->src_regs_[0]);
  IRegister *rhs = FindLocalVarRegister(insn->src_regs_[1]);
  iinsn->inputs_.push_back(lhs);
  iinsn->inputs_.push_back(rhs);
  IRegister *res = FindLocalVarRegister(insn->dst_regs_[0]);
  iinsn->outputs_.push_back(res);
  StateWrapper *sw = AllocState();
  sw->state_->insns_.push_back(iinsn);
}

void MethodSynth::SynthBitRange(vm::Insn *insn) {
  IRegister *src = FindLocalVarRegister(insn->src_regs_[0]);
  IRegister *res = FindLocalVarRegister(insn->dst_regs_[0]);
  int msb = numeric::Numeric::GetInt(insn->src_regs_[1]->initial_num_);
  int lsb = numeric::Numeric::GetInt(insn->src_regs_[2]->initial_num_);

  StateWrapper *sw = AllocState();
  IValueType vt_none;
  IResource *bit_sel = res_->GetOpResource(vm::OP_BIT_RANGE, vt_none);
  IInsn *iinsn = new IInsn(bit_sel);

  iinsn->inputs_.push_back(src);
  iinsn->inputs_.push_back(DesignTool::AllocConstNum(tab_, 32, msb));
  iinsn->inputs_.push_back(DesignTool::AllocConstNum(tab_, 32, lsb));
  iinsn->outputs_.push_back(res);
  sw->state_->insns_.push_back(iinsn);
}

IRegister *MethodSynth::FindLocalVarRegister(vm::Register *vreg) {
  IRegister *ireg = local_reg_map_[vreg];
  if (ireg) {
    return ireg;
  }
  char name[10];
  sprintf(name, "r%d_", vreg->id_);
  int w = numeric::Width::GetWidth(vreg->type_.width_);
  if (vreg->type_.value_type_ == vm::Value::ENUM_ITEM) {
    w = 0;
  }
  ireg = DesignTool::AllocRegister(tab_, name + method_name_,
				   w);
  local_reg_map_[vreg] = ireg;
  return ireg;
}

IRegister *MethodSynth::FindArgRegister(int nth, fe::VarDecl *arg_decl) {
  int w = 0;
  if (arg_decl->type == sym_bool) {
    w = 0;
  } else if (arg_decl->type == sym_int) {
    w = numeric::Width::GetWidth(arg_decl->width);
  } else {
    CHECK(false);
  }
  string reg_name(sym_cstr(arg_decl->name_expr->sym_));
  return DesignTool::AllocRegister(tab_, reg_name, w);
}

void MethodSynth::ResolveJumps() {
  int sw_idx = 0;
  for (auto &sw : context_->states_) {
    if (sw->vm_insn_) {
      if (sw->vm_insn_->op_ == vm::OP_GOTO) {
	IState *st = vm_insn_state_map_[sw->vm_insn_->jump_target_]->state_;
	CHECK(st) << "couldn't resolve goto" << sw->vm_insn_->jump_target_;
	DesignTool::AddNextState(sw->state_, st);
      }
      if (sw->vm_insn_->op_ == vm::OP_IF) {
	// next, jump_target
	IState *next_st = context_->states_[sw_idx + 1]->state_;
	IState *target_st =
	  vm_insn_state_map_[sw->vm_insn_->jump_target_]->state_;
	IInsn *tr_insn = DesignUtil::FindTransitionInsn(sw->state_);
	tr_insn->target_states_.push_back(target_st);
	tr_insn->target_states_.push_back(next_st);
      }
    }
    ++sw_idx;
  }
}

StateWrapper *MethodSynth::AllocState() {
  StateWrapper *w = new StateWrapper();
  IState *st = new IState(tab_);
  w->state_ = st;
  context_->states_.push_back(w);
  return w;
}

void MethodSynth::SynthBinCalcExpr(vm::Insn *insn) {
  IValueType vt;
  InsnToCalcValueType(insn, &vt);
  IResource *res = res_->GetOpResource(insn->op_, vt);
  IInsn *iinsn = new IInsn(res);
  for (vm::Register *vreg : insn->src_regs_) {
    IRegister *reg = FindLocalVarRegister(vreg);
    iinsn->inputs_.push_back(reg);
  }

  // GT: x > y : x > y
  // LT: x < y : y > x
  // LTE: x <= y : !(x > y)
  // GTE: x >= y : !(y > x)
  if (insn->op_ == vm::OP_LT || insn->op_ == vm::OP_GTE) {
    // swap.
    IRegister *tmp_reg = iinsn->inputs_[0];
    iinsn->inputs_[0] = iinsn->inputs_[1];
    iinsn->inputs_[1] = tmp_reg;
  }
  StateWrapper *w = AllocState();
  IRegister *res_reg = FindLocalVarRegister(insn->dst_regs_[0]);
  if (insn->op_ == vm::OP_LTE || insn->op_ == vm::OP_GTE ||
      insn->op_ == vm::OP_NE) {
    IRegister *neg_reg = thr_synth_->AllocRegister("t_");
    neg_reg->value_type_.SetWidth(0);
    iinsn->outputs_.push_back(neg_reg);
    GenNeg(neg_reg, res_reg);
    w->state_->insns_.push_back(iinsn);
  } else {
    iinsn->outputs_.push_back(res_reg);
    w->state_->insns_.push_back(iinsn);
  }
}

void MethodSynth::SynthShiftExpr(vm::Insn *insn) {
  CHECK(insn->src_regs_[1]->type_.is_const_);
  int shift_count = numeric::Numeric::GetInt(insn->src_regs_[1]->initial_num_);
  IValueType vt;
  IResource *shifter = res_->GetOpResource(insn->op_, vt);
  IInsn *iinsn = new IInsn(shifter);
  iinsn->inputs_.push_back(FindLocalVarRegister(insn->src_regs_[0]));
  iinsn->inputs_.push_back(DesignTool::AllocConstNum(tab_, 32, shift_count));
  iinsn->outputs_.push_back(FindLocalVarRegister(insn->dst_regs_[0]));
  if (insn->op_ == vm::OP_LSHIFT) {
    iinsn->SetOperand("left");
  } else {
    iinsn->SetOperand("right");
  }
  StateWrapper *w = AllocState();
  w->state_->insns_.push_back(iinsn);
}

void MethodSynth::SynthGoto(vm::Insn *insn) {
  StateWrapper *w = AllocState();
  w->vm_insn_ = insn;
}

void MethodSynth::SynthMemberAccess(vm::Insn *insn, bool is_store) {
  vm::Value *value = obj_->LookupValue(insn->label_, false);
  CHECK(value) << "member not found";
  if (value->is_const_) {
    CHECK(!is_store);
    CHECK(value->type_ == vm::Value::ENUM_ITEM);
    IRegister *reg = DesignTool::AllocConstNum(tab_, 0, value->enum_val_.val);
    local_reg_map_[insn->dst_regs_[0]] = reg;
  } else if (value->type_ == vm::Value::OBJECT) {
    CHECK(false) << "member object access is not yet implemented";
  } else {
    CHECK(false) << "member access is not yet implemented";
  }
}

void MethodSynth::SynthChannelAccess(vm::Insn *insn, bool is_write) {
  vm::Object *obj = member_reg_to_obj_map_[insn->obj_reg_];
  CHECK(vm::Channel::IsChannel(obj));
  int width = vm::Channel::ChannelWidth(obj);
  IResource *res = res_->GetChannelResource(obj, is_write, width);
  IInsn *iinsn = new IInsn(res);
  if (is_write) {
    iinsn->inputs_.push_back(FindLocalVarRegister(insn->src_regs_[1]));
  } else {
    iinsn->outputs_.push_back(FindLocalVarRegister(insn->dst_regs_[0]));
  }
  StateWrapper *w = AllocState();
  w->state_->insns_.push_back(iinsn);
  thr_synth_->GetObjectSynth()->GetChannelSynth()->AddChannel(obj, res);
}

void MethodSynth::SynthArrayAccess(vm::Insn *insn, bool is_write,
				   bool is_memory) {
  vm::Object *array_obj = member_reg_to_obj_map_[insn->obj_reg_];
  CHECK(!(is_memory && array_obj));
  IResource *res;
  if (is_memory) {
    res = res_->GetExternalArrayResource();
  } else {
    res = res_->GetInternalArrayResource(array_obj);
  }
  IInsn *iinsn = new IInsn(res);
  // index
  iinsn->inputs_.push_back(FindLocalVarRegister(insn->src_regs_[0]));
  // value
  if (is_write) {
    iinsn->inputs_.push_back(FindLocalVarRegister(insn->src_regs_[1]));
  } else {
    iinsn->outputs_.push_back(FindLocalVarRegister(insn->dst_regs_[0]));
  }
  StateWrapper *w = AllocState();
  w->state_->insns_.push_back(iinsn);
}

void MethodSynth::GenNeg(IRegister *src, IRegister *dst) {
  StateWrapper *w = AllocState();
  IValueType vt;
  vt.SetWidth(0);
  IResource *bit_inv = res_->GetOpResource(vm::OP_BIT_INV, vt);
  IInsn *insn = new IInsn(bit_inv);
  insn->inputs_.push_back(src);
  insn->outputs_.push_back(dst);
  w->state_->insns_.push_back(insn);
}

void MethodSynth::EmitEntryInsn(vm::Method *method) {
  IResource *pseudo = res_->PseudoResource();
  context_->method_insn_ = new IInsn(pseudo);
  fe::VarDeclSet *args = method->parse_tree_->args_;
  int num_args = 0;
  if (args) {
    num_args = args->decls.size();
    for (size_t i = 0; i < args->decls.size(); ++i) {
      IRegister *ireg = FindArgRegister(i, args->decls[i]);
      context_->method_insn_->inputs_.push_back(ireg);
    }
  }
  fe::VarDeclSet *rets = method->parse_tree_->returns_;
  if (rets) {
    for (size_t i = 0; i < rets->decls.size(); ++i) {
      vm::Register *vreg = method->method_regs_[i + num_args];
      IRegister *ireg = FindLocalVarRegister(vreg);
      context_->method_insn_->outputs_.push_back(ireg);
    }
    // Adds a dummy return value.
    if (rets->decls.size() == 0) {
      IRegister *ireg = thr_synth_->AllocRegister("r_");
      context_->method_insn_->outputs_.push_back(ireg);
    }
  }
}

void MethodSynth::InsnToCalcValueType(vm::Insn *insn, IValueType *vt) {
  vm::Register *reg;
  if (vm::InsnType::IsComparison(insn->op_)) {
    reg = insn->src_regs_[0];
  } else {
    reg = insn->dst_regs_[0];
  }
  vt->SetIsSigned(false);
  if (reg->type_.value_type_ == vm::Value::NUM) {
    vt->SetWidth(numeric::Width::GetWidth(reg->type_.width_));
  } else if (reg->type_.value_type_ == vm::Value::ENUM_ITEM) {
    vt->SetWidth(numeric::Width::GetWidth(reg->type_.width_));
  }
}

}  // namespace isynth
