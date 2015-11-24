#include "writer/vl_channel.h"

#include "dfg/dfg.h"
#include "writer/vl_util.h"

namespace writer {

VLChannelWriter::VLChannelWriter(const string &prefix) : prefix_(prefix) {
}

void VLChannelWriter::MaybeOutputModuleCode(int width, ostream &os) {
  if (bits.find(width) != bits.end()) {
    return;
  }
  bits.insert(width);

  //              +----------+
  // wdata     -> | rdata    | -> rdata
  // wdata_en  -> | rdata_en | -> rdata_en
  // wdata_ack <- |          | <- rdata_ack
  //              +----------+

  VLIOSet pins;
  pins.AddPin("clk", VLIOSet::INPUT, 0, "");
  pins.AddPin("rst", VLIOSet::INPUT, 0, "");
  pins.AddPin("wdata", VLIOSet::INPUT, width, "");
  pins.AddPin("wdata_en", VLIOSet::INPUT, 0, "");
  pins.AddPin("wdata_ack", VLIOSet::OUTPUT, 0, "");
  pins.AddPin("rdata", VLIOSet::OUTPUT, width, "");
  pins.AddPin("rdata_en", VLIOSet::OUTPUT, 0, "");
  pins.AddPin("rdata_ack", VLIOSet::INPUT, 0, "");
  os << "\n//channel width "<< width << "\n";
  os << "module " << ModuleName(width) << "(";
  pins.Output(VLIOSet::PIN_NAME, os);
  os <<");\n";
  pins.Output(VLIOSet::PIN_TYPE, os);
  os << "  wire [" << width - 1 << ":0] data;\n"
     << "  wire full;\n"
     << "  assign full = rdata_en;\n"
     << "  assign data = rdata;\n"
     << "  always @(posedge clk) begin\n"
     << "    if (rst) begin\n"
     << "      wdata_ack <= 0;\n"
     << "      rdata_en <= 0;\n"
     << "    end else begin\n"
     << "`ifdef NLI_DEBUG\n"
     << "      $display(\"NLI: full=%d, data=%d, wdata=%d, wdata_en=%d, wdata_ack=%d, rdata=%d, rdata_en=%d, rdata_ack=%d\", full, data, wdata, wdata_en, wdata_ack, rdata, rdata_en, rdata_ack);\n"
     << "`endif\n"
     << "      if (rdata_ack && full) begin\n"
     << "        rdata_en <= 0;\n"
     << "        wdata_ack <= 0;\n"
     << "`ifdef NLI_DEBUG\n"
     << "       $display(\"NLI: read %d\", data);\n"
     << "`endif\n"
     << "      end else if (wdata_en && !full) begin\n"
     << "        rdata <= wdata;\n"
     << "        rdata_en <= 1;\n"
     << "        wdata_ack <= 1;\n"
     << "`ifdef NLI_DEBUG\n"
     << "      $display(\"NLI: write %d\", wdata);\n"
     << "`endif\n"
     << "      end else begin\n"
     << "        wdata_ack <= 0;\n"
     << "      end\n"
     << "    end\n"
     << "  end\n";
  os << "endmodule\n\n";
}

string VLChannelWriter::ModuleName(int width) {
  ostringstream os;
  os << prefix_ + "_channel_" << width;
  return string(os.str());
}

void VLChannelWriter::OutputChannelWires(DModule *mod, ostream &os) {
  for (size_t i = 0; i < mod->channels_.size(); ++i) {
    DChannel *chan = mod->channels_[i];
    if (chan->reader_module_ == NULL || chan->writer_module_ == NULL) {
      continue;
    }
    const string &c = chan->channel_name_;
    int width = chan->data_width_;
    
    os << "  // channel " << c << "\n"
       << "  wire [" << (width - 1) << ":0] " << c << "_wdata;\n"
       << "  wire " << c << "_wdata_en;\n"
       << "  wire " << c << "_wdata_rdy;\n"
       << "  wire [" << (width - 1) << ":0] " << c << "_rdata;\n"
       << "  wire " << c << "_rdata_en;\n"
       << "  wire " << c << "_rdata_ack;\n"
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
    string mod_name = ModuleName(chan->data_width_);
    string inst_name =
      mod_name + "_" + chan->channel_name_ + "_" +
      chan->writer_module_->module_name_ + "_" +
      chan->reader_module_->module_name_ + "_inst";
    os << "  " << mod_name << " " << inst_name << "(.clk(clk), .rst(rst),\n"
       << "    .wdata("<< c << "_wdata), .wdata_en("<< c
       << "_wdata_en), .wdata_ack("<< c <<"_wdata_ack),\n"
       << "    .rdata("<< c << "_rdata), "
       << ".rdata_en("<< c << "_rdata_en), "
       << ".rdata_ack("<< c <<"_rdata_ack));\n";
  }
}

void VLChannelWriter::MaybeOutputChannelConnections(DModule *mod,
						    DModule *sub_mod,
						    ostream &os) {
  for (size_t i = 0; i < mod->channels_.size(); ++i) {
    DChannel *chan = mod->channels_[i];
    const string &c = chan->channel_name_;
    const string p = "channel_" + chan->channel_name_;
    if (chan->writer_module_ == sub_mod) {
      os << "/* write */, ." << p << "_data(" << c <<"_wdata), "
	 << "." << p << "_en(" << c << "_wdata_en), "
	 << "." << p << "_ack(" << c << "_wdata_ack)";
    }
    if (chan->reader_module_ == sub_mod) {
      os << "/* read */, ." << p << "_data(" << c << "_rdata), "
	 << "." << p << "_en(" << c << "_rdata_en), "
	 << "." << p << "_ack(" << c << "_rdata_ack)";
    }
  }
}

}  // namespace writer
