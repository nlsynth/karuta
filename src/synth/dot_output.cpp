#include "synth/dot_output.h"

#include "iroha/dot.h"
#include "synth/design_synth.h"
#include "synth/object_synth.h"
#include "synth/object_tree.h"
#include "synth/thread_synth.h"
#include "vm/array_wrapper.h"

namespace synth {

DotOutput::DotOutput(DesignSynth *synth, ObjectTree *tree)
  : synth_(synth), tree_(tree) {
  dot_.reset(new iroha::Dot());
}

DotOutput::~DotOutput() {
}

void DotOutput::Write(const string &fn) {
  WriteObject("", tree_->GetRootObject(), nullptr);
  dot_->Write(fn);
}

iroha::Cluster *DotOutput::WriteObject(const string &name,
				       vm::Object *obj,
				       iroha::Cluster *parent) {
  ObjectSynth *osynth = synth_->GetObjectSynth(obj, false);
  if (osynth == nullptr) {
    MayWriteMemberObject(name, obj, parent);
    return nullptr;
  }
  string obj_name = osynth->GetName();
  Cluster *c = dot_->GetCluster(obj_name);
  WriteObjectDetail(osynth, c);
  auto m = tree_->GetChildObjects(obj);
  for (auto it : m) {
    Cluster *cc = WriteObject(it.second, it.first, c);
    if (cc != nullptr) {
      cc->SetSink(c);
    }
  }
  return c;
}

void DotOutput::WriteObjectDetail(ObjectSynth *osynth, iroha::Cluster *cl) {
  const auto &threads = osynth->GetAllThreads();
  set<string> show_index;
  for (ThreadSynth *tsynth : threads) {
    if (tsynth->GetIndex() > 0) {
      show_index.insert(tsynth->GetEntryMethodName());
    }
  }
  for (ThreadSynth *tsynth : threads) {
    string index;
    if (show_index.find(tsynth->GetEntryMethodName()) != show_index.end()) {
      index = Util::Itoa(tsynth->GetIndex());
    }
    string name = osynth->GetName() + tsynth->GetEntryMethodName();
    if (!index.empty()) {
      name += "_" + index;
    }
    Node *n = dot_->GetNode(name);
    string label = tsynth->GetEntryMethodName();
    if (!index.empty()) {
      label += "@" + index;
    }
    n->SetLabel(label);
    n->SetCluster(cl);
  }
}

void DotOutput::MayWriteMemberObject(const string &name,
				     vm::Object *obj, iroha::Cluster *cl) {
  if (vm::ArrayWrapper::IsIntArray(obj)) {
    if (name == "Memory") {
      // Excludes default memory.
      return;
    }
    Node *n = dot_->GetNode("memory_" + name);
    n->SetLabel(name + "[]");
    n->SetCluster(cl);
  }
}

}  // namespace synth
