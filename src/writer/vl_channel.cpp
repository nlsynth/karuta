#include "writer/vl_channel.h"

#include "dfg/dfg.h"
#include "writer/vl_util.h"

namespace writer {

void VLChannelWriter::MaybeOutput(int width, ostream &os) {
  if (bits.find(width) != bits.end()) {
    return;
  }
  bits.insert(width);

  VLIOSet pins;
  pins.AddPin("clk", VLIOSet::INPUT, 0, "");
  pins.AddPin("rst", VLIOSet::INPUT, 0, "");
  pins.AddPin("wdata", VLIOSet::INPUT, width, "");
  pins.AddPin("wdata_en", VLIOSet::INPUT, 0, "");
  pins.AddPin("wdata_rdy", VLIOSet::OUTPUT, 0, "");
  pins.AddPin("rdata", VLIOSet::OUTPUT, width, "");
  pins.AddPin("rdata_valid", VLIOSet::OUTPUT, 0, "");
  pins.AddPin("rdata_req", VLIOSet::INPUT, 0, "");
  os << "\n//channel width "<< width << "\n";
  os << "module " << ModuleName(width) << "(";
  pins.Output(VLIOSet::PIN_NAME, os);
  os <<");\n";
  pins.Output(VLIOSet::PIN_TYPE, os);
  os << "  wire [" << width - 1 << ":0] data;\n"
     << "  wire full;\n"
     << "  assign full = rdata_valid;\n"
     << "  assign data = rdata;\n"
     << "  always @(posedge clk) begin\n"
     << "    if (rst) begin\n"
     << "      wdata_rdy <= 1;\n"
     << "      rdata_valid <= 0;\n"
     << "    end else begin\n"
     << "`ifdef NLI_DEBUG\n"
     << "      $display(\"NLI: full=%d, data=%d, wdata=%d, wdata_en=%d, wdata_rdy=%d, rdata=%d, rdata_valid=%d, rdata_req=%d\", full, data, wdata, wdata_en, wdata_rdy, rdata, rdata_valid, rdata_req);\n"
     << "`endif\n"
     << "      if (rdata_req && full) begin\n"
     << "        rdata_valid <= 0;\n"
     << "        wdata_rdy <= 1;\n"
     << "`ifdef NLI_DEBUG\n"
     << "       $display(\"NLI: read %d\", data);\n"
     << "`endif\n"
     << "      end else if (wdata_en && !full) begin\n"
     << "        rdata <= wdata;\n"
     << "        rdata_valid <= 1;\n"
     << "        wdata_rdy <= 0;\n"
     << "`ifdef NLI_DEBUG\n"
     << "      $display(\"NLI: write %d\", wdata);\n"
     << "`endif\n"
     << "      end\n"
     << "    end\n"
     << "  end\n";
  os << "endmodule\n\n";
}

string VLChannelWriter::ModuleName(int width) {
  ostringstream os;
  os << "channel_" << width;
  return string(os.str());
}

void VLChannelWriter::OutputChannelWires(DModule *mod, ostream &os) {
  for (size_t i = 0; i < mod->channels_.size(); ++i) {
    DChannel *chan = mod->channels_[i];
    if (chan->reader_module_ == NULL || chan->writer_module_ == NULL) {
      continue;
    }
    const string &c = chan->channel_name_;
    
    os << "  // channel " << c << "\n"
       << "  wire [31:0] " << c << "_wdata;\n"
       << "  wire " << c << "_wdata_en;\n"
       << "  wire " << c << "_wdata_rdy;\n"
       << "  wire [31:0] " << c << "_rdata;\n"
       << "  wire " << c << "_rdata_valid;\n"
       << "  wire " << c << "_rdata_req;\n"
       << "\n";
  }
}

void VLChannelWriter::OutputChannelInstances(DModule *mod, ostream &os) {
  for (size_t i = 0; i < mod->channels_.size(); ++i) {
    DChannel *chan = mod->channels_[i];
    if (chan->reader_module_ == NULL || chan->writer_module_ == NULL) {
      continue;
    }
    const string &c = chan->channel_name_;
    os << "  // channel from "
	<< chan->writer_module_->module_name_ << " to "
	<< chan->reader_module_->module_name_ << "\n";
    string mod_name = ModuleName(32);
    string inst_name =
      mod_name + "_" + chan->channel_name_ + "_" +
      chan->writer_module_->module_name_ + "_" +
      chan->reader_module_->module_name_ + "_inst";
    os << "  " << mod_name << " " << inst_name << "(.clk(clk), .rst(rst),\n"
       << "    .wdata("<< c << "_wdata), .wdata_en("<< c
       << "_wdata_en), .wdata_rdy("<< c <<"_wdata_rdy),\n"
       << "    .rdata("<< c << "_rdata), .rdata_valid("<< c << "_rdata_valid), .rdata_req("<< c <<"_rdata_req));\n";
  }
}

void VLChannelWriter::MayOutputChannelConnections(DModule *mod, DModule *sub_mod, ostream &os) {
  for (size_t i = 0; i < mod->channels_.size(); ++i) {
    DChannel *chan = mod->channels_[i];
    const string &c = chan->channel_name_;
    const string p = "channel_" + chan->channel_name_;
    if (chan->writer_module_ == sub_mod) {
      os << "/* write */, ." << p << "_data(" << c <<"_wdata), "
	 << "." << p << "_en(" << c << "_wdata_en), "
	 << "." << p << "_rdy(" << c << "_wdata_rdy)";
    }
    if (chan->reader_module_ == sub_mod) {
      os << "/* read */, ." << p << "_data(" << c << "_rdata), "
	 << "." << p << "_en(" << c << "_rdata_valid), "
	 << "." << p << "_rdy(" << c << "_rdata_req)";
    }
  }
}

}  // namespace writer
