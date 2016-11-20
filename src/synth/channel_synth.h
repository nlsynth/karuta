// -*- C++ -*-
#ifndef _synth_channel_synth_h_
#define _synth_channel_synth_h_

#include "synth/common.h"

#include <map>

using std::map;
using std::pair;

namespace synth {

class ChannelSynth {
public:
  void AddChannel(vm::Object *ch_obj, IResource *res);
  void Resolve(IDesign *design);

private:
  // obj to pair of (reader, writer)
  map<vm::Object *, pair<IResource *, IResource *> > channels_;
};

}  // namespace synth

#endif  // _synth_channel_synth_h_
