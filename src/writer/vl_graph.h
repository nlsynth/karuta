// -*- C++ -*-
#ifndef _writer_vl_graph_h_
#define _writer_vl_graph_h_

#include "nli.h"

#include <map>

using std::map;

namespace dfg {
class DGraph;
class DInsn;
class DRegister;
class DResource;
class DState;
class DType;
class ImportedResource_pin;
}  // namespace
using namespace dfg;

namespace writer {

class ModuleTemplate;
class VLChannelWriter;
class VLIOSet;
class VLStateEncoder;
class Writer;

class VLGraph {
public:
  VLGraph(DGraph *graph, const string &path_name,
	  ModuleTemplate *tmpl, ostream &os);
  ~VLGraph();

  void Output();
  void PreProcess();

private:
  // Toplevel output functions.
  void OutputRegisters();
  void OutputTaskReadySignal();
  void OutputTaskEntryState();
  void DeclareStateVariable();
  void OutputResourcesAll();
  void OutputInsnWiresAll();
  void OutputInsnResultWiresAll();
  void OutputFSM();
  void OutputImportedModuleInstancesAll();

  void OutputInsnWire(DInsn *insn);
  void OutputInsnResultWire(DInsn *insn);
  void OutputResource(DResource *r);
  void OutputImportedOp(DResource *r);
  void OutputImportedModulePin(DResource *res);
  void OutputImportedOpInputPin(DResource *r,
				ImportedResource_pin *pin,
				int nth_input);
  void OutputBinopSharedResource(DResource *r);
  void OutputBinopWire(DResource *r);
  void OutputUnsharedResourceInsnWire(DInsn *insn);
  void OutputArrayRefResource(DResource *r);
  void OutputBitSelInsnWire(const DInsn *insn);
  void OutputBitConcatInsnWire(const DInsn *insn);
  void OutputRegType(const DType *type);
  void OutputWireType(const DType *type);

  void OutputDebugDisplay();
  void OutputInitialVals();
  void OutputStateOutput();
  void SetEnabledStateSet(DResource *res, const string &dst_signal);

  void OutputResourceName(const DResource *res, ostream &os);

  static const DRegister *GetNthInput(const DInsn *insn, int nth);

  Writer *writer_;
  ostream &os_;
  const string path_name_;
  DGraph *graph_;
  ModuleTemplate *tmpl_;

  std::unique_ptr<VLIOSet> pins_;
  std::unique_ptr<VLStateEncoder> state_encoder_;
};

}  // namespace writer

#endif  // _writer_vl_graph_h_
