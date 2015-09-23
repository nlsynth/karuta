// -*- C++ -*-
#ifndef _opt_ssa_h_
#define _opt_ssa_h_

#include "nli.h"

#include <list>
#include <set>
#include <map>
#include "pool.h"

using std::list;
using std::set;
using std::map;
using std::multimap;

namespace dfg {
class DGraph;
class DInsn;
class DRegister;
class DState;
}  // namespace dfg
using namespace dfg;

namespace opt {

class BasicBlockSet;
class DataFlowCollector;
class DefInfo;

class SSA {
public:
  static void Init();
  static void Perform(DGraph *graph);
  static void Cleanup(DGraph *graph);
};

class SSAUtil {
public:
  // singular register: All usages of the register is from single assign insn.
  static void CollectSingularRegister(DataFlowCollector *dfc,
				      BasicBlockSet *bset,
				      set<DRegister *> *singular_regs);
  // Move insns in the first state to the newly allocated state.
  // (st) -> new_state -> (2nd_state)
  static void PrependState(DGraph *graph, DState *st);

  static void CopyRegisterList(vector<DRegister *> &src, vector<DRegister *> *dst);
  static DefInfo *GetDefInfo(multimap<DInsn *, DefInfo *> &def_info_map,
			     DInsn *insn,
			     DRegister *output_reg);
};

}  // namespace opt

#endif //  _opt_ssa_h_
