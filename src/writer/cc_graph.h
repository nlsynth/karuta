// -*- C++ -*-
#ifndef _writer_cc_graph_h_
#define _writer_cc_graph_h_

#include "writer/writer.h"

#include <map>

using std::map;

namespace dfg {
class DGraph;
class DInsn;
class DModule;
class DState;
}  // namespace dfg
using namespace dfg;

namespace writer {

class CCState;
class CCModule;
class ClassWriter;
class CCWriter;
class ModuleTemplate;
class Writer;

class CCGraph {
public:
  CCGraph(DGraph *graph, ClassWriter *cw,
	  ModuleTemplate *tmpl, ostream &os);
  ~CCGraph();

  void PreProcess();
  void Output();

private:
  void OutputArrayInstantiation();
  void OutputRegisters();

  DGraph *graph_;
  ModuleTemplate *tmpl_;
  ostream &os_;
  ClassWriter *cw_;

  vector<string> sub_instances_;
  map<DState *, CCState *> state_writers_;
};
  
}  // namespace writer

#endif  // _writer_cc_graph_h_
