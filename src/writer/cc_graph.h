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
class Writer;

class CCGraph {
public:
  CCGraph(DGraph *graph, ClassWriter *cw, Writer *writer,
	  ostream &os);

  void OutputGraph();

private:
  void OutputArrayDecl(const string &name, const DArray *array);
  void OutputArrayInstantiation(const DGraph *g);
  void OutputStateDumper(const DGraph *g);
  void OutputResetHandler(const DGraph *g);
  void OutputRegisters(const DGraph *g);
  void OutputState(const DGraph *g, const DState *st);
  // insn output
  void OutputInsnList(const DState *st, ostream &os);
  void OutputInsn(const DInsn *insn, ostream &os);
  void OutputBitSelInsn(const DInsn *insn, ostream &os);
  void OutputBitConcatInsn(const DInsn *insn, ostream &os);
  void OutputImportedInsn(const DInsn *insn, ostream &os);
  void OutputSRAMInsn(const DInsn *insn, ostream &os);
  void OutputBinOp(const DInsn *insn, ostream &os);
  void OutputUniOp(const DInsn *insn, ostream &os);
  void OutputAssign(const DInsn *insn, ostream &os);
  void OutputBranch(const DInsn *insn, ostream &os);
  void OutputSelectorInsn(const DInsn *insn, ostream &os);
  void OutputChannelWriteInsn(const DInsn *insn, ostream &os);
  void OutputChannelReadInsn(const DInsn *insn, ostream &os);
  string RegisterName(const DRegister *reg);
  void OutputImportedInsn(const DRegister *reg, ostream &os);

  bool IsTerminal(const DState *st) const;

  DGraph *graph_;
  ostream &os_;
  ClassWriter *cw_;
  Writer *writer_;

  vector<string> sub_instances_;
};
  
}  // namespace writer

#endif  // _writer_cc_graph_h_
