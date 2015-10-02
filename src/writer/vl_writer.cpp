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

namespace writer {

VLWriter::VLWriter(DModule *mod, ostream &os) : Writer(mod, os) {
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
}

bool VLWriter::WriteModule(DModule *mod, const char *fn) {
  std::unique_ptr<VLWriter> vw;
  std::ostringstream ss;
  vw.reset(new VLWriter(mod, ss));
  vw->Output();

  if (!fn) {
    cout << ss.str();
  } else {
    std::unique_ptr<Message> m(Message::CreateMessage(Message::INFO));
    m->os() << "output file name=" << fn;
    std::unique_ptr<std::ofstream> fos(new std::ofstream(fn));
    if (fos->fail()) {
      std::unique_ptr<Message> n(Message::CreateMessage(Message::USER));
      n->os() << "failed to open " << fn;
      return false;
    }
    *fos << ss.str();
  }
  return true;
}

}  // namespace writer
