// -*- C++ -*-
#ifndef _synth_channel_synth_h_
#define _synth_channel_synth_h_

#include "nli.h"

#include <map>

using std::map;
using std::pair;

namespace dfg {
class DChannel;
class DGraph;
class DModule;
}  // namespace dfg
using namespace dfg;

namespace synth {

class ChannelSynth {
public:
  static void ResolveChannels(DModule *root_mod);

private:
  struct ChannelInfo {
    ChannelInfo() : reader_channel(NULL), writer_channel(NULL) {
      data_width = 32;
    }
    DChannel *reader_channel;
    DChannel *writer_channel;
    int data_width;
  };
  map<string, ChannelInfo> channel_infos_;

  void ConnectChannels();
  // Channel connected between 2 DModules.
  // DChannels are allocated for reader, writer and common parent DModule.
  void ConnectInternal(ChannelInfo &c);
  // Channel connected to outside.
  // DChannels are allocated for all DModules above the reader/writer.
  void ConnectExternal(ChannelInfo &c);

  void ExtractChannels(DModule *mod);
  void GetChannels(DGraph *graph,
		   vector<pair<string, int> > *read_channels,
		   vector<pair<string, int> > *write_channels);
};

}  // namespace synth

#endif  // _synth_channel_synth_h_
