// -*- C++ -*-
#ifndef _synth_dot_output_h_
#define _synth_dot_output_h_

#include "synth/common.h"

#include <map>

namespace iroha {
class Cluster;
class Dot;
}  // namespace iroha

namespace synth {

class DotOutput {
public:
  DotOutput(DesignSynth *synth, ObjectTree *tree);
  ~DotOutput();

  void Write(const string &fn);

private:
  iroha::Cluster *WriteObject(const string &name, vm::Object *obj,
			      iroha::Cluster *parent);
  void WriteObjectDetail(ObjectSynth *osynth, iroha::Cluster *cl);
  void MayWriteMemberObject(const string &name, vm::Object *obj,
			    iroha::Cluster *cl);
  string GetObjectName(vm::Object *obj);

  std::unique_ptr<iroha::Dot> dot_;
  DesignSynth *synth_;
  ObjectTree *tree_;
  std::map<vm::Object *, int> obj_seq_;
};

}  // namespace synth

#endif  // _synth_dot_output_h_
