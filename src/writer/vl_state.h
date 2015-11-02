// -*- C++ -*-
#ifndef _writer_vl_state_h_
#define _writer_vl_state_h_

#include "nli.h"

#include <map>

using std::map;

namespace dfg {
class DGraph;
class DInsn;
class DRegister;
class DResource;
class DState;
}  // namespace
using namespace dfg;

namespace writer {

class ModuleTemplate;
class VLStateEncoder;

class VLState {
public:
  VLState(DState *st, DGraph *g, VLStateEncoder *e,
	  ostream &os);
  ~VLState();

  void Output();
  void PreProcess(ModuleTemplate *tmpl);

  // primitive output
  static string InsnOutputWireName(const DInsn *insn, int n);
  static string RegisterName(const DRegister *reg);

private:
  void OutputInsn(const DInsn *insn);
  void OutputTransition(DGraph *g, DState *st);
  void OutputSRAMInsn(const DInsn *insn);
  void OutputChannelWriteInsn(const DInsn *insn);
  void OutputChannelReadInsn(const DInsn *insn);
  void OutputArrayRefInsn(const DInsn *insn);
  void OutputAssignInsn(const DInsn *insn);
  void OutputInsnWireToRegisterAssign(const DInsn *insn);
  void OutputRegisterValue(const DRegister *reg);
  void OutputSubModuleCall(const DInsn *insn);
  void OutputTaskFinish(const DInsn *insn);
  void OutputSubModuleArgs(const DInsn *insn);
  void CollectSubState(string *state_guard, string *initialize);

  string SubStateRegName(const DInsn *insn);

  DState *st_;
  DGraph *graph_;
  VLStateEncoder *state_encoder_;
  ostream &os_;
};

}  // namespace writer

#endif  // _writer_vl_graph_h_
