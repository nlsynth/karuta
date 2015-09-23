// -*- C++ -*-
#ifndef _writer_writer_h_
#define _writer_writer_h_

#include <iostream>
#include "nli.h"

using std::ostream;

namespace dfg {
class DArray;
class DInsn;
class DModule;
class DRegister;
}  // namespace dfg
using namespace dfg;

namespace writer {

class Writer {
public:
  Writer(const string &name, DModule *mod, ostream &os);
  static bool WriteModule(DModule *mod, const char *fn);

  void ICE(const char *msg, const sym_t sym = NULL);

  struct BitSelOperands {
    DRegister *src_reg;
    int src_msb_pos;
    int src_lsb_pos;
    int selected_width;
  };
  static void DecodeBitSelInsn(const DInsn *insn,
			       BitSelOperands *opr);
  static string ArrayDescription(const string &name, const DArray *array);

protected:
  string OutputSignature();
  DModule *mod_;
  ostream &os_;

private:
  const string lang_;
};

}  // namespace writer

#endif  // _writer_writer_h_
