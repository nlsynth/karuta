#include "writer/cc_graph.h"

#include "dfg/dfg.h"
#include "writer/writer.h"
#include "writer/cc_class.h"

static sym_t sym_print, sym_assert;

namespace writer {

CCGraph::CCGraph(DGraph *graph, ClassWriter *cw, Writer *writer, ostream &os)
  : graph_(graph), os_(os), cw_(cw), writer_(writer) {
  sym_print = sym_lookup("print");
  sym_assert = sym_lookup("assert");
}

string CCGraph::RegisterName(const DRegister *reg) {
  if (reg->reg_type_ == DRegister::REG_NORMAL ||
      reg->reg_type_ == DRegister::REG_WIRE) {
    return reg->reg_name_;
  } else {
    char buf[20];
    sprintf(buf, "%luUL", reg->num_);
    return string(buf);
  }
}

void CCGraph::OutputBinOp(const DInsn *insn, ostream &os) {
  os << "  " << RegisterName(*(insn->outputs_.begin()));
  os << " = " << RegisterName(*(insn->inputs_.begin()));
  os << " ";
  sym_t type = insn->resource_->opr_->type_;
  if (type == sym_add) {
    os << "+";
  } else if (type == sym_sub) {
    os << "-";
  } else if (type == sym_mul) {
    os << "*";
  } else if (type == sym_gt) {
    os << ">";
  } else if (type == sym_lt) {
    os << "<";
  } else if (type == sym_eq) {
    os << "==";
  } else if (type == sym_lshift) {
    os << "<<";
  } else if (type == sym_rshift) {
    os << ">>";
  } else if (type == sym_bit_or) {
    os << "|";
  } else if (type == sym_bit_and) {
    os << "&";
  } else if (type == sym_bit_xor) {
    os << "^";
  } else {
    writer_->ICE("unknown binop", type);
  }
  os << " " << RegisterName(*(insn->inputs_.rbegin())) << ";\n";
}

void CCGraph::OutputAssign(const DInsn *insn, ostream &os) {
  os << "  " << RegisterName(*(insn->outputs_.begin()));
  os << " = " << RegisterName(*(insn->inputs_.begin()));
  os << ";\n";
}

void CCGraph::OutputUniOp(const DInsn *insn, ostream &os) {
  os << "  ";
  sym_t type = insn->resource_->opr_->type_;
  os << RegisterName(*(insn->outputs_.begin()));
  os << " =";
  if (type == sym_logic_inv) {
    os << "!";
  }
  os << RegisterName(*(insn->inputs_.begin()));
  os << ";\n";
}

void CCGraph::OutputBranch(const DInsn *insn, ostream &os) {
  vector<DRegister *>::const_iterator it;
  vector<DState *>::const_iterator jt;
  for (it = insn->inputs_.begin(), jt = insn->targets_.begin();
       it != insn->inputs_.end();
       it ++, jt ++) {
    os << "  if (" << RegisterName(*it);
    os << ") state = " << ((*jt)->state_id_) << ";\n";
    os << "  else\n";
  }
  os << "  state = " << (*jt)->state_id_ << ";\n";
}

void CCGraph::OutputSRAMInsn(const DInsn *insn, ostream &os) {
  string ram_name = "NULL";
  const string &ram_id = insn->resource_->name_;
  if (!ram_id.empty()) {
    ram_name = "&" + ram_id + "_inst";
  }
  if (insn->inputs_.size() == 2) {
    // write
    os << "  SRAMWrite(";
    os << RegisterName((*insn->inputs_.begin()));
    os << ", " << RegisterName((*insn->inputs_.rbegin()));
    os << ", " << ram_name << ");\n";
  } if (insn->outputs_.size() == 0) {
    // read cycle 1/2
    //  nothing
  } else {
    // read cycle 2/2
    os << "  " << RegisterName((*insn->outputs_.begin()));
    os << " = SRAMRead(" << RegisterName((*insn->inputs_.begin()));
    os << ", " << ram_name << ");\n";
  }
}

void CCGraph::OutputBitSelInsn(const DInsn *insn, ostream &os) {
  Writer::BitSelOperands opr;
  Writer::DecodeBitSelInsn(insn, &opr);
  os << "  " << RegisterName(*(insn->outputs_.begin()));
  os << " = BitSelect(" << RegisterName(*(insn->inputs_.begin())) << ", ";
  os << opr.src_msb_pos << ", " << opr.src_lsb_pos << ");\n";
}

void CCGraph::OutputBitConcatInsn(const DInsn *insn, ostream &os) {
  os << "  ";
  const DRegister *output = *(insn->outputs_.begin());
  os << RegisterName(output);
  os << " = 0;\n";
  // Number of input should be 2, though this code can process more
  // than 2.
  for (DRegister *reg : insn->inputs_) {
    os << "  " << RegisterName(output);
    os << " <<= " << reg->data_type_->size_ << ";\n";
    os << "  " << RegisterName(output);
    os << " |= " << RegisterName(reg);
    os << ";\n";
  }
}

void CCGraph::OutputImportedInsn(const DInsn *insn, ostream &os) {
  const sym_t type = sym_lookup(insn->resource_->name_.c_str());
  if (type == sym_print) {
    for (vector<DRegister *>::const_iterator it = insn->inputs_.begin();
	 it != insn->inputs_.end(); ++it) {
      const DRegister *reg = *it;
      os << "  cout << " << RegisterName(reg);
      os << " << \"\\n\";\n";
    }
  } else if (type == sym_assert) {
    const DRegister *reg = *(insn->inputs_.begin());
    os << "  Assert(" << RegisterName(reg) << ");\n";
  } else {
    writer_->ICE("imported insn", sym_lookup(insn->resource_->name_.c_str()));
  }
}

void CCGraph::OutputSelectorInsn(const DInsn *insn, ostream &os) {
  os << "  " << RegisterName(*(insn->outputs_.begin()));
  vector<DRegister *>::const_iterator it = insn->inputs_.begin();
  DRegister *op1 = *(it++);
  DRegister *op2 = *(it++);
  DRegister *cond = *it;
  os << " = " << RegisterName(cond) << " ? " << RegisterName(op2) << " : " << RegisterName(op1);
  os << ";\n";
}

void CCGraph::OutputChannelWriteInsn(const DInsn *insn, ostream &os) {
  os << "  // channel write.\n";
  string channel_name = insn->resource_->name_ + "_channel_inst";
  os << "  " << channel_name << ".Write(" << RegisterName((*insn->inputs_.begin())) << ");\n";
}

void CCGraph::OutputChannelReadInsn(const DInsn *insn, ostream &os) {
  os << "  // channel read.\n";
  string channel_name = insn->resource_->name_ + "_channel_inst";
  os << "  " << RegisterName((*insn->outputs_.begin())) << " = "
     << channel_name << ".Read();\n";
}

void CCGraph::OutputInsnList(const DState *st, ostream& os) {
  // TODO(yusuke): reorder by wire dependency
  list<DInsn *> insns = st->insns_;
  set<DRegister *> wires;
  do {
    list<DInsn *> insns_to_be_later;
    for (list<DInsn *>::iterator it = insns.begin();
	 it != insns.end(); it++) {
      DInsn *insn = *it;
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
      OutputInsn(insn, os);
      for (DRegister *output : insn->outputs_) {
	if (output->reg_type_ == DRegister::REG_WIRE) {
	  wires.insert(output);
	}
      }
    }
    CHECK(insns_to_be_later.size() < insns.size());
    insns = insns_to_be_later;
  } while (insns.size() > 0);
}

void CCGraph::OutputInsn(const DInsn *insn, ostream& os) {
  sym_t type = insn->resource_->opr_->type_;
  if (type == sym_add || type == sym_sub || type == sym_mul ||
      type == sym_lshift || type == sym_rshift ||
      type == sym_eq || type == sym_gt || type == sym_lt ||
      type == sym_bit_and || type == sym_bit_or ||
      type == sym_bit_xor) {
    OutputBinOp(insn, os);
  } else if (type == sym_logic_inv) {
    OutputUniOp(insn, os);
  } else if (type == sym_assign) {
    OutputAssign(insn, os);
  } else if (type == sym_branch) {
    OutputBranch(insn, os);
  } else if (type == sym_sram_if) {
    OutputSRAMInsn(insn, os);
  } else if (type == sym_bit_sel) {
    OutputBitSelInsn(insn, os);
  } else if (type == sym_bit_concat) {
    OutputBitConcatInsn(insn, os);
  } else if (type == sym_imported) {
    OutputImportedInsn(insn, os);
  } else if (type == sym_selector) {
    OutputSelectorInsn(insn, os);
  } else if (type == sym_write_channel) {
    OutputChannelWriteInsn(insn, os);
  } else if (type == sym_read_channel) {
    OutputChannelReadInsn(insn, os);
  } else if (type == sym_task_entry) {
    // TBD
  } else if (type == sym_sub_module_call) {
    // TBD
  } else {
    writer_->ICE("unknown insn", type);
  }
}

bool CCGraph::IsTerminal(const DState *st) const {
  if (st->insns_.size() != 1) {
    return false;
  }
  const DInsn *insn = *st->insns_.begin();
  if (insn->targets_.size() == 1 &&
      *(insn->targets_.begin()) == st) {
    return true;
  }
  return false;
}

void CCGraph::OutputState(const DGraph *g, const DState *st) {
  char buf[16];
  sprintf(buf, "s_%d()", st->state_id_);
  cw_->AddMember("", "void", buf);
  ostream &os = cw_->os();
  set<const DRegister *> wires;
  for (const DInsn *insn : st->insns_) {
    for (const DRegister *reg : insn->inputs_) {
      if (reg->reg_type_ == DRegister::REG_WIRE) {
	wires.insert(reg);
      }
    }
  }
  for (const DRegister *reg : wires) {
    os << "  uint64_t " << RegisterName(reg) << ";\n";
  }
  OutputInsnList(st, os);
  if (IsTerminal(st)) {
    os << "  finish = true;\n";
  }
  cw_->EndMethod();
}

void CCGraph::OutputRegisters(const DGraph *g) {
  for (DRegister *reg : g->registers_) {
    if (reg->reg_type_ == DRegister::REG_NORMAL) {
      cw_->AddMember("", "uint64_t", reg->reg_name_);
    }
  }
}

void CCGraph::OutputStateDumper(const DGraph *g) {
  cw_->AddMember("", "void", "DumpState()");
  if (g) {
    cw_->os() << "  // dumper;\n"
	      << "  printf(\"st=%d\\n\", state);\n";
  } else {
    cw_->os() << "  // dumper;\n";
  }
  cw_->EndMethod();
}

void CCGraph::OutputResetHandler(const DGraph *g) {
  cw_->AddMember("", "void", "reset()");
  for (vector<string>::iterator it = sub_instances_.begin();
       it != sub_instances_.end(); it++) {
    cw_->os() << "  " << *it << ".reset();\n";
  }
  if (g) {
    cw_->os() << "  state = "<< g->initial_state_->state_id_ <<";\n";
  }
  cw_->os() << "  finish = false;\n";
  cw_->EndMethod();
}

void CCGraph::OutputGraph() {
  // state variable
  cw_->AddMember("", "int", "state");
  OutputRegisters(graph_);
  OutputArrayInstantiation(graph_);
  // function body
  for (list<DState *>::const_iterator it = graph_->states_.begin();
       it != graph_->states_.end(); it++) {
    OutputState(graph_, *it);
  }
}

void CCGraph::OutputArrayDecl(const string &name, const DArray *array) {
  char buf[10];
  int len = (1 << array->address_width);
  sprintf(buf, "%d", len);
  ClassWriter cw(name.c_str(), "NliArray", buf);
  ostringstream dtor;
  dtor << "~" <<  name << "() {}";
  cw.AddMember("", "", dtor.str());
  cw.AddMember("", "void", "Init()");
  cw.os() << "  //\n";
  for (int i = 0; i < (int)array->num_.size(); ++i) {;
    if (array->num_[i]) {
      cw.os() << "  image_[" << i << "] = "<< array->num_[i] << ";\n";
    }
  }
  cw.EndMethod();
  cw.Output(os_);
}

void CCGraph::OutputArrayInstantiation(const DGraph *graph) {
  for (DResource *r : graph->resources_) {
    if (r->array_) {
      const string name = r->name_;
      cw_->AddMember("", name, name + "_inst");
    }
  }
}

}  // namespace writer
