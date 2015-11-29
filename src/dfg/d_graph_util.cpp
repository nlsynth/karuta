#include "dfg/d_graph_util.h"

static list<DOperator *> operators;
vector<DType *> DTypeUtil::all_types;

static void ice(const char *msg) {
  std::cout << "ICE:dfg:" << msg << "\n";  
  abort();
}

namespace dfg {

DRegister *DGraphUtil::FindNum(DGraph *g, uint64_t num) {
  return FindWidthNum(g, num, 0);
}

DRegister *DGraphUtil::FindWidthNum(DGraph *g, uint64_t num, int width) {
  uint64_t mask = 0xffffffffffffffff;
  mask >>= (64 - width);
  num &= mask;
  for (list<DRegister *>::iterator it = g->registers_.begin();
       it != g->registers_.end(); it++) {
    DRegister *reg = *it;
    if (reg->reg_type_ == DRegister::REG_CONST &&
	reg->num_ == num &&
	(width == 0 ||
	 reg->data_type_->size_ == width)) {
      return reg;
    }
  }
  DType *type;
  if (width) {
    type = DTypeUtil::FindDType(DType::INT, width);
  } else {
    type = DTypeUtil::FindDType(DType::INT, 32);
  }
  DRegister *reg = AllocRegister(g, DRegister::REG_CONST, type);
  reg->num_ = num;
  g->registers_.push_back(reg);
  return reg;
}

DInsn *DGraphUtil::InsnNew(DGraph *g, DResource *r) {
  if (!r) {
    ice("insn_new without resource");
  }
  DInsn *insn = new DInsn(r, g->last_insn_id_);
  g->pool_->insns_.Add(insn);
  g->last_insn_id_++;
  return insn;
}

DRegister *DGraphUtil::CloneInitialValue(DGraph *g, DRegister *reg) {
  if (reg->data_type_->type_ == DType::INT) {
    return DGraphUtil::FindNum(g, reg->num_);
  }
  return DGraphUtil::FindEnum(g, NULL, reg->data_type_, reg->num_);
}

DRegister *DGraphUtil::FindSym(DGraph *g, const string &name, DType *type) {
  list<DRegister *>::iterator it;
  for (it = g->registers_.begin(); it != g->registers_.end(); it++) {
    DRegister *reg = *it;
    if (reg->reg_type_ == DRegister::REG_NORMAL &&
	reg->reg_name_ == name) {
      return reg;
    }
  }
  DRegister *reg = AllocRegister(g, DRegister::REG_NORMAL, type);
  reg->reg_name_ = name;
  g->registers_.push_back(reg);
  return reg;
}

DRegister *DGraphUtil::FindEnum(DGraph *g, const string &name, DType *type, int num) {
  for (DRegister *reg : g->registers_) {
    if (reg->reg_type_ == DRegister::REG_CONST &&
	(name.empty() ||
	 reg->reg_name_ == name) &&
	reg->data_type_ == type &&
	(int)reg->num_ == num) {
      return reg;
    }
  }
  DRegister *reg = AllocRegister(g, DRegister::REG_CONST, type);
  reg->reg_name_ = name;
  reg->num_ = num;
  g->registers_.push_back(reg);
  return reg;
}

DRegister *DGraphUtil::AllocTmpReg(DGraph *g, DType *type) {
  return AllocTempOrWireRegister(g, type, DRegister::REG_NORMAL, "reg_t%d");
}

DRegister *DGraphUtil::AllocWireReg(DGraph *g, DType *type) {
  return AllocTempOrWireRegister(g, type, DRegister::REG_WIRE, "wire_t%d");
}

DRegister *DGraphUtil::AllocTempOrWireRegister(DGraph *graph, DType *data_type,
					       enum DRegister::RegType reg_type,
					       const char *tmpl) {
  graph->last_tmp_reg_id_++;
  DRegister *reg = AllocRegister(graph, reg_type, data_type);
  //
  char buf[20];
  sprintf(buf, tmpl, graph->last_tmp_reg_id_);
  reg->reg_name_ = string(buf);
  graph->registers_.push_back(reg);
  return reg;
}

DResource *DGraphUtil::AllocResource(DGraph *g, sym_t op_name) {
  DOperator *opr = DOperatorUtil::FindOperator(op_name);
  if (!opr) {
    abort();
  }
  DResource *res = new DResource(opr);
  g->pool_->resources_.Add(res);
  ++g->last_resource_id_;
  g->resources_.push_back(res);
  ++res->resource_id_ = g->last_resource_id_;
  return res;
}

DResource *DGraphUtil::CopyResource(DGraph *g, DResource *src) {
  DResource *res = AllocResource(g, src->opr_->type_);
  res->input_types_ = src->input_types_;
  res->output_types_ = src->output_types_;
  return res;
}

DResource *DGraphUtil::FindResource(DGraph *g, sym_t sym, bool cr) {
  // find from already generated resource
  for (DResource *res : g->resources_) {
    if (res->opr_->type_ == sym) {
      return res;
    }
  }
  if (cr) {
    return DGraphUtil::AllocResource(g, sym);
  }
  return NULL;
}

void DGraphUtil::FindResourceAll(DGraph *g, sym_t sym, vector<DResource *> *res) {
  for (DResource *r : g->resources_) {
    if (r->opr_->type_ == sym) {
      res->push_back(r);
    }
  }
}

DRegister *DGraphUtil::GetNthOutput(DInsn *insn, int nth) {
  int n = 0;
  for (vector<DRegister *>::iterator it = insn->outputs_.begin();
       it != insn->outputs_.end(); ++it, ++n) {
    if (n == nth) {
      return *it;
    }
  }
  return NULL;
}

bool DGraphUtil::IsCompatibleResource(DResource *src, DResource *res) {
  if (src->input_types_.size() != res->input_types_.size() ||
      src->output_types_.size() != res->output_types_.size()) {
    return false;
  }
  for (size_t i = 0; i < src->input_types_.size(); ++i) {
    if (!DTypeUtil::IsCompatibleType(src->input_types_[i],
				     res->input_types_[i])) {
      return false;
    }
  }
  for (size_t i = 0; i < src->output_types_.size(); ++i) {
    if (!DTypeUtil::IsCompatibleType(src->output_types_[i],
				     res->output_types_[i])) {
      return false;
    }
  }
  return true;
}

DState *DGraphUtil::AllocState(DGraph *g) {
  DState *state = new DState(g->last_state_id_);
  g->pool_->states_.Add(state);
  ++g->last_state_id_;
  g->states_.push_back(state);
  return state;
}

DState *DGraphUtil::AllocStateNext(DGraph *g, DState *s) {
  list<DState*>::iterator it;
  for (it = g->states_.begin(); it != g->states_.end(); it++) {
    if ((*it) == s) {
      break;
    }
  }
  if (it == g->states_.end()) {
    return NULL;
  }
  //TODO(yusuke): unify this code with AllocState(g)
  DState *state = new DState(g->last_state_id_);
  g->pool_->states_.Add(state);
  ++g->last_state_id_;
  //
  it++;
  g->states_.insert(it, state);
  return state;
}

void DGraphUtil::KillIntermediateResource(DGraph *graph) {
  DResource *entry = FindResource(graph, sym_lookup("function_entry"), true);
  DResource *funcall = FindResource(graph, sym_lookup("funcall"), true);
  DResource *transition = FindResource(graph, sym_lookup("transition"), true);
  //
  set<DState *> reachable;
  DStateUtil::CollectReachable(graph, graph->initial_state_, &reachable);
  for (DState *st : reachable) {
    DStateUtil::EraseInsnByResource(st, entry);
    DStateUtil::EraseInsnByResource(st, funcall);
    DStateUtil::EraseInsnByResource(st, transition);
  }
}

DGraph *DGraphUtil::Create(DModule *mod) {
  DGraph *graph = new DGraph(mod);
  graph->initial_state_ = DGraphUtil::AllocState(graph);
  return graph;
}

DRegister *DGraphUtil::AllocRegister(DGraph *g, enum DRegister::RegType reg_type, DType *val_type) {
  DRegister *reg = new DRegister(reg_type, val_type);
  g->pool_->registers_.Add(reg);
  return reg;
}

void DGraphUtil::ClearAnnotation(DGraph *g) {
  // States
  for (list<DState *>::iterator it = g->states_.begin();
       it != g->states_.end(); it++) {
    if ((*it)->annotation_) {
      delete (*it)->annotation_;
      (*it)->annotation_ = NULL;
    }
  }
  // Resources
  for (list<DResource *>::iterator jt = g->resources_.begin();
       jt != g->resources_.end(); jt++) {
    if ((*jt)->annotation_) {
      delete (*jt)->annotation_;
      (*jt)->annotation_ = NULL;
    }
  }
}

DInsn *DStateUtil::FindInsnByResource(DState *s, const DResource *r) {
  int nr = DStateUtil::GetNrInsnsByResource(s, r);
  if (nr == 0) {
    return NULL;
  }
  if (nr > 1) {
    ice("multiple insn for a resource\n");
  }

  return DStateUtil::FindNthInsnByResource(s, r, 0);
}

DType *DTypeUtil::FindDType(enum DType::TypeClass type, int width) {
  for (DType *dt : all_types) {
    if (dt->type_ == type &&
	dt->size_ == width) {
      return dt;
    }
  }
  DType *t = new DType(type, width);
  all_types.push_back(t);
  return t;
}

void DTypeUtil::ReleaseTypes() {
  STLDeleteValues(&all_types);
  for(list<DOperator *>::iterator it = operators.begin();
      it != operators.end(); ++it) {
    delete *it;
  }
}

bool DTypeUtil::IsCompatibleType(DType *src, DType *type) {
  if (type->type_ != src->type_) {
    return false;
  }
  if (type->type_ == DType::ENUM) {
    if (type->size_ == src->size_) {
      return true;
    } else {
      return false;
    }
  }
  // TYPE_INT.
  if (src->size_ <= type->size_) {
    return true;
  }
  return false;
}

DType *DTypeUtil::GetIntType(int width) {
  return FindDType(DType::INT, width);
}

DType *DTypeUtil::GetBoolType() {
  static DType *bool_type = nullptr;
  if (bool_type == nullptr) {
    bool_type = DTypeUtil::FindDType(DType::ENUM, 2);
  }
  return bool_type;
}

int DTypeUtil::GetWidth(DType *type) {
  if (type->type_ == DType::ENUM) {
    CHECK(type->size_ == 2);
    // Scalar value.
    return 0;
  }
  return type->size_;
}

DOperator *DOperatorUtil::FindOperator(sym_t opr) {
  std::list<DOperator *>::iterator it;
  for (it = operators.begin(); it != operators.end(); it++) {
    if ((*it)->type_ == opr) {
      return *it;
    }
  }
  std::cout << sym_cstr(opr) << " (failed to find operator)\n";
  ice("fatal");
  return NULL;
}

// add frontend dependent pseudo operator
DOperator *DOperatorUtil::InstallOperator(sym_t name, bool is_exclusive) {
  DOperator *opr = new DOperator(name);
  opr->is_exclusive_ = is_exclusive;
  operators.push_back(opr);
  return opr;
}

DOperator *DOperatorUtil::InstallOperatorWithSideEffect(sym_t name) {
  DOperator *opr = InstallOperator(name, true);
  opr->has_side_effect_ = true;
  return opr;
}

int DStateUtil::GetNrInsnsByResource(DState *s, const DResource *r) {
  int nr = 0;
  std::list<DInsn *>::iterator it;
  for (it = s->insns_.begin(); it != s->insns_.end(); it++) {
    if ((*it)->resource_ == r) {
      nr ++;
    }
  }
  return nr;
}

DInsn *DStateUtil::FindNthInsnByResource(DState *s, const DResource *r,
					 int nth) {
  int n = 0;
  std::list<DInsn *>::iterator it;
  for (it = s->insns_.begin(); it != s->insns_.end(); it++) {
    if ((*it)->resource_ == r) {
      if (nth == n) {
	return *it;
      }
      n ++;
    }
  }
  return NULL;
}

void DStateUtil::EraseInsn(DState *ds, DInsn *insn) {
  std::list<DInsn *>::iterator it;
  for (it = ds->insns_.begin(); it != ds->insns_.end(); it++) {
    if ((*it) == insn) {
      ds->insns_.erase(it);
      return ;
    }
  }
}

void DStateUtil::EraseInsnByResource(DState *ds, DResource *r) {
  for (list<DInsn *>::iterator it = ds->insns_.begin();
       it != ds->insns_.end(); it++) {
    if ((*it)->resource_ == r) {
      ds->insns_.erase(it);
      return ;
    }
  }
}

void DStateUtil::MoveInsn(DInsn *insn, DState *src, DState *dst) {
  dst->insns_.push_back(insn);
  DStateUtil::EraseInsn(src, insn);
}

DState *DStateUtil::GetNextState(DGraph *graph, DState *st) {
  DResource *br = DGraphUtil::FindResource(graph, sym_branch, true);
  DInsn *insn = DStateUtil::FindInsnByResource(st, br);
  if (insn && insn->targets_.size() == 1) {
    return *(insn->targets_.begin());
  }
  return NULL;
}

void DStateUtil::SetNextState(DGraph *graph, DState *st, DState *to) {
  DResource *br =
    DGraphUtil::FindResource(graph, sym_branch, true);
  DInsn *insn = DStateUtil::FindInsnByResource(st, br);
  if (!insn) {
    insn = DGraphUtil::InsnNew(graph, br);
    st->insns_.push_back(insn);
  } else {
    insn->targets_.erase(insn->targets_.begin(),
			 insn->targets_.end());
  }
  insn->targets_.push_back(to);
}

void DStateUtil::CollectTargets(DGraph *graph, bool reverse,
				map<DState *, set<DState *> > *targets) {
  DResource *br = DGraphUtil::FindResource(graph, sym_branch, true);
  for (list<DState *>::iterator it = graph->states_.begin();
       it != graph->states_.end(); it++) {
    DState *st = *it;
    DInsn *insn = DStateUtil::FindInsnByResource(st, br);
    if (!insn) {
      continue;
    }
    for (vector<DState *>::iterator jt = insn->targets_.begin();
	 jt != insn->targets_.end(); jt++) {
      if (reverse) {
	(*targets)[*jt].insert(st);
      } else {
	(*targets)[st].insert(*jt);
      }
    }
  }
}

void DStateUtil::CollectReachable(DGraph *g,
				  DState *initial,
				  std::set<DState *> *reachable) {
  map<DState *, set<DState *> > targets;
  CollectTargets(g, false /* reverse */, &targets);
  reachable->erase(reachable->begin(),
		   reachable->end());
  set<DState *> frontier;
  frontier.insert(initial);

  while (frontier.size()) {
    DState *ds = *(frontier.begin());
    frontier.erase(ds);
    reachable->insert(ds);

    set<DState *> &next = targets[ds];
    for (set<DState *>::iterator it = next.begin();
	 it != next.end(); ++it) {
      if (reachable->find(*it) == reachable->end()) {
	frontier.insert(*it);
      }
    }
  }
}

STATIC_FINALIZER(dtype_util, DTypeUtil::ReleaseTypes());
}  // namespace dfg
