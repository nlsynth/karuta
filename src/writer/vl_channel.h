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
  void MaybeOutput(int width, ostream &os);
  static string ModuleName(int width);

  static void OutputChannelWires(DModule *mod, ostream &os);
  static void OutputChannelInstances(DModule *mod, ostream &os);
  static void MayOutputChannelConnections(DModule *mod, DModule *sub_mod, ostream &os);

  set<int> bits;
};

}  // namespace writer

#endif  // _writer_vl_channel_h_
