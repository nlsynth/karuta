#include "writer/writer_util.h"

#include "dfg/dfg.h"

namespace writer {

void WriterUtil::DecodeBitSelInsn(const DInsn *insn,
				  BitSelOperands *opr) {
  vector<DRegister *>::const_iterator it = insn->inputs_.begin();
  opr->src_reg = *it;
  it++;
  opr->src_msb_pos = (*it)->num_;
  it++;
  opr->src_lsb_pos = (*it)->num_;
  opr->selected_width = opr->src_msb_pos - opr->src_lsb_pos + 1;
}

string WriterUtil::ArrayDescription(const string &name,
				    const DArray *array) {
  string ram_or_rom = "rom";
  if (array->may_write_) {
    ram_or_rom = "ram";
  }
  ostringstream os;
  os << name << " length="
     << array->num_.size() << " (" << ram_or_rom << ")";
  return string(os.str());
}

bool WriterUtil::IsMultiCycleInsn(const DInsn *insn) {
  sym_t type = insn->resource_->opr_->type_;
  return (type == sym_sub_module_call || type == sym_write_channel ||
	  type == sym_read_channel);
}

DInsn *WriterUtil::FindTaskEntryInsn(DGraph *graph) {
  DResource *task_entry =
    DGraphUtil::FindResource(graph, sym_task_entry, false);
  return DStateUtil::FindInsnByResource(graph->initial_state_, task_entry);
}

}  // namespace writer
