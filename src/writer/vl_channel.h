// -*- C++ -*-
#ifndef _writer_vl_channel_h_
#define _writer_vl_channel_h_

#include "nli.h"

#include <set>

using std::set;

namespace dfg {
class DModule;
}  // namespace dfg
using namespace dfg;

namespace writer {

class VLChannelWriter {
public:
  VLChannelWriter(const string &prefix);
  // Module for each width can be output up to once.
  // Each module may be instantiated multiple times.
  void MaybeOutputModuleCode(int width, ostream &os);

  string ModuleName(int width);

  void OutputChannelInstances(DModule *mod, ostream &os);
  static void OutputChannelWires(DModule *mod, ostream &os);
  static void MaybeOutputChannelConnections(DModule *mod, DModule *sub_mod,
					    ostream &os);

  set<int> bits;
  const string &prefix_;
};

}  // namespace writer

#endif  // _writer_vl_channel_h_
