// -*- C++ -*-
#ifndef _writer_vl_writer_h_
#define _writer_vl_writer_h_

#include "writer.h"

namespace dfg {
class DModule;
}  // namespace dfg

namespace writer {

class VLWriter : public Writer {
public:
  VLWriter(DModule *mod, ostream &os);
  void Output();

  static bool WriteModule(DModule *mod, const string &fn);

  static void ICE(const char *msg, const sym_t sym = NULL);

private:
  void OutputSubModules(DModule *mod, const string &path_name,
			vector<string> *files, ostream &os);
};

}  // namespace writer

#endif  // _writer_vl_writer_h_
