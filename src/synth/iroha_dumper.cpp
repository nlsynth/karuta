#include "synth/iroha_dumper.h"

#include "dfg/dfg.h"
#include "dfg/resource_params.h"

#include <fstream>

namespace synth {

IrohaDumper::IrohaDumper(DModule *root_mod, ostream &os)
  : root_mod_(root_mod), os_(os) {
  AssignModuleIds(root_mod);
}

void IrohaDumper::Dump(DModule *mod, const string &path) {
  std::unique_ptr<std::ofstream> ofs;
  ofs.reset(new std::ofstream(path));
  IrohaDumper dumper(mod, *ofs);
  dumper.DumpDesign();
}

void IrohaDumper::DumpDesign() {
  os_ << "(PARAMS";
  os_ << "(RESET-POLARITY true)";
  const string &prefix = Env::GetModulePrefix();
  if (!prefix.empty()) {
    os_ << "(MODULE-NAME-PREFIX " << prefix << "_)";
  }
  os_ << ")\n";

  DumpModule(root_mod_);
}

void IrohaDumper::DumpModule(DModule *mod) {
  for (DModule *sub : mod->sub_modules_) {
    DumpModule(sub);
  }
  IModuleDumper mod_dumper(mod, this, os_);
  int nth_ch = 0;
  for (DChannel *ch : mod->channels_) {
    if (ch->is_root_or_source_) {
      mod_dumper.DumpChannel(ch, nth_ch);
    }
    ++nth_ch;
  }
  mod_dumper.Dump();
}

int IrohaDumper::GetModuleId(DModule *mod) {
  return module_ids_[mod];
}

int IrohaDumper::GetModuleIdByName(const string &name) {
  return module_ids_by_name_[name];
}

void IrohaDumper::AssignModuleIds(DModule *mod) {
  int id = module_ids_.size();
  module_ids_[mod] = id;
  module_ids_by_name_[mod->module_name_] = id;
  for (DModule *sub : mod->sub_modules_) {
    AssignModuleIds(sub);
  }
}

IModuleDumper::IModuleDumper(DModule *mod, IrohaDumper *dumper, ostream &os)
  : mod_(mod), dumper_(dumper), os_(os) {
}

void IModuleDumper::Dump() {
  os_ << "(MODULE " << dumper_->GetModuleId(mod_) << " " << mod_->module_name_ << "\n";
  if (mod_->parent_mod_ != nullptr) {
    os_ << " (PARENT " << dumper_->GetModuleId(mod_->parent_mod_) << ")\n";
  }
  if (mod_->graph_) {
    DumpGraph(mod_->graph_);
  }
  os_ << ")\n";
}

void IModuleDumper::DumpGraph(DGraph *graph) {
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

void IModuleDumper::DumpState(DState *st) {
  os_ << "    (STATE " << st->state_id_ << "\n";
  DResource *task_entry = DGraphUtil::FindResource(mod_->graph_, sym_task_entry, false);
  if (st == mod_->graph_->initial_state_) {
    if (task_entry) {
      // Output task_entry insn at the initial_state_ even if it is
      // not at the initial (synth may put empty states).
      vector<DInsn *> insns;
      DGraphUtil::FindInsnsByResource(mod_->graph_, task_entry, &insns);
      CHECK(insns.size() == 1);
      DumpInsn(insns[0]);
    }
  }
  for (DInsn *insn : st->insns_) {
    if (insn->resource_ == task_entry) {
      continue;
    }
    DumpInsn(insn);
  }
  os_ << "    )\n";
}

void IModuleDumper::DumpRegister(DRegister *reg) {
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
  os_ << "(UINT ";
  if (reg->data_type_->type_ == DType::INT) {
    os_ << reg->data_type_->size_;
  } else {
    os_ << 0;
  }
  os_ << ")";
  if (reg->has_initial_ || reg->reg_type_ == DRegister::REG_CONST) {
    os_ << " " << reg->num_;
  } else {
    os_ << " ()";
  }
  os_ << "\n      )\n";
}

void IModuleDumper::DumpResource(DResource *res) {
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
  if (c == "sub-module-task-call") {
    vector<DInsn *> insns;
    DGraphUtil::FindInsnsByResource(mod_->graph_, res, &insns);
    string s = "not_used";
    if (insns.size() > 0) {
      s = insns[0]->func_name_;
    }
    os_ << "\n        (CALLEE-TABLE " << dumper_->GetModuleIdByName(s)
	<< " 1)\n";
  }
  os_ << "      )\n";
}

void IModuleDumper::WriteArraySpec(DResource *res) {
  DArray *array = res->array_;
  os_ << "        (ARRAY ";
  if (array == nullptr) {
    os_ << "32 (UINT 32) EXTERNAL RAM";
  } else {
    os_ << array->address_width << " (UINT " << array->data_width
	<< ") INTERNAL ";
    if (array->may_write_) {
      os_ << "RAM";
    } else {
      os_ << "ROM";
    }
  }
  os_ << ")\n";
}

void IModuleDumper::DumpInsn(DInsn *insn) {
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

void IModuleDumper::DumpTransition(DInsn *insn) {
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

void IModuleDumper::DumpRegs(vector<DRegister *> &regs) {
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

void IModuleDumper::DumpTypes(vector<DType *> &types) {
  os_ << "(";
  bool is_first = true;
  for (DType *type: types) {
    if (!is_first) {
      os_ << " ";
    }
    os_ << "(UINT ";
    if (type->type_ == DType::INT) {
      os_ << type->size_;
    } else {
      os_ << 0;
    }
    os_ << ")";
    is_first = false;
  }
  os_ << ")";
}
  
string IModuleDumper::GetResourceClass(DResource *res) {
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
  if (c == "task_entry") {
    return "sub-module-task";
  }
  if (c == "task_finish") {
    return "";
  }
  if (c == "sub_module_call") {
    return "sub-module-task-call";
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

void IModuleDumper::DumpChannel(DChannel *ch, int id) {
  os_ << "(CHANNEL " << id << " (UINT " << ch->data_width_ << ") ";
  DumpChannelEndPoint(ch, ch->reader_module_);
  os_ << " ";
  DumpChannelEndPoint(ch, ch->writer_module_);
  os_ << "\n  (PARAMS\n"
      << "    (CHANNEL-DATA channel_" << ch->channel_name_ << "_data)\n"
      << "    (CHANNEL-EN channel_" << ch->channel_name_ << "_en)\n"
      << "    (CHANNEL-ACK channel_" << ch->channel_name_ << "_ack)\n";
  os_ << "))\n";
}

void IModuleDumper::DumpChannelEndPoint(DChannel *ch, DModule *mod) {
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
  os_ << "(" << dumper_->GetModuleId(mod) << " 1 " << res_id << ")";
}

}  // namespace synth
