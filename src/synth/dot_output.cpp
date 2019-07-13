#include "synth/dot_output.h"

#include "iroha/dot.h"
#include "synth/design_synth.h"
#include "synth/object_synth.h"
#include "synth/object_tree.h"
#include "synth/thread_synth.h"

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
  WriteObjectDetail(osynth, c);
  auto m = tree_->GetChildObjects(obj);
  for (auto it : m) {
    Cluster *cc = WriteObject(it.first);
    if (cc != nullptr) {
      cc->SetSink(c);
    }
  }
  return c;
}

void DotOutput::WriteObjectDetail(ObjectSynth *osynth, iroha::Cluster *cl) {
  const auto &threads = osynth->GetAllThreads();
  for (ThreadSynth *tsynth : threads) {
    string name =
      osynth->GetName() + tsynth->GetEntryMethodName() + "_" +
      Util::Itoa(tsynth->GetIndex());
    Node *n = dot_->GetNode(name);
    n->SetLabel(tsynth->GetEntryMethodName() + "@" +
		Util::Itoa(tsynth->GetIndex()));
    n->SetCluster(cl);
  }
}

}  // namespace synth
