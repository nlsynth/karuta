// -*- C++ -*-
#ifndef _opt_ssa_cleaner_h_
#define _opt_ssa_cleaner_h_

#include "nli.h"

#include <map>

using std::map;
using std::multimap;

namespace dfg {
class DGraph;
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

class SSACleaner {
public:
  SSACleaner(DGraph *graph);

  void Perform();
private:
  DGraph *graph_;
  
  DResource *assign_res_;
  DResource *phi_res_;
  DResource *selector_res_;

  // use multimap, since the same insn can have multiple outputs.
  multimap<DInsn *, DefInfo *> def_info_map_;

  std::unique_ptr<BasicBlockSet> bset_;
  std::unique_ptr<DataFlowCollector> dfc_;

  void ProcessBB(BasicBlock *bb);
  void ProcessInsn(map<DRegister *, DefInfo *> *last_defs, DState *st, DInsn *insn);
  void EmitSelector(map<DRegister *, DefInfo *> *last_defs, DState *st, DInsn *insn);
};

}  // namespace opt

#endif //  _opt_ssa_cleaner_h_
