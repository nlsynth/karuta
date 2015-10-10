#include "writer/vl_graph.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "nli.h"
#include "dfg/dfg.h"
#include "dfg/imported_resource.h"
#include "messages.h"
#include "writer/module_template.h"
#include "writer/vl_channel.h"
#include "writer/vl_state.h"
#include "writer/vl_util.h"
#include "writer/vl_writer.h"
#include "writer/writer_util.h"

namespace writer {

VLGraph::VLGraph(DGraph *graph, const string& path_name,
		 ModuleTemplate *tmpl, ostream &os)
  : os_(os), path_name_(path_name), graph_(graph), tmpl_(tmpl) {
  CHECK(graph_);
  state_encoder_.reset(new VLStateEncoder(graph_));
}

VLGraph::~VLGraph() {
}

void VLGraph::Output() {
  OutputRegisters();
  DeclareStateVariable();
  OutputTaskReadySignal();
  OutputResourcesAll();
  OutputInsnWiresAll();
  OutputInsnResultWiresAll();
  os_ << " // sub state regs begin\n";
  os_ << tmpl_->GetContents(ModuleTemplate::SUB_STATE_REGS);
  os_ << " // sub state regs end\n";
  OutputFSM();
  OutputImportedModuleInstancesAll();
}

void VLGraph::PreProcess() {
  for (DState *st : graph_->states_) {
    VLState state_writer(st, graph_, state_encoder_.get(), os_);
    state_writer.PreProcess(tmpl_);
  }
}

const DRegister *VLGraph::GetNthInput(const DInsn *insn, int nth) {
  int i = 0;
  for (DRegister *reg : insn->inputs_) {
    if (i == nth) {
      return reg;
    }
    i++;
  }
  return NULL;
}

void VLGraph::OutputResourceName(const DResource *res, ostream &os) {
  os << sym_cstr(res->opr_->type_) << "_" << res->resource_id_;
}

void VLGraph::DeclareStateVariable() {
  // calc minimal width
  int w = state_encoder_->GetStateWidth();
  os_ << " // declare state begin\n";
  if (graph_->owner_module_->module_type_ == DModule::MODULE_TASK) {
    os_ << " `define "
	<< state_encoder_->TaskEntryStateNameWithoutQuote()
	<< " " << state_encoder_->GetTaskEntryState() <<"\n";
  }
  for (DState *st : graph_->states_) {
    os_ << " `define "
	<< state_encoder_->StateNameWithoutQuote(st);
    os_ << " " << state_encoder_->GetEncodedState(st) <<"\n";
  }

  os_ << "\n"
      << "  reg [" << w << ":0] cur_st;\n"
      << " // declare state end\n\n";
}

void VLGraph::OutputStateOutput() {
  os_ << "      // state output\n";

  vector<DResource *> memories;
  DGraphUtil::FindResourceAll(graph_, sym_sram_if, &memories);
  for (size_t i = 0; i < memories.size(); ++i) {
    DResource *mem = memories[i];
    if (VLUtil::IsExternalRAM(mem)) {
      SetEnabledStateSet(mem, "write_en_o");
    }
    if (VLUtil::IsInternalMEM(mem)) {
      SetEnabledStateSet(mem, mem->name_ + "_write_en");
    }
  }
}

void VLGraph::SetEnabledStateSet(DResource *res, const string &dst_signal) {
  string chan_states;
  for (DState *st : graph_->states_) {
    DInsn *insn = DStateUtil::FindInsnByResource(st, res);
    if (insn && insn->inputs_.size() == 2) {
      if (!chan_states.empty()) {
	chan_states += " | ";
      }
      chan_states +=
	string("(cur_st == `") +
	state_encoder_->StateNameWithoutQuote(st) + ")";
    }
  }
  if (!chan_states.empty()) {
    os_ << "      " << dst_signal << " <= " << chan_states << ";\n";
  }
}

void VLGraph::OutputFSM() {
  os_ << "  always @(posedge clk) begin\n"
      << "    if (rst) begin\n"
      << "      cur_st <= ";
  if (graph_->owner_module_->module_type_ == DModule::MODULE_TASK) {
    os_ << state_encoder_->TaskEntryStateName();
  } else {
    os_ << state_encoder_->StateName(graph_->initial_state_);
  }
  os_ << ";\n";
  OutputInitialVals();
  os_ << tmpl_->GetContents(ModuleTemplate::RESET_STATE);
  os_ << "    end else begin\n";
  OutputDebugDisplay();
  OutputStateOutput();
  os_ << "      // FSM.\n"
      << "      case (cur_st)\n";
  OutputTaskEntryState();
  for (DState *st : graph_->states_) {
    VLState state_writer(st, graph_, state_encoder_.get(), os_);
    state_writer.Output();
  }
  os_ << "      endcase\n"
      << "    end\n"
      << "  end\n\n";
}

void VLGraph::OutputDebugDisplay() {
  string fmt = "NLI:";
  string values = "";
  int num_normal_regs = 0;
  for (DRegister *reg : graph_->registers_) {
    if (reg->reg_type_ != DRegister::REG_NORMAL) {
      continue;
    }
    ++num_normal_regs;
    string name = VLState::RegisterName(reg);
    fmt += string(" ") + name + " =%d";
    values += string(" ,") + name;
  }
  os_ << "`ifdef NLI_DEBUG\n";
  os_ << "      $display(\"NLI:st "
      << (path_name_ + "_" + graph_->owner_module_->module_name_)
      << "=%d\", cur_st);\n";
  if (num_normal_regs > 0) {
    os_ << "      $display(\"" << fmt << "\"" << values << ");\n";
  }
  os_ << "`endif\n";
}

void VLGraph::OutputInitialVals() {
  for (DRegister *reg : graph_->registers_) {
    if (reg->has_initial_) {
      os_ << "      " << reg->reg_name_ << " <= " << reg->num_ << ";\n";
    }
  }
}

void VLGraph::OutputRegType(const DType *type) {
  if (type->type_ == DType::ENUM) {
    os_ << "  reg ";
  } else {
    os_ << "  reg [" << (type->size_ - 1) << ":0] ";
  }
}

void VLGraph::OutputWireType(const DType *type) {
  if (type->type_ == DType::ENUM) {
    os_ << "  wire ";
  } else {
    os_ << "  wire [" << (type->size_ - 1) << ":0] ";
  }
}

void VLGraph::OutputRegisters() {
  for (DRegister *reg : graph_->registers_) {
    if (reg->reg_type_ == DRegister::REG_NORMAL) {
      OutputRegType(reg->data_type_);
      os_ << " "<< reg->reg_name_ <<";\n";
    }
    if (reg->reg_type_ == DRegister::REG_WIRE) {
      OutputWireType(reg->data_type_);
      os_ << " "<< reg->reg_name_ <<";\n";
    }
  }
  os_ << "\n";
}

void VLGraph::OutputTaskReadySignal() {
  if (graph_->owner_module_->module_type_ == DModule::MODULE_TASK) {
    os_ << "  // Task ready signal.\n";
    string pin_base = VLUtil::TaskControlPinName(graph_->owner_module_);
    os_ << "  assign " << pin_base << "_rdy = (cur_st == ";
    os_ << state_encoder_->TaskEntryStateName();
    os_ << ");\n";
  }
}

void VLGraph::OutputTaskEntryState() {
  if (graph_->owner_module_->module_type_ == DModule::MODULE_TASK) {
    os_ << "        "
	<< state_encoder_->TaskEntryStateName()
	<< ":begin\n"
	<< "          if (";
    string pin_base = VLUtil::TaskControlPinName(graph_->owner_module_);
    os_ << pin_base << "_en) begin\n"
	<< "            cur_st <= "
	<< state_encoder_->StateName(graph_->initial_state_);
    os_ << ";\n"
	<< "          end else begin\n"
	<< "            cur_st <= "
	<< state_encoder_->TaskEntryStateName()
	<< ";\n";
    OutputTaskEntryArgs();
    os_ << "          end\n";
    os_ << "        end\n";
  }
}

void VLGraph::OutputTaskEntryArgs() {
  string pin_base = VLUtil::TaskControlPinName(graph_->owner_module_);
  DInsn *insn = WriterUtil::FindTaskEntryInsn(graph_);
  for (DRegister *reg : insn->inputs_) {
    os_ << "            " << reg->reg_name_ << " <= "
	<< (pin_base + "_" + reg->reg_name_) << ";\n";
  }
}

void VLGraph::OutputBinopWire(DResource *r) {
  vector<DType *>::iterator it;
  int i;
  for (it = r->output_types_.begin(), i = 0;
       it != r->output_types_.end(); it++, i++) {
    OutputWireType(*it);
    OutputResourceName(r, os_);
    os_ << "_d" << i << ";\n";
  }

  for (it = r->input_types_.begin(), i = 0;
       it != r->input_types_.end(); it++, i++) {
    OutputWireType(*it);
    OutputResourceName(r, os_);
    os_ << "_s"<< i <<";\n";
  }
}

void VLGraph::OutputBinopSharedResource(DResource *r) {
  OutputBinopWire(r);
  std::ostringstream ss[2];
  int i;
  for (i = 0; i < 2; i++) {
    ss[i] << "  assign ";
    OutputResourceName(r, ss[i]);
    ss[i] << "_s" << i << " = ";
  }
  list<DState *>::iterator it;
  int nr = 0;
  for (DState *state : graph_->states_) {
    DInsn *insn = DStateUtil::FindInsnByResource(state, r);
    if (!insn) {
      continue;
    }
    DRegister *src0, *src1;
    src0 = *(insn->inputs_.begin());
    src1 = *(insn->inputs_.rbegin());
    CHECK(src0 != NULL && src1 != NULL) << insn->insn_id_ << "\n";
    ss[0] << "(cur_st == "
	  << state_encoder_->StateName(state)
	  << ") ? ";
    ss[0] << VLState::RegisterName(src0);
    ss[0] << " : (";
    ss[1] << "(cur_st == "
	  << state_encoder_->StateName(state);
    ss[1] << ") ? ";
    ss[1] << VLState::RegisterName(src1);
    ss[1] << " : (";
    ++nr;
  }

  ss[0] << "0";
  ss[1] << "0";
  for (i = 0; i < nr; i++) {
    ss[0] << ")";
    ss[1] << ")";
  }
  os_ << ss[0].str() << ";\n"
      << ss[1].str() << ";\n";

  os_ << "  assign ";
  OutputResourceName(r, os_);
  os_ << "_d0 = (";
  OutputResourceName(r, os_);
  os_ << "_s0 ";
  sym_t type = r->opr_->type_;
  if (type == sym_add) {
    os_ << "+";
  } else if (type == sym_sub) {
    os_ << "-";
  } else if (type == sym_mul) {
    os_ << "*";
  } else if (type == sym_gt) {
    os_ << ">";
  } else if (type == sym_eq) {
    os_ << "==";
  } else if (type == sym_ne) {
    os_ << "!=";
  } else {
    VLWriter::ICE("unknown operator");
  }
  os_ << " ";
  OutputResourceName(r, os_);
  os_ << "_s1);\n";
}

void VLGraph::OutputArrayRefResource(DResource *r) {
  DArray *array = r->array_;
  const string &name = r->name_;
  os_ << "  reg [" << (array->address_width - 1) << ":0] "
      << name << "_addr;\n"
      << "  wire [" << (array->data_width - 1) << " :0] "
      << name << "_rdata;\n";
  if (array->may_write_) {
    os_ << "  reg " << name << "_write_en;\n"
	<< "  reg [" << (array->data_width - 1) << " :0] "
	<< name << "_wdata;\n";
  }
  os_ << "  " << r->name_ << " "
      << r->name_ << "_inst("
      << ".clk(clk), .rst(rst), "
      << ".addr_i(" << name << "_addr), "
      << ".rdata_o(" << name << "_rdata)";
  if (array->may_write_) {
    os_ << ", .wdata_i( " << name << "_wdata), "
	<< ".write_en_i(" << name << "_write_en)";
  }
  os_ << ");\n";
}

void VLGraph::OutputImportedOpInputPin(DResource *r,
				       ImportedResource_pin *pin,
				       int nth_input) {
  os_ << "  wire ";
  if (pin->width > 1) {
    os_ << "[" << pin->width - 1 << ":0] ";
  }
  os_ << r->name_
      << r->resource_id_ << "_" << sym_cstr(pin->name) << ";\n";
  os_ << "  assign " << r->name_ << r->resource_id_ << "_"
      << sym_cstr(pin->name) << " = ";

  int nr = 0;
  for (DState *st : graph_->states_) {
    DInsn *insn = DStateUtil::FindInsnByResource(st, r);
    if (!insn) {
      continue ;
    }
    os_ << "(cur_st == "
	<< state_encoder_->StateName(st);
    os_ << ") ? ";
    const DRegister *input = GetNthInput(insn, nth_input);
    os_ << VLState::RegisterName(input);
    os_ << " : (";
    nr ++;
  }
  os_ << "0";
  int i;
  for (i = 0; i < nr; i++) {
    os_ << ")";
  }
  os_ << ";\n";
}

void VLGraph::OutputImportedOp(DResource *r) {
  // enable wire
  os_ << "  wire " << r->name_ << r->resource_id_ << "_en;\n";
  os_ << "  assign " << r->name_ << r->resource_id_ << "_en = ";
  int nr = 0;
  for (DState *st : graph_->states_) {
    DInsn *insn = DStateUtil::FindInsnByResource(st, r);
    if (!insn) {
      continue;
    }
    if (nr > 0) {
      os_ << " | ";
    }
    os_ << "(cur_st == "
	<< state_encoder_->StateName(st);
    os_ << ")";
    nr ++;
  }
  if (nr == 0) {
    os_ << "0";
  }
  os_ << ";\n";
  // I/O pins
  ImportedResource *ir = r->imported_resource_;
  nr = ir->GetNrPinDecls();
  int i;
  int nth_input = 0;
  for (i = 0; i < nr; i++) {
    ImportedResource_pin pin;
    ir->GetNthPinDecl(i, &pin);
    if (!pin.is_out) {
      OutputImportedOpInputPin(r, &pin, nth_input);
      nth_input ++;
    }
  }
}

void VLGraph::OutputResource(DResource *r) {
  sym_t type = r->opr_->type_;
  if (type == sym_assign) {
    return;
  }

  os_ << "  // ";
  OutputResourceName(r, os_);
  os_ << "\n";
  if (VLUtil::IsResourceShareBinOp(r)) {
    OutputBinopSharedResource(r);
  }
  if (VLUtil::IsInternalMEM(r)) {
    OutputArrayRefResource(r);
  }
  if (type == sym_imported) {
    OutputImportedOp(r);
  }
}

void VLGraph::OutputResourcesAll() {
  os_ << "  // resources begin\n";

  for (DResource *res : graph_->resources_) {
    OutputResource(res);
    os_ << "\n";
  }
  os_ << "  // resources end\n\n";
}

void VLGraph::OutputBitSelInsnWire(const DInsn *insn) {
  WriterUtil::BitSelOperands opr;
  WriterUtil::DecodeBitSelInsn(insn, &opr);
  os_ << "  assign " <<
    VLState::InsnOutputWireName(insn, 0);
  os_ << "[" << opr.selected_width - 1 << ":0] = "
      << VLState::RegisterName(opr.src_reg);
  os_ << "[" << opr.src_msb_pos << ":" << opr.src_lsb_pos << "];\n";
}

void VLGraph::OutputBitConcatInsnWire(const DInsn *insn) {
  os_ << "  assign "
      << VLState::InsnOutputWireName(insn, 0);
  os_ << " = {";
  bool initial = true;
  for (vector<DRegister *>::const_iterator it = insn->inputs_.begin();
       it != insn->inputs_.end(); ++it) {
    if (!initial) {
      os_ << ", ";
    }
    os_ << VLState::RegisterName(*it);
    initial = false;
  }
  os_ << "};\n";
}

void VLGraph::OutputUnsharedResourceInsnWire(DInsn *insn) {
  sym_t type = insn->resource_->opr_->type_;
  // binary, not share resource
  os_ << "  assign "
      << VLState::InsnOutputWireName(insn, 0);
  os_ << " = ";
  if (type == sym_selector) {
    os_ << VLState::RegisterName(*insn->inputs_.rbegin());
    os_ << " ? ";
    vector<DRegister *>::reverse_iterator it = insn->inputs_.rbegin();
    ++it;
    os_ << VLState::RegisterName(*it);
    os_ << " : ";
    ++it;
    os_ << VLState::RegisterName(*it);
  } else {
    os_ << VLState::RegisterName(*insn->inputs_.begin());
    if (type == sym_eq) {
      os_ << "==";
    } else if (type == sym_bit_and || type == sym_logic_and) {
      os_ << "&";
    } else if (type == sym_bit_or || type == sym_logic_or) {
      os_ << "|";
    } else if (type == sym_bit_xor) {
      os_ << "^";
    } else {
      VLWriter::ICE("unknown non-share resource");
    }
    os_ << VLState::RegisterName(*insn->inputs_.rbegin());
  }
  os_ << ";\n";
}

void VLGraph::OutputInsnWire(DInsn *insn) {
  sym_t type = insn->resource_->opr_->type_;
  if (type == sym_assign) {
    return ;
  }
  //
  vector<DRegister *>::iterator it;
  int n;
  for (n = 0, it = insn->outputs_.begin();
       it != insn->outputs_.end(); it++, n++) {
    DRegister *reg = *it;
    OutputWireType(reg->data_type_);
    os_ << VLState::InsnOutputWireName(insn, n);
    os_ << "; // id:" << insn->insn_id_ << "\n";
  }
  if (VLUtil::IsResourceUnshareUniOp(insn->resource_)) {
    // unary
    // sym_or_reduce, output here
    os_ << "  assign "
	<< VLState::InsnOutputWireName(insn, 0);
    os_ << " = ";
    if (type == sym_or_reduce) {
      os_ << "|";
    } else if (type == sym_logic_inv) {
      os_ << "!";
    } else {
      VLWriter::ICE("unknown uniop to make wire");
    }
    os_ << VLState::RegisterName(*insn->inputs_.begin())
	<< ";\n";
  }
  if (VLUtil::IsResourceShareBinOp(insn->resource_)) {
    // binary, shared resource
    os_ << "  assign "
	<< VLState::InsnOutputWireName(insn, 0);
    os_ << " = ";
    OutputResourceName(insn->resource_, os_);
    os_ << "_d0;\n";
  }
  if (VLUtil::IsResourceUnshareBinOp(insn->resource_)) {
    OutputUnsharedResourceInsnWire(insn);
  }
  if (type == sym_bit_sel) {
    OutputBitSelInsnWire(insn);
  }
  if (type == sym_bit_concat) {
    OutputBitConcatInsnWire(insn);
  }
  if (type == sym_read_channel) {
    os_ << "  assign "
	<< VLState::InsnOutputWireName(insn, 0);
    os_ << " = channel_" << insn->resource_->name_ << "_data;\n";
  }
  if (type == sym_sram_if) {
    os_ << "  assign "
	<< VLState::InsnOutputWireName(insn, 0);
    os_ << " = ";
    if (VLUtil::IsInternalMEM(insn->resource_)) {
      os_ << insn->resource_->name_ << "_rdata";
    } else {
      os_ << "data_i";
    }
    os_ << ";\n";
  }
}

void VLGraph::OutputInsnWiresAll() {
  os_ << "  // insn wires begin\n";
  for (DState *ds : graph_->states_) {
    for (DInsn *insn : ds->insns_) {
      OutputInsnWire(insn);
    }
  }
  os_ << "  // insn wires end\n\n";
}

void VLGraph::OutputInsnResultWiresAll() {
  os_ << "  // insn result wires begin\n";
  for (DState *ds : graph_->states_) {
    for (DInsn *insn : ds->insns_) {
      OutputInsnResultWire(insn);
    }
  }
  os_ << "  // insn result wires end\n\n";
}

void VLGraph::OutputInsnResultWire(DInsn *insn) {
  int n = 0;
  for (vector<DRegister *>::const_iterator it = insn->outputs_.begin();
       it != insn->outputs_.end(); ++it, ++n) {
    DRegister *reg = *it;
    if (reg->reg_type_ == DRegister::REG_WIRE) {
      os_ << "   assign "
	  << VLState::RegisterName(reg);
      os_ << " = "
	  << VLState::InsnOutputWireName(insn, n);
      os_ << ";\n";
    }
  }
}

// outputs I/O pins for instantiated imported modules
void VLGraph::OutputImportedModulePin(DResource *res) {
  ImportedResource *ir = res->imported_resource_;
  int nr = ir->GetNrPinDecls();
  for (int i = 0; i < nr; i++) {
    ImportedResource_pin pin;
    ir->GetNthPinDecl(i, &pin);
    os_ << ", ." << sym_cstr(pin.name) << "(" << res->name_
	<< res->resource_id_ << "_" << sym_cstr(pin.name) << ")";
  }
}

void VLGraph::OutputImportedModuleInstancesAll() {
  os_ << "  // imported modules begin\n";
  //
  for (DResource *r : graph_->resources_) {
    if (!r->imported_resource_) {
      continue;
    }
    sym_t mod_name = r->imported_resource_->GetModuleName();
    sym_t clk_name = r->imported_resource_->GetClockPinName();
    sym_t rst_name = r->imported_resource_->GetResetPinName();
    os_ << "  " << sym_cstr(mod_name) << " ";
    os_ << r->name_ << "_inst";
    os_ << r->resource_id_ << "(";
    os_ << "." << sym_cstr(clk_name) << "(clk), ";
    os_ << "." << sym_cstr(rst_name) << "(rst), ";
    os_ << ".req(";
    os_ << r->name_ << r->resource_id_ << "_en)";
    OutputImportedModulePin(r);
    os_ << ");\n";
  }
  os_ << "  // imported modules end\n";
}

}  // namespace writer
