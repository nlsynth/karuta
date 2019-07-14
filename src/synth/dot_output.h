// -*- C++ -*-
#ifndef _synth_dot_output_h_
#define _synth_dot_output_h_

#include "synth/common.h"

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

  std::unique_ptr<iroha::Dot> dot_;
  DesignSynth *synth_;
  ObjectTree *tree_;
};

}  // namespace synth

#endif  // _synth_dot_output_h_
