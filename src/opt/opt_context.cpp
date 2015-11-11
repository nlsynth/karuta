#include "opt/opt_context.h"

#include "dfg/dfg.h"

#include <fstream>

using std::ofstream;

namespace opt {

OptimizeContext::OptimizeContext(DModule *mod) :
  flags_(0), index_(0), ddc_(NULL), mod_(mod), current_phase_(NULL) {
}

void OptimizeContext::SetFlag(int flag) {
  flags_ |= flag;
}

void OptimizeContext::ClearFlag(int flag) {
  flags_ &= (~flag);
}

bool OptimizeContext::IsSet(int flag) const {
  return flags_ & flag;
}

void OptimizeContext::BeginPhase(const char *phase) {
  if (dump_fn_.empty()) {
    return ;
  }
  current_phase_ = phase;
}

void OptimizeContext::DoBeginPhase() {
  char idx[10];
  sprintf(idx, "%d", index_);
  ++index_;
  string fn = dump_fn_ + "." + idx + "." + current_phase_ + ".html";
  ddc_ = dfg::DFGDump::Start(fn);
  dump_fn_list_.push_back(fn);
}

void OptimizeContext::EndPhase() {
  if (ddc_) {
    dfg::DFGDump::End(ddc_);
    ddc_ = NULL;
  }
  current_phase_ = NULL;
}

void OptimizeContext::WriteDumpIndex() {
  if (dump_fn_list_.size() == 0) {
    return;
  }
  if (dump_fn_.empty()) {
    return ;
  }
  string fn = dump_fn_ + ".index.html";
  std::unique_ptr<ofstream> ofs(new ofstream(fn.c_str()));
  DoDumpIndex(*ofs.get());
  OverwriteFileIndex();
}

void OptimizeContext::CreateFileIndex(string *str) {
  for (string &raw_fn : dump_fn_list_) {
    string fn = Util::GetBaseName(raw_fn.c_str());
    *str += "|<a href=\"" + fn + "\" target=\"fr\">"
      + fn.c_str() + "</a>|<wbr>";
  }
}

void OptimizeContext::DoDumpIndex(ostream &ofs) {
  ofs << "<html><head></head><body>";
  string index;
  CreateFileIndex(&index);
  ofs << index;
  string initial_page =
    Util::GetBaseName((*dump_fn_list_.begin()).c_str()).c_str();
  ofs << "<hr><iframe src=\"" << initial_page;
  ofs << "\" name=\"fr\" width=100% height=80%>iframe</iframe>";
  ofs << "</body></html>";
}

void OptimizeContext::OverwriteFileIndex() {
  string index;
  CreateFileIndex(&index);
  for (string &fn : dump_fn_list_) {
    // <!-- NLI_HTML_BODY -->
    Util::RewriteFile(fn.c_str(), "<!-- NLI_HTML_BODY -->",
		      index.c_str());
  }
}

void OptimizeContext::DumpIntermediateModule(dfg::DGraphAnnotation *an,
					     const char *suffix) {
  BeginPhase(suffix);
  DumpModuleOrGraph(mod_, NULL, an, suffix);
  EndPhase();
}

void OptimizeContext::DumpIntermediateGraph(DGraph *graph,
					    dfg::DGraphAnnotation *an,
					    const char *suffix) {
  DumpModuleOrGraph(NULL, graph, an, suffix);
}

void OptimizeContext::DumpModuleOrGraph(DModule *mod, DGraph *graph,
					dfg::DGraphAnnotation *an,
					const char *phase) {
  if (!ddc_) {
    if (current_phase_) {
      DoBeginPhase();
    } else {
      return;
    }
  }
  if (mod) {
    dfg::DFGDump::AddNote(ddc_, phase);
    dfg::DFGDump::DumpModule(ddc_, mod, an);
  }
  if (graph) {
    dfg::DFGDump::AddNote(ddc_, phase);
    dfg::DFGDump::DumpGraph(ddc_, graph, an);
  }
}

void OptimizeContext::SetDumpFn(const char *fn) {
  dump_fn_ = string(fn);
}

}  // namespace opt
