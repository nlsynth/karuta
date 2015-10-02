#include "writer/cc_state.h"

#include "dfg/dfg.h"
#include "writer/cc_class.h"
#include "writer/cc_writer.h"
#include "writer/module_template.h"
#include "writer/writer_util.h"

static sym_t sym_print, sym_assert;

namespace writer {

CCState::CCState(const DState *state, ClassWriter *cw)
  : state_(state), cw_(cw), os_(cw->os()) {
  sym_print = sym_lookup("print");
  sym_assert = sym_lookup("assert");
}

void CCState::PreProcess(ModuleTemplate *tmpl) {
  ostream &sr = tmpl->GetStream(ModuleTemplate::RESET_STATE);
  for (const DInsn *insn : state_->insns_) {
    if (WriterUtil::IsMultiCycleInsn(insn)) {
      sr << "  " << SubStateRegName(insn) << " = 0;\n";
    }
  }
}

void CCState::Output() {
  char buf[16];
  sprintf(buf, "s_%d()", state_->state_id_);
  cw_->AddMember("", "void", buf);
  set<const DRegister *> wires;
  for (const DInsn *insn : state_->insns_) {
    for (const DRegister *reg : insn->inputs_) {
      if (reg->reg_type_ == DRegister::REG_WIRE) {
	wires.insert(reg);
      }
    }
  }
  for (const DRegister *reg : wires) {
    os_ << "  uint64_t " << RegisterName(reg) << ";\n";
  }
  OutputInsnList();
  if (IsTerminal()) {
    os_ << "  finish_ = true;\n";
  }
  cw_->EndMethod();

  for (const DInsn *insn : state_->insns_) {
    if (WriterUtil::IsMultiCycleInsn(insn)) {
      string st_name = SubStateRegName(insn);
      cw_->AddMember("", "int", st_name);
    }
  }
}

string CCState::RegisterName(const DRegister *reg) {
  if (reg->reg_type_ == DRegister::REG_NORMAL ||
      reg->reg_type_ == DRegister::REG_WIRE) {
    return reg->reg_name_;
  } else {
    char buf[20];
    sprintf(buf, "%luUL", reg->num_);
    return string(buf);
  }
}

void CCState::OutputBinOp(const DInsn *insn) {
  os_ << "  " << RegisterName(*(insn->outputs_.begin()))
      << " = " << RegisterName(*(insn->inputs_.begin()))
      << " ";
  sym_t type = insn->resource_->opr_->type_;
  if (type == sym_add) {
    os_ << "+";
  } else if (type == sym_sub) {
    os_ << "-";
  } else if (type == sym_mul) {
    os_ << "*";
  } else if (type == sym_gt) {
    os_ << ">";
  } else if (type == sym_lt) {
    os_ << "<";
  } else if (type == sym_eq) {
    os_ << "==";
  } else if (type == sym_lshift) {
    os_ << "<<";
  } else if (type == sym_rshift) {
    os_ << ">>";
  } else if (type == sym_bit_or) {
    os_ << "|";
  } else if (type == sym_bit_and) {
    os_ << "&";
  } else if (type == sym_bit_xor) {
    os_ << "^";
  } else {
    CCWriter::ICE("unknown binop", type);
  }
  os_ << " " << RegisterName(*(insn->inputs_.rbegin())) << ";\n";
}

void CCState::OutputAssign(const DInsn *insn) {
  os_ << "  " << RegisterName(*(insn->outputs_.begin()))
      << " = " << RegisterName(*(insn->inputs_.begin()))
    << ";\n";
}

void CCState::OutputUniOp(const DInsn *insn) {
  os_ << "  ";
  sym_t type = insn->resource_->opr_->type_;
  os_ << RegisterName(*(insn->outputs_.begin()))
      << " =";
  if (type == sym_logic_inv) {
    os_ << "!";
  }
  os_ << RegisterName(*(insn->inputs_.begin()))
      << ";\n";
}

void CCState::OutputBranch(const DInsn *insn) {
  vector<DRegister *>::const_iterator it;
  vector<DState *>::const_iterator jt;
  for (it = insn->inputs_.begin(), jt = insn->targets_.begin();
       it != insn->inputs_.end();
       it ++, jt ++) {
    os_ << "  if (" << RegisterName(*it)
	<< ") state = " << ((*jt)->state_id_) << ";\n"
	<< "  else\n";
  }
  os_ << "  state = " << (*jt)->state_id_ << ";\n";
}

void CCState::OutputSRAMInsn(const DInsn *insn) {
  string ram_name = "NULL";
  const string &ram_id = insn->resource_->name_;
  if (!ram_id.empty()) {
    ram_name = "&" + ram_id + "_inst";
  }
  if (insn->inputs_.size() == 2) {
    // write
    os_ << "  SRAMWrite("
	<< RegisterName((*insn->inputs_.begin()))
	<< ", " << RegisterName((*insn->inputs_.rbegin()))
	<< ", " << ram_name << ");\n";
  } if (insn->outputs_.size() == 0) {
    // read cycle 1/2
    //  nothing
  } else {
    // read cycle 2/2
    os_ << "  " << RegisterName((*insn->outputs_.begin()))
	<< " = SRAMRead(" << RegisterName((*insn->inputs_.begin()))
	<< ", " << ram_name << ");\n";
  }
}

void CCState::OutputBitSelInsn(const DInsn *insn) {
  WriterUtil::BitSelOperands opr;
  WriterUtil::DecodeBitSelInsn(insn, &opr);
  os_ << "  " << RegisterName(*(insn->outputs_.begin()))
      << " = BitSelect(" << RegisterName(*(insn->inputs_.begin())) << ", "
      << opr.src_msb_pos << ", " << opr.src_lsb_pos << ");\n";
}

void CCState::OutputBitConcatInsn(const DInsn *insn) {
  os_ << "  ";
  const DRegister *output = *(insn->outputs_.begin());
  os_ << RegisterName(output)
      << " = 0;\n";
  // Number of input should be 2, though this code can process more
  // than 2.
  for (DRegister *reg : insn->inputs_) {
    os_ << "  " << RegisterName(output)
	<< " <<= " << reg->data_type_->size_ << ";\n"
	<< "  " << RegisterName(output)
	<< " |= " << RegisterName(reg)
	<< ";\n";
  }
}

void CCState::OutputImportedInsn(const DInsn *insn) {
  const sym_t type = sym_lookup(insn->resource_->name_.c_str());
  if (type == sym_print) {
    for (const DRegister *reg : insn->inputs_) {
      os_ << "  cout << " << RegisterName(reg)
	  << " << \"\\n\";\n";
    }
  } else if (type == sym_assert) {
    const DRegister *reg = *(insn->inputs_.begin());
    os_ << "  Assert(" << RegisterName(reg) << ");\n";
  } else {
    CCWriter::ICE("imported insn", sym_lookup(insn->resource_->name_.c_str()));
  }
}

void CCState::OutputSelectorInsn(const DInsn *insn) {
  os_ << "  " << RegisterName(*(insn->outputs_.begin()));
  vector<DRegister *>::const_iterator it = insn->inputs_.begin();
  DRegister *op1 = *(it++);
  DRegister *op2 = *(it++);
  DRegister *cond = *it;
  os_ << " = " << RegisterName(cond) << " ? " << RegisterName(op2)
      << " : " << RegisterName(op1)
      << ";\n";
}

void CCState::OutputChannelWriteInsn(const DInsn *insn) {
  os_ << "  // channel write.\n";
  string channel_name = insn->resource_->name_ + "_channel_inst";
  os_ << "  " << channel_name << ".Write("
      << RegisterName((*insn->inputs_.begin())) << ");\n";
}

void CCState::OutputChannelReadInsn(const DInsn *insn) {
  os_ << "  // channel read.\n";
  string channel_name = insn->resource_->name_ + "_channel_inst";
  os_ << "  " << RegisterName((*insn->outputs_.begin())) << " = "
      << channel_name << ".Read();\n";
}

void CCState::OutputInsnList() {
  list<DInsn *> insns = state_->insns_;
  set<DRegister *> wires;
  // TODO(yusuke): reorder by wire dependency
  do {
    list<DInsn *> insns_to_be_later;
    for (DInsn *insn : insns) {
      // check inputs.
      bool all_ready = true;
      for (DRegister *input : insn->inputs_) {
	if (input->reg_type_ == DRegister::REG_WIRE &&
	    wires.find(input) == wires.end()) {
	  all_ready = false;
	}
      }
      if (!all_ready) {
	insns_to_be_later.push_back(insn);
	continue;
      }
      // output and add wires.
      OutputInsn(insn);
      for (DRegister *output : insn->outputs_) {
	if (output->reg_type_ == DRegister::REG_WIRE) {
	  wires.insert(output);
	}
      }
    }
    CHECK(insns_to_be_later.size() < insns.size());
    insns = insns_to_be_later;
  } while (insns.size() > 0);

  // Branch comes at the last.
  for (DInsn *insn : insns) {
    if (insn->resource_->opr_->type_ == sym_branch) {
      OutputBranch(insn);
    }
  }
}

void CCState::OutputInsn(const DInsn *insn) {
  sym_t type = insn->resource_->opr_->type_;
  if (type == sym_add || type == sym_sub || type == sym_mul ||
      type == sym_lshift || type == sym_rshift ||
      type == sym_eq || type == sym_gt || type == sym_lt ||
      type == sym_bit_and || type == sym_bit_or ||
      type == sym_bit_xor) {
    OutputBinOp(insn);
  } else if (type == sym_logic_inv) {
    OutputUniOp(insn);
  } else if (type == sym_assign) {
    OutputAssign(insn);
  } else if (type == sym_sram_if) {
    OutputSRAMInsn(insn);
  } else if (type == sym_bit_sel) {
    OutputBitSelInsn(insn);
  } else if (type == sym_bit_concat) {
    OutputBitConcatInsn(insn);
  } else if (type == sym_imported) {
    OutputImportedInsn(insn);
  } else if (type == sym_selector) {
    OutputSelectorInsn(insn);
  } else if (type == sym_write_channel) {
    OutputChannelWriteInsn(insn);
  } else if (type == sym_read_channel) {
    OutputChannelReadInsn(insn);
  } else if (type == sym_sub_module_call) {
    OutputSubModuleCallInsn(insn);
  } else if (type == sym_branch) {
    // Do nothing.
  } else if (type == sym_task_entry) {
    // Do nothing.
  } else {
    CCWriter::ICE("unknown insn", type);
  }
}

void CCState::OutputSubModuleCallInsn(const DInsn *insn) {
  string task_prefix =
    "Task_" + insn->resource_->name_ + "_" + insn->func_name_;
  string st_name = SubStateRegName(insn);
  os_ << "  if (" << st_name << " == 0) {\n"
      << "    //if (" << task_prefix << "_Ready()) {\n"
      << "    //  " << task_prefix << "_En();\n"
      << "    //}\n"
      << "  }\n";
}

bool CCState::IsTerminal() const {
  if (state_->insns_.size() != 1) {
    return false;
  }
  const DInsn *insn = *state_->insns_.begin();
  if (insn->targets_.size() == 1 &&
      *(insn->targets_.begin()) == state_) {
    return true;
  }
  return false;
}

string CCState::SubStateRegName(const DInsn *insn) {
  char buf[16];
  sprintf(buf, "st_%d_", insn->insn_id_);
  return string(buf);
}

}  // namespace writer
