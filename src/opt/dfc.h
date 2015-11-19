// -*- C++ -*-
#ifndef _opt_dfc_h_
#define _opt_dfc_h_

#include "nli.h"

#include <map>
#include <set>
#include <string>

using std::map;
using std::multimap;
using std::set;
using std::string;

namespace dfg {
class DGraph;
class DGraphAnnotation;
class DInsn;
class DRegister;
class DState;
}  // namespace dfg
using namespace dfg;

namespace opt {

class BasicBlock;
class BasicBlockSet;

class DefInfo {
 public:
  DRegister *output_reg;
  int output_index;
  DInsn *insn;
  DState *st;
  BasicBlock *bb;

  string ToString() const;
  static void SortDefInfo(vector<DefInfo *> *sorted);
};

class DataFlowCollector {
public:
  DataFlowCollector(DGraph *graph, BasicBlockSet *bbs,
		    dfg::DGraphAnnotation *an);
  ~DataFlowCollector();
  void Perform();
  void GetReachDefs(BasicBlock *bb, set<DefInfo *> *s);
  void GetAllDefs(set<DefInfo *> *s);

  struct BBInfo {
    map<DRegister *, DefInfo *> defs;
    set<DefInfo *> kills;
    set<DefInfo *> reaches;
    set<BBInfo *> pred;
  };
private:
  string DefInfoToString(const DefInfo &di) const;

  void CollectDefs(BasicBlock *bb, BBInfo *bbi);
  void CollectKills(BasicBlock *bb, BBInfo *bbi);
  void CollectReaches();
  // DEF(P) U {REACH(P) - KILL(P)}
  void CollectPropagates(BBInfo *bbi, set<DefInfo *> *prop);

  void AnnotateDefs();
  void AnnotateKillsAndReaches(bool is_reach);

  BasicBlockSet *bbs_;
  dfg::DGraphAnnotation *an_;
  map<BasicBlock *, BBInfo *> bb_info_;
  multimap<DRegister *, DefInfo *> all_defs_;
};

}  // namespace opt

#endif  // _opt_dfc_h_
