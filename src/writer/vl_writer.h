// -*- C++ -*-
#ifndef _vlwriter_h_included_
#define _vlwriter_h_included_

#include "writer.h"

namespace dfg {
class DModule;
}  // namespace dfg

namespace writer {

class VLWriter : public Writer {
public:
  VLWriter(DModule *mod, ostream &os);
  void Output();

  static bool WriteModule(DModule *mod, const char *fn);

private:
  void OutputSubModules(DModule *mod, const string &path_name,
			vector<string> *files, ostream &os);
};

}  // namespace writer

#endif
