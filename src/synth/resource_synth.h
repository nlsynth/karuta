// -*- C++ -*-
#ifndef _synth_resource_synth_h_
#define _synth_resource_synth_h_

#include "synth/common.h"

namespace synth {

class ResourceSynth {
public:
  ResourceSynth(ResourceSet *rset);

  void MayAddAxiMasterPort(vm::Object *array_obj);
  void MayAddAxiSlavePort(vm::Object *array_obj);

private:
  ResourceSet *rset_;
};

}  // namespace synth

#endif  // _synth_resource_synth_h_
