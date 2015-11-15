#include "synth/thread_synth.h"

#include "dfg/dfg.h"
#include "synth/method_synth.h"
#include "synth/resource_set.h"
#include "vm/vm.h"

namespace synth {

ThreadSynth::ThreadSynth(vm::VM *vm, vm::Object *obj, DModule *module,
			 const char *method_name)
  : vm_(vm), obj_(obj), module_(module), method_name_(method_name),
    root_method_synth_(nullptr) {
  graph_ = DGraphUtil::Create(module);
  resource_.reset(new ResourceSet(graph_));
}

ThreadSynth::~ThreadSynth() {
  STLDeleteSecondElements(&function_map_);
}

bool ThreadSynth::Synth() {
  set<sym_t> all_functions;
  all_functions.insert(sym_lookup(method_name_));
  int num_compiled;
  do {
    num_compiled = 0;
    set<sym_t> all_called;
    for (sym_t name : all_functions) {
      if (function_map_.find(name) != function_map_.end()) {
	// Already compiled.
	continue;
      }
      ++num_compiled;
      bool is_task_root = false;
      if (!root_method_synth_ &&
	  module_->module_type_ == DModule::MODULE_TASK) {
	is_task_root = true;
      }
      MethodSynth *synth =
	new MethodSynth(vm_, obj_, sym_cstr(name), is_task_root,
			resource_.get(), graph_);
      if (!root_method_synth_) {
	// First function is the root.
	root_method_synth_ = synth;
      }
      if (!synth->Synth()) {
	return false;
      }
      function_map_[name] = synth;

      for (sym_t called : synth->GetCalledFunctions()) {
	all_called.insert(called);
      }
    }
    for (sym_t s : all_called) {
      all_functions.insert(s);
    }
  } while (num_compiled > 0);
  return true;
}

void ThreadSynth::ExpandFunctions() {
  MethodSynth *entry_func = function_map_[sym_lookup(method_name_)];
  CHECK(entry_func);
  while (ExpandOneFunction(entry_func)) {
    // just loop.
  }

  DState *initial = root_method_synth_->InitialState();
  DStateUtil::SetNextState(graph_, graph_->initial_state_, initial);
  DState *last = root_method_synth_->LastState();
  DStateUtil::SetNextState(graph_, last, last);
  graph_->last_state_ = last;

  AddMemberInitializers();

  DGraphUtil::KillIntermediateResource(graph_);
}

bool ThreadSynth::ExpandOneFunction(MethodSynth *func) {
  int num_expand = 0;
  set<DState*> reachable;
  DStateUtil::CollectReachable(graph_, func->InitialState(), &reachable);
  DResource *funcall = resource_->FuncallResource();
  for (auto *state : reachable) {
    DInsn *call_insn = DStateUtil::FindInsnByResource(state, funcall);
    if (!call_insn) {
      continue;
    }
    ++num_expand;
    sym_t callee_name = sym_lookup(call_insn->func_name_.c_str());
    MethodSynth *callee = function_map_[callee_name];
    CHECK(callee);
    CopiedFunctionStates copied = CopyFunction(callee, call_insn);

    DState *next = DStateUtil::GetNextState(graph_, state);
    DStateUtil::SetNextState(graph_, state, copied.initial);
    DStateUtil::SetNextState(graph_, copied.final, next);

    DStateUtil::EraseInsn(state, call_insn);
  }
  return (num_expand > 0);
}

CopiedFunctionStates ThreadSynth::CopyFunction(MethodSynth *func,
					       DInsn *call_insn) {
  vector<DState *> &orig_states = func->AllStates();
  // mapping of orig -> new.
  map<DState *, DState *> state_mapping;
  for (size_t i = 0; i < orig_states.size(); ++i) {
    DState *new_state = DGraphUtil::AllocState(graph_);
    state_mapping[orig_states[i]] = new_state;
  }
  map<DRegister *, DRegister *> reg_mapping;
  RewriteArgs(call_insn, orig_states[0], &reg_mapping);
  CopyStates(state_mapping, func, &reg_mapping);
  CopiedFunctionStates copy;
  copy.initial = state_mapping[func->InitialState()];
  copy.final = state_mapping[func->LastState()];
  return copy;
}

void ThreadSynth::RewriteArgs(DInsn *call_insn, DState *callee_state,
			      map<DRegister *, DRegister *> *reg_mapping) {
  DInsn *callee_insn =
    DStateUtil::FindInsnByResource(callee_state,
				   resource_->FunctionEntryResource(false));
  for (size_t i = 0; i < callee_insn->inputs_.size(); ++i) {
    (*reg_mapping)[callee_insn->inputs_[i]] = call_insn->inputs_[i];
  }
  for (size_t i = 0; i < callee_insn->outputs_.size(); ++i) {
    DRegister *ret_reg = call_insn->outputs_[i];
    if (ret_reg) {
      (*reg_mapping)[callee_insn->outputs_[i]] = ret_reg;
    }
    // else. the number of return values is smaller.
  }
}

void ThreadSynth::CopyStates(map<DState *, DState *> &state_mapping,
			     MethodSynth *func,
			     map<DRegister *, DRegister *> *reg_mapping) {
  vector<DState *> &orig_states = func->AllStates();
  for (size_t i = 0; i < orig_states.size(); ++i) {
    DState *orig_state = orig_states[i];
    DState *new_state = state_mapping[orig_state];
    for (list<DInsn *>::iterator it = orig_state->insns_.begin();
	 it != orig_state->insns_.end(); ++it) {
      DInsn *orig_insn = *it;
      DInsn *new_insn = DGraphUtil::InsnNew(graph_, orig_insn->resource_);
      new_insn->func_name_ = orig_insn->func_name_;
      new_state->insns_.push_back(new_insn);
      // copy target states.
      for (vector<DState *>::iterator jt = orig_insn->targets_.begin();
	   jt != orig_insn->targets_.end(); ++jt) {
	DState *orig_target = *jt;
	DState *new_target = state_mapping[orig_target];
	new_insn->targets_.push_back(new_target);
      }
      // copy input/output regs.
      CopyInsnRegs(orig_insn, &orig_insn->inputs_,
		   &new_insn->inputs_, reg_mapping);
      CopyInsnRegs(orig_insn, &orig_insn->outputs_,
		   &new_insn->outputs_, reg_mapping);
    }
  }
}

void ThreadSynth::CopyInsnRegs(DInsn *src, vector<DRegister *> *orig_regs,
			       vector<DRegister *> *new_regs,
			       map<DRegister *, DRegister *> *reg_map) {
  for (size_t i = 0; i < orig_regs->size(); ++i) {
    DRegister *orig_reg = orig_regs->at(i);
    if (orig_reg->reg_type_ == DRegister::REG_CONST ||
	orig_reg->has_initial_) {
      new_regs->push_back(orig_reg);
    } else {
      map<DRegister *, DRegister *>::iterator it = reg_map->find(orig_reg);
      if (it == reg_map->end()) {
	DRegister *reg = DGraphUtil::AllocTmpReg(graph_, orig_reg->data_type_);
	(*reg_map)[orig_reg] = reg;
	new_regs->push_back(reg);
      } else {
	new_regs->push_back(it->second);
      }
    }
  }
}

void ThreadSynth::AddMemberInitializers() {
  DResource *assign = DGraphUtil::FindResource(graph_, sym_assign, true);
  for (DRegister *reg : graph_->registers_) {
    if (!reg->has_initial_) {
      continue;
    }
    reg->has_initial_ = false;
    DInsn *insn = DGraphUtil::InsnNew(graph_, assign);
    insn->inputs_.push_back(DGraphUtil::CloneInitialValue(graph_, reg));
    insn->outputs_.push_back(reg);
    graph_->initial_state_->insns_.push_back(insn);
  }
}

ResourceSet *ThreadSynth::GetResource() {
  return resource_.get();
}

DModule *ThreadSynth::GetModule() {
  return module_;
}

}  // namespace synth
