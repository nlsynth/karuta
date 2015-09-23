#include "opt/reg_share.h"

#include "opt/opt.h"
#include "opt/opt_context.h"
#include "opt/opt_phase.h"
#include "dfg/dfg.h"

namespace opt {

void ConflictInfo::Dump(dfg::DGraphAnnotation *a) {
  a->SummaryAnnotation() << conflict_pairs_.size() << "conflict pairs\n";
  a->Flush();
  for (map<DRegister *, set<DRegister *> >::iterator it =
	 conflict_pairs_.begin(); it != conflict_pairs_.end(); ++it) {
    ostream &os =  a->RegisterAnnotation(it->first);
    os << "conflict";
    const set<DRegister *> &s = it->second;
    for (set<DRegister *>::const_iterator jt = s.begin();
	 jt != s.end(); ++jt) {
      os << "," << dfg::DFG::RegisterName(*jt);
    }
    a->Flush();
  }
}

void ConflictInfo::AddConflictPair(DRegister *r1, DRegister *r2) {
  AddConflict(r1, r2);
  AddConflict(r2, r1);
}

void ConflictInfo::CollectConflict(DRegister *reg,
				   set<DRegister *> *reg_set) {
  map<DRegister *, set<DRegister *> >::iterator it =
    conflict_pairs_.find(reg);
  if (it == conflict_pairs_.end()) {
    return;
  }
  set<DRegister *> &regs = it->second;
  for (set<DRegister *>::iterator jt = regs.begin();
       jt != regs.end(); ++jt) {
    reg_set->insert(*jt);
  }
}

void ConflictInfo::AddConflict(DRegister *r1, DRegister *r2) {
  if (conflict_pairs_.find(r1) == conflict_pairs_.end()) {
    set<DRegister *> empty_set;
    conflict_pairs_[r1] = empty_set;
  }
  conflict_pairs_[r1].insert(r2);
}

LiveRegisterCollector::LiveRegisterCollector(DGraph *graph) : graph_(graph) {
}

void LiveRegisterCollector::Perform(map<DState *, set<DRegister *> > *live_regs, dfg::DGraphAnnotation *an) {
  FindReadWrittenRegisters();
  set<DState *> reachable;
  DStateUtil::CollectReachable(graph_, graph_->initial_state_, &reachable);
  // for each written registers, seeks path to all the read points.
  // TODO(yusuke): is this slow? can I make this per block?
  for (map<DRegister *, set<StateAnnotation *> >::iterator it = write_points_.begin();
       it != write_points_.end(); ++it) {
    set<StateAnnotation *> &s = it->second;
    FindLiveRegisterPath(s, it->first);
    for (set<StateAnnotation *>::iterator jt = s.begin(); jt != s.end(); ++jt) {
      ostream &os = an->StateAnnotation((*jt)->state_);
      // written regs.
      os << "(" << dfg::DFG::RegisterName(it->first) << ")";
      an->Flush();
    }
  }
  *live_regs = live_regs_;
}

void LiveRegisterCollector::FindReadWrittenRegisters() {
  set<DState *> reachable;
  DStateUtil::CollectReachable(graph_, graph_->initial_state_, &reachable);
  for (set<DState *>::iterator it = reachable.begin();
       it != reachable.end(); ++it) {
    DState *ds = *it;
    StateAnnotation *sa = StateAnnotation::Get(ds);
    for (list<DInsn *>::iterator jt = ds->insns_.begin();
	 jt != ds->insns_.end(); ++jt) {
      DInsn *insn = *jt;
      // written
      for (vector<DRegister *>::iterator kt = insn->outputs_.begin();
	   kt != insn->outputs_.end(); ++kt) {
	DRegister *reg = *kt;
	if (reg->reg_type_ == DRegister::REG_NORMAL) {
	  sa->written_regs_.insert(reg);
	  write_points_[reg].insert(sa);
	}
      }
      // read
      for (vector<DRegister *>::iterator kt = insn->inputs_.begin();
	   kt != insn->inputs_.end(); kt++) {
	DRegister *reg = *kt;
	if (reg->reg_type_ == DRegister::REG_NORMAL) {
	  sa->read_regs_.insert(reg);
	}
      }
    }
  }
}

void LiveRegisterCollector::FindLiveRegisterPath(set<StateAnnotation *> &initials,
						 DRegister *reg) {
  set<StateAnnotation *> live;
  set<StateAnnotation *> roots = initials;
  while (true) {
    size_t num_live = live.size();
    for (set<StateAnnotation *>::iterator it = roots.begin(); it != roots.end(); ++it) {
      StateAnnotation *initial_sa = *it;
      list<StateAnnotation *> path;
      set<StateAnnotation *> visited;
      path.push_back(initial_sa);
      visited.insert(initial_sa);
      TraverseLiveRegisterPath(initial_sa, reg, &path, &visited, &live);
    }
    if (num_live == live.size()) {
      return;
    }

    roots.clear();

    for (set<StateAnnotation *>::iterator it = live.begin(); it != live.end(); ++it) {
      StateAnnotation *sa = *it;
      if (sa->next_states_.size() < 2) {
	continue;
      }
      for (list<StateAnnotation *>::iterator jt = sa->next_states_.begin();
	   jt != sa->next_states_.end(); ++jt) {
	StateAnnotation *next = *jt;
	if (live.find(next) == live.end()) {
	  LOG(INFO) << dfg::DFG::RegisterName(reg) << " "
		    << next->state_->state_id_;
	  roots.insert(next);
	}
      }
    }
    if (roots.size() == 0) {
      return;
    }
  }
}

void LiveRegisterCollector::TraverseLiveRegisterPath(StateAnnotation *cur,
						     DRegister *reg,
						     list<StateAnnotation *> *path,
						     set<StateAnnotation *> *visited,
						     set<StateAnnotation *> *live) {
  if (path->size() == 1 ||
      cur->read_regs_.find(reg) != cur->read_regs_.end()) {
    // NOTE(yusuke): if only path->size() == 1 exists, it means no one
    // reads this register. it might be removed here.
    CommitLiveRegisterPath(reg, path, live);
  }
  visited->insert(cur);
  for (list<StateAnnotation *>::iterator it = cur->next_states_.begin();
       it != cur->next_states_.end(); ++it) {
    StateAnnotation *next = *it;
    if (visited->find(next) != visited->end()) {
      continue;
    }
    if (next->written_regs_.find(reg) != next->written_regs_.end()) {
      continue;
    }
    path->push_back(next);
    TraverseLiveRegisterPath(next, reg, path, visited, live);
    path->pop_back();
  }
  visited->erase(cur);
}

void LiveRegisterCollector::CommitLiveRegisterPath(DRegister *reg,
						   list<StateAnnotation *> *path,
						   set<StateAnnotation *> *live) {
  for (list<StateAnnotation *>::iterator it = path->begin();
       it != path->end(); ++it) {
    StateAnnotation *sa = *it;
    set<DRegister *> &regs = live_regs_[sa->state_];
    regs.insert(reg);
    live->insert(sa);
  }
}

RegisterConflictCollector::RegisterConflictCollector(DGraph *graph)
  : graph_(graph) {
}

void RegisterConflictCollector::Perform(ConflictInfo *cinfo,
					dfg::DGraphAnnotation *an) {
  LiveRegisterCollector lrc(graph_);
  lrc.Perform(&live_regs_, an);
  CollectRegisterConflict(cinfo, an);
}

void RegisterConflictCollector::CollectRegisterConflict(ConflictInfo *cinfo,
							dfg::DGraphAnnotation *an) {
  set<DState *> reachable;
  DStateUtil::CollectReachable(graph_, graph_->initial_state_, &reachable);
  for (set<DState *>::iterator it = reachable.begin();
       it != reachable.end(); ++it) {
    map<DState *, set<DRegister *> >::iterator jt = live_regs_.find(*it);
    if (jt == live_regs_.end()) {
      continue;
    }
    // iterate all pairs of live registers in this state.
    ostream &os = an->StateAnnotation(jt->first);
    set<DRegister *> &regs = jt->second;
    for (set<DRegister *>::iterator kt = regs.begin();
	 kt != regs.end(); ++kt) {
      for (set<DRegister *>::iterator lt = regs.begin();
	   lt != regs.end(); ++lt) {
	if (*kt == *lt) {
	  continue;
	}
	cinfo->AddConflictPair(*kt, *lt);
      }
      // live registers.
      os << "," << dfg::DFG::RegisterName(*kt);
    }
    an->Flush();
  }
}

void RegisterShare::Perform(DGraph *graph) {
  GraphOptimizeStat::SetupStateAnnotation(graph);
  ConflictInfo cinfo;
  dfg::DGraphAnnotation conflict_collect_info;
  RegisterConflictCollector rcc(graph);
  rcc.Perform(&cinfo, &conflict_collect_info);
  OptimizeContext *ctx = graph->owner_module_->GetOptimizeContext();
  ctx->DumpIntermediateGraph(graph, &conflict_collect_info,
			     "conflict_analysis");
  dfg::DGraphAnnotation conflict_info;
  cinfo.Dump(&conflict_info);
  ctx->DumpIntermediateGraph(graph, &conflict_info, "reg_conflict");
  dfg::DGraphAnnotation register_share_info;
  RegisterShare::MergeRegisters(cinfo, graph, &register_share_info);
  ctx->DumpIntermediateGraph(graph, &register_share_info,
			     "reg_share");
}

void RegisterShare::MergeRegisters(ConflictInfo &cinfo, DGraph *graph,
				   dfg::DGraphAnnotation *an) {
  set<DRegister *> regs;
  for (DRegister *reg : graph->registers_) {
    if (reg->reg_type_ == DRegister::REG_NORMAL) {
      regs.insert(reg);
    }
  }
  map<DRegister *, DRegister *> merged;
  GetShareMap(cinfo, regs, &merged, an);
  ReplaceRegs(merged, graph);
}

void RegisterShare::GetShareMap(ConflictInfo &cinfo,
				const set<DRegister *> &regs_src,
				map<DRegister *, DRegister *> *merged,
				dfg::DGraphAnnotation *an) {
  int num_merged = 0;
  set<DRegister *> regs = regs_src;
  // stupid/greedy merge
  while (regs.size() > 0) {
    // pick up one register.
    DRegister *reg = *(regs.begin());
    regs.erase(reg);
    set<DRegister *> conflict_regs;
    cinfo.CollectConflict(reg, &conflict_regs);
    // checks it against rest of all.
    set<DRegister *> mergable;
    for (set<DRegister *>::iterator it = regs.begin(); it != regs.end();
	 ++it) {
      if (conflict_regs.find(*it) == conflict_regs.end() &&
	  reg->data_type_->size_ == (*it)->data_type_->size_ &&
	  reg->data_type_->type_ == (*it)->data_type_->type_ &&
	  reg->has_initial_ == (*it)->has_initial_) {
	mergable.insert(*it);
	ostream &os = an->RegisterAnnotation(reg);
	os << ",merged " << dfg::DFG::RegisterName(*it);
	an->Flush();
	cinfo.CollectConflict(*it, &conflict_regs);
	DRegister *tmp = *it;
	++it;
	regs.erase(tmp);
	if (it == regs.end()) {
	  break;
	}
      }
    }
    for (set<DRegister *>::iterator it = mergable.begin();
	 it != mergable.end(); ++it) {
      (*merged)[*it] = reg;
      ++num_merged;
    }
  }
  an->SummaryAnnotation() << num_merged << " registers were merged\n";
  an->Flush();
}

void RegisterShare::ReplaceRegs(map<DRegister *, DRegister *> &merged,
				DGraph *graph) {
  for (list<DState *>::iterator it = graph->states_.begin();
       it != graph->states_.end(); it++) {
    DState *s = *it;
    for (list<DInsn *>::iterator jt = s->insns_.begin();
	 jt != s->insns_.end(); jt++) {
      DInsn *insn = *jt;
      ReplaceRegList(merged, &insn->inputs_);
      ReplaceRegList(merged, &insn->outputs_);
    }
  }
}

void RegisterShare::ReplaceRegList(map<DRegister *, DRegister *> &merged,
				   vector<DRegister *> *regs) {
  for (vector<DRegister *>::iterator it = regs->begin();
       it != regs->end(); ++it) {
    DRegister *target = merged[*it];
    if (!target) {
      continue;
    }
    *it = target;
  }
}

class OptRegShare : public OptimizationPhase {
public:
  virtual bool Perform(const char *phase, DGraph *graph, const char *note);
  static OptimizationPhase *Create(const char *phase) {
    return new OptRegShare;
  }
};

bool OptRegShare::Perform(const char *phase, DGraph *graph, const char *note) {
  RegisterShare::Perform(graph);
  return true;
}

static void register_reg_share() {
  OptimizationPhase::registerPhase("opt_register_share", &OptRegShare::Create, NULL);
}

STATIC_INITIALIZER(opt_reg_share, register_reg_share());

}  // namespace opt
