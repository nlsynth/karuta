#include "writer/vl_state.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "dfg/dfg.h"
#include "messages.h"
#include "nli.h"
#include "writer/module_template.h"
#include "writer/vl_channel.h"
#include "writer/vl_util.h"
#include "writer/writer.h"
#include "writer/writer_util.h"

namespace writer {

VLState::VLState(DState *st, DGraph *g, VLStateEncoder *e,
		 Writer *writer, ostream &os)
  : st_(st), graph_(g), state_encoder_(e), writer_(writer), os_(os) {
}

VLState::~VLState() {
}

void VLState::Output() {
  os_ << "        ";
  state_encoder_->OutputStateName(st_, os_);
  os_ << ": begin\n";
  for (DInsn *insn : st_->insns_) {
    OutputInsn(insn);
  }
  OutputTransition(graph_, st_);
  os_ << "        end\n";
}

void VLState::PreProcess(ModuleTemplate *tmpl) {
  for (DInsn *insn : st_->insns_) {
    if (WriterUtil::IsMultiCycleInsn(insn)) {
      ostream &ss = tmpl->GetStream(ModuleTemplate::SUB_STATE_REGS);
      ss << "  reg [1:0] " << SubStateRegName(insn) << ";\n";
      ostream &sr = tmpl->GetStream(ModuleTemplate::RESET_STATE);
      sr << "      " << SubStateRegName(insn) << " <= 0;\n";
    }
  }
}

void VLState::OutputRegisterName(const DRegister *reg, ostream &os) {
  string s;
  RegisterName(reg, &s);
  os << s;
}

void VLState::RegisterName(const DRegister *reg, string *s) {
  if (reg->reg_type_ == DRegister::REG_NORMAL ||
      reg->reg_type_ == DRegister::REG_WIRE) {
    *s = reg->reg_name_;
  } else if (reg->reg_type_ == DRegister::REG_CONST) {
    char buf[64];
    sprintf(buf, "%d'd%lu", reg->data_type_->size_ , reg->num_);
    *s = string(buf);
  }
}

void VLState::OutputInsnOutputWireName(const DInsn *insn, int n, ostream &os) {
  os << "o_insn_" << insn->insn_id_ << "_" << n;
}

void VLState::OutputInsnWireToRegisterAssign(const DInsn *insn) {
  int nth = 0;
  for (vector<DRegister *>::const_iterator it = insn->outputs_.begin();
       it != insn->outputs_.end(); ++it, ++nth) {
    DRegister *dst_reg = *it;
    if (dst_reg->reg_type_ != DRegister::REG_NORMAL) {
      continue;
    }
    os_ << "          " << dst_reg->reg_name_
	<< " <= ";
    OutputInsnOutputWireName(insn, nth, os_);
    os_ << ";\n";
  }
}

void VLState::OutputAssignInsn(const DInsn *insn) {
  DRegister *src = *(insn->inputs_.begin());
  DRegister *dst = *(insn->outputs_.begin());
  os_ << "          "<< dst->reg_name_ <<" <= ";
  OutputRegisterName(src, os_);
  os_ << ";\n";
}

void VLState::OutputSRAMInsn(const DInsn *insn) {
  if (insn->inputs_.size() == 1 &&
      insn->outputs_.size() == 0) {
    // 1st phase of READ
    DRegister *addr = *(insn->inputs_.begin());
    os_ << "          addr_o <= ";
    OutputRegisterValue(addr);
    os_ << ";\n";
  } else if (insn->inputs_.size() == 1 &&
	     insn->outputs_.size() == 1) {
    // 2nd phase of READ
  } else if (insn->inputs_.size() == 2) {
    // WRITE
    DRegister *addr = *(insn->inputs_.begin());
    DRegister *data = *(insn->inputs_.rbegin());
    os_ << "          addr_o <= ";
    OutputRegisterValue(addr);
    os_ << ";\n";
    os_ << "          data_o <= ";
    OutputRegisterValue(data);
    os_ << ";\n";
  }
}

void VLState::OutputRegisterValue(const DRegister *reg) {
  if (reg->reg_type_ == DRegister::REG_NORMAL ||
      reg->reg_type_ == DRegister::REG_WIRE) {
    os_ << reg->reg_name_;
  } else if (reg->reg_type_ == DRegister::REG_CONST) {
    os_ << reg->num_;
  }
}

void VLState::OutputArrayRefInsn(const DInsn *insn) {
  if (insn->outputs_.size() == 0 &&
      insn->inputs_.size() == 1) {
    // 1st clock of READ
    DRegister *addr = *(insn->inputs_.begin());
    os_ << "          ";
    os_ << insn->resource_->name_ << "_addr <= ";
    OutputRegisterValue(addr);
    os_ << ";\n";
    return;
  }
  if (insn->inputs_.size() == 1) {
    // 2nd clock of READ
  } else {
    // WRITE
    DRegister *addr = *(insn->inputs_.begin());
    os_ << "          ";
    os_ << insn->resource_->name_ << "_addr <= ";
    OutputRegisterValue(addr);
    os_ << ";\n";
    DRegister *data = *(insn->inputs_.rbegin());
    os_ << "          "
	<< insn->resource_->name_ << "_wdata"
	<< " <= ";
    OutputRegisterValue(data);
    os_ << ";\n";
  }
}

void VLState::OutputInsn(const DInsn *insn) {
  sym_t type = insn->resource_->opr_->type_;
  if (VLUtil::IsExternalRAM(insn->resource_)) {
    OutputInsnWireToRegisterAssign(insn);
    OutputSRAMInsn(insn);
  } else if (VLUtil::IsInternalMEM(insn->resource_)) {
    OutputInsnWireToRegisterAssign(insn);
    OutputArrayRefInsn(insn);
  } else if (type == sym_assign) {
    OutputAssignInsn(insn);
  } else if (VLUtil::IsResourceShareBinOp(insn->resource_) ||
	     VLUtil::IsResourceUnshareBinOp(insn->resource_)) {
    OutputInsnWireToRegisterAssign(insn);
  } else if (VLUtil::IsResourceUnshareUniOp(insn->resource_)) {
    OutputInsnWireToRegisterAssign(insn);
  } else if (type == sym_bit_sel || type == sym_bit_not ||
	     type == sym_bit_concat) {
    // resource would not shared
    OutputInsnWireToRegisterAssign(insn);
  } else if (type == sym_write_channel) {
    OutputChannelWriteInsn(insn);
  } else if (type == sym_read_channel) {
    OutputChannelReadInsn(insn);
  } else if (type == sym_branch || type == sym_gt) {
    // do nothing
  } else if (type == sym_imported) {
    // do nothing
  } else if (type == sym_sub_module_call) {
    OutputSubModuleCall(insn);
  } else if (type == sym_task_entry) {
    CHECK(graph_->owner_module_->module_type_ == DModule::MODULE_TASK);
  } else {
    writer_->ICE("unknown type of insn", type);
  }
}

void VLState::OutputTransition(DGraph *g, DState *st) {
  if (st_ == graph_->last_state_ &&
      graph_->owner_module_->module_type_ == DModule::MODULE_TASK) {
    os_ << "          cur_st <= ";
    state_encoder_->OutputTaskEntryStateName(os_);
    os_ <<";\n";
    return;
  }
  
  string state_guard;
  string sub_state_initializer;
  CollectSubState(&state_guard, &sub_state_initializer);

  if (!state_guard.empty()) {
    os_ << "          if (" << state_guard << ") begin\n";
    if (!sub_state_initializer.empty()) {
      os_ << sub_state_initializer;
    }
  }
  DResource *br = DGraphUtil::FindResource(g, sym_branch, false);
  DInsn *br_insn = DStateUtil::FindInsnByResource(st, br);
  if (br_insn) {
    vector<DRegister *>::iterator it;
    vector<DState *>::iterator jt;
    for (it = br_insn->inputs_.begin(), jt = br_insn->targets_.begin();
	 it != br_insn->inputs_.end();
	 it ++, jt++) {
      os_ << "          if (";
      OutputRegisterName(*it, os_);
      os_ << ") begin\n";
      os_ << "            cur_st <= ";
      state_encoder_->OutputStateName((*jt), os_);
      os_ <<";\n";
      os_ << "          end else\n";
    }
    os_ << "          cur_st <= ";
    state_encoder_->OutputStateName((*jt), os_);
    os_ <<";\n";
  } else {
    // no branch resource
    int next_id = st->state_id_ + 1;
    os_ << "          cur_st <= ";
    os_ << next_id;
    os_ <<";\n";
  }
  if (!state_guard.empty()) {
    os_ << "          end else begin\n"
	<< "            cur_st <= cur_st;\n"
	<< "          end\n";
  }
}

void VLState::CollectSubState(string *state_guard, string *initializer) {
  vector<string> regs;
  for (DInsn *insn : st_->insns_) {
    if (WriterUtil::IsMultiCycleInsn(insn)) {
      regs.push_back(SubStateRegName(insn));
    }
  }
  bool is_first = true;
  if (!state_guard->empty() && regs.size() > 0) {
    *state_guard = "(" + *state_guard + ")";
    is_first = false;
  }
  for (const string &sub_st : regs) {
    if (!is_first) {
      *state_guard += " && ";
    }
    *state_guard += "( " + sub_st + " == 3)";
    *initializer += "            " + sub_st + " <= 0;\n";
    is_first = false;
  }
}

void VLState::OutputChannelReadInsn(const DInsn *insn) {
  os_ << "          // channel read\n";
  string pin_base = "channel_" + insn->resource_->name_;
  os_ << "          if (" << SubStateRegName(insn) << " == 0) begin\n"
      << "            if (" << pin_base << "_en) begin\n"
      << "              " << SubStateRegName(insn) << " <= 3;\n"
      << "              " << pin_base << "_rdy <= 1;\n";
  OutputInsnWireToRegisterAssign(insn);
    os_ << "            end\n"
      << "          end ";
  os_ << "else if (" << SubStateRegName(insn) << " == 3) begin\n"
      << "            " << pin_base << "_rdy <= 0;\n"
      << "          end\n";
}

void VLState::OutputChannelWriteInsn(const DInsn *insn) {
  os_ << "          // channel write\n";
  string pin_base = "channel_" + insn->resource_->name_;
  os_ << "          if (" << SubStateRegName(insn) << " == 0) begin\n"
      << "            if (" << pin_base << "_rdy) begin\n"
      << "              " << SubStateRegName(insn) << " <= 3;\n"
      << "              " << pin_base << "_en <= 1;\n";
  os_ << "              " << pin_base << "_data <= ";
  OutputRegisterValue(*(insn->inputs_.begin()));
  os_ << ";\n";
  os_ << "            end\n"
      << "          end ";
  os_ << "else if (" << SubStateRegName(insn) << " == 3) begin\n"
      << "            " << pin_base << "_en <= 0;\n"
      << "          end\n";
}

void VLState::OutputSubModuleCall(const DInsn *insn) {
  string pin_base = insn->resource_->name_ + "_" + insn->func_name_;
  os_ << "          if (" << SubStateRegName(insn) << " == 0) begin\n"
      << "            if (" << pin_base << "_rdy) begin\n"
      << "              " << SubStateRegName(insn) << " <= 3;\n"
      << "              " << pin_base << "_en <= 1;\n"
      << "            end\n"
      << "          end ";
  os_ << "else if (" << SubStateRegName(insn) << " == 3) begin\n"
      << "            " << pin_base << "_en <= 0;\n"
      << "          end\n";
}

string VLState::SubStateRegName(const DInsn *insn) {
  char buf[16];
  sprintf(buf, "st_%d", insn->insn_id_);
  return string(buf);
}

}  // namespace writer
