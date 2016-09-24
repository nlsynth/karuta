// -*- C++ -*-
//
// Manages per table resource objects.

#ifndef _isynth_resource_set_h_
#define _isynth_resource_set_h_

#include "isynth/common.h"

// for IValueType
#include "iroha/i_design.h"
#include "vm/opcode.h"

#include <map>

using std::map;

namespace isynth {

class ResourceSet {
public:
  ResourceSet(ITable *tab);
  ~ResourceSet();

  IResource *AssignResource();
  IResource *BranchResource();
  IResource *PseudoResource();
  IResource *GetOpResource(vm::OpCode op, IValueType &vt);

  IResource *GetImportedResource(vm::Method *method);
  IResource *GetExternalArrayResource();
  IResource *GetInternalArrayResource(vm::Object *obj);
  IResource *GetChannelResource(vm::Object *ch, bool is_write,
				int data_width);

private:
  string GetResourceClassName(vm::OpCode op);
  void PopulateResourceDataType(int op, IValueType &vt, IResource *res);

  ITable *tab_;
  IResource *assign_;
  IResource *br_;
  IResource *mem_if_;
  IResource *pseudo_;

  class ResourceEntry {
  public:
    vm::OpCode op;
    IValueType vt;
    IResource *resource;
  };
  vector<ResourceEntry> resources_;

  vector<IResource *> imported_resources_;
  map<vm::Object *, IResource *> array_resources_;
  map<vm::Object *, IResource *> channel_resources_;
};

}  // namespace isynth

#endif  // _isynth_resource_set_h_
