// -*- C++ -*-
#ifndef _dfg_util_h_included_
#define _dfg_util_h_included_

#include "dfg/dfg.h"

namespace dfg {

// Be careful not to modify the list during traversal.
// If you want to modify insn list, you may do it from state_cb.
template <class T>
class DGraphWalker {
public:
  DGraphWalker(T *obj,
	       void (T::*state_cb)(DGraph *graph, DState *state),
	       void (T::*insn_cb)(DGraph *graph, DState *state, DInsn *insn),
	       void (T::*reg_cb)(DGraph *graph, DState *state, DInsn *insn, DRegister *reg, bool is_input))
    : obj_(obj), state_cb_(state_cb), insn_cb_(insn_cb), reg_cb_(reg_cb) {
  }
  void Traverse(DGraph *graph);
private:
  T *obj_;
  void (T::*state_cb_)(DGraph *graph, DState *state);
  void (T::*insn_cb_)(DGraph *graph, DState *state, DInsn *insn);
  void (T::*reg_cb_)(DGraph *graph, DState *state, DInsn *insn, DRegister *reg, bool is_input);
};

template<class T>
void DGraphWalker<T>::Traverse(DGraph *graph) {
  for (auto *ds : graph->states_) {
    if (state_cb_) {
      (obj_->*state_cb_)(graph, ds);
    }
    for (auto *insn : ds->insns_) {
      if (insn_cb_) {
	(obj_->*insn_cb_)(graph, ds, insn);
      }
      if (reg_cb_) {
	for (auto *input_reg : insn->inputs_) {
	  (obj_->*reg_cb_)(graph, ds, insn, input_reg, true);
	}
	for (auto *output_reg : insn->outputs_) {
	  (obj_->*reg_cb_)(graph, ds, insn, output_reg, false);
	}
      }
    }
  }
}

}  // namespace dfg

#endif // _dfg_util_h_included_
