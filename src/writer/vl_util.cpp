#include "writer/vl_util.h"

#include "dfg/dfg.h"

namespace writer {

void VLIOSet::AddPin(const string &name, PinType type, int width,
		     const string &comment) {
  Pin pin;
  pin.name_ = name;
  pin.type_ = type;
  pin.width_ = width;
  pin.comment_ = comment;
  pins_.push_back(pin);
}

void VLIOSet::Output(bool only_names, ostream &os) {
  for (size_t i = 0; i < pins_.size(); ++i) {
    Pin &pin = pins_[i];
    if (only_names) {
      if (i > 0) {
	os << ", ";
      }
      os << pin.name_;
    } else {
      if (i > 0 && !pin.comment_.empty() &&
	  pins_[i-1].comment_ != pin.comment_) {
	os << "  // " << pin.comment_ << "\n";
      }
      os << "  ";
      if (pin.type_ == VLIOSet::OUTPUT ||
	  pin.type_ == VLIOSet::OUTPUT_WIRE) {
	os << "output";
      } else {
	os << "input";
      }
      if (pin.width_ > 0) {
	os << " [" << (pin.width_ - 1) << ":0]";
      }
      os << " " << pin.name_ << ";\n";
    }
  }

  bool has_buffer_reg = false;
  if (!only_names) {
    for (size_t i = 0; i < pins_.size(); ++i) {
      Pin &pin = pins_[i];
      if (pin.type_ == VLIOSet::OUTPUT) {
	if (!has_buffer_reg) {
	  has_buffer_reg = true;
	  os << "\n";
	}
	os << "  reg";
	if (pin.width_ > 0) {
	  os << " [" << (pin.width_ - 1) << ":0]";
	}
	os << " " << pin.name_ << ";\n";
      }
    }
  }
}

VLStateEncoder::VLStateEncoder(DGraph *graph) {
  int max = -1;
  for (DState *st : graph->states_) {
    if (max < st->state_id_) {
      max = st->state_id_;
    }
  }
  if (graph->owner_module_->module_type_ == DModule::MODULE_TASK) {
    ++max;
    task_entry_state_ = max;
  } else {
    task_entry_state_ = -1;
  }
  // Calculates the minimum width to represent [0..max].
  int w;
  for (w = 0; max > 0; w++, max /= 2);
  state_width_ = w;
}

int VLStateEncoder::GetStateWidth() {
  return state_width_;
}

int VLStateEncoder::GetEncodedState(DState *st) {
  return st->state_id_;
}

int VLStateEncoder::GetTaskEntryState() {
  return task_entry_state_;
}

string VLStateEncoder::StateNameWithoutQuote(const DState *st) {
  char buf[10];
  sprintf(buf, "S_%d", st->state_id_);
  return string(buf);
}

string VLStateEncoder::StateName(const DState *st) {
  return "`" + StateNameWithoutQuote(st);
}

string VLStateEncoder::TaskEntryStateName() {
  return "`" +  TaskEntryStateNameWithoutQuote();
}

string VLStateEncoder::TaskEntryStateNameWithoutQuote() {
  char buf[10];
  sprintf(buf, "S_%d", task_entry_state_);
  return string(buf);
}
  
string VLUtil::TaskControlPinName(const DModule *dm) {
  return dm->parent_mod_->module_name_ + "_" + dm->module_name_;
}

string VLUtil::TaskControlPinNameFromInsn(const DGraph *graph,
					  const DInsn *insn) {
  DModule *callee_mod = nullptr;
  for (DModule *mod : graph->owner_module_->sub_modules_) {
    if (mod->module_name_ == insn->resource_->name_) {
      callee_mod = mod;
    }
  }
  CHECK(callee_mod);
  if (callee_mod->module_type_ == DModule::MODULE_TASK) {
    return TaskControlPinName(callee_mod);
  } else {  // DMODULE_CONTAINER
    DModule *sub_module = nullptr;
    for (DModule *mod : callee_mod->sub_modules_) {
      cout << mod->module_name_;
      if (mod->module_name_ == insn->func_name_) {
	sub_module = mod;
      }
    }
    CHECK(sub_module);
    return TaskControlPinName(sub_module);
  }
}

bool VLUtil::IsExternalRAM(const DResource *r) {
  if (r->opr_->type_ == sym_sram_if &&
      !r->array_) {
    return true;
  }
  return false;
}

bool VLUtil::IsInternalMEM(const DResource *r) {
  if (r->opr_->type_ == sym_sram_if &&
      r->array_) {
    return true;
  }
  return false;
}

bool VLUtil::IsResourceShareBinOp(const DResource *r) {
  sym_t type = r->opr_->type_;
  if (type == sym_add || type == sym_sub ||
      type == sym_gt || type == sym_mul) {
    return true;
  }
  return false;
}

bool VLUtil::IsResourceUnshareBinOp(const DResource *r) {
  sym_t type = r->opr_->type_;
  if (type == sym_eq || type == sym_bit_or ||
      type == sym_bit_and || type == sym_bit_xor ||
      type == sym_logic_and || type == sym_logic_or ||
      type == sym_selector) {
    return true;
  }
  return false;
}

bool VLUtil::IsResourceUnshareUniOp(const DResource *r) {
  sym_t type = r->opr_->type_;
  if (type == sym_logic_inv || type == sym_or_reduce) {
    return true;
  }
  return false;
}

}  // namespace writer
