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

bool DInsnUtil::IsMultiCycle(const DInsn *insn) {
  sym_t type = insn->resource_->opr_->type_;
  return (type == sym_sub_module_call || type == sym_write_channel ||
	  type == sym_read_channel);
}

}  // namespace dfg
