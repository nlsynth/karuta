#include "isynth/channel_synth.h"

#include "iroha/iroha.h"

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
  }
}

}  // namespace isynth
