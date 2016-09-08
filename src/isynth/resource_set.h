// -*- C++ -*-
//
// Manages per table resource objects.

#ifndef _isynth_resource_set_h_
#define _isynth_resource_set_h_

#include "isynth/common.h"

namespace isynth {

class ResourceSet {
public:
  ResourceSet(ITable *tab);
  ~ResourceSet();

  IResource *AssignResource();
  IResource *BranchResource();
  IResource *PseudoResource();

  IResource *GetImportedResource(dfg::ResourceParams *dparams);

private:
  ITable *tab_;
  IResource *assign_;
  IResource *br_;
  IResource *pseudo_;

  vector<IResource *> imported_resources_;
};

}  // namespace isynth

#endif  // _synth_resource_set_h_
