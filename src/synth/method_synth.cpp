#include "synth/method_synth.h"

#include <stdio.h>

#include "dfg/dfg.h"
#include "messages.h"
#include "dump_stream.h"
#include "compiler/compiler.h"
#include "dfg/imported_resource.h"
#include "fe/expr.h"
#include "fe/method.h"
#include "fe/var_decl.h"
#include "synth/resource_set.h"
#include "vm/array_wrapper.h"
#include "vm/channel.h"
#include "vm/insn.h"
#include "vm/int_array.h"
#include "vm/method.h"
#include "vm/object.h"
#include "vm/opcode.h"
#include "vm/value.h"

namespace synth {

MethodSynth::MethodSynth(vm::VM *vm,
			 vm::Object *obj,
			 const char *method_name,
			 bool is_task_root,
			 ResourceSet *resource,
			 DGraph *graph)
  : vm_(vm), obj_(obj), method_name_(method_name), is_task_root_(is_task_root),
    resource_(resource), graph_(graph) {
}

MethodSynth::~MethodSynth() {
}

bool MethodSynth::Synth() {
  vm::Value *value = obj_->LookupValue(sym_lookup(method_name_), false);
  if (!value || value->type_ != vm::Value::METHOD) {
    Message::os(Message::USER) << "Failed to find method: " << method_name_;
    MessageFlush::Get(Message::USER);
    return false;
  }

  current_zinsn_index_ = -1;
  method_ = value->method_;

  if (!method_->parse_tree_) {
    SynthNativeMethod(method_);
    return true;
  }
  compiler::Compiler::CompileMethod(vm_, obj_,
				    method_->parse_tree_,
				    method_);

  EmitEntryInsn(method_);
  for (size_t i = 0; i < method_->insns_.size(); ++i) {
    current_zinsn_index_ = i;
    SynthInsn(method_->insns_[i]);
  }
  if (is_task_root_) {
    EmitTaskFinishInsn();
  }

  ResolveJumps();
  LinkStates();
  return true;
}

DState *MethodSynth::InitialState() {
  return all_states_[0];
}

DState *MethodSynth::LastState() {
  return all_states_[all_states_.size() - 1];
}

void MethodSynth::SynthInsn(vm::Insn *insn) {
  switch (insn->op_) {
  case vm::OP_NOP:
    AllocState();
    break;
  case vm::OP_NUM:
    SynthNum(insn);
    break;
  case vm::OP_FUNCALL:
    SynthFuncall(insn);
    break;
  case vm::OP_FUNCALL_DONE:
    AllocState();
    break;
  case vm::OP_LOAD_OBJ:
    SynthLoadObj(insn);
    break;
  case vm::OP_ASSIGN:
    SynthAssign(insn);
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
  case vm::OP_LOGIC_INV:
    SynthLogicInv(insn);
    break;
  case vm::OP_BIT_RANGE:
    SynthBitRange(insn);
    break;
  case vm::OP_GOTO:
    SynthGoto(insn);
    break;
  case vm::OP_PRE_DEC:
  case vm::OP_PRE_INC:
    SynthPreIncDec(insn);
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
  case vm::OP_CHANNEL_WRITE:
    SynthChannelWrite(insn);
    break;
  case vm::OP_CHANNEL_READ:
    SynthChannelRead(insn);
    break;
  default:
    CHECK(false) << "unknown insn:" << vm::OpCodeName(insn->op_);
  }
}

DRegister *MethodSynth::FindLocalVarRegister(vm::Register *zreg) {
  DRegister *dreg = local_reg_map_[zreg];
  if (dreg) {
    return dreg;
  }
  char name[10];
  sprintf(name, "r%d_", zreg->id_);
  DType *type;
  if (zreg->type_.value_type_ == vm::Value::NUM) {
    type = DTypeUtil::GetIntType(numeric::Width::GetWidth(zreg->type_.width_));
  } else {
    CHECK(zreg->type_.value_type_ == vm::Value::ENUM_ITEM);
    type = DTypeUtil::GetBoolType();
  }
  dreg = DGraphUtil::FindSym(graph_, string(name) + method_name_, type);
  local_reg_map_[zreg] = dreg;
  return dreg;
}

DRegister *MethodSynth::FindArgRegister(fe::VarDecl *arg_decl) {
  DType *type = NULL;
  if (arg_decl->type == sym_bool) {
    type = DTypeUtil::GetBoolType();
  } else if (arg_decl->type == sym_int) {
    type = DTypeUtil::GetIntType(numeric::Width::GetWidth(arg_decl->width));
  } else {
    CHECK(false);
  }
  return DGraphUtil::FindSym(graph_,
			     string(sym_cstr(arg_decl->name_expr->sym_)),
			     type);
}

void MethodSynth::ResolveJumps() {
  for (size_t i = 0; i < jumps_.size(); ++i) {
    JumpEntry &jump = jumps_[i];
    DState *target_state = zinsn_dstate_map_[jump.target];
    jump.insn->targets_.push_back(target_state);
  }
}

void MethodSynth::LinkStates() {
  for (size_t i = 0; i < all_states_.size() - 1; ++i) {
    DState *state = all_states_[i];
    DResource *br = resource_->BranchResource();
    DInsn *br_insn = DStateUtil::FindInsnByResource(state, br);
    if (!br_insn) {
      br_insn = DGraphUtil::InsnNew(graph_, br);
      state->insns_.push_back(br_insn);
    }
    if (br_insn->inputs_.size() == 0 &&
	br_insn->targets_.size() > 0) {
      // unconditional jump.
      continue;
    }
    DState *next_state = all_states_[i + 1];
    br_insn->targets_.push_back(next_state);
    if (br_insn->targets_.size() == 2) {
      // swap
      DState *tmp = br_insn->targets_[0];
      br_insn->targets_[0] = br_insn->targets_[1];
      br_insn->targets_[1] = tmp;
    }
  }
}

DState *MethodSynth::AllocState() {
  DState *state = DGraphUtil::AllocState(graph_);
  if (zinsn_dstate_map_.find(current_zinsn_index_) ==
      zinsn_dstate_map_.end()) {
    // records the only first state.
    zinsn_dstate_map_[current_zinsn_index_] = state;
  }
  all_states_.push_back(state);
  return state;
}

void MethodSynth::SynthNum(vm::Insn *insn) {
  AllocState();
  vm::Register *zreg = insn->src_regs_[0];
  CHECK(zreg->type_.value_type_ == vm::Value::NUM);
  local_reg_map_[insn->dst_regs_[0]] =
    DGraphUtil::FindNum(graph_, numeric::Numeric::GetInt(zreg->initial_num_));
}

void MethodSynth::SynthAssign(vm::Insn *insn) {
  EmitOneAssign(insn->src_regs_[0], insn->src_regs_[1]);
}

void MethodSynth::SynthBinCalcExpr(vm::Insn *insn) {
  DResource *res =
    resource_->GetOpResource(insn->op_, InsnToCalcDType(insn));
  DInsn *d_insn = DGraphUtil::InsnNew(graph_, res);
  for (size_t i = 0; i < insn->src_regs_.size(); ++i) {
    DRegister *reg = FindLocalVarRegister(insn->src_regs_[i]);
    d_insn->inputs_.push_back(reg);
  }

  // GT: x > y : x > y
  // LT: x < y : y > x
  // LTE: x <= y : !(x > y)
  // GTE: x >= y : !(y > x)
  if (insn->op_ == vm::OP_LT || insn->op_ == vm::OP_GTE) {
    // swap.
    DRegister *tmp_reg = d_insn->inputs_[0];
    d_insn->inputs_[0] = d_insn->inputs_[1];
    d_insn->inputs_[1] = tmp_reg;
  }

  DState *state = AllocState();
  DRegister *res_reg = FindLocalVarRegister(insn->dst_regs_[0]);
  if (insn->op_ == vm::OP_LTE || insn->op_ == vm::OP_GTE ||
      insn->op_ == vm::OP_NE) {
    DRegister *neg_reg =
      DGraphUtil::AllocTmpReg(graph_, DTypeUtil::GetBoolType());
    d_insn->outputs_.push_back(neg_reg);
    state->insns_.push_back(d_insn);
    GenNeg(neg_reg, res_reg);
  } else {
    // normal case.
    d_insn->outputs_.push_back(res_reg);
    state->insns_.push_back(d_insn);
  }
}

void MethodSynth::SynthShiftExpr(vm::Insn *insn) {
  CHECK(insn->src_regs_[1]->type_.is_const_);
  int shift_count = numeric::Numeric::GetInt(insn->src_regs_[1]->initial_num_);
  int src_width = numeric::Width::GetWidth(insn->src_regs_[0]->type_.width_);
  int src_msb, src_lsb;
  int dst_width;
  if (insn->op_ == vm::OP_LSHIFT) {
    src_msb = src_width - shift_count - 1;
    src_lsb = 0;
    dst_width = src_width - shift_count;
  } else {
    src_msb = src_width - 1;
    src_lsb = shift_count;
    dst_width = src_width - shift_count;
  }
  DRegister *src_reg = FindLocalVarRegister(insn->src_regs_[0]);
  DRegister *sel_reg =
    DGraphUtil::AllocTmpReg(graph_,
			    DTypeUtil::GetIntType(dst_width));
  GenBitSelect(src_reg, src_msb, src_lsb, dst_width, sel_reg);
  DRegister *pad = DGraphUtil::FindWidthNum(graph_, 0,
					    src_width - dst_width);
  DRegister *res = FindLocalVarRegister(insn->dst_regs_[0]);
  if (insn->op_ == vm::OP_LSHIFT) {
    GenConcat(sel_reg, pad, res);
  } else {
    GenConcat(pad, sel_reg, res);
  }
}

void MethodSynth::SynthConcat(vm::Insn *insn) {
  DResource *concat = resource_->GetOpResource(vm::OP_CONCAT, NULL);
  DInsn *d_insn = DGraphUtil::InsnNew(graph_, concat);
  DRegister *lhs = FindLocalVarRegister(insn->src_regs_[0]);
  DRegister *rhs = FindLocalVarRegister(insn->src_regs_[1]);
  d_insn->inputs_.push_back(lhs);
  d_insn->inputs_.push_back(rhs);
  DRegister *res = FindLocalVarRegister(insn->dst_regs_[0]);
  d_insn->outputs_.push_back(res);
  DState *state = AllocState();
  state->insns_.push_back(d_insn);
}

void MethodSynth::SynthBitRange(vm::Insn *insn) {
  DRegister *src = FindLocalVarRegister(insn->src_regs_[0]);
  DRegister *res = FindLocalVarRegister(insn->dst_regs_[0]);
  int msb = numeric::Numeric::GetInt(insn->src_regs_[1]->initial_num_);
  int lsb = numeric::Numeric::GetInt(insn->src_regs_[2]->initial_num_);
  GenBitSelect(src, msb, lsb, msb - lsb + 1, res);
}

void MethodSynth::SynthLogicInv(vm::Insn *insn) {
  DRegister *src = FindLocalVarRegister(insn->src_regs_[0]);
  DRegister *res = FindLocalVarRegister(insn->dst_regs_[0]);
  GenNeg(src, res);
}

void MethodSynth::SynthChannelRead(vm::Insn *insn) {
  vm::Object *obj = member_reg_to_obj_map_[insn->obj_reg_];
  CHECK(vm::Channel::IsChannel(obj));
  int width = vm::Channel::ChannelWidth(obj);
  DResource *res = resource_->GetChannelResource(vm::Channel::ChannelName(obj),
						 false, width);
  DInsn *d_insn = DGraphUtil::InsnNew(graph_, res);
  d_insn->outputs_.push_back(FindLocalVarRegister(insn->dst_regs_[0]));
  DState *state = AllocState();
  state->insns_.push_back(d_insn);
}

void MethodSynth::SynthChannelWrite(vm::Insn *insn) {
  vm::Object *obj = member_reg_to_obj_map_[insn->obj_reg_];
  CHECK(vm::Channel::IsChannel(obj));
  int width = vm::Channel::ChannelWidth(obj);
  DResource *res =
    resource_->GetChannelResource(vm::Channel::ChannelName(obj), true, width);
  DInsn *d_insn = DGraphUtil::InsnNew(graph_, res);
  d_insn->inputs_.push_back(FindLocalVarRegister(insn->src_regs_[1]));
  DState *state = AllocState();
  state->insns_.push_back(d_insn);
}

void MethodSynth::SynthArrayAccess(vm::Insn *insn, bool is_write,
				   bool is_memory) {
  vm::Object *array_obj = member_reg_to_obj_map_[insn->obj_reg_];
  CHECK(!(is_memory && array_obj));
  sym_t array_name = NULL;
  if (array_obj) {
    vector<sym_t> names;
    obj_->LookupMemberNames(array_obj, &names);
    CHECK(names.size() == 1) << names.size();
    array_name = names[0];
  }
  DResource *res = resource_->GetArrayResource(array_name);
  if (!is_memory && !res->array_) {
    InitializeArrayResource(res, insn, array_name);
  }
  if (!is_memory && is_write) {
    res->array_->may_write_ = true;
  }
  DInsn *d_insn = DGraphUtil::InsnNew(graph_, res);
  // index
  d_insn->inputs_.push_back(FindLocalVarRegister(insn->src_regs_[0]));
  // value
  if (is_write) {
    d_insn->inputs_.push_back(FindLocalVarRegister(insn->src_regs_[1]));
  } else {
    d_insn->outputs_.push_back(FindLocalVarRegister(insn->dst_regs_[0]));
  }
  DState *state = AllocState();
  state->insns_.push_back(d_insn);
}

void MethodSynth::SynthMemberAccess(vm::Insn *insn, bool is_store) {
  vm::Value *value = obj_->LookupValue(insn->label_, false);
  CHECK(value) << "member not found";
  if (value->is_const_) {
    CHECK(!is_store);
    CHECK(value->type_ == vm::Value::ENUM_ITEM);
    DType *type = DTypeUtil::GetBoolType();
    DRegister *reg =
      DGraphUtil::FindEnum(graph_, "unused_name", type, value->enum_val_.val);
    local_reg_map_[insn->dst_regs_[0]] = reg;
    // dummy.
    AllocState();
  } else if (value->type_ == vm::Value::OBJECT) {
    CHECK(!is_store);
    member_reg_to_obj_map_[insn->dst_regs_[0]] = value->object_;
    // dummy.
    AllocState();
  } else {
    DRegister *reg = member_reg_map_[insn->label_];
    if (!reg) {
      string name = sym_cstr(insn->label_);
      name = "m_" + name;
      DType *type;
      if (value->type_ == vm::Value::NUM) {
	type = DTypeUtil::GetIntType(numeric::Width::GetWidth(value->num_.type));
      } else {
	type = DTypeUtil::GetBoolType();
      }
      reg = DGraphUtil::FindSym(graph_, name, type);
      member_reg_map_[insn->label_] = reg;
      reg->has_initial_ = true;
      reg->num_ = numeric::Numeric::GetInt(value->num_);
    }
    DResource *assign = resource_->AssignResource();
    DInsn *d_insn = DGraphUtil::InsnNew(graph_, assign);
    if (!is_store) {
      d_insn->inputs_.push_back(reg);
      d_insn->outputs_.push_back(FindLocalVarRegister(insn->dst_regs_[0]));
    } else {
      d_insn->inputs_.push_back(FindLocalVarRegister(insn->src_regs_[0]));
      d_insn->outputs_.push_back(reg);
    }
    DState *state = AllocState();
    state->insns_.push_back(d_insn);
  }
}

DInsn *MethodSynth::EmitEntryInsn(vm::Method *method) {
  DState *entry_state = AllocState();
  entry_state->text_annotation_ = "entry";
  DInsn *entry_insn =
    DGraphUtil::InsnNew(graph_,
			resource_->FunctionEntryResource(is_task_root_));
  int num_args = 0;
  fe::VarDeclSet *args = method->parse_tree_->args_;
  if (args) {
    num_args = args->decls.size();
    for (size_t i = 0; i < args->decls.size(); ++i) {
      DRegister *reg = FindArgRegister(args->decls[i]);
      entry_insn->inputs_.push_back(reg);
    }
  }
  // Task root uses task_finish insn instead.
  if (!is_task_root_) {
    fe::VarDeclSet *rets = method->parse_tree_->returns_;
    if (rets) {
      for (size_t i = 0; i < rets->decls.size(); ++i) {
	vm::Register *zreg = method->method_regs_[i + num_args];
	entry_insn->outputs_.push_back(FindLocalVarRegister(zreg));
      }
    }
  }

  entry_state->insns_.push_back(entry_insn);
  return entry_insn;
}

void MethodSynth::EmitTaskFinishInsn() {
  DState *finish_state = AllocState();
  finish_state->text_annotation_ = "finish";
  DInsn *finish_insn =
    DGraphUtil::InsnNew(graph_, resource_->TaskFinishResource());
  CHECK(is_task_root_);
  int num_args = 0;
  fe::VarDeclSet *args = method_->parse_tree_->args_;
  if (args) {
    num_args = args->decls.size();
  }
  fe::VarDeclSet *rets = method_->parse_tree_->returns_;
  if (rets) {
    for (size_t i = 0; i < rets->decls.size(); ++i) {
      vm::Register *zreg = method_->method_regs_[i + num_args];
      finish_insn->inputs_.push_back(FindLocalVarRegister(zreg));
    }
  }
  finish_state->insns_.push_back(finish_insn);
}

void MethodSynth::EmitOneAssign(vm::Register *lhs, vm::Register *rhs) {
  DRegister *lhs_reg = FindLocalVarRegister(lhs);
  DRegister *rhs_reg = FindLocalVarRegister(rhs);
  DResource *assign = resource_->AssignResource();
  DInsn *d_insn = DGraphUtil::InsnNew(graph_, assign);
  d_insn->inputs_.push_back(rhs_reg);
  d_insn->outputs_.push_back(lhs_reg);
  DState *state = AllocState();
  state->insns_.push_back(d_insn);
}

void MethodSynth::SynthFuncall(vm::Insn *insn) {
  DState *state = AllocState();
  DResource *res = nullptr;
  sym_t func_name = insn->label_;
  vm::Object *callee_obj = nullptr;
  if (insn->obj_reg_) {
    callee_obj = member_reg_to_obj_map_[insn->obj_reg_];
  }
  bool is_sub_module_call;
  if (insn->obj_reg_ && callee_obj != obj_) {
    sym_t orig_name = orig_name_map_[insn->obj_reg_];
    res = resource_->GetSubModuleCallResource(callee_obj, func_name,
					      orig_name);
    is_sub_module_call = true;
  } else {
    res = resource_->FuncallResource();
    is_sub_module_call = false;
  }
  DInsn *d_insn = DGraphUtil::InsnNew(graph_, res);
  d_insn->func_name_ = sym_cstr(func_name);
  for (size_t i = 0; i < insn->src_regs_.size(); ++i) {
    DRegister *reg = FindLocalVarRegister(insn->src_regs_[i]);
    d_insn->inputs_.push_back(reg);
  }
  RequestFunction(callee_obj, insn->label_);
  state->insns_.push_back(d_insn);

  SynthFuncallOutput(state, d_insn, res, callee_obj, is_sub_module_call);
}

void MethodSynth::SynthFuncallOutput(DState *state, DInsn *d_insn,
				     DResource *res,
				     vm::Object *callee_obj,
				     bool is_sub_module_call) {
  vm::Insn *call_insn = method_->insns_[current_zinsn_index_];
  sym_t func_name = call_insn->label_;
  vm::Value *value = callee_obj->LookupValue(func_name, false);
  CHECK(value->type_ ==vm::Value::METHOD);
  vm::Insn *done_insn = method_->insns_[current_zinsn_index_ + 1];
  // Required number of outputs.
  int num_outputs = std::min(value->method_->GetNumReturnRegisters(),
			     (int)done_insn->dst_regs_.size());

  if (num_outputs > 0) {
    if (is_sub_module_call) {
      // Allocate new state to receive return values.
      state = AllocState();
      d_insn = DGraphUtil::InsnNew(graph_, res);
      d_insn->func_name_ = sym_cstr(func_name);
    }
    for (int i = 0; i < num_outputs; ++i) {
      DRegister *reg = FindLocalVarRegister(done_insn->dst_regs_[i]);
      d_insn->outputs_.push_back(reg);
    }
    if (is_sub_module_call) {
      state->insns_.push_back(d_insn);
    }
  }
}

void MethodSynth::SynthIf(vm::Insn *insn) {
  DState *state = AllocState();
  DInsn *d_insn = DGraphUtil::InsnNew(graph_, resource_->BranchResource());
  DRegister *cond_reg = FindLocalVarRegister(insn->src_regs_[0]);
  d_insn->inputs_.push_back(cond_reg);
  state->insns_.push_back(d_insn);

  JumpEntry jump;
  jump.insn = d_insn;
  jump.target = insn->jump_target_;
  jumps_.push_back(jump);
}

void MethodSynth::SynthGoto(vm::Insn *insn) {
  DState *state = AllocState();
  DInsn *d_insn = DGraphUtil::InsnNew(graph_, resource_->BranchResource());
  state->insns_.push_back(d_insn);

  JumpEntry jump;
  jump.insn = d_insn;
  jump.target = insn->jump_target_;
  jumps_.push_back(jump);
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
  AllocState();
}

void MethodSynth::SynthPreIncDec(vm::Insn *insn) {
  DResource *res =
    resource_->GetOpResource(insn->op_ == vm::OP_PRE_INC ?
			     vm::OP_ADD : vm::OP_SUB,
			     InsnToCalcDType(insn));
  DState *state = AllocState();
  DInsn *d_insn = DGraphUtil::InsnNew(graph_, res);
  DRegister *reg = FindLocalVarRegister(insn->src_regs_[0]);
  d_insn->inputs_.push_back(reg);
  d_insn->inputs_.push_back(DGraphUtil::FindNum(graph_, 1));
  d_insn->outputs_.push_back(reg);
  state->insns_.push_back(d_insn);
}

void MethodSynth::RequestFunction(vm::Object *callee_obj, sym_t name) {
  if (callee_obj == obj_) {
    called_functions_.insert(name);
  }
}

set<sym_t> MethodSynth::GetCalledFunctions() {
  return called_functions_;
}

vector<DState *> &MethodSynth::AllStates() {
  return all_states_;
}

void MethodSynth::SynthNativeMethod(vm::Method *method) {
  sym_t name = sym_lookup(method->AlternativeImplementation());
  vm::Value *value = obj_->LookupValue(name, false);
  CHECK(value && value->type_ == vm::Value::METHOD) << sym_cstr(name);
  vm::Method *alt_method = value->method_;
  CHECK(alt_method->parse_tree_ &&
	alt_method->parse_tree_->imported_resource_);

  DInsn *entry_insn = EmitEntryInsn(alt_method);
  ImportedResource *imported_resource =
    alt_method->parse_tree_->imported_resource_;

  DResource *resource = resource_->GetImportedResource(imported_resource);
  DState *state = AllocState();
  DInsn *d_insn = DGraphUtil::InsnNew(graph_, resource);
  for (size_t i = 0; i < entry_insn->inputs_.size(); ++i) {
    d_insn->inputs_.push_back(entry_insn->inputs_[i]);
  }
  state->insns_.push_back(d_insn);

  LinkStates();
}

void MethodSynth::GenBitSelect(DRegister *src_reg, int msb, int lsb,
			       int dst_width, DRegister *res_reg) {
  DState *state = AllocState();
  DResource *bit_sel =
    resource_->GetOpResource(vm::OP_BIT_RANGE,
			     DTypeUtil::GetIntType(dst_width));
  DInsn *insn = DGraphUtil::InsnNew(graph_, bit_sel);
  //
  DRegister *src_msb_reg = DGraphUtil::FindNum(graph_, msb);
  DRegister *src_lsb_reg = DGraphUtil::FindNum(graph_, lsb);
  //
  insn->inputs_.push_back(src_reg);
  insn->inputs_.push_back(src_msb_reg);
  insn->inputs_.push_back(src_lsb_reg);
  insn->outputs_.push_back(res_reg);
  //
  state->insns_.push_back(insn);
}

void MethodSynth::GenNeg(DRegister *src, DRegister *dst) {
  DState *state = AllocState();
  DResource *logic_inv =
    resource_->GetOpResource(vm::OP_LOGIC_INV, NULL);
  DInsn *insn = DGraphUtil::InsnNew(graph_, logic_inv);
  insn->inputs_.push_back(src);
  insn->outputs_.push_back(dst);
  state->insns_.push_back(insn);
}

DRegister *MethodSynth::GenConcat(DRegister *lhs, DRegister *rhs, DRegister *res) {
  DResource *concat = resource_->GetOpResource(vm::OP_CONCAT, NULL);
  DInsn *insn = DGraphUtil::InsnNew(graph_, concat);
  insn->inputs_.push_back(lhs);
  insn->inputs_.push_back(rhs);
  insn->outputs_.push_back(res);
  DState *state = AllocState();
  state->insns_.push_back(insn);
  
  return res;
}

void MethodSynth::InitializeArrayResource(DResource *res, vm::Insn *insn, sym_t array_name) {
  vm::Value *value = obj_->LookupValue(array_name, false);
  CHECK(value && value->type_ == vm::Value::INT_ARRAY);
  DArray *array = new DArray;
  vm::IntArray *memory = vm::ArrayWrapper::GetIntArray(value->object_);
  int bits;
  for (bits = 0; (1<<bits) < (int)memory->GetLength(); ++bits) {
    // do nothing here.
  }
  array->address_width = bits;
  array->data_width = numeric::Width::GetWidth(memory->GetWidth());
  for (int i = 0; i < memory->GetLength(); ++i) {
    array->num_.push_back(numeric::Numeric::GetInt(memory->Read(i)));
  }
  res->array_ = array;
}

DType *MethodSynth::InsnToCalcDType(vm::Insn *insn) {
  vm::Register *reg;
  if (vm::InsnType::IsComparison(insn->op_)) {
    reg = insn->src_regs_[0];
  } else {
    reg = insn->dst_regs_[0];
  }
  if (reg->type_.value_type_ == vm::Value::NUM) {
    return DTypeUtil::GetIntType(numeric::Width::GetWidth(reg->type_.width_));
  } else if (reg->type_.value_type_ == vm::Value::ENUM_ITEM) {
    return DTypeUtil::GetBoolType();
  }
  return NULL;
}

}  // namespace synth
