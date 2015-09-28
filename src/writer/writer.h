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

protected:
  string OutputSignature();
  DModule *mod_;
  ostream &os_;

private:
  const string lang_;
};

}  // namespace writer

#endif  // _writer_writer_h_
