// -*- C++ -*-
#ifndef _writer_writer_util_h_
#define _writer_writer_util_h_

#include "writer/writer.h"

namespace dfg {
class DArray;
class DGraph;
class DInsn;
class DRegister;
}  // namespace dfg
using namespace dfg;

namespace writer {

class WriterUtil {
public:
  struct BitSelOperands {
    DRegister *src_reg;
    int src_msb_pos;
    int src_lsb_pos;
    int selected_width;
  };
  static void DecodeBitSelInsn(const DInsn *insn,
			       BitSelOperands *opr);
  static string ArrayDescription(const string &name, const DArray *array);
  static DInsn *FindTaskEntryInsn(DGraph *graph);
  static DInsn *FindTaskFinishInsn(DGraph *graph);
};

}  // namespace writer

#endif  // _writer_writer_util_h_
