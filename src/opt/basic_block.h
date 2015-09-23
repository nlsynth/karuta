// -*- C++ -*-
#ifndef _opt_basic_block_h_
#define _opt_basic_block_h_

#include <list>
#include <set>
#include <map>

#include "nli.h"

namespace dfg {
class DGraph;
class DGraphAnnotation;
class DInsn;
class DRegister;
class DResource;
class DState;
}  // namespace dfg
using namespace dfg;

using std::set;
using std::list;
using std::map;

namespace opt {

class BasicBlock {
public:
  int bb_id;
  vector<DState *> states;
  set<BasicBlock *> next_bb;
  set<BasicBlock *> prev_bb;
  set<BasicBlock *> reachable_bb;
};

class BasicBlockSet {
public:
  set<BasicBlock *> bbs_;
  BasicBlock *initial_;
  map<DState *, BasicBlock *> state_bb_mapping_;

  ~BasicBlockSet();
  void GetSortedBBs(vector<BasicBlock *> *bbs);
  static void SortBBs(const set<BasicBlock *> &input,
		      vector<BasicBlock *> *sorted);
};

class BasicBlockCollector {
public:
  BasicBlockCollector(DGraph *graph, BasicBlockSet *bbs);
  void CollectBBAll(dfg::DGraphAnnotation *an);
private:
  void CollectNextBB();
  void CollectReachableBB();
  void ExpandNext(BasicBlock *bb, set<BasicBlock *> *frontier);
  void CollectBBEntryStates();
  void CollectBB(DState *bb_head, DState *bb_next);
  void BuildBBStateMapping();
  void AnnotateBB(dfg::DGraphAnnotation *an);
  set<DState *> bb_entry_;
  int next_bb_id_;
  DGraph *graph_;
  BasicBlockSet *bbs_;
};

class BasicBlockShrinker {
public:
  BasicBlockShrinker(DGraph *graph);
  void Perform(set<BasicBlock *> *bb, dfg::DGraphAnnotation *an);
  void CramInsns(BasicBlock *bb,
		 dfg::DGraphAnnotation *an);
  int TryMove(BasicBlock *bb, int current_index,
	      DInsn *insn, int target_index);
private:
  void UpdateRegAccessLocation(DInsn *insn, DState *st, int pos);
  void UpdateMemWriteLocation(DInsn *insn, DState *st, int pos);
  int UpdateMinTarget(int min_target, bool is_write, vector<DRegister *> *regs);
  void FindTargets(DState *st, int idx, map<DInsn *, int> *move_targets);

  DGraph *graph_;
  int num_moves_;
  // map from register to last written state
  struct access_location {
    DState *state;
    int index;
  };
  map<DRegister *, access_location> written_regs_;
  map<DRegister *, access_location> read_regs_;
  map<DResource *, access_location> written_mems_;
};

}  // namespace opt

#endif // _opt_basic_block_h_
