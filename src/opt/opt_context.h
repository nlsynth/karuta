// -*- C++ -*-
#ifndef _opt_opt_context_h_
#define _opt_opt_context_h_

#include "nli.h"

#include <list>

using std::list;

namespace dfg {
class DFGDumpContext;
class DGraph;
class DGraphAnnotation;
class DModule;
}  // namespace dfg
using namespace dfg;

namespace opt {


// Per DModule state
class OptimizeContext {
public:
  OptimizeContext(dfg::DModule *mod);

  void SetFlag(int flag);
  void ClearFlag(int flag);
  bool IsSet(int flag) const;

  void BeginPhase(const char *phase);
  void EndPhase();
  void WriteDumpIndex();
  void DoDumpIndex(ostream &ofs);
  void CreateFileIndex(string *str);
  void OverwriteFileIndex();
  void DumpIntermediateModule(DGraphAnnotation *an,
			      const char *suffix);
  void DumpIntermediateGraph(DGraph *graph, DGraphAnnotation *an,
			     const char *suffix);
  void SetDumpFn(const char *fn);

  // ready to output HDL.
  static const int SynthReady = 1;
  // registers sharing optimization was performed.
  static const int RegisterShare = 2;
  // SSA form. (either phi or selector can be used).
  static const int SSAForm = 4;
  // interfaces are synthesizable
  static const int InterfaceCompiled = 8;

private:
  // Delayed initialization of output file.
  // This is called when actual output happens.
  void DoBeginPhase();
  void DumpModuleOrGraph(DModule *mod, DGraph *graph,
			 dfg::DGraphAnnotation *an,
			 const char *suffix);
  int flags_;
  int index_;
  dfg::DFGDumpContext *ddc_;
  DModule *mod_;
  const char *current_phase_;
  list<string> dump_fn_list_;
  string dump_fn_;
};

}  // namespace opt

#endif  // _opt_opt_context_h_
