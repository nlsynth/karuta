// -*- C++ -*-
#ifndef _synth_iroha_h_
#define _synth_iroha_h_

#include "nli.h"

#include <map>

using std::map;

namespace dfg {
class DChannel;
class DModule;
class DGraph;
class DState;
class DInsn;
class DResource;
class DRegister;
class DType;
}  // namespace dfg
using namespace dfg;

namespace synth {

class IrohaDumper {
public:
  IrohaDumper(DModule *root_mod, ostream &os);

  static void Dump(DModule *mod, const string &path);
  void DumpDesign();

private:
  void DumpModule(DModule *mod);

  DModule *root_mod_;
  ostream &os_;
};

class IModuleDumper {
public:
  IModuleDumper(DModule *mod, ostream &os);
  void Dump();
  void DumpChannel(DChannel *ch, int id);

private:
  void DumpGraph(DGraph *graph);
  void DumpState(DState *st);
  void DumpInsn(DInsn *insn);
  void DumpTransition(DInsn *insn);
  string GetResourceClass(DResource *res);
  void DumpRegs(vector<DRegister *> &regs);
  void DumpRegister(DRegister *reg);
  void DumpResource(DResource *res);
  void DumpTypes(vector<DType *> &types);
  void WriteArraySpec(DResource *res);
  void DumpChannelEndPoint(DChannel *ch, DModule *mod);

  DModule *mod_;
  ostream &os_;
  map<DRegister *, int> reg_id_map_;
};
  
}  // namespace synth

#endif  // _synth_iroha_h_
