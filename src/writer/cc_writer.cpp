// Copyright Yusuke Tabata 2007-2015
// C++ writer
#include "writer/cc_writer.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "messages.h"
#include "nli.h"
#include "dfg/dfg.h"
#include "writer/cc_class.h"
#include "writer/cc_module.h"

namespace writer {

CCWriter::CCWriter(DModule *mod, ostream &os) : Writer(mod, os) {
}

void CCWriter::ICE(const char *msg, const sym_t sym) {
  CommonICE("cc", msg, sym);
}

void CCWriter::Output() {
  os_ << "// " << OutputSignature() << "\n";
  os_ << "#include \"ccrt.h\"\n\n";

  OutputModule(mod_->module_name_, mod_);
  OutputMain();
}

void CCWriter::OutputModule(const string &cur_path, DModule *mod) {
  for (DModule *cur_mod : mod->sub_modules_) {
    OutputModule(cur_path + "_" + cur_mod->module_name_, cur_mod);
  }
  CCModule w(cur_path, mod, os_);
  w.Output();
}

void CCWriter::OutputMain() {
  Util::CopyFile("ccrt_main.cpp", os_);
}

bool CCWriter::WriteModule(DModule *mod, const string &fn) {
  std::unique_ptr<CCWriter> cw;
  std::unique_ptr<std::ofstream> fos;

  std::unique_ptr<Message> m(Message::CreateMessage(Message::INFO));
  m->os() << "output file name=" << fn;
  fos.reset(new std::ofstream(fn));
  if (fos->fail()) {
    std::unique_ptr<Message> n(Message::CreateMessage(Message::USER));
    n->os() << "failed to open " << fn;
    return false;
  }
  cw.reset(new CCWriter(mod, *(fos.get())));

  cw->Output();
  return true;
}

}  // namespace writer
