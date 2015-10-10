// -*- C++ -*-
#ifndef _synth_interface_h_
#define _synth_interface_h_

#include <map>

using std::map;

namespace dfg {
class DArray;
class DGraph;
class DInsn;
class DModule;
class DResource;
class DState;
}  // namespace dfg
using namespace dfg;

namespace synth {

class InterfaceCompiler {
public:
  void CompileGraph(DGraph *g);

  static void CompileInterface(DModule *mod);


private:
  void GenerateSRAMWrite(DGraph *g, DResource *sram,
			 DState *ds, DInsn *mem_insn);
  void GenerateSRAMRead(DGraph *g, DResource *sram,
			DState *ds, DInsn *mem_insn);
  DResource *GetSRAM(DGraph *g, DResource *mem);

  map<DArray *, DResource *> srams_;
};

}  // namespace synth

#endif  // _synth_interface_h_
