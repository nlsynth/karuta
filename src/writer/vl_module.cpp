#include "writer/vl_module.h"

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include "nli.h"
#include "dfg/dfg.h"
#include "dfg/imported_resource.h"
#include "messages.h"
#include "writer/module_template.h"
#include "writer/vl_channel.h"
#include "writer/vl_graph.h"
#include "writer/vl_util.h"
#include "writer/writer_util.h"

namespace writer {

//
// VLModule
//   VLGraph
//     VLState

VLModule::VLModule(DModule *mod, const string& path_name,
		   VLChannelWriter *ch, ostream &os)
  : path_name_(path_name), ch_(ch), mod_(mod), os_(os) {
  template_.reset(new ModuleTemplate);
}

VLModule::~VLModule() {
}

void VLModule::Output(vector<string> *copy_files) {
  OutputExternalStuff(copy_files);
  OutputVLModule(path_name_ + "_" + mod_->module_name_);
}

void VLModule::OutputExternalStuff(vector<string> *copy_files) {
  if (mod_->graph_) {
    for (DResource *r : mod_->graph_->resources_) {
      if (r->imported_resource_) {
	// imported resource
	sym_t fn = r->imported_resource_->GetCopyFileName();
	copy_files->push_back(sym_cstr(fn));
      }
      if (r->array_) {
	// array
	OutputArray(r->name_, r->array_);
      }
    }
  }

  for (size_t i = 0; i < mod_->channels_.size(); ++i) {
    DChannel *chan = mod_->channels_[i];
    if (chan->writer_ != mod_ && chan->reader_ != mod_) {
      ch_->MaybeOutput(32, os_);
    }
  }
}

void VLModule::CollectTaskPins(DModule *dm, bool in_container) {
  if (dm->module_type_ != DModule::MODULE_TASK) {
    return;
  }
  string pin_base = VLUtil::TaskControlPinName(dm);
  pins_->AddPin(pin_base + "_en", VLIOSet::INPUT_WIRE, 0, "");
  pins_->AddPin(pin_base + "_rdy", VLIOSet::OUTPUT_WIRE, 0, "");
  if (dm->graph_) {
    DInsn *entry_insn = WriterUtil::FindTaskEntryInsn(dm->graph_);
    CHECK(entry_insn);
    for (size_t nth_arg = 0; nth_arg < entry_insn->inputs_.size(); ++nth_arg)  {
      DRegister *reg = entry_insn->inputs_[nth_arg];
      pins_->AddPin(VLUtil::TaskParamPinName(pin_base, nth_arg, "_i"),
		    VLIOSet::INPUT_WIRE,
		    reg->data_type_->size_, "");
    }
    DInsn *finish_insn = WriterUtil::FindTaskFinishInsn(dm->graph_);
    CHECK(finish_insn);
    for (size_t nth_rv = 0; nth_rv < finish_insn->inputs_.size(); ++nth_rv) {
      DRegister *reg = finish_insn->inputs_[nth_rv];
      VLIOSet::PinType type;
      if (in_container) {
	type = VLIOSet::OUTPUT_WIRE;
      } else {
	type = VLIOSet::OUTPUT;
      }
      pins_->AddPin(VLUtil::TaskParamPinName(pin_base, nth_rv, "_o"),
		    type, reg->data_type_->size_, "");
    }
  }
}

void VLModule::CollectPinDecls() {
  if (mod_->module_type_ == DModule::MODULE_CONTAINER) {
    for (DModule *sub_module : mod_->sub_modules_) {
      CollectTaskPins(sub_module, true);
    }
  }
  CollectTaskPins(mod_, false);

  if (!mod_->graph_) {
    return;
  }
  bool has_external_ram = false;
  for (auto *r : mod_->graph_->resources_) {
    if (VLUtil::IsExternalRAM(r)) {
      has_external_ram = true;
    }
  }

  for (size_t i = 0; i < mod_->channels_.size(); ++i) {
    DChannel *chan = mod_->channels_[i];
    string c = "Channel " + chan->name_;
    if (chan->writer_ == mod_) {
      CHECK(chan->reader_ != mod_);
      pins_->AddPin("channel_" + chan->name_ + "_data", VLIOSet::OUTPUT, 32, c);
      pins_->AddPin("channel_" + chan->name_ + "_en", VLIOSet::OUTPUT, 0, c);
      pins_->AddPin("channel_" + chan->name_ + "_rdy", VLIOSet::INPUT, 0, c);
    } else if (chan->reader_ == mod_) {
      CHECK(chan->writer_ != mod_);
      pins_->AddPin("channel_" + chan->name_ + "_data", VLIOSet::INPUT, 32, c);
      pins_->AddPin("channel_" + chan->name_ + "_en", VLIOSet::INPUT, 0, c);
      pins_->AddPin("channel_" + chan->name_ + "_rdy", VLIOSet::OUTPUT, 0, c);
    } else {
      CHECK(false);
    }
  }
  if (has_external_ram) {
    string c = "EXTERNAL_RAM";
    pins_->AddPin("addr_o", VLIOSet::OUTPUT, 32, c);
    pins_->AddPin("write_en_o", VLIOSet::OUTPUT, 0, c);
    pins_->AddPin("data_o", VLIOSet::OUTPUT, 32, c);
    pins_->AddPin("data_i", VLIOSet::INPUT, 32, c);
  }
}

void VLModule::PreProcessModule(const string &path_name) {
  bool has_graph = (mod_->module_type_ != DModule::MODULE_CONTAINER);
  ostream &os =
    template_->GetStream(ModuleTemplate::SUB_MODULE_INSTANCES);
  for (DModule *sub_module : mod_->sub_modules_) {
    string sub_module_name = path_name + "_" +  sub_module->module_name_;
    os << "  " << sub_module_name << " " << sub_module_name
       << "_inst(.clk(clk), .rst(rst)";
    if (sub_module->module_type_ == DModule::MODULE_TASK) {
      PreProcessSubModuleControl(sub_module, has_graph, os);
    }
    if (sub_module->module_type_ == DModule::MODULE_CONTAINER) {
      for (DModule *sub_sub_module : sub_module->sub_modules_) {
	PreProcessSubModuleControl(sub_sub_module, has_graph, os);
      }
    }
    VLChannelWriter::MayOutputChannelConnections(mod_, sub_module, os);
    os << ");\n";
  }
}

void VLModule::OutputModuleHead(const string &path_name) {
  pins_.reset(new VLIOSet);
  pins_->AddPin("clk", VLIOSet::INPUT, 0, "");
  pins_->AddPin("rst", VLIOSet::INPUT, 0, "");
  CollectPinDecls();
  os_ << "\nmodule " << path_name << "(";
  pins_->Output(true, os_);
  os_ << ");\n";
  pins_->Output(false, os_);
  os_ << "\n";
}

void VLModule::OutputArray(const string &name, DArray *array) {
  int length = array->num_.size();
  os_ << "// Array model "
      << WriterUtil::ArrayDescription(name, array) << "\n";
  os_ << "module " << name << "(clk, rst, ";
  if (array->may_write_) {
    os_ << "addr_i, rdata_o, wdata_i, write_en_i";
  } else {
    os_ << "addr_i, rdata_o";
  }
  os_ << ");\n"
      << "  input clk;\n"
      << "  input rst;\n";
  os_ << "  input [" << (array->address_width - 1) << ":0] addr_i;\n"
      << "  output [" << (array->data_width - 1) << ":0] rdata_o;\n";
  if (array->may_write_) {
    os_ << "  input ["<< (array->data_width - 1) << ":0] wdata_i;\n"
	<< "  input write_en_i;\n";
  }
  os_ << "  reg [" << (array->data_width - 1) << ":0] rdata_o;\n\n";

  if (array->may_write_) {
    // RAM
    OutputRAM(array);
  } else {
    // ROM
    os_ << "  always @(addr_i) begin\n"
	<< "    case(addr_i)\n";
    for (int i = 0; i < (1 << array->address_width); ++i) {
      os_ << "      " << i << ": rdata_o = ";
      if (i < length) {
	os_ << array->num_[i] << ";\n";
      } else {
	os_ << "0;\n";
      }
    }
    os_ << "    endcase\n";
    os_ << "  end\n";
  }
  os_ << "\n"
      << "endmodule\n"
      << "// array end\n\n";
}

void VLModule::OutputRAM(const DArray *array) {
  os_ << "  reg [" << (array->data_width - 1) << ":0] data [0:"
      << (1 << array->address_width) << "];\n\n";
  os_ << "  always @(posedge clk) begin\n"
      << "    if (rst) begin\n";
  size_t len = (1 << array->address_width);
  for (size_t i = 0; i < len; ++i) {
    int num = 0;
    if (i < array->num_.size()) {
      num = array->num_[i];
    }
    os_ << "      data[" << i << "] = " << num << ";\n";
  }
  os_ << "    end else begin\n"
      << "      if (write_en_i) begin\n"
      << "        data[addr_i] <= wdata_i;\n"
      << "      end\n"
      << "    end\n"
      << "  end\n"
      << "  // read side\n"
      << "  always @(addr_i or clk) begin\n"
      << "    rdata_o = data[addr_i];\n"
      << "  end\n";
}

void VLModule::PreProcessSubModuleControl(const DModule *sub_mod,
					  bool has_graph,
					  ostream &os) {
  string pin_base = VLUtil::TaskControlPinName(sub_mod);
  os << ", ." << pin_base << "_en(" << pin_base << "_en)"
     << ", ." << pin_base << "_rdy(" << pin_base << "_rdy)";

  if (has_graph) {
    string pin_base = VLUtil::TaskControlPinName(sub_mod);
    ostream &sw =
      template_->GetStream(ModuleTemplate::SUB_MODULE_CONTROL_WIRES);
    sw << "  reg " << pin_base << "_en;\n"
       << "  wire " << pin_base << "_rdy;\n";
  }

  // Args and return values.
  if (sub_mod->graph_) {
    DInsn *entry_insn = WriterUtil::FindTaskEntryInsn(sub_mod->graph_);
    for (size_t nth_arg = 0; nth_arg < entry_insn->inputs_.size(); ++nth_arg) {
      DRegister *reg = entry_insn->inputs_[nth_arg];
      string reg_name = VLUtil::TaskParamPinName(pin_base, nth_arg, "_i");
      os << ", ." << reg_name << "(" << reg_name << ")";

      if (has_graph) {
	ostream &sw =
	  template_->GetStream(ModuleTemplate::SUB_MODULE_CONTROL_WIRES);
	sw << VLUtil::RegType(reg->data_type_)
	   << reg_name << ";\n";
      }
    }
    DInsn *finish_insn = WriterUtil::FindTaskFinishInsn(sub_mod->graph_);
    for (size_t nth_rv = 0; nth_rv < finish_insn->inputs_.size(); ++nth_rv) {
      DRegister *reg = finish_insn->inputs_[nth_rv];
      string reg_name = VLUtil::TaskParamPinName(pin_base, nth_rv, "_o");
      os << ", ." << reg_name << "(" << reg_name << ")";
      ostream &sw =
	template_->GetStream(ModuleTemplate::SUB_MODULE_CONTROL_WIRES);
      sw << VLUtil::WireType(reg->data_type_) << " " << reg_name << ";\n";
    }
  }
}

void VLModule::OutputVLModule(const string &path_name) {
  std::unique_ptr<VLGraph> graph_writer;
  if (mod_->graph_) {
    graph_writer.reset(new VLGraph(mod_->graph_, path_name,
				   template_.get(), os_));
    graph_writer->PreProcess();
  }
  PreProcessModule(path_name);

  OutputModuleHead(path_name);

  os_ << template_->GetContents(ModuleTemplate::SUB_MODULE_CONTROL_WIRES);

  VLChannelWriter::OutputChannelWires(mod_, os_);

  if (mod_->graph_) {
    graph_writer->Output();
  }

  os_ << "\n  // sub modules begin\n";
  os_ << template_->GetContents(ModuleTemplate::SUB_MODULE_INSTANCES);
  os_ << "  // sub modules end\n";

  VLChannelWriter::OutputChannelInstances(mod_, os_);

  os_ << "\n"
      << "endmodule\n";
}

}  // namespace writer
