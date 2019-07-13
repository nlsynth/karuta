#include "synth/dot_output.h"

#include "iroha/dot.h"
#include "synth/design_synth.h"
#include "synth/object_synth.h"
#include "synth/object_tree.h"

namespace synth {

DotOutput::DotOutput(DesignSynth *synth, ObjectTree *tree)
  : synth_(synth), tree_(tree) {
  dot_.reset(new iroha::Dot());
}

DotOutput::~DotOutput() {
}

void DotOutput::Write(const string &fn) {
  WriteObject(tree_->GetRootObject());
  dot_->Write(fn);
}

iroha::Cluster *DotOutput::WriteObject(vm::Object *obj) {
  ObjectSynth *osynth = synth_->GetObjectSynth(obj, false);
  if (osynth == nullptr) {
    return nullptr;
  }
  string name = osynth->GetName();
  Cluster *c = dot_->GetCluster(name);
  Node *n = dot_->GetNode(name);
  n->SetCluster(c);
  auto m = tree_->GetChildObjects(obj);
  for (auto it : m) {
    Cluster *cc = WriteObject(it.first);
    if (cc != nullptr) {
      cc->SetSink(c);
    }
  }
  return c;
}

}  // namespace synth
