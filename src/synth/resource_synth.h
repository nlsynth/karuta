// -*- C++ -*-
#ifndef _synth_resource_synth_h_
#define _synth_resource_synth_h_

#include "synth/common.h"

namespace synth {

class ResourceSynth {
 public:
  ResourceSynth(ResourceSet *rset, ThreadSynth *thr_synth_);

  void MayAddAxiMasterPort(vm::Object *owner_obj, vm::Object *array_obj);
  void MayAddAxiSlavePort(vm::Object *owner_obj, vm::Object *array_obj);
  void MayAddSramIfPort(vm::Object *owner_obj, vm::Object *array_obj);
  IResource *MayAddExtIO(vm::Method *method, bool is_output);
  void MayAddSharedRegExtWriter(vm::Object *mailbox_obj);
  void MayAddIO(vm::Object *io, bool is_owner);
  void MayConfigureExternalSram(vm::Object *obj, IResource *res);
  void MayAddExternalSram(vm::Object *array_obj);

 private:
  void SetArrayName(vm::Object *owner_obj, vm::Object *array_obj,
                    IResource *res);
  void ConfigureSlavePort(vm::Object *owner_obj, vm::Object *array_obj,
                          Annotation *an, IResource *if_port);

  ResourceSet *rset_;
  ThreadSynth *thr_synth_;
};

}  // namespace synth

#endif  // _synth_resource_synth_h_
