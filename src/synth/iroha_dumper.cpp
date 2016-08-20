#include "synth/iroha_dumper.h"

#include "dfg/dfg.h"
#include "dfg/resource_params.h"

#include <fstream>

namespace synth {

IrohaDumper::IrohaDumper(DModule *mod, ostream &os) : mod_(mod), os_(os) {
}

void IrohaDumper::Dump(DModule *mod, const string &path) {
  std::unique_ptr<std::ofstream> ofs;
  ofs.reset(new std::ofstream(path));
  IrohaDumper dumper(mod, *ofs);
  dumper.DumpIR();
}

void IrohaDumper::DumpIR() {
  os_ << "(PARAMS";
  os_ << "(RESET-POLARITY true)";
  const string &prefix = Env::GetModulePrefix();
  if (!prefix.empty()) {
    os_ << "(MODULE-NAME-PREFIX " << prefix << "_)";
  }
  os_ << ")\n";
  int nth_ch = 0;
  for (DChannel *ch : mod_->channels_) {
    DumpChannel(ch, nth_ch);
    ++nth_ch;
  }
  os_ << "(MODULE " << mod_->module_name_ << "\n";
  if (mod_->graph_) {
    DumpGraph(mod_->graph_);
  }
  os_ << ")\n";
}

void IrohaDumper::DumpGraph(DGraph *graph) {
  reg_id_map_.clear();
  int nth = 0;
  for (DRegister *reg : graph->registers_) {
    reg_id_map_[reg] = nth;
    ++nth;
  }
  os_ << "  (TABLE 1\n"
      << "    (REGISTERS\n";
  for (DRegister *reg : graph->registers_) {
    DumpRegister(reg);
  }
  os_ << "    )\n";
  os_ << "    (RESOURCES\n";
  for (DResource *res : graph->resources_) {
    DumpResource(res);
  }
  os_ << "    )\n";
  os_ << "    (INITIAL " << graph->initial_state_->state_id_ << ")\n";
  set<DState *> reachables;
  DStateUtil::CollectReachable(graph, graph->initial_state_, &reachables);
  for (DState *st : graph->states_) {
    if (reachables.find(st) == reachables.end()) {
      continue;
    }
    DumpState(st);
  }
  os_ << "  )\n";
}

void IrohaDumper::DumpState(DState *st) {
  os_ << "    (STATE " << st->state_id_ << "\n";
  for (DInsn *insn : st->insns_) {
    DumpInsn(insn);
  }
  os_ << "    )\n";
}

void IrohaDumper::DumpRegister(DRegister *reg) {
  os_ << "      (REGISTER " << reg_id_map_[reg] << " ";
  if (!reg->reg_name_.empty()) {
    os_ << reg->reg_name_;
  } else {
    os_ << "()";
  }
  os_ << "\n        ";
  if (reg->reg_type_ == DRegister::REG_NORMAL) {
    os_ << "REG ";
  } else if (reg->reg_type_ == DRegister::REG_WIRE) {
    os_ << "WIRE ";
  } else if (reg->reg_type_ == DRegister::REG_CONST) {
    os_ << "CONST ";
  }
  os_ << "UINT ";
  if (reg->data_type_->type_ == DType::INT) {
    os_ << reg->data_type_->size_;
  } else {
    os_ << 0;
  }
  if (reg->has_initial_ || reg->reg_type_ == DRegister::REG_CONST) {
    os_ << " " << reg->num_;
  } else {
    os_ << " ()";
  }
  os_ << "\n      )\n";
}

void IrohaDumper::DumpResource(DResource *res) {
  string c = GetResourceClass(res);
  if (c.empty()) {
    return;
  }
  os_ << "      (RESOURCE " << res->resource_id_ << " " << c << "\n"
      << "        ";
  DumpTypes(res->input_types_);
  os_ << " ";
  DumpTypes(res->output_types_);
  os_ << "\n        (PARAMS";
  if (c == "ext_output") {
    os_ << " (OUTPUT " << res->imported_resource_->GetOutputPinName() << ") "
	<< "(WIDTH " << DTypeUtil::GetWidth(res->input_types_[0]) << ")";
  }
  if (c == "ext_input") {
    os_ << " (INPUT " << res->imported_resource_->GetInputPinName() << ") "
	<< "(WIDTH " << DTypeUtil::GetWidth(res->output_types_[0]) << ")";
  }
  if (c == "embedded") {
    os_ << " (EMBEDDED-MODULE-FILE " << res->imported_resource_->GetCopyFileName() << ")";
    os_ << " (EMBEDDED-MODULE " << res->imported_resource_->GetModuleName() << ")";
    os_ << " (EMBEDDED-MODULE-REQ req)";
    string ack = res->imported_resource_->GetAckPinName();
    if (!ack.empty()) {
      os_ << " (EMBEDDED-MODULE-REQ " << ack << ")";
    }
  }
  os_ << ")\n";
  if (c == "array") {
    WriteArraySpec(res);
  }
  os_ << "      )\n";
}

void IrohaDumper::WriteArraySpec(DResource *res) {
  DArray *array = res->array_;
  os_ << "        (ARRAY ";
  if (array == nullptr) {
    os_ << "32 UINT 32 EXTERNAL RAM";
  } else {
    os_ << array->address_width << " UINT " << array->data_width
	<< " INTERNAL ";
    if (array->may_write_) {
      os_ << "RAM";
    } else {
      os_ << "ROM";
    }
  }
  os_ << ")\n";
}

void IrohaDumper::DumpInsn(DInsn *insn) {
  DResource *res = insn->resource_;
  string c = GetResourceClass(res);
  if (c.empty()) {
    return;
  }
  os_ << "      (INSN " << insn->insn_id_;
  os_ << " " << c << " " << res->resource_id_ << " ()";
  DumpTransition(insn);
  DumpRegs(insn->inputs_);
  DumpRegs(insn->outputs_);
  os_ << ")\n";
}

void IrohaDumper::DumpTransition(DInsn *insn) {
  os_ << " (";
  bool is_first = true;
  // Iroha's order is value: 0, 1, 2...
  for (auto it = insn->targets_.rbegin(); it != insn->targets_.rend(); ++it) {
    DState *st = *it;
    if (!is_first) {
      os_ << " ";
    }
    os_ << st->state_id_;
    is_first = false;
  }
  os_ << ")";
}

void IrohaDumper::DumpRegs(vector<DRegister *> &regs) {
  os_ << " (";
  bool is_first = true;
  for (DRegister *reg : regs) {
    if (!is_first) {
      os_ << " ";
    }
    os_ << reg_id_map_[reg];
    is_first = false;
  }
  os_ << ")";
}

void IrohaDumper::DumpTypes(vector<DType *> &types) {
  os_ << "(";
  bool is_first = true;
  for (DType *type: types) {
    if (!is_first) {
      os_ << " ";
    }
    os_ << "UINT ";
    if (type->type_ == DType::INT) {
      os_ << type->size_;
    } else {
      os_ << 0;
    }
    is_first = false;
  }
  os_ << ")";
}
  
string IrohaDumper::GetResourceClass(DResource *res) {
  string c = string(sym_cstr(res->opr_->type_));
  if (c == "function_entry" || c == "funcall" || c == "transition") {
    return "";
  }
  if (c == "ext_io") {
    if (res->input_types_.size() > 0) {
      CHECK(res->output_types_.size() == 0);
      return "ext_output";
    }
    if (res->output_types_.size() > 0) {
      return "ext_input";
    }
    return "";
  }
  if (c == "memory") {
    return "array";
  }
  if (c == "branch") {
    return "tr";
  }
  if (c == "assign") {
    return "set";
  }
  if (c == "logic_and") {
    return "bit-and";
  }
  if (c == "logic_or") {
    return "bit-or";
  }
  if (c == "read_channel") {
    return "channel-read";
  }
  if (c == "write_channel") {
    return "channel-write";
  }
  if (c == "bit_and") {
    return "bit-and";
  }
  if (c == "bit_or") {
    return "bit-or";
  }
  if (c == "bit_xor") {
    return "bit-xor";
  }
  if (c == "bit_sel") {
    return "bit-sel";
  }
  if (c == "bit_inv") {
    return "bit-inv";
  }
  if (c == "concat") {
    return "bit-concat";
  }
  if (c == "imported") {
    if (res->name_ == "print") {
      return "print";
    }
    if (res->name_ == "assert") {
      return "assert";
    }
    return "embedded";
  }
  return c;
}

void IrohaDumper::DumpChannel(DChannel *ch, int id) {
  os_ << "(CHANNEL " << id << " UINT 32 ";
  DumpChannelEndPoint(ch, ch->reader_module_);
  os_ << " ";
  DumpChannelEndPoint(ch, ch->writer_module_);
  os_ << ")\n";
}

void IrohaDumper::DumpChannelEndPoint(DChannel *ch, DModule *mod) {
  if (mod == nullptr) {
    os_ << "()";
    return;
  }
  int res_id = 0;
  for (DResource *res : mod->graph_->resources_) {
    if (res->name_ == ch->channel_name_) {
      res_id = res->resource_id_;
    }
  }
  // mod name, table id, res id
  os_ << "(" << mod->module_name_ << " 1 " << res_id << ")";
}

}  // namespace synth
