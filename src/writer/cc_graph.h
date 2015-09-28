// -*- C++ -*-
#ifndef _writer_cc_graph_h_
#define _writer_cc_graph_h_

#include "writer/writer.h"

namespace dfg {
class DGraph;
class DInsn;
class DModule;
class DState;
}  // namespace dfg
using namespace dfg;

namespace writer {

class ClassWriter;
class ModuleTemplate;
class Writer;

class CCGraph {
public:
  CCGraph(DGraph *graph, ClassWriter *cw, Writer *writer,
	  ModuleTemplate *tmpl, ostream &os);

  void PreProcess();
  void Output();

private:
  void OutputArrayInstantiation();
  void OutputRegisters();

  DGraph *graph_;
  ModuleTemplate *tmpl_;
  ostream &os_;
  ClassWriter *cw_;
  Writer *writer_;

  vector<string> sub_instances_;
};
  
}  // namespace writer

#endif  // _writer_cc_graph_h_
