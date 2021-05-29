#include "synth/dot_output.h"

#include "iroha/dot/dot.h"
#include "karuta/annotation.h"
#include "synth/design_synth.h"
#include "synth/object_synth.h"
#include "synth/object_tree.h"
#include "synth/thread_synth.h"
#include "vm/array_wrapper.h"
#include "vm/channel_wrapper.h"
#include "vm/int_array.h"
#include "vm/mailbox_wrapper.h"

using iroha::dot::Cluster;
using iroha::dot::Dot;
using iroha::dot::Edge;
using iroha::dot::Node;

namespace synth {

DotOutput::DotOutput(DesignSynth *synth, ObjectTree *tree)
    : synth_(synth), tree_(tree) {
  dot_.reset(new Dot());
}

DotOutput::~DotOutput() {}

void DotOutput::Write(const string &fn) {
  WriteObject("main", tree_->GetRootObject(), nullptr);
  WriteDistance();
  dot_->Write(fn);
}

iroha::dot::Cluster *DotOutput::WriteObject(const string &name, vm::Object *obj,
                                            iroha::dot::Cluster *parent) {
  ObjectSynth *osynth = synth_->GetObjectSynth(obj, false);
  if (osynth == nullptr) {
    MayWriteMemberObject(name, obj, parent);
    return nullptr;
  }
  if (obj_cluster_map_.find(obj) != obj_cluster_map_.end()) {
    return nullptr;
  }
  Cluster *c = dot_->GetCluster(GetObjectName(osynth->GetObject()));
  c->SetLabel(name);
  obj_cluster_map_[obj] = c;
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

void DotOutput::MayWriteMemberObject(const string &name, vm::Object *obj,
                                     iroha::dot::Cluster *cl) {
  if (vm::ArrayWrapper::IsIntArray(obj)) {
    WriteArrayObject(name, obj, cl);
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

void DotOutput::WriteArrayObject(const string &name, vm::Object *obj,
                                 iroha::dot::Cluster *cl) {
  if (name == "Memory") {
    // Excludes default memory.
    return;
  }
  Node *n = dot_->GetNode(GetObjectName(obj));
  n->SetCluster(cl);
  uint64_t len = vm::ArrayWrapper::GetIntArray(obj)->GetLength();
  string label = name + " #" + Util::Itoa(vm::ArrayWrapper::GetDataWidth(obj)) +
                 "[" + Util::Itoa(len) + "]";
  Annotation *a = vm::ArrayWrapper::GetAnnotation(obj);
  if (a != nullptr &&
      (a->IsAxiMaster() || a->IsAxiSlave() || a->IsExportSramIf())) {
    WriteAXIorSramPortInfo(name, obj, n, a);
  }
  n->SetLabel(label);
}

string DotOutput::GetObjectName(vm::Object *obj) {
  auto it = obj_seq_.find(obj);
  if (it != obj_seq_.end()) {
    return "o" + Util::Itoa(it->second);
  }
  obj_seq_[obj] = obj_seq_.size();
  return GetObjectName(obj);
}

void DotOutput::WriteDistance() {
  const auto &dists = tree_->GetDistanceMap();
  for (auto it : dists) {
    vm::Object *src_obj = it.first;
    Cluster *src_cl = obj_cluster_map_[src_obj];
    if (src_cl == nullptr) {
      // This can happen for an empty object.
      continue;
    }
    for (auto jt : it.second) {
      vm::Object *dst_obj = jt.first;
      Cluster *dst_cl = obj_cluster_map_[dst_obj];
      if (dst_cl == nullptr) {
        // Ditto. This can happen for an empty object.
        continue;
      }
      int dist = jt.second;
      Edge *e = src_cl->AddSink(dot_.get(), dst_cl);
      e->SetDotted(true);
      e->SetLabel("distance=" + Util::Itoa(dist));
    }
  }
}

void DotOutput::WriteAXIorSramPortInfo(const string &name, vm::Object *obj,
                                       Node *n, Annotation *an) {
  bool is_sram = an->IsExportSramIf();
  string prefix = (is_sram ? "sram_" : "axi_");
  Node *nn = dot_->GetNode(prefix + n->GetName());
  string label = name;
  if (is_sram) {
    label += " - SRAM ";
  } else {
    label += " - AXI ";
  }
  if (an->IsAxiMaster()) {
    label += "Master";
  } else {
    // SRAM IF as well.
    label += "Slave";
  }
  label += " #" + Util::Itoa(vm::ArrayWrapper::GetDataWidth(obj));
  nn->SetLabel(label);
  n->SetSinkNode(nn);
}

}  // namespace synth
