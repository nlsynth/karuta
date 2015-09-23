#include "synth/channel_synth.h"

#include "dfg/dfg.h"

#include <set>

using std::set;

namespace synth {

void ChannelSynth::ResolveChannels(DModule *mod) {
  ChannelSynth synth;
  synth.ExtractChannels(mod);
  synth.ConnectChannels();
}

void ChannelSynth::ConnectChannels() {
  for (auto &p : channels_) {
    Channel &c = p.second;
    if (c.reader_channel != NULL && c.writer_channel != NULL) {
      ConnectInternal(c);
    } else {
      ConnectExternal(c);
    }
  }
}

void ChannelSynth::ConnectInternal(Channel &c) {
  // find the common parent.
  set<DModule *> reader_parents_set;
  for (DModule *p = c.reader_channel->reader_->parent_mod_; p != NULL; p = p->parent_mod_) {
    reader_parents_set.insert(p);
  }
  DModule *common_parent = NULL;
  for (DModule *p = c.writer_channel->writer_->parent_mod_; p != NULL; p = p->parent_mod_) {
    if (reader_parents_set.find(p) != reader_parents_set.end()) {
      common_parent = p;
      break;
    }
  }
  CHECK(common_parent);
  DChannel *dchan = DModuleUtil::CreateChannel(common_parent);
  dchan->name_ = c.reader_channel->name_;
  dchan->writer_ = c.writer_channel->writer_;
  dchan->reader_ = c.reader_channel->reader_;
  // Supports just 1 level between the root.
}

void ChannelSynth::ConnectExternal(Channel &c) {
  string name;
  DModule *p;
  if (c.reader_channel == NULL) {
    name = c.writer_channel->name_;
    p = c.writer_channel->writer_->parent_mod_;
  } else {
    name = c.reader_channel->name_;
    p = c.reader_channel->reader_->parent_mod_;
  }
  for (; p != NULL; p = p->parent_mod_) {
    DChannel *dchan = DModuleUtil::CreateChannel(p);
    dchan->name_ = name;
    if (c.reader_channel != NULL) {
      dchan->reader_ = c.reader_channel->reader_;
    } else {
      dchan->writer_ = c.writer_channel->writer_;
    }
  }
}

void ChannelSynth::ExtractChannels(DModule *mod) {
  if (mod->graph_) {
    vector<string> r_channels;
    vector<string> w_channels;
    GetChannels(mod->graph_, &r_channels, &w_channels);
    for (size_t i = 0; i < w_channels.size(); ++i) {
      DChannel *chan = DModuleUtil::CreateChannel(mod);
      chan->writer_ = mod;
      chan->name_ = w_channels[i];
      CHECK(channels_[chan->name_].writer_channel == NULL);
      channels_[chan->name_].writer_channel = chan;
    }
    for (size_t i = 0; i < r_channels.size(); ++i) {
      DChannel *chan = DModuleUtil::CreateChannel(mod);
      chan->reader_ = mod;
      chan->name_ = r_channels[i];
      CHECK(channels_[chan->name_].reader_channel == NULL);
      channels_[chan->name_].reader_channel = chan;
    }
  }
  for (size_t i = 0; i < mod->sub_modules_.size(); ++i) {
    ExtractChannels(mod->sub_modules_[i]);
  }
}

void ChannelSynth::GetChannels(DGraph *graph, vector<string> *r_channels, vector<string> *w_channels) {
  for (DResource *res : graph->resources_) {
    if (res->opr_->type_ == sym_read_channel) {
      r_channels->push_back(res->name_);
    }
    if (res->opr_->type_ == sym_write_channel) {
      w_channels->push_back(res->name_);
    }
  }
}

}  // namespace synth
