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

void Writer::DecodeBitSelInsn(const DInsn *insn,
			      BitSelOperands *opr) {
  vector<DRegister *>::const_iterator it = insn->inputs_.begin();
  opr->src_reg = *it;
  it++;
  opr->src_msb_pos = (*it)->num_;
  it++;
  opr->src_lsb_pos = (*it)->num_;
  opr->selected_width = opr->src_msb_pos - opr->src_lsb_pos + 1;
}

string Writer::OutputSignature() {
  return Env::GetVersion();
}

string Writer::ArrayDescription(const string &name,
				const DArray *array) {
  string ram_or_rom = "rom";
  if (array->may_write_) {
    ram_or_rom = "ram";
  }
  ostringstream os;
  os << name << " length="
     << array->num_.size() << " (" << ram_or_rom << ")";
  return string(os.str());
}

}  // namespace writer
