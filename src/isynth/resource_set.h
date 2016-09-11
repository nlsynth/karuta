// -*- C++ -*-
//
// Manages per table resource objects.

#ifndef _isynth_resource_set_h_
#define _isynth_resource_set_h_

#include "isynth/common.h"

// for IValueType
#include "iroha/i_design.h"
#include "vm/opcode.h"

namespace isynth {

class ResourceSet {
public:
  ResourceSet(ITable *tab);
  ~ResourceSet();

  IResource *AssignResource();
  IResource *BranchResource();
  IResource *PseudoResource();
  IResource *GetOpResource(vm::OpCode op, IValueType &vt);

  IResource *GetImportedResource(dfg::ResourceParams *dparams);

private:
  string GetResourceClassName(vm::OpCode op);
  void PopulateResourceDataType(int op, IValueType &vt, IResource *res);

  ITable *tab_;
  IResource *assign_;
  IResource *br_;
  IResource *pseudo_;

  class ResourceEntry {
  public:
    vm::OpCode op;
    IValueType vt;
    IResource *resource;
  };
  vector<ResourceEntry> resources_;

  vector<IResource *> imported_resources_;
};

}  // namespace isynth

#endif  // _synth_resource_set_h_
