#include "isynth/channel_synth.h"

#include "iroha/iroha.h"
#include "vm/channel.h"

namespace isynth {

void ChannelSynth::AddChannel(vm::Object *ch_obj, IResource *res) {
  pair<IResource *, IResource *> rw = channels_[ch_obj];
  if (resource::IsChannelRead(*res->GetClass())) {
    CHECK(rw.first == nullptr);
    rw.first = res;
  } else {
    CHECK(rw.second == nullptr);
    rw.second = res;
  }
  channels_[ch_obj] = rw;
}

void ChannelSynth::Resolve(IDesign *design) {
  for (auto c : channels_) {
    auto &p = c.second;
    IChannel *ic = new IChannel(design);
    design->channels_.push_back(ic);
    if (p.first != nullptr) {
      ic->SetReader(p.first);
    }
    if (p.second != nullptr) {
      ic->SetWriter(p.second);
    }
    iroha::ResourceParams *params = ic->GetParams();
    vector<string> v(1);
    vm::Object *obj = c.first;
    string name = vm::Channel::ChannelName(obj);
    v[0] = "channel_" + name + "_data";
    params->SetValues(resource::kChannelDataPort, v);
    v[0] = "channel_" + name + "_en";
    params->SetValues(resource::kChannelEnPort, v);
    v[0] = "channel_" + name + "_ack";
    params->SetValues(resource::kChannelAckPort, v);
  }
}

}  // namespace isynth
