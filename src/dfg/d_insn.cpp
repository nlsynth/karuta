#include "dfg/d_insn.h"

#include "dfg.h"

namespace dfg {

DInsn::DInsn(DResource *r, int id) {
  resource_ = r;
  insn_id_ = id;
  annotation_ = NULL;
}

DInsn::~DInsn() {
  if (annotation_) {
    delete annotation_;
  }
}

bool DInsnUtil::HasSideEffect(DInsn *insn) {
  return insn->resource_->opr_->has_side_effect_;
}

}  // namespace dfg
