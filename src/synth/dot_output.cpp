#include "synth/dot_output.h"

#include "iroha/dot/dot.h"
#include "synth/design_synth.h"
#include "synth/object_synth.h"
#include "synth/object_tree.h"
#include "synth/thread_synth.h"
#include "vm/array_wrapper.h"
#include "vm/channel_wrapper.h"
#include "vm/mailbox_wrapper.h"

using iroha::dot::Dot;
using iroha::dot::Cluster;
using iroha::dot::Node;

namespace synth {

DotOutput::DotOutput(DesignSynth *synth, ObjectTree *tree)
  : synth_(synth), tree_(tree) {
  dot_.reset(new Dot());
}

DotOutput::~DotOutput() {
}

void DotOutput::Write(const string &fn) {
  WriteObject("", tree_->GetRootObject(), nullptr);
  dot_->Write(fn);
}

iroha::dot::Cluster *DotOutput::WriteObject(const string &name,
					    vm::Object *obj,
					    iroha::dot::Cluster *parent) {
  ObjectSynth *osynth = synth_->GetObjectSynth(obj, false);
  if (osynth == nullptr) {
    MayWriteMemberObject(name, obj, parent);
    return nullptr;
  }
  Cluster *c = dot_->GetCluster(GetObjectName(osynth->GetObject()));
  WriteObjectDetail(osynth, c);
  auto m = tree_->GetChildObjects(obj);
  for (auto it : m) {
    Cluster *cc = WriteObject(it.second, it.first, c);
    if (cc != nullptr) {
      cc->AddSink(dot_.get(), c);
    }
  }
  return c;
}

void DotOutput::WriteObjectDetail(ObjectSynth *osynth,
				  iroha::dot::Cluster *cl) {
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
    Node *n = dot_->GetNode(GetObjectName(osynth->GetObject()) + name);
    string label = tsynth->GetEntryMethodName();
    if (!index.empty()) {
      label += "@" + index;
    }
    n->SetLabel(label);
    n->SetCluster(cl);
  }
}

void DotOutput::MayWriteMemberObject(const string &name,
				     vm::Object *obj, iroha::dot::Cluster *cl) {
  if (vm::ArrayWrapper::IsIntArray(obj)) {
    if (name == "Memory") {
      // Excludes default memory.
      return;
    }
    Node *n = dot_->GetNode(GetObjectName(obj));
    n->SetLabel(name + "[]");
    n->SetCluster(cl);
  }
  if (vm::ChannelWrapper::IsChannel(obj)) {
    Node *n = dot_->GetNode(GetObjectName(obj));
    n->SetLabel(name + "<->");
    n->SetCluster(cl);
  }
  if (vm::MailboxWrapper::IsMailbox(obj)) {
    Node *n = dot_->GetNode(GetObjectName(obj));
    n->SetLabel(name + "|-|");
    n->SetCluster(cl);
  }
}

string DotOutput::GetObjectName(vm::Object *obj) {
  auto it = obj_seq_.find(obj);
  if (it != obj_seq_.end()) {
    return "o" + Util::Itoa(it->second);
  }
  obj_seq_[obj] = obj_seq_.size();
  return GetObjectName(obj);
}

}  // namespace synth
