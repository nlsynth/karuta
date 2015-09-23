// -*- C++ -*-
#ifndef _opt_dominator_h_
#define _opt_dominator_h_

#include "nli.h"

#include <map>
#include <set>
#include <vector>

using std::map;
using std::set;
using std::vector;

namespace dfg {
class DGraph;
class DGraphAnnotation;
}  // namespace dfg
using namespace dfg;

namespace opt {

class BasicBlock;
class BasicBlockSet;

class DominatorTreeBuilder {
public:
  DominatorTreeBuilder(DGraph *graph, BasicBlockSet *bbs,
		       dfg::DGraphAnnotation *an);
  ~DominatorTreeBuilder();
  void Perform();
  void GetFrontier(BasicBlock *bb, vector<BasicBlock *> *s);
  void AnnotateDominatorTree(ostream& os);
private:
  struct DominatorInfo {
    DominatorInfo(BasicBlock *b) {
      bb = b;
    };
    BasicBlock *bb;
    // dominator should be passed or debug printed in bb_id order.
    set<DominatorInfo *> dominators;
    set<DominatorInfo *> frontiers;
    set<DominatorInfo *> pred;
  };
  void CalculateDominator();
  void CalculateFrontier();

  void GetSortedBBs(const set<DominatorInfo *> &di,
		    vector<BasicBlock *> *bbs);

  void DumpBBs(const set<DominatorInfo *> &di, ostream& os);

  void Union(set<DominatorInfo *> &s1,
	     set<DominatorInfo *> &s2,
	     set<DominatorInfo *> *d);

  BasicBlockSet *bbs_;
  dfg::DGraphAnnotation *an_;

  map<BasicBlock *, DominatorInfo *> dom_info_;
};

}  // namespace opt

#endif //  _opt_dominator_h_
