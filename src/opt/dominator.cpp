// see standard textbook or wikipedia about this algorithm.
#include "opt/dominator.h"

#include "dfg/dfg.h"
#include "logging.h"
#include "opt/basic_block.h"

namespace opt {

DominatorTreeBuilder::DominatorTreeBuilder(DGraph *graph, BasicBlockSet *bbs,
					   dfg::DGraphAnnotation *an)
  : bbs_(bbs),
    an_(an) {
  for (set<BasicBlock *>::iterator it = bbs_->bbs_.begin();
       it != bbs_->bbs_.end(); ++it) {
    dom_info_[*it] = new DominatorInfo(*it);
  }
}

DominatorTreeBuilder::~DominatorTreeBuilder() {
  STLDeleteSecondElements(&dom_info_);
}

void DominatorTreeBuilder::Perform() {
  LOG(PHASE) << "Building dominator tree";
  CalculateDominator();
  CalculateFrontier();
  AnnotateDominatorTree(an_->SummaryAnnotation());
}

void DominatorTreeBuilder::Union(set<DominatorInfo *> &s1,
				 set<DominatorInfo *> &s2,
				 set<DominatorInfo *> *d) {
  for (set<DominatorInfo *>::iterator it = s1.begin(); it != s1.end(); ++it) {
    if (s2.find(*it) != s2.end()) {
      d->insert(*it);
    }
  }
}

void DominatorTreeBuilder::CalculateDominator() {
  for (map<BasicBlock *, DominatorInfo *>::iterator it = dom_info_.begin();
       it != dom_info_.end(); ++it) {
    DominatorInfo *di = it->second;
    BasicBlock *bb = it->first;
    // set initial dominators values.
    if (bb == bbs_->initial_) {
      di->dominators.insert(di);
    } else {
      for (map<BasicBlock *, DominatorInfo *>::iterator jt = dom_info_.begin();
	   jt != dom_info_.end(); ++jt) {
	di->dominators.insert(jt->second);
      }
    }
    // Get pred blocks' info.
    for (set<BasicBlock *>::iterator jt = di->bb->next_bb.begin();
	 jt != di->bb->next_bb.end(); ++jt) {
      DominatorInfo *next_di = dom_info_[*jt];
      next_di->pred.insert(di);
    }
  }
  bool changed;
  do {
    changed = false;
    for (map<BasicBlock *, DominatorInfo *>::iterator it = dom_info_.begin();
	 it != dom_info_.end(); ++it) {
      if (it->first == bbs_->initial_) {
	continue;
      }
      // U(all pred blocks) + itself.
      DominatorInfo *di = it->second;
      CHECK(di->pred.size() > 0);
      set<DominatorInfo *> cur = (*(di->pred.begin()))->dominators;
      for (set<DominatorInfo *>::iterator jt = di->pred.begin();
	   jt != di->pred.end(); ++jt) {
	set<DominatorInfo *> tmp;
	Union(cur, (*jt)->dominators, &tmp);
	cur = tmp;
      }
      cur.insert(di);
      // update
      if (cur != di->dominators) {
	changed = true;
	di->dominators = cur;
      }
    }
  } while (changed);
}

void DominatorTreeBuilder::GetFrontier(BasicBlock *bb,
				       vector<BasicBlock *> *s) {
  DominatorInfo *di = dom_info_[bb];
  GetSortedBBs(di->frontiers, s);
}

void DominatorTreeBuilder::CalculateFrontier() {
 for (map<BasicBlock *, DominatorInfo *>::iterator it = dom_info_.begin();
       it != dom_info_.end(); ++it) {
   DominatorInfo *cur_di = it->second;
   for (set<BasicBlock *>::iterator jt = cur_di->bb->next_bb.begin();
	jt != cur_di->bb->next_bb.end(); ++jt) {
     DominatorInfo *next_di = dom_info_[*jt];
     for (set<DominatorInfo *>::iterator kt = cur_di->dominators.begin();
	  kt != cur_di->dominators.end(); ++kt) {
       if (next_di->dominators.find(*kt) == next_di->dominators.end()) {
	 DominatorInfo *di = *kt;
	 di->frontiers.insert(next_di);
       }
     }
   }
 }
}

void DominatorTreeBuilder::AnnotateDominatorTree(ostream &os) {
  os << "Dominator tree<br>\n";
  for (map<BasicBlock *, DominatorInfo *>::iterator it = dom_info_.begin();
       it != dom_info_.end(); ++it) {
    BasicBlock *bb = it->first;
    DominatorInfo *di = it->second;
    os << "bb:" << bb->bb_id << " dominators";
    DumpBBs(di->dominators, os);
    if (di->frontiers.size()) {
      os << " frontiers";
      DumpBBs(di->frontiers, os);
    }
    os << "<br>\n";
  }
  os << "<br>\n";
  an_->Flush();
}

void DominatorTreeBuilder::DumpBBs(const set<DominatorInfo *> &di,
				   ostream& os) {
  vector<BasicBlock *> bbs;
  GetSortedBBs(di, &bbs);
  for (vector<BasicBlock *>::iterator it = bbs.begin();
       it != bbs.end(); ++it) {
    os << " " << (*it)->bb_id;
  }
}

void DominatorTreeBuilder::GetSortedBBs(const set<DominatorInfo *> &di,
					vector<BasicBlock *> *bbs) {
  set<BasicBlock *> bset;
  for (set<DominatorInfo *>::iterator it = di.begin();
       it != di.end(); ++it) {
    bset.insert((*it)->bb);
  }
  BasicBlockSet::SortBBs(bset, bbs);
}

}  // namespace opt
