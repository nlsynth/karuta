// -*- C++ -*-
#ifndef _opt_ssa_converter_h_
#define _opt_ssa_converter_h_

#include "nli.h"

#include <set>
#include <map>
#include <vector>

using std::set;
using std::map;
using std::multimap;
using std::vector;

namespace dfg {
class DGraph;
class DGraphAnnotation;
class DInsn;
class DRegister;
class DResource;
class DState;
}  // namespace dfg
using namespace dfg;

namespace opt {

class BasicBlock;
class BasicBlockSet;
class DataFlowCollector;
class DefInfo;
class DominatorTreeBuilder;
class RegisterVersionManager;

class SSAConverter {
public:
  SSAConverter(DGraph *graph);
  ~SSAConverter();

  void Perform();

private:
  void PreparePHI(dfg::DGraphAnnotation *an);
  void CalculatePHI(dfg::DGraphAnnotation *an);

  void CollectOriginalDefs();
  void PropagatePHIs();
  void CommitPHIInsn();

  DGraph *graph_;
  DResource *phi_res_;
  bool IsSingularReg(DRegister *reg);
  set<DRegister *> singular_regs_;

  std::unique_ptr<BasicBlockSet> bset_;
  std::unique_ptr<DataFlowCollector> dfc_;
  std::unique_ptr<DominatorTreeBuilder> dtb_;
  std::unique_ptr<RegisterVersionManager> rvm_;

  class PerRegister {
  public:
    set<DefInfo *> original_defs_;
    set<BasicBlock *> phi_bbs_;
  };
  map<DRegister *, PerRegister *> reg_phis_map_;
  class PHI {
  public:
    DInsn *insn_;
    set<DefInfo *> defs_;
  };
  vector<PHI *> phis_;

  // use multimap, since the same insn can have multiple outputs.
  multimap<DInsn *, DefInfo *> def_info_map_;

  void CalculatePHIInputsforBB(BasicBlock *bb);
  PerRegister *GetPerRegister(DRegister *reg);
  void PropagatePHIforBB(PerRegister *pr, BasicBlock *bb);
  void UpdatePHIInputs(PHI *phi);
  void UpdateVersionsForBB(BasicBlock *bb);
  void UpdateVersionsForInsn(map<DRegister *, DefInfo *> *last_defs, DInsn *insn);
  void DumpPerRegister(dfg::DGraphAnnotation *an);
  void DumpPHIs(dfg::DGraphAnnotation *an);
};

}  // namespace opt

#endif //  _opt_ssa_converter_h_
