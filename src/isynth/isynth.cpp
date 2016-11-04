#include "isynth/isynth.h"

#include "iroha/i_design.h"
#include "iroha/iroha.h"
#include "isynth/channel_synth.h"
#include "isynth/object_synth.h"

using namespace iroha;

namespace isynth {

bool ISynth::Synthesize(vm::VM *vm, vm::Object *obj, const string &ofn) {
  std::unique_ptr<IDesign> design(new IDesign());

  // Libraries of neon light assumes positive reset.
  iroha::ResourceParams *params = design->GetParams();
  params->SetResetPolarity(true);

  const string &prefix = Env::GetModulePrefix();
  if (!prefix.empty()) {
    params->SetModuleNamePrefix(prefix + "_");
  }

  ChannelSynth channel;

  vector<string> no_task;
  ObjectSynth o(vm, obj, "main", no_task, design.get(), &channel);
  if (!o.Synth()) {
    return false;
  }

  channel.Resolve(design.get());

  DesignTool::Validate(design.get());

  iroha::OptAPI *optimizer = iroha::Iroha::CreateOptimizer(design.get());
  optimizer->ApplyPhase("clean_pseudo_resource");

  WriterAPI *writer = Iroha::CreateWriter(design.get());
  writer->SetLanguage("");
  writer->Write(ofn);
  return true;
}

}  // namespace isynth
