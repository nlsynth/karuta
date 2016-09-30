// -*- C++ -*-
#ifndef _isynth_channel_synth_h_
#define _isynth_channel_synth_h_

#include "isynth/common.h"

#include <map>

using std::map;
using std::pair;

namespace isynth {

class ChannelSynth {
public:
  void AddChannel(vm::Object *ch_obj, IResource *res);
  void Resolve(IDesign *design);

private:
  // obj to pair of (reader, writer)
  map<vm::Object *, pair<IResource *, IResource *> > channels_;
};

}  // namespace isynth

#endif  // _isynth_channel_synth_h_
