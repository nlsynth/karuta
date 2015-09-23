// -*- C++ -*-
#ifndef _dfg_dfg_dump_h_
#define _dfg_dfg_dump_h_

#include "nli.h"

namespace dfg {

class DFGDumpContext;
class DGraph;
class DGraphAnnotation;
class DModule;

class DFGDump {
public:
  static DFGDumpContext *Start(const char *fn);
  static void AddNote(DFGDumpContext *dc, const char *note);
  static void DumpModule(DFGDumpContext *dc, DModule *mod,
			 DGraphAnnotation *a);
  static void DumpGraph(DFGDumpContext *dc, DGraph *graph,
			DGraphAnnotation *a);
  static void End(DFGDumpContext *ctx);
private:
  static void DumpModuleRec(const string &path, DFGDumpContext *dc,
			    DModule *mod, DGraphAnnotation *a);
};

}  // namespace dfg

#endif // _dfg_dfg_dump_h_
