#include "synth/method_synth.h"

#include "base/annotation.h"
#include "base/status.h"
#include "fe/expr.h"
#include "fe/method.h"
#include "fe/var_decl.h"
#include "iroha/iroha.h"
#include "synth/channel_synth.h"
#include "synth/design_synth.h"
#include "synth/method_context.h"
#include "synth/object_method.h"
#include "synth/object_method_names.h"
#include "synth/object_synth.h"
#include "synth/resource_set.h"
#include "synth/resource_synth.h"
#include "synth/shared_resource_set.h"
#include "synth/thread_synth.h"
#include "synth/tool.h"
#include "vm/array_wrapper.h"
#include "vm/channel.h"
#include "vm/insn.h"
#include "vm/method.h"
#include "vm/object.h"
#include "vm/register.h"
#include "vm/value.h"

namespace synth {

MethodSynth::MethodSynth(ThreadSynth *thr_synth,
			 vm::Object *obj, const string &method_name,
			 ITable *tab, ResourceSynth *rsynth, ResourceSet *res)
  : InsnWalker(thr_synth, obj),
    thr_synth_(thr_synth), method_name_(method_name),
    tab_(tab), rsynth_(rsynth), res_set_(res), method_(nullptr),
    is_task_entry_(false), is_root_(false) {
  context_.reset(new MethodContext(this));
  vm::Value *value = obj_->LookupValue(sym_lookup(method_name_.c_str()), false);
  method_ = value->method_;
}

MethodSynth::~MethodSynth() {
}

ResourceSet *MethodSynth::GetResourceSet() {
  return res_set_;
}

bool MethodSynth::Synth() {
  if (method_ == nullptr) {
    return false;
  }
  if (method_->parse_tree_ == nullptr && method_->GetSynthName() != kMain) {
    SynthNativeImplMethod(method_);
    return true;
  }
  if (method_->GetAnnotation()->IsExtIO()) {
    SynthExtIOMethod();
    return true;
  }

  EmitEntryInsn(method_);
  StateWrapper *last = nullptr;
  // mapping from vm::insn index to state index.
  map<int, int> state_index;
  state_index[0] = context_->states_.size();
  for (size_t i = 0; i < method_->insns_.size(); ++i) {
    SynthInsn(method_->insns_[i]);
    StateWrapper *lw = context_->LastState();
    if (last == lw) {
      AllocState();
    }
    state_index[i + 1] = context_->states_.size();
    last = context_->LastState();
  }
  for (size_t i = 0; i < method_->insns_.size(); ++i) {
    vm_insn_state_map_[i] = context_->states_[state_index[i]];
  }
  AllocState();

  ResolveJumps();
  LinkStates();
  if (is_task_entry_) {
    EmitTaskEntry(context_->states_[0]->state_);
    EmitTaskReturn(context_->states_[context_->states_.size() - 1]->state_);
  }
  if (is_root_ && IsExtEntry()) {
    EmitExtTaskEntry(context_->states_[0]->state_);
    EmitExtTaskDone(context_->states_[context_->states_.size() - 1]->state_);
  }
  if (is_root_ && IsDataFlowEntry()) {
    EmitDataFlowEntry(context_->states_[0]->state_);
  }
  return true;
}

void MethodSynth::SetTaskEntry() {
  is_task_entry_ = true;
}

void MethodSynth::SetRoot() {
  is_root_ = true;
}

MethodContext *MethodSynth::GetContext() {
  return context_.get();
}

void MethodSynth::EmitDataFlowEntry(IState *st) {
  vm::Object *obj = thr_synth_->GetThreadObject();
  CHECK(obj);
  IResource *mb = res_set_->GetMailbox(obj, true, false);
  IResource *df = res_set_->GetDataFlowInResource();
  df->SetParentResource(mb);
  IInsn *df_insn = new IInsn(df);
  st->insns_.push_back(df_insn);
  int width = 0;
  for (IRegister *arg : context_->method_insn_->inputs_) {
    df_insn->outputs_.push_back(arg);
    width += arg->value_type_.GetWidth();
  }
  // 1 for dummy argument.
  if (width == 0) {
    width = 1;
  }
  mb->GetParams()->SetWidth(width);
}

void MethodSynth::EmitTaskEntry(IState *st) {
  IResource *res = res_set_->GetSubModuleTaskResource();
  IInsn *iinsn = new IInsn(res);
  // Args
  for (IRegister *reg : context_->method_insn_->inputs_) {
    iinsn->outputs_.push_back(reg);
    res->output_types_.push_back(reg->value_type_);
  }
  st->insns_.push_back(iinsn);
}

void MethodSynth::EmitTaskReturn(IState *last) {
  int num_rets = method_->GetNumReturnRegisters();
  if (num_rets == 0) {
    return;
  }
  int num_args = method_->GetNumArgRegisters();
  int width = 0;
  for (int i = 0; i < num_rets; ++i) {
    vm::Register *ret = method_->method_regs_[i + num_args];
    if (ret->type_.value_type_ == vm::Value::ENUM_ITEM) {
      // Assumes bool.
      width += 1;
    } else {
      width += ret->type_.width_.GetWidth();
    }
  }
  IResource *res = res_set_->GetTaskReturnRegWriter(width);
  IInsn *insn = new IInsn(res);
  for (int i = 0; i < num_rets; ++i) {
    vm::Register *ret = method_->method_regs_[i + num_args];
    IRegister *reg = local_reg_map_[ret];
    insn->inputs_.push_back(reg);
  }
  insn->SetOperand(iroha::operand::kNotify);
  last->insns_.push_back(insn);
}

void MethodSynth::EmitExtTaskEntry(IState *st) {
  IResource *ext_task = res_set_->GetExtTaskResource();
  string name = method_->GetAnnotation()->GetName();
  if (name.empty()) {
    name = method_name_;
  }
  ext_task->GetParams()->SetExtTaskName(name);
  IInsn *task_insn = new IInsn(ext_task);
  // Args
  for (IRegister *arg : context_->method_insn_->inputs_) {
    task_insn->outputs_.push_back(arg);
    ext_task->output_types_.push_back(arg->value_type_);
  }
  st->insns_.push_back(task_insn);
}

void MethodSynth::EmitExtTaskDone(IState *st) {
  IResource *ext_task_done = res_set_->GetExtTaskDoneResource();
  IResource *ext_task = res_set_->GetExtTaskResource();
  ext_task_done->SetParentResource(ext_task);
  IInsn *task_done_insn = new IInsn(ext_task_done);
  st->insns_.push_back(task_done_insn);
  int num_rets = method_->GetNumReturnRegisters();
  if (num_rets == 0) {
    return;
  }
  int num_args = method_->GetNumArgRegisters();
  for (int i = 0; i < num_rets; ++i) {
    vm::Register *ret = method_->method_regs_[i + num_args];
    IRegister *reg = local_reg_map_[ret];
    task_done_insn->inputs_.push_back(reg);
    ext_task_done->input_types_.push_back(reg->value_type_);
  }
}

bool MethodSynth::IsDataFlowEntry() const {
  return method_->GetAnnotation()->IsDataFlowEntry();
}

bool MethodSynth::IsExtEntry() const {
  return method_->GetAnnotation()->IsExtEntry();
}

void MethodSynth::SynthNativeImplMethod(vm::Method *method) {
  sym_t name = sym_lookup(method->AlternativeImplementation());
  CHECK(name != sym_null);
  vm::Value *value = obj_->LookupValue(name, false);
  CHECK(value && value->type_ == vm::Value::METHOD) << sym_cstr(name);
  vm::Method *alt_method = value->method_;
  CHECK(alt_method->GetAnnotation()->IsImportedModule()) << sym_cstr(name);

  SynthEmbeddedMethod(alt_method);
}

void MethodSynth::SynthEmbeddedMethod(vm::Method *method) {
  EmitEntryInsn(method);
  StateWrapper *sw = AllocState();
  IResource *res = res_set_->GetImportedResource(method);
  IInsn *iinsn = new IInsn(res);
  iinsn->inputs_ = context_->method_insn_->inputs_;
  iinsn->outputs_ = context_->method_insn_->outputs_;
  sw->state_->insns_.push_back(iinsn);
}

void MethodSynth::SynthExtIOMethod() {
  EmitEntryInsn(method_);
  Annotation *an = method_->GetAnnotation();
  if (an->IsExtOutput()) {
    DoSynthExtIO(true);
  }
  if (an->IsExtInput()) {
    DoSynthExtIO(false);
  }
}

void MethodSynth::DoSynthExtIO(bool is_output) {
  IResource *res = rsynth_->MayAddExtIO(method_, is_output);
  IInsn *iinsn = new IInsn(res);
  if (is_output) {
    CHECK(context_->method_insn_->inputs_.size() == 1);
    iinsn->inputs_.push_back(context_->method_insn_->inputs_[0]);
  } else {
    CHECK(context_->method_insn_->outputs_.size() == 1);
    iinsn->outputs_.push_back(context_->method_insn_->outputs_[0]);
  }
  StateWrapper *sw = AllocState();
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
  case vm::OP_BIT_RANGE:
    SynthBitRange(insn);
    break;
  case vm::OP_BIT_INV:
  case vm::OP_LOGIC_INV:
    SynthBitInv(insn);
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
			      src_reg->type_.width_.GetWidth(),
			      src_reg->initial_num_.GetValue());
  local_reg_map_[dst_reg] = ireg;
}

void MethodSynth::SynthAssign(vm::Insn *insn) {
  IRegister *lhs_reg = FindLocalVarRegister(insn->src_regs_[0]);
  IRegister *rhs_reg = FindLocalVarRegister(insn->src_regs_[1]);
  IResource *assign = res_set_->AssignResource();
  IInsn *iinsn = new IInsn(assign);
  iinsn->inputs_.push_back(rhs_reg);
  iinsn->outputs_.push_back(lhs_reg);
  StateWrapper *sw = AllocState();
  sw->state_->insns_.push_back(iinsn);
}

void MethodSynth::SynthLoadObj(vm::Insn *insn) {
  InsnWalker::LoadObj(insn);
}

void MethodSynth::SynthPreIncDec(vm::Insn *insn) {
  IValueType vt;
  InsnToCalcValueType(insn, &vt);
  IResource *res = res_set_->GetOpResource(insn->op_ == vm::OP_PRE_INC ?
				       vm::OP_ADD : vm::OP_SUB,
				       vt);
  IInsn *iinsn = new IInsn(res);
  IRegister *reg = FindLocalVarRegister(insn->src_regs_[0]);
  iinsn->inputs_.push_back(reg);
  int w = reg->value_type_.GetWidth();
  iinsn->inputs_.push_back(DesignTool::AllocConstNum(tab_, w, 1));
  iinsn->outputs_.push_back(reg);
  StateWrapper *sw = AllocState();
  sw->state_->insns_.push_back(iinsn);
}

void MethodSynth::SynthNative(vm::Insn *insn) {
  ObjectMethod m(this, this, rsynth_, insn);
  m.Synth();
}

void MethodSynth::SynthFuncall(vm::Insn *insn) {
  if (IsNativeFuncall(insn)) {
    SynthNative(insn);
    return;
  }

  // Setup arguments.
  vector<IRegister *> iargs;
  for (vm::Register *arg : insn->src_regs_) {
    IRegister *iarg = FindLocalVarRegister(arg);
    iargs.push_back(iarg);
  }
  if (IsDataFlowCall(insn) || IsExtStubCall(insn)) {
    AdjustArgWidth(insn, &iargs);
  }
  IInsn *iinsn = new IInsn(res_set_->PseudoCallResource());
  StateWrapper *sw = AllocState();
  sw->state_->insns_.push_back(iinsn);
  for (IRegister *iarg : iargs) {
    iinsn->inputs_.push_back(iarg);
  }

  vm::Object *callee_obj = GetCalleeObject(insn);
  sym_t func_name = insn->label_;
  sw->callee_func_name_ = sym_str(func_name);
  sw->callee_vm_obj_ = callee_obj;
  if (IsExtStubCall(insn)) {
    sw->is_ext_stub_call_ = true;
    sw->is_ext_flow_stub_call_ = IsExtFlowStubCall(insn);
  }
  if (IsDataFlowCall(insn)) {
    sw->is_data_flow_call_ = true;
  }
  if (IsSubObjCall(insn)) {
    CHECK(callee_obj);
    sw->is_sub_obj_call_ = true;
    DesignSynth *ds = thr_synth_->GetObjectSynth()->GetDesignSynth();
    sw->obj_name_ = ds->GetObjectName(callee_obj);
  }
}

void MethodSynth::AdjustArgWidth(vm::Insn *insn,
				 vector<IRegister *> *args) {
  vm::Object *callee_obj = GetCalleeObject(insn);
  vm::Value *value = callee_obj->LookupValue(insn->label_, false);
  CHECK(value && value->type_ == vm::Value::METHOD) << sym_cstr(insn->label_);
  vm::Method *method = value->method_;
  int num_args = method->GetNumArgRegisters();
  CHECK(num_args == args->size());
  for (int i = 0; i < args->size(); ++i) {
    IRegister *arg = args->at(i);
    const iroha::NumericWidth &actual_width = method->GetNthArgWidth(i);
    if (arg->value_type_.GetWidth() != actual_width.GetWidth()) {
      IResource *assign = res_set_->AssignResource();
      IRegister *lhs = thr_synth_->AllocRegister("df_arg_");
      lhs->value_type_.SetWidth(actual_width.GetWidth());
      IInsn *a = new IInsn(assign);
      a->inputs_.push_back(arg);
      a->outputs_.push_back(lhs);
      StateWrapper *sw = AllocState();
      sw->state_->insns_.push_back(a);
      (*args)[i] = lhs;
    }
  }
}

void MethodSynth::SynthFuncallDone(vm::Insn *insn) {
  // Adds return values to the insn generated for funcall.
  StateWrapper *sw = context_->LastState();
  CHECK(sw->state_->insns_.size() == 1);
  IInsn *iinsn = sw->state_->insns_[0];
  for (vm::Register *ret : insn->dst_regs_) {
    IRegister *iret = FindLocalVarRegister(ret);
    iinsn->outputs_.push_back(iret);
  }

  if (IsSubObjCall(insn) || IsExtStubCall(insn)) {
    // state for capturing return value.
    AllocState();
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
  IResource *concat = res_set_->GetOpResource(vm::OP_CONCAT, vt);
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
  int msb = insn->src_regs_[1]->initial_num_.GetValue();
  int lsb = insn->src_regs_[2]->initial_num_.GetValue();

  StateWrapper *sw = AllocState();
  IValueType vt_none;
  IResource *bit_sel = res_set_->GetOpResource(vm::OP_BIT_RANGE, vt_none);
  IInsn *iinsn = new IInsn(bit_sel);

  iinsn->inputs_.push_back(src);
  iinsn->inputs_.push_back(DesignTool::AllocConstNum(tab_, 32, msb));
  iinsn->inputs_.push_back(DesignTool::AllocConstNum(tab_, 32, lsb));
  iinsn->outputs_.push_back(res);
  sw->state_->insns_.push_back(iinsn);
}

void MethodSynth::SynthBitInv(vm::Insn *insn) {
  IRegister *src = FindLocalVarRegister(insn->src_regs_[0]);
  IRegister *res = FindLocalVarRegister(insn->dst_regs_[0]);
  GenNeg(src, res);
}

IRegister *MethodSynth::FindLocalVarRegister(vm::Register *vreg) {
  IRegister *ireg = local_reg_map_[vreg];
  if (ireg) {
    return ireg;
  }
  char name[10];
  sprintf(name, "r%d_", vreg->id_);
  int w = vreg->type_.width_.GetWidth();
  if (vreg->type_.value_type_ == vm::Value::ENUM_ITEM) {
    w = 0;
  }
  ireg = thr_synth_->AllocRegister(name + method_name_);
  ireg->value_type_.SetWidth(w);
  local_reg_map_[vreg] = ireg;
  return ireg;
}

ITable *MethodSynth::GetITable() {
  return tab_;
}

IRegister *MethodSynth::FindArgRegister(vm::Method *method, int nth,
					fe::VarDecl *arg_decl) {
  int w = 0;
  if (arg_decl->GetType() == sym_bool) {
    w = 0;
  } else if (arg_decl->GetType() == sym_int ||
	     arg_decl->GetType() == sym_null) {
    w = arg_decl->GetWidth().GetWidth();
  } else {
    CHECK(false);
  }
  string reg_name = sym_str(arg_decl->GetNameExpr()->sym_);
  IRegister *reg = thr_synth_->AllocRegister(reg_name);
  reg->value_type_.SetWidth(w);
  // Add as a local variable if this isn't an imported method.
  if (!(method->GetAnnotation()->IsImportedModule())) {
    local_reg_map_[method->method_regs_[nth]] = reg;
  }
  return reg;
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
  IResource *res = res_set_->GetOpResource(insn->op_, vt);
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
  int shift_count = insn->src_regs_[1]->initial_num_.GetValue();
  IValueType vt;
  IResource *shifter = res_set_->GetOpResource(insn->op_, vt);
  IInsn *iinsn = new IInsn(shifter);
  iinsn->inputs_.push_back(FindLocalVarRegister(insn->src_regs_[0]));
  iinsn->inputs_.push_back(DesignTool::AllocConstNum(tab_, 32, shift_count));
  iinsn->outputs_.push_back(FindLocalVarRegister(insn->dst_regs_[0]));
  if (insn->op_ == vm::OP_LSHIFT) {
    iinsn->SetOperand(iroha::operand::kLeft);
  } else {
    iinsn->SetOperand(iroha::operand::kRight);
  }
  StateWrapper *w = AllocState();
  w->state_->insns_.push_back(iinsn);
}

void MethodSynth::SynthGoto(vm::Insn *insn) {
  StateWrapper *w = AllocState();
  w->vm_insn_ = insn;
}

void MethodSynth::SynthMemberAccess(vm::Insn *insn, bool is_store) {
  InsnWalker::MaybeLoadMemberObject(insn);
  vm::Object *obj;
  if (is_store) {
    obj = member_reg_to_obj_map_[insn->src_regs_[1]];
  } else {
    obj = member_reg_to_obj_map_[insn->src_regs_[0]];
  }
  CHECK(obj);
  vm::Value *value = obj->LookupValue(insn->label_, false);
  CHECK(value) << "member not found";
  if (value->is_const_) {
    // assuming only bool type for now.
    CHECK(!is_store);
    CHECK(value->type_ == vm::Value::ENUM_ITEM);
    IRegister *reg = DesignTool::AllocConstNum(tab_, 0, value->enum_val_.val);
    local_reg_map_[insn->dst_regs_[0]] = reg;
  } else if (value->type_ == vm::Value::OBJECT) {
    // processed in MaybeLoadMemberObject()
    CHECK(!is_store);
  } else {
    SharedResource *sres =
      shared_resource_set_->GetBySlotName(obj, insn->label_);
    if (sres->accessors_.size() > 1) {
      SynthMemberSharedRegAccess(insn, value, is_store);
    } else {
      SynthMemberRegAccess(insn, value, is_store);
    }
  }
}

void MethodSynth::SynthMemberRegAccess(vm::Insn *insn, vm::Value *value,
				       bool is_store) {
  IRegister *reg = member_name_reg_map_[sym_cstr(insn->label_)];
  if (!reg) {
    string name = sym_cstr(insn->label_);
    name = "m_" + name;
    reg = thr_synth_->AllocRegister(name);
    iroha::Numeric iv;
    iv.SetValue(value->num_.GetValue());
    reg->SetInitialValue(iv);
    int w = 0;
    if (value->type_ == vm::Value::NUM) {
      w = value->num_.type_.GetWidth();
    }
    reg->value_type_.SetWidth(w);
    member_name_reg_map_[sym_cstr(insn->label_)] = reg;
  }
  IResource *assign = res_set_->AssignResource();
  IInsn *iinsn = new IInsn(assign);
  if (is_store) {
    iinsn->inputs_.push_back(FindLocalVarRegister(insn->src_regs_[0]));
    iinsn->outputs_.push_back(reg);
  } else {
    iinsn->inputs_.push_back(reg);
    iinsn->outputs_.push_back(FindLocalVarRegister(insn->dst_regs_[0]));
  }
  StateWrapper *sw = AllocState();
  sw->state_->insns_.push_back(iinsn);
}

void MethodSynth::SynthMemberSharedRegAccess(vm::Insn *insn, vm::Value *value,
					     bool is_store) {
  SharedResource *sres =
    shared_resource_set_->GetBySlotName(obj_, insn->label_);
  IResource *res;
  if (sres->owner_thr_ == thr_synth_) {
    res = res_set_->GetMemberSharedReg(insn->label_, true, is_store);
    sres->AddOwnerResource(res);
    int w = value->num_.type_.GetWidth();
    auto *params = res->GetParams();
    params->SetWidth(w);
  } else {
    res = res_set_->GetMemberSharedReg(insn->label_, false, is_store);
    sres->AddAccessorResource(res);
  }
  IInsn *iinsn = new IInsn(res);
  vm::Register *vm_reg;
  if (is_store) {
    vm_reg = insn->src_regs_[0];
  } else {
    vm_reg = insn->dst_regs_[0];
  }
  IRegister *ireg = FindLocalVarRegister(vm_reg);
  if (is_store) {
    iinsn->inputs_.push_back(ireg);
  } else {
    iinsn->outputs_.push_back(ireg);
  }
  StateWrapper *sw = AllocState();
  sw->state_->insns_.push_back(iinsn);
}

void MethodSynth::SynthChannelAccess(vm::Insn *insn, bool is_write) {
  vm::Object *obj = member_reg_to_obj_map_[insn->obj_reg_];
  CHECK(vm::Channel::IsChannel(obj));
  int width = vm::Channel::ChannelWidth(obj);
  IResource *res = res_set_->GetChannelResource(obj, is_write, width);
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
    res = res_set_->GetExternalArrayResource();
  } else {
    if (UseSharedArray(array_obj)) {
      SynthSharedArrayAccess(insn, is_write);
      return;
    }
    res = res_set_->GetInternalArrayResource(array_obj);
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

bool MethodSynth::UseSharedArray(vm::Object *array_obj) {
  SharedResource *sres =
    shared_resource_set_->GetByObj(array_obj);
  Annotation *a = vm::ArrayWrapper::GetAnnotation(array_obj);
  if (a != nullptr && (a->IsAxiMaster() || a->IsAxiSlave())) {
    return true;
  }
  if (sres->accessors_.size() >= 2 ||
      sres->axi_ctrl_thrs_.size() > 0) {
    return true;
  }
  return false;
}

void MethodSynth::SynthSharedArrayAccess(vm::Insn *insn, bool is_write) {
  vm::Object *array_obj = GetObjByReg(insn->obj_reg_);
  SharedResource *sres =
    shared_resource_set_->GetByObj(array_obj);
  IResource *res = nullptr;
  if (sres->owner_thr_ == thr_synth_) {
    res = res_set_->GetSharedArray(array_obj, true, false);
    sres->AddOwnerResource(res);
    rsynth_->MayAddAxiSlavePort(obj_, array_obj);
  } else {
    res = res_set_->GetSharedArray(array_obj, false, is_write);
    sres->AddAccessorResource(res);
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
  StateWrapper *sw = AllocState();
  sw->state_->insns_.push_back(iinsn);
}

void MethodSynth::GenNeg(IRegister *src, IRegister *dst) {
  StateWrapper *w = AllocState();
  IValueType vt;
  vt.SetWidth(0);
  IResource *bit_inv = res_set_->GetOpResource(vm::OP_BIT_INV, vt);
  IInsn *insn = new IInsn(bit_inv);
  insn->inputs_.push_back(src);
  insn->outputs_.push_back(dst);
  w->state_->insns_.push_back(insn);
}

void MethodSynth::EmitEntryInsn(vm::Method *method) {
  // This insn doesn't belong to a state.
  IResource *pseudo = res_set_->PseudoCallResource();
  context_->method_insn_ = new IInsn(pseudo);
  context_->method_insn_->SetOperand("method_entry");

  fe::VarDeclSet *args = nullptr;
  if (method->parse_tree_ != nullptr) {
    args = method->parse_tree_->args_;
  }
  int num_args = 0;
  if (args) {
    num_args = args->decls.size();
    for (size_t i = 0; i < args->decls.size(); ++i) {
      IRegister *ireg = FindArgRegister(method, i, args->decls[i]);
      context_->method_insn_->inputs_.push_back(ireg);
    }
  }
  fe::VarDeclSet *rets = nullptr;
  if (method->parse_tree_ != nullptr) {
    rets = method->parse_tree_->returns_;
  }
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
    vt->SetWidth(reg->type_.width_.GetWidth());
  } else if (reg->type_.value_type_ == vm::Value::ENUM_ITEM) {
    vt->SetWidth(reg->type_.width_.GetWidth());
  }
}

}  // namespace synth
