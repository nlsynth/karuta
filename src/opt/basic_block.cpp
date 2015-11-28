// basic block optimizer
#include "opt/basic_block.h"

#include "dfg/dfg.h"
#include "opt/opt.h"

#include <algorithm>

namespace {
struct LessBBP {
  bool operator()(opt::BasicBlock *l, opt::BasicBlock *r) const {
    return l->bb_id < r->bb_id;
  }
};
}

namespace opt {

BasicBlockSet::~BasicBlockSet() {
  STLDeleteValues(&bbs_);
}

void BasicBlockSet::GetSortedBBs(vector<BasicBlock *> *bbs) {
  SortBBs(bbs_, bbs);
}

void BasicBlockSet::SortBBs(const set<BasicBlock *> &input,
			    vector<BasicBlock *> *sorted) {
  sorted->clear();
  for (BasicBlock *bb : input) {
    sorted->push_back(bb);
  }
  std::sort(sorted->begin(), sorted->end(), LessBBP());
}

BasicBlockCollector::BasicBlockCollector(DGraph *graph, BasicBlockSet *bbs)
  : graph_(graph), bbs_(bbs) {
  next_bb_id_ = 0;
}

void BasicBlockCollector::CollectBBEntryStates() {
  set<DState *> reachable;
  DStateUtil::CollectReachable(graph_, graph_->initial_state_, &reachable);
  DResource *br = DGraphUtil::FindResource(graph_, sym_branch, true);
  // push entry point of basic blocks
  for (set<DState *>::iterator it = reachable.begin();
       it != reachable.end(); it++) {
    const StateAnnotation *da = StateAnnotation::Get(*it);
    if (da->nr_branch_ > 1) {
      DInsn *insn = DStateUtil::FindInsnByResource(*it, br);
      for (vector<DState *>::iterator jt = insn->targets_.begin();
           jt != insn->targets_.end(); jt++) {
        bb_entry_.insert(*jt);
      }
    }
    if (da->nr_join_ > 1) {
      bb_entry_.insert(*it);
    }
  }
  bb_entry_.insert(graph_->initial_state_);
}

void BasicBlockCollector::CollectBB(DState *bb_head, DState *bb_next) {
  BasicBlock *bb = new BasicBlock();
  bb->bb_id = next_bb_id_;
  next_bb_id_++;
  // adds initial state
  StateAnnotation *sa = StateAnnotation::Get(bb_head);
  sa->bb_ = bb;
  bb->states.push_back(bb_head);
  // appends successor state
  int idx = 0;
  DState *ds = bb_next;
  while (ds) {
    sa = StateAnnotation::Get(ds);
    // Initial state is technically a joining point from reset state.
    if (sa->nr_join_ > 1 || ds == graph_->initial_state_) {
      // new BB begins from here
      break;
    }
    sa->bb_ = bb;
    sa->nth_state_ = idx;
    idx ++;
    //
    bb->states.push_back(ds);
    //
    if (sa->nr_branch_ > 1) {
      // final state of this block
      break;
    }
    DState *next = DStateUtil::GetNextState(graph_, ds);
    if (!next || next == ds) {
      // loop
      break;
    }
    ds = next;
  }
  bbs_->bbs_.insert(bb);
}

void BasicBlockCollector::CollectBBAll(dfg::DGraphAnnotation *an) {
  CollectBBEntryStates();

  DResource *br = DGraphUtil::FindResource(graph_, sym_branch, true);
  for (set<DState *>::iterator it = bb_entry_.begin();
       it != bb_entry_.end(); it++) {
    DInsn *insn = DStateUtil::FindInsnByResource(*it, br);
    set<DState *> targets_seen;
    for (vector<DState *>::iterator jt = insn->targets_.begin();
	 jt != insn->targets_.end(); jt++) {
      DState *next = *jt;
      StateAnnotation *sa = StateAnnotation::Get(next);
      if (sa->nr_join_ > 1) {
	// next state have multiple incoming path, so not in this bb
	next = NULL;
      }
      if (bb_entry_.find(next) != bb_entry_.end()) {
	next = NULL;
      }
      if (targets_seen.find(next) != targets_seen.end()) {
	// there may dupes in targets.
	continue;
      }
      targets_seen.insert(next);
      CollectBB(*it, next);
    }
  }
  BuildBBStateMapping();
  CollectNextBB();
  CollectReachableBB();
  StateAnnotation *sa = StateAnnotation::Get(graph_->initial_state_);
  bbs_->initial_ = sa->bb_;
  if (an) {
    AnnotateBB(an);
  }
}

void BasicBlockCollector::BuildBBStateMapping() {
  for (set<BasicBlock *>::iterator it = bbs_->bbs_.begin();
       it != bbs_->bbs_.end(); ++it) {
    BasicBlock *bb = *it;
    for (int i = 0; i < (int)bb->states.size(); ++i) {
      DState *st = bb->states[i];
      bbs_->state_bb_mapping_[st] = bb;
    }
  }
}

void BasicBlockCollector::CollectNextBB() {
  for (set<BasicBlock *>::iterator it = bbs_->bbs_.begin();
       it != bbs_->bbs_.end(); ++it) {
    BasicBlock *bb = *it;
    for (int i = 0; i < (int)bb->states.size(); ++i) {
      DState *st = bb->states[i];
      StateAnnotation *sa = StateAnnotation::Get(st);
      for (list<StateAnnotation *>::iterator jt = sa->next_states_.begin();
	   jt != sa->next_states_.end(); ++jt) {
	StateAnnotation *next_sa = *jt;
	if (next_sa->bb_ == bb &&
	    next_sa->state_ != bb->states[0]) {
	  // if next state is in this block and is not initail state,
	  // this just goes to next state. ignore it.
	  continue;
	}
	bb->next_bb.insert(next_sa->bb_);
	next_sa->bb_->prev_bb.insert(bb);
      }
    }
  }
}

void BasicBlockCollector::CollectReachableBB() {
  for (set<BasicBlock *>::iterator it = bbs_->bbs_.begin();
       it != bbs_->bbs_.end(); ++it) {
    BasicBlock *bb = *it;
    set<BasicBlock *> frontier;
    ExpandNext(bb, &frontier);
    while (frontier.size()) {
      BasicBlock *bb_cur = *(frontier.begin());
      frontier.erase(bb_cur);
      if (bb->reachable_bb.find(bb_cur) != bb->reachable_bb.end()) {
	continue;
      }
      bb->reachable_bb.insert(bb_cur);
      ExpandNext(bb_cur, &frontier);
    }
  }
}

void BasicBlockCollector::ExpandNext(BasicBlock *bb_cur,
				     set<BasicBlock *> *frontier) {
  for (set<BasicBlock *>::iterator it = bb_cur->next_bb.begin();
       it != bb_cur->next_bb.end(); ++it) {
    frontier->insert(*it);
  }
}

  void BasicBlockCollector::AnnotateBB(dfg::DGraphAnnotation *an) {
  an->SummaryAnnotation() << "Basic blocks<br>\n* id -> next | reachable<br>\n";
  vector<BasicBlock *> sorted_bbs;
  bbs_->GetSortedBBs(&sorted_bbs);
  for (vector<BasicBlock *>::iterator it = sorted_bbs.begin();
       it != sorted_bbs.end(); ++it) {
    BasicBlock *bb = *it;
    vector<BasicBlock *> related_bbs;
    an->SummaryAnnotation() << bb->bb_id << "->";
    BasicBlockSet::SortBBs(bb->next_bb, &related_bbs);
    for (vector<BasicBlock *>::iterator jt = related_bbs.begin();
	 jt != related_bbs.end(); ++jt) {
      an->SummaryAnnotation() << " " << (*jt)->bb_id;
    }
    an->SummaryAnnotation() << "|";
    BasicBlockSet::SortBBs(bb->reachable_bb, &related_bbs);
    for (vector<BasicBlock *>::iterator jt = related_bbs.begin();
	 jt != related_bbs.end(); ++jt) {
      an->SummaryAnnotation() << " " << (*jt)->bb_id;
    }
    an->SummaryAnnotation() << "<br>\n";
    an->Flush();
    for (int i = 0; i < (int)bb->states.size(); ++i) {
      DState *st = bb->states[i];
      an->StateAnnotation(st) << ",bb_id=" << bb->bb_id << "(" << i << ")";
      an->Flush();
    }
  }
  an->SummaryAnnotation() << "<br>\n";
  an->Flush();
}

BasicBlockShrinker::BasicBlockShrinker(DGraph *graph) : graph_(graph) {
  num_moves_ = 0;
}

void BasicBlockShrinker::Perform(set<BasicBlock *> *bb,
				 dfg::DGraphAnnotation *an) {
  for (set<BasicBlock *>::iterator it = bb->begin();
       it != bb->end(); it++) {
    CramInsns(*it, an);
  }
  an->SummaryAnnotation() << num_moves_ << "moved\n";
  an->Flush();
}

void BasicBlockShrinker::CramInsns(BasicBlock *bb, dfg::DGraphAnnotation *an) {
  // for each state
  for (int i = 0; i < (int)bb->states.size(); ++i) {
    DState *st = bb->states[i];
    if (i > 0) {
      map<DInsn *, int> move_targets;
      FindTargets(st, i, &move_targets);
      for (map<DInsn *, int>::iterator it = move_targets.begin();
	   it != move_targets.end(); ++it) {
	DInsn *insn = it->first;
	int target = TryMove(bb, i, insn, it->second);
	if (target >= 0) {
	  UpdateRegAccessLocation(insn, bb->states[target], target); 
	  UpdateMemWriteLocation(insn, bb->states[target], target);
	}
      }
    }

    // update write location for each insn
    for (list<DInsn *>::iterator it = st->insns_.begin();
	 it != st->insns_.end(); it++) {
      DInsn *insn = *it;
      UpdateRegAccessLocation(insn, st, i);
      UpdateMemWriteLocation(insn, st, i);
    }
  }
}

void BasicBlockShrinker::FindTargets(DState *st, int idx, map<DInsn *, int> *move_targets) {
  DResource *br = DGraphUtil::FindResource(graph_, sym_branch, true);
  for (list<DInsn *>::iterator it = st->insns_.begin();
       it != st->insns_.end(); it++) {
    DInsn *insn = *it;
    if (insn->resource_ == br) {
      continue;
    }
    int min_target = 0;
    // memory write location
    if (insn->resource_->opr_->type_ == sym_memory) {
      map<DResource *, access_location>::iterator jt = written_mems_.find(insn->resource_);
      if (jt != written_mems_.end()) {
	access_location &loc = jt->second;
	int target = loc.index + 1;
	if (min_target < target) {
	  min_target = target;
	}
      }
    }
    // Register write position
    min_target = UpdateMinTarget(min_target, /* is_write */ false, &insn->inputs_);
    min_target = UpdateMinTarget(min_target, /* is_write */ true, &insn->outputs_);
    if (min_target < idx) {
      (*move_targets)[insn] = min_target;
    }
  }
}

void BasicBlockShrinker::UpdateRegAccessLocation(DInsn *insn, DState *st, int pos) {
  for (vector<DRegister *>::iterator it = insn->outputs_.begin();
       it != insn->outputs_.end(); ++it) {
    // Just overwrite. No reordering will happen for write.
    access_location &loc = written_regs_[*it];
    loc.index = pos;
    loc.state = st;
  }
  for (vector<DRegister *>::iterator it = insn->inputs_.begin();
       it != insn->inputs_.end(); ++it) {
    access_location &loc = read_regs_[*it];
    if (loc.index < pos) {
      loc.index = pos;
      loc.state = st;
    }
  }
}

void BasicBlockShrinker::UpdateMemWriteLocation(DInsn *insn, DState *st, int pos) {
  if (insn->resource_->opr_->type_ == sym_memory && insn->outputs_.size() == 0) {
    // memory write
    written_mems_[insn->resource_].index = pos;
    written_mems_[insn->resource_].state = st;
  }
}

int BasicBlockShrinker::UpdateMinTarget(int min_target,
					bool is_write,
					vector<DRegister *> *regs) {
  for (vector<DRegister *>::iterator it = regs->begin();
       it != regs->end(); ++it) {
    map<DRegister *, access_location>::iterator jt =
      written_regs_.find(*it);
    if (jt != written_regs_.end()) {
      // + 1, currently this don't use insn wire.
      if (min_target < jt->second.index + 1) {
	min_target = jt->second.index + 1;
      }
    }
    if (is_write) {
      jt = read_regs_.find(*it);
      if (jt != read_regs_.end()) {
	if (min_target < jt->second.index + 1) {
	  min_target = jt->second.index + 1;
	}
      }
    }
  }
  return min_target;
}

int BasicBlockShrinker::TryMove(BasicBlock *bb, int current_index,
				DInsn *insn, int target_index) {
  DResource *res = insn->resource_;
  int index;
  for (index = target_index; index < current_index; ++index) {
    DState *target_state = bb->states[index];
    if (res->opr_->is_exclusive_) {
      if (DStateUtil::FindInsnByResource(target_state, res)) {
	// this resource was used by other insn.
	continue;
      }
    }
    // don't move to where read channel exists.
    bool has_read_channel = false;
    for (list<DInsn *>::iterator it = target_state->insns_.begin(); it != target_state->insns_.end(); it++) {
      if ((*it)->resource_->opr_->type_ == sym_read_channel) {
	has_read_channel = true;
      }
    }
    if (has_read_channel) {
      continue;
    }
    if (target_state->insns_.size() > 0 && insn->resource_->opr_->type_ == sym_read_channel) {
      continue;
    }
    // ok let's move
    DState *current_state = bb->states[current_index];
    DStateUtil::MoveInsn(insn, current_state, target_state);
    ++num_moves_;
    return index;
  }
  return -1;
}

}  // namespace opt

