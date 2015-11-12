// Copyright (C) Yusuke Tabata 2010-2015

#include "writer/writer.h"

#include "dfg/dfg.h"
#include "writer/cc_writer.h"
#include "writer/vl_writer.h"

#include <sstream>
#include <stdlib.h>
#include <string.h>

namespace writer {

bool Writer::WriteModule(DModule *mod, const string &raw_fn) {
  string fn;
  CHECK(Env::GetOutputPath(raw_fn.c_str(), &fn))
    << "Failed to get output file path: " << raw_fn;

  bool success = true;

  if (Util::IsHtmlFileName(fn)) {
    dfg::DFGDumpContext *ddc = dfg::DFGDump::Start(fn);
    dfg::DFGDump::DumpModule(ddc, mod, NULL);
    dfg::DFGDump::End(ddc);
  } else if (Util::IsCCFileName(fn)) {
    success = CCWriter::WriteModule(mod, fn);
  } else {
    success = VLWriter::WriteModule(mod, fn);
  }
  if (success) {
    const string &marker = Env::GetOutputMarker();
    if (!marker.empty()) {
      cout << marker << raw_fn << "\n";
    }
  }
  return success;
}

Writer::Writer(DModule *mod, ostream &os)
  : mod_(mod), os_(os) {
}

void Writer::CommonICE(const char *lang, const char *msg, const sym_t sym) {
  cout << "ICE:(" << lang << ")" << msg << "\n";
  if (sym) {
    cout << sym_cstr(sym) << "\n";
  }
  exit(1);
}

string Writer::OutputSignature() {
  return Env::GetVersion();
}

}  // namespace writer
