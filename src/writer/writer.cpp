// Copyright (C) Yusuke Tabata 2010-2015

#include "writer/writer.h"

#include "dfg/dfg.h"
#include "writer/cc_writer.h"
#include "writer/vl_writer.h"

#include <sstream>
#include <stdlib.h>
#include <string.h>

namespace writer {

bool Writer::WriteModule(DModule *mod, const char *fn) {
  if (Util::IsHtmlFileName(fn)) {
    dfg::DFGDumpContext *ddc = dfg::DFGDump::Start(fn);
    dfg::DFGDump::DumpModule(ddc, mod, NULL);
    dfg::DFGDump::End(ddc);
    return true;
  } else if (Util::IsCCFileName(fn)) {
    return CCWriter::WriteModule(mod, fn);
  } else {
    return VLWriter::WriteModule(mod, fn);
  }
}

Writer::Writer(const string &name, DModule *mod, ostream &os)
  : mod_(mod), os_(os), lang_(name) {
}

void Writer::ICE(const char *msg, const sym_t sym) {
  cout << "ICE:(" << lang_ << ")" << msg << "\n";
  if (sym) {
    cout << sym_cstr(sym) << "\n";
  }
  exit(1);
}

string Writer::OutputSignature() {
  return Env::GetVersion();
}

}  // namespace writer
