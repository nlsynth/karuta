#include "synth/design_synth.h"

#include "iroha/i_design.h"
#include "iroha/iroha.h"
#include "synth/channel_synth.h"
#include "synth/object_synth.h"

namespace synth {

DesignSynth::DesignSynth(vm::VM *vm, vm::Object *obj) : vm_(vm), obj_(obj) {
  channel_synth_.reset(new ChannelSynth);
  i_design_.reset(new IDesign);
}

DesignSynth::~DesignSynth() {
}

bool DesignSynth::Synth() {
  // Libraries of neon light assumes positive reset.
  iroha::ResourceParams *params = i_design_->GetParams();
  params->SetResetPolarity(true);

  const string &prefix = Env::GetModulePrefix();
  if (!prefix.empty()) {
    params->SetModuleNamePrefix(prefix + "_");
  }

  ObjectSynth o(obj_, this);
  o.SetName("main");
  if (!o.Synth()) {
    return false;
  }

  channel_synth_->Resolve(i_design_.get());

  DesignTool::Validate(i_design_.get());

  iroha::OptAPI *optimizer = iroha::Iroha::CreateOptimizer(i_design_.get());
  optimizer->ApplyPhase("clean_pseudo_resource");
  return true;
}

vm::VM *DesignSynth::GetVM() {
  return vm_;
}

ChannelSynth *DesignSynth::GetChannelSynth() {
  return channel_synth_.get();
}

IDesign *DesignSynth::GetIDesign() {
  return i_design_.get();
}

}  // namespace synth
