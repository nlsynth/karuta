#include "isynth/isynth.h"

#include "iroha/i_design.h"
#include "iroha/iroha.h"
#include "isynth/object_synth.h"

// WIP: this has copying from synth/ and huge amount of duplication.

using namespace iroha;

namespace isynth {

bool ISynth::Synthesize(vm::VM *vm, vm::Object *obj, const string &ofn) {
  std::unique_ptr<IDesign> design(new IDesign());

  ObjectSynth o(vm, obj, "main", design.get());
  if (!o.Synth()) {
    return false;
  }

  DesignTool::Validate(design.get());

  WriterAPI *writer = Iroha::CreateWriter(design.get());
  writer->SetLanguage("");
  writer->Write(ofn);
  return true;
}

}  // namespace isynth
