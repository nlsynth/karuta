// -*- C++ -*-
#ifndef _synth_dot_output_h_
#define _synth_dot_output_h_

#include "synth/common.h"

#include <map>

namespace iroha {
namespace dot {
class Cluster;
class Dot;
class Node;
}  // namespace dot
}  // namespace iroha

namespace synth {

class DotOutput {
public:
  DotOutput(DesignSynth *synth, ObjectTree *tree);
  ~DotOutput();

  void Write(const string &fn);

private:
  iroha::dot::Cluster *WriteObject(const string &name, vm::Object *obj,
				   iroha::dot::Cluster *parent);
  void WriteDistance();
  void WriteObjectDetail(ObjectSynth *osynth, iroha::dot::Cluster *cl);
  void MayWriteMemberObject(const string &name, vm::Object *obj,
			    iroha::dot::Cluster *cl);
  string GetObjectName(vm::Object *obj);
  void WriteAXIPortInfo(iroha::dot::Node *node, Annotation *an);

  std::unique_ptr<iroha::dot::Dot> dot_;
  DesignSynth *synth_;
  ObjectTree *tree_;
  std::map<vm::Object *, int> obj_seq_;
  std::map<vm::Object *, iroha::dot::Cluster *> obj_cluster_map_;
};

}  // namespace synth

#endif  // _synth_dot_output_h_
