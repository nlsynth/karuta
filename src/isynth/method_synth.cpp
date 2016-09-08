#include "isynth/method_synth.h"

#include "compiler/compiler.h"
#include "dfg/resource_params.h"
#include "fe/expr.h"
#include "fe/method.h"
#include "fe/var_decl.h"
#include "iroha/iroha.h"
#include "iroha/i_design.h"
#include "isynth/thread_synth.h"
#include "isynth/object_synth.h"
#include "isynth/resource_set.h"
#include "isynth/method_context.h"
#include "status.h"
#include "vm/insn.h"
#include "vm/method.h"
#include "vm/object.h"
#include "vm/register.h"

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
  for (size_t i = 0; i < method->insns_.size(); ++i) {
    SynthInsn(method->insns_[i]);
  }
  AllocState();
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
  dfg::ResourceParams *imported_resource =
    method->parse_tree_->imported_resource_;
  IResource *res = res_->GetImportedResource(imported_resource);
  IInsn *iinsn = new IInsn(res);
  iinsn->inputs_ = context_->method_insn_->inputs_;
  iinsn->outputs_ = context_->method_insn_->outputs_;
  sw->state_->insns_.push_back(iinsn);
}

void MethodSynth::LinkStates() {
  for (size_t i = 0; i < context_->states_.size() - 1; ++i) {
    StateWrapper *s0 = context_->states_[i];
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
    break;
  case vm::OP_LOAD_OBJ:
    SynthLoadObj(insn);
    break;
  case vm::OP_ADD:
    SynthBinCalcExpr(insn);
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

IRegister *MethodSynth::FindLocalVarRegister(vm::Register *vreg) {
  IRegister *ireg = local_reg_map_[vreg];
  if (ireg) {
    return ireg;
  }
  char name[10];
  sprintf(name, "r%d_", vreg->id_);
  int w = numeric::Width::GetWidth(vreg->type_.width_);
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

StateWrapper *MethodSynth::AllocState() {
  StateWrapper *w = new StateWrapper();
  IState *st = new IState(tab_);
  w->state_ = st;
  context_->states_.push_back(w);
  return w;
}

void MethodSynth::SynthBinCalcExpr(vm::Insn *insn) {
}

void MethodSynth::SynthGoto(vm::Insn *insn) {
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
  }
}

}  // namespace isynth
