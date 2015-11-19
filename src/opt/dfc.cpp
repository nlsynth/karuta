// Copyright (C) Yusuke Tabata 2012
#include "opt/dfc.h"

#include "dfg/dfg.h"
#include "nli.h"
#include "opt/basic_block.h"

#include <algorithm>

namespace {
struct LessDefInfoP {
  bool operator()(opt::DefInfo *l, opt::DefInfo *r) const {
    if (l->insn->insn_id_ == r->insn->insn_id_) {
      return l->output_index < r->output_index;
    }
    return l->insn->insn_id_ < r->insn->insn_id_;
  }
};
}  // namespace

namespace opt {

string DefInfo::ToString() const {
  ostringstream s;
  s << "-&gt " << dfg::DFG::RegisterName(output_reg)
    << " (insn" << insn->insn_id_
    << " st" << st->state_id_
    << " bb" << bb->bb_id << ")";
  return s.str();
}

void DefInfo::SortDefInfo(vector<DefInfo *> *vec) {
  std::sort(vec->begin(), vec->end(), LessDefInfoP());
}

DataFlowCollector::DataFlowCollector(DGraph *g,
				     BasicBlockSet *bbs,
				     dfg::DGraphAnnotation *an) : bbs_(bbs),
								  an_(an) {
}

DataFlowCollector::~DataFlowCollector() {
  STLDeleteSecondElements(&bb_info_);
  STLDeleteSecondElements(&all_defs_);
}

void DataFlowCollector::Perform() {
  for (BasicBlock *bb : bbs_->bbs_) {
    bb_info_[bb] = new BBInfo;
  }
  // update bbi.pred
  for (BasicBlock *bb : bbs_->bbs_) {
    for (BasicBlock *next_bb : bb->next_bb) {
      BBInfo *pred_bbi = bb_info_[bb];
      bb_info_[next_bb]->pred.insert(pred_bbi);
    }
  }
  for (BasicBlock *bb : bbs_->bbs_) {
    CollectDefs(bb, bb_info_[bb]);
  }
  if (an_) {
    an_->SummaryAnnotation() << "Data flow analysys<br>\n";
  }
  AnnotateDefs();
  for (BasicBlock *bb : bbs_->bbs_) {
    CollectKills(bb, bb_info_[bb]);
  }
  AnnotateKillsAndReaches(false);
  CollectReaches();
  AnnotateKillsAndReaches(true);
  if (an_) {
    an_->SummaryAnnotation() << "<br>\n";
  }
}

void DataFlowCollector::GetReachDefs(BasicBlock *bb, set<DefInfo *> *s) {
  BBInfo *bbi = bb_info_[bb];
  for (DefInfo *di : bbi->reaches) {
    s->insert(di);
  }
}

void DataFlowCollector::GetAllDefs(set<DefInfo *> *s) {
  for (multimap<DRegister *, DefInfo *>::iterator it = all_defs_.begin();
       it != all_defs_.end(); ++it) {
    s->insert(it->second);
  }
}

void DataFlowCollector::CollectReaches() {
  bool changed;
  do {
    changed = false;
    for (BasicBlock *bb : bbs_->bbs_) {
      BBInfo *bbi = bb_info_[bb];
      set<DefInfo *> temp;
      for (BBInfo *pred_bbi : bbi->pred) {
	CollectPropagates(pred_bbi, &temp);
      }
      if (temp.size() > bbi->reaches.size()) {
	changed = true;
	bbi->reaches = temp;
      }
    }
  } while (changed);
}

void DataFlowCollector::CollectPropagates(BBInfo *bbi, set<DefInfo *> *prop) {
  // DEF(P)
  for (map<DRegister *, DefInfo *>::iterator it = bbi->defs.begin();
       it != bbi->defs.end(); ++it) {
    prop->insert(it->second);
  }
  // REACH(P) - KILL(P)
  set<DefInfo *> di;
  for (DefInfo *reach : bbi->reaches) {
    di.insert(reach);
  }
  for (DefInfo *kills : bbi->kills) {
    di.erase(kills);
  }
  for (DefInfo *r : di) {
    prop->insert(r);
  }
}

void DataFlowCollector::AnnotateDefs() {
  if (!an_) {
    return;
  }
  ostream &os = an_->SummaryAnnotation();
  os << "Defs<br>\n";
  vector<BasicBlock *> sorted_bbs;
  bbs_->GetSortedBBs(&sorted_bbs);
  for (BasicBlock *bb : sorted_bbs) {
    BBInfo *bbi = bb_info_[bb];
    os << "bb" << bb->bb_id << "<br>";
    vector<DefInfo *> di;
    for (map<DRegister *, DefInfo *>::iterator jt = bbi->defs.begin();
	 jt != bbi->defs.end(); ++jt) {
      di.push_back(jt->second);
    }
    DefInfo::SortDefInfo(&di);
    for (DefInfo *d : di) {
      os << DefInfoToString(*d) << "<br>";
    }
    os << "\n";
  }
  os << "\n";
  an_->Flush();
}

void DataFlowCollector::AnnotateKillsAndReaches(bool is_reach) {
  if (!an_) {
    return;
  }
  ostream &os = an_->SummaryAnnotation();
  if (is_reach) {
    os << "Reaches<br>";
  } else {
    os << "Kills<br>";
  }
  for (set<BasicBlock *>::iterator it = bbs_->bbs_.begin();
       it != bbs_->bbs_.end(); ++it) {
    BBInfo *bbi = bb_info_[*it];
    os << "bb" << (*it)->bb_id << "<br>";
    set<DefInfo *> &di_set = is_reach ? bbi->reaches : bbi->kills;
    for (set<DefInfo *>::iterator jt = di_set.begin();
	 jt != di_set.end(); ++jt) {
      os << DefInfoToString(*(*jt)) << "<br>";
    }
  }
  an_->Flush();
}

string DataFlowCollector::DefInfoToString(const DefInfo &di) const {
  return di.ToString();
}

void DataFlowCollector::CollectDefs(BasicBlock *bb, BBInfo *info) {
  map<DRegister *, DefInfo *> last_write;
  for (int i = 0; i < (int)bb->states.size(); ++i) {
    DState *st = bb->states[i];
    for (DInsn *insn : st->insns_) {
      int nth_output = 0;
      for (vector<DRegister *>::iterator it = insn->outputs_.begin();
	   it != insn->outputs_.end(); ++it, ++nth_output) {
	DRegister *reg = *it;
	if (reg->reg_type_ != DRegister::REG_NORMAL) {
	  continue;
	}
	DefInfo *dinfo = new DefInfo;
	dinfo->output_reg = reg;
	dinfo->output_index = nth_output;
	dinfo->insn = insn;
	dinfo->st = st;
	dinfo->bb = bb;
	last_write[reg] = dinfo;
	all_defs_.insert(std::make_pair(reg, dinfo));
      }
    }
  }
  info->defs = last_write;
}

void DataFlowCollector::CollectKills(BasicBlock *bb, BBInfo *bb_info) {
  for (multimap<DRegister *, DefInfo *>::iterator it = all_defs_.begin();
       it != all_defs_.end(); ++it) {
    DefInfo *dinfo = it->second;
    if (dinfo->bb == bb) {
      continue;
    }
    if (bb_info->defs.find(dinfo->output_reg) == bb_info->defs.end()) {
      continue;
    }
    bb_info->kills.insert(dinfo);
  }
}

}  // namespace opt
