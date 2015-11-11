// -*- C++ -*-
#ifndef _writer_cc_writer_h_
#define _writer_cc_writer_h_

#include "writer/writer.h"

namespace dfg {
class DModule;
}  // namespace dfg
using namespace dfg;

namespace writer {

class CCWriter : public Writer {
public:
  CCWriter(DModule *mod, ostream &os);
  void Output();
  
  static bool WriteModule(DModule *mod, const string &fn);

  static void ICE(const char *msg, const sym_t sym = NULL);

private:
  void OutputModule(const string &cur_path, DModule *mod);
  void OutputMain();
};

}  // namespace writer

#endif  // _writer_cc_writer_h_
