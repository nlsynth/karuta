#include "opt/constant_insn.h"

namespace opt {

bool ConstantInsnElimination::IsConstantInputInsn(DInsn *insn) {
  for (vector<DRegister *>::iterator it = insn->inputs_.begin();
       it != insn->inputs_.end(); it++) {
    if ((*it)->reg_type_ != DRegister::REG_CONST) {
      return false;
    }
  }
  return true;
}

DRegister *ConstantInsnElimination::CalcConstantInputResult(DGraph *g,
							    DInsn *insn) {
  sym_t op = insn->resource_->opr_->type_;
  uint64_t res = 0;
  int width = 32;
  if (op == sym_bit_sel) {
    // i_0[i_1:i_2]
    vector<DRegister *>::iterator it = insn->inputs_.begin();
    uint64_t v = (*it)->num_;
    ++it;
    int h = (*it)->num_;
    ++it;
    int l = (*it)->num_;
    for (int i = l; i <= h; ++i) {
      int pos = i - l;
      if ((v >> i) & 1) {
	res |= (1 << pos);
      }
    }
    width = h - l + 1;
  } else if (op == sym_add || op == sym_sub) {
    // add, sub
    int nth;
    vector<DRegister *>::iterator it;
    for (it = insn->inputs_.begin(), nth = 0;
	 it != insn->inputs_.end(); it++, nth ++) {
      DRegister *input_reg = *it;
      if (nth == 0) {
	res = input_reg->num_;
      } else {
	if (op == sym_add) {
	  res += input_reg->num_;
	} else if (op == sym_sub) {
	  res -= input_reg->num_;
	}
      }
      if (input_reg->data_type_->size_ > width) {
	width = input_reg->data_type_->size_;
      }
    }
    DRegister *output_reg = *(insn->outputs_.begin());
    width = output_reg->data_type_->size_;
  } else if (op == sym_bit_concat) {
    res = CalcBitConcat(insn, &width);
  } else if (insn->inputs_.size() == 2) {
    DRegister *lhs = *(insn->inputs_.begin());
    DRegister *rhs = *(insn->inputs_.rbegin());
    if (op == sym_gt) {
      bool b = lhs->num_ > rhs->num_;
      return DGraphUtil::FindEnum(g, "", DTypeUtil::GetBoolType(), b ? 1 : 0);
    } else if (op == sym_bit_xor) {
      if (lhs == rhs) {
	res = 0;
      } else {
	return NULL;
      }
    } else {
      return NULL;
    }
  } else {
    return NULL;
  }
  return DGraphUtil::FindWidthNum(g, res, width);
}

uint64_t ConstantInsnElimination::CalcBitConcat(DInsn *insn, int *width) {
  uint64_t res = 0;
  *width = 0;
  for (vector<DRegister *>::iterator it = insn->inputs_.begin();
       it != insn->inputs_.end(); ++it) {
    DRegister *reg = *it;
    DType *type = reg->data_type_;
    res <<= type->size_;
    *width += type->size_;
    uint64_t mask = ~(-1 << type->size_);
    res |= (mask & reg->num_);
  }
  return res;
}

DRegister *ConstantInsnElimination::CalcMaybeConstantResult(DGraph *g, DInsn *insn) {
  sym_t op = insn->resource_->opr_->type_;
  bool same_input = false;
  if (insn->inputs_.size() >= 2) {
    vector<DRegister *>::iterator it = insn->inputs_.begin();
    DRegister *r1 = *it;
    ++it;
    DRegister *r2 = *it;
    if (r1 == r2) {
      same_input = true;
    }
  }
  if (same_input) {
    if (op == sym_eq) {
      return DGraphUtil::FindEnum(g, NULL, DTypeUtil::GetBoolType(), 1);
    }
    if (op == sym_ne) {
      return DGraphUtil::FindEnum(g, NULL, DTypeUtil::GetBoolType(), 0);
    }
    if (op == sym_selector) {
      return *(insn->inputs_.begin());
    }
    if (op == sym_bit_xor) {
      DRegister *r1 = *(insn->inputs_.begin());
      return DGraphUtil::FindWidthNum(g, 0, r1->data_type_->size_);
    }
  }
  return NULL;
}

bool ConstantInsnElimination::ModifyConstantInsn(DGraph *graph,
						 DState *st, DInsn *insn) {
  DRegister *reg = NULL;
  if (IsConstantInputInsn(insn)) {
    reg = CalcConstantInputResult(graph, insn);
  } else {
    reg = CalcMaybeConstantResult(graph, insn);
  }
  if (!reg) {
    return false;
  }
  // find assign
  DResource *res = DGraphUtil::FindResource(graph, sym_assign, true);
  // make assign insn
  DInsn *new_insn = DGraphUtil::InsnNew(graph, res);
  new_insn->inputs_.push_back(reg);
  new_insn->outputs_.push_back(*insn->outputs_.begin());
  st->insns_.push_back(new_insn);
  return true;
}

bool ConstantInsnElimination::Perform(const char *phase, DGraph *graph,
				      const char *note) {
  for (list<DState *>::iterator it = graph->states_.begin();
       it != graph->states_.end(); it++) {
    DState *st = *it;
    list<DInsn *> copied_insns = st->insns_;
    for (list<DInsn *>::iterator jt = copied_insns.begin();
	 jt != copied_insns.end(); jt++) {
      if (ModifyConstantInsn(graph, st, *jt)) {
	DStateUtil::EraseInsn(st, *jt);
      }
    }
  }
  return true;
}

///Optimizer: Constant instruction elmination
static void register_constant_insn() {
  OptimizationPhase::registerPhase("opt_constant_insn_elimination",
				   &ConstantInsnElimination::Create, NULL);
}

STATIC_INITIALIZER(constant_insn, register_constant_insn());

}  // namespace opt
