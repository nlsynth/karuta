// -*- C++ -*-
#ifndef _writer_writer_h_
#define _writer_writer_h_

#include <iostream>

#include "nli.h"

using std::ostream;

namespace dfg {
class DModule;
}  // namespace dfg
using namespace dfg;

namespace writer {

class Writer {
public:
  Writer(DModule *mod, ostream &os);

  static bool WriteModule(DModule *mod, const char *fn);

  static void CommonICE(const char *lang, const char *msg,
			const sym_t sym = NULL);

protected:
  string OutputSignature();
  DModule *mod_;
  ostream &os_;
};

}  // namespace writer

#endif  // _writer_writer_h_
