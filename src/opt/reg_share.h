// -*- C++ -*-
#ifndef _opt_reg_share_h_
#define _opt_reg_share_h_

#include "nli.h"

#include <list>
#include <set>
#include <map>

using std::set;
using std::map;
using std::list;

namespace dfg {
class DGraph;
class DGraphAnnotation;
class DRegister;
class DState;
}  // namespace dfg
using namespace dfg;

namespace opt {

class StateAnnotation;

class ConflictInfo {
public:
  void Dump(dfg::DGraphAnnotation *a);
  // construction
  void AddConflictPair(DRegister *r1, DRegister *r2);
  // accessor
  void CollectConflict(DRegister *reg, set<DRegister *> *regs);
private:
  void AddConflict(DRegister *r1, DRegister *r2);
  // conflict pairs
  map<DRegister *, set<DRegister *> > conflict_pairs_;
};

class LiveRegisterCollector {
public:
  LiveRegisterCollector(DGraph *graph);
  void Perform(map<DState *, set<DRegister *> > *live_regs, dfg::DGraphAnnotation *an);
private:
  void FindReadWrittenRegisters();
  void FindLiveRegisterPath(set<StateAnnotation *> &initials,
			    DRegister *reg);
  void TraverseLiveRegisterPath(StateAnnotation *cur,
				DRegister *reg,
				list<StateAnnotation *> *path,
				set<StateAnnotation *> *visited,
				set<StateAnnotation *> *live);
  void CommitLiveRegisterPath(DRegister *reg,
			      list<StateAnnotation *> *path,
			      set<StateAnnotation *> *live);
  DGraph *graph_;
  map<DState *, set<DRegister *> > live_regs_;
  map<DRegister *, set<StateAnnotation *> > write_points_;
};

class RegisterConflictCollector {
public:
  RegisterConflictCollector(DGraph *graph);
  void Perform(ConflictInfo *cinfo, dfg::DGraphAnnotation *an);
private:
  // "conflict" means 2 registers are live in a same state.
  void CollectRegisterConflict(ConflictInfo *cinfo,
			       dfg::DGraphAnnotation *an);

  DGraph *graph_;
  map<DState *, set<DRegister *> > live_regs_;
};

class RegisterShare {
public:
  static void Perform(DGraph *graph);
private:
  static void MergeRegisters(ConflictInfo &cinfo, DGraph *graph,
			     dfg::DGraphAnnotation *an);
  // map from merge source to target.
  static void GetShareMap(ConflictInfo &cinfo,
			  const set<DRegister *> &regs,
			  map<DRegister *, DRegister *> *merged,
			  dfg::DGraphAnnotation *an);
  static void ReplaceRegs(map<DRegister *, DRegister *> &merged,
			  DGraph *graph);
  static void ReplaceRegList(map<DRegister *, DRegister *> &merged,
			     vector<DRegister *> *regs);
};

}  // namespace opt

#endif  // _opt_reg_share_h_
