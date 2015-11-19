// Copyright Yusuke Tabata 2007-2015
//
// Verilog writer

#include "writer/vl_writer.h"

#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "nli.h"
#include "dfg/dfg.h"
#include "dfg/imported_resource.h"
#include "messages.h"
#include "writer/vl_channel.h"
#include "writer/vl_module.h"
#include "writer/vl_util.h"

namespace writer {

VLWriter::VLWriter(DModule *mod, const string &name, ostream &os) : Writer(mod, os), top_module_name_(name) {
}

void VLWriter::ICE(const char *msg, const sym_t sym) {
  CommonICE("vl", msg, sym);
}

void VLWriter::Output() {
  os_ << "// " << OutputSignature() << "\n";
  std::ostringstream ss;
  vector<string> files;
  OutputSubModules(mod_, "mod", &files, ss);
  std::set<string> file_set;
  for (string &fn : files) {
    file_set.insert(fn);
  }
  for (const string &fn : file_set) {
    if (!Util::CopyFile(fn.c_str(), os_)) {
      CHECK(false) << "can not copy file";
    }
  }
  os_ << ss.str();
}

void VLWriter::OutputSubModules(DModule *dm, const string &path_name,
				vector<string> *files, ostream &os) {
  string cur_path = path_name + "_" + dm->module_name_;
  for (DModule *sub_module : dm->sub_modules_) {
    OutputSubModules(sub_module, cur_path, files, os);
  }
  VLChannelWriter ch;
  VLModule mod(dm, path_name, &ch, os);
  mod.Output(files);

  if (!dm->parent_mod_ && mod.GetModuleName() != top_module_name_) {
    OutputTopLevelWrapper(&mod, os);
  }
}

void VLWriter::OutputTopLevelWrapper(VLModule *module_writer,
				     ostream &os) {
  os << "\nmodule " << top_module_name_ << "(";
  VLIOSet *pins = module_writer->GetPins();
  pins->Output(VLIOSet::PIN_NAME, os);
  os << ");\n";
  pins->Output(VLIOSet::PIN_DIRECTION, os);
  const string &name = module_writer->GetModuleName();
  os << "  " << name << " " << name << "_inst(";
  pins->Output(VLIOSet::PIN_CONNECTION, os);
  os << ");\n"
     << "endmodule\n";
}

bool VLWriter::WriteModule(DModule *mod, const string &fn) {
  string name = Util::BaseNameWithoutSuffix(fn);
  std::ostringstream ss;

  VLWriter vw(mod, name, ss);
  vw.Output();

  Message::os(Message::INFO) << "output file name=" << fn;
  MessageFlush::Get(Message::INFO);
  std::unique_ptr<std::ofstream> fos(new std::ofstream(fn));
  if (fos->fail()) {
    Message::os(Message::USER) << "failed to open " << fn;
    MessageFlush::Get(Message::USER);
    return false;
  }
  *fos << ss.str();

  return true;
}

}  // namespace writer
