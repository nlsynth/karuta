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
#include "dfg/resource_params.h"
#include "status.h"
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
  string prefix = Env::GetModulePrefix();
  if (prefix.empty()) {
    prefix = top_module_name_;
  }
  VLChannelWriter ch(prefix);
  OutputSubModulesRec(mod_, prefix, &ch, &files, ss);
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

void VLWriter::OutputSubModulesRec(DModule *dm, const string &path_name,
				   VLChannelWriter *ch,
				   vector<string> *files, ostream &os) {
  string cur_path = path_name + "_" + dm->module_name_;
  for (DModule *sub_module : dm->sub_modules_) {
    OutputSubModulesRec(sub_module, cur_path, ch, files, os);
  }
  VLModule mod(dm, path_name, ch, os);
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

  Status::os(Status::INFO) << "output file name=" << fn;
  MessageFlush::Get(Status::INFO);
  std::unique_ptr<std::ofstream> fos(new std::ofstream(fn));
  if (fos->fail()) {
    Status::os(Status::USER) << "failed to open " << fn;
    MessageFlush::Get(Status::USER);
    return false;
  }
  *fos << ss.str();

  return true;
}

}  // namespace writer
