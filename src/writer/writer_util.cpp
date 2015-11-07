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

DInsn *WriterUtil::FindTaskEntryInsn(DGraph *graph) {
  DResource *task_entry =
    DGraphUtil::FindResource(graph, sym_task_entry, false);
  return DStateUtil::FindInsnByResource(graph->initial_state_, task_entry);
}

DInsn *WriterUtil::FindTaskFinishInsn(DGraph *graph) {
  DResource *task_finish =
    DGraphUtil::FindResource(graph, sym_task_finish, false);
  return DStateUtil::FindInsnByResource(graph->last_state_, task_finish);
}

}  // namespace writer
