// -*- C++ -*-
#ifndef _synth_channel_synth_h_
#define _synth_channel_synth_h_

#include "nli.h"

#include <map>

using std::map;

namespace dfg {
class DChannel;
class DGraph;
class DModule;
}  // namespace dfg
using namespace dfg;

namespace synth {

class ChannelSynth {
public:
  static void ResolveChannels(DModule *mod);

private:
  struct Channel {
    Channel() : reader_channel(NULL), writer_channel(NULL) {}
    DChannel *reader_channel;
    DChannel *writer_channel;
  };
  map<string, Channel> channels_;

  void ConnectChannels();
  void ConnectInternal(Channel &c);
  void ConnectExternal(Channel &c);
  void ExtractChannels(DModule *mod);
  void GetChannels(DGraph *graph, vector<string> *read_channels, vector<string> *write_channels);
};

}  // namespace synth

#endif  // _synth_channel_synth_h_
