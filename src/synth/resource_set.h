// -*- C++ -*-
//
// Manages per graph resource objects.

#ifndef _synth_resource_set_h_
#define _synth_resource_set_h_

#include "nli.h"

#include "vm/opcode.h"

namespace vm {
class Object;
}  // namespace vm

namespace dfg {
class DGraph;
class DInsn;
class DResource;
class DType;
class ImportedResource;
}  // namespace dfg
using namespace dfg;

namespace synth {

class SubModuleCallEntry {
public:
  vm::Object *obj;
  sym_t method_name;
  sym_t orig_obj_name;
  DResource *resource;
};

class ResourceSet {
public:
  ResourceSet(DGraph *graph);

  DResource *AssignResource();
  DResource *BranchResource();
  DResource *FuncallResource();
  DResource *FunctionEntryResource(bool is_task_root);
  DResource *TaskFinishResource();
  DResource *GetExtIOResource(sym_t name,
			      ImportedResource *resource,
			      DInsn *insn);

  DResource *GetOpResource(vm::OpCode op, DType *type);
  DResource *GetImportedResource(ImportedResource *resource);
  DResource *GetArrayResource(sym_t name);
  DResource *GetChannelResource(const string &name, bool is_write,
				int data_width);
  DResource *GetSubModuleCallResource(vm::Object *callee_object,
				      sym_t method_name,
				      sym_t orig_obj_name);
  vector<SubModuleCallEntry> &GetSubModuleCalls();

private:
  sym_t GetResourceType(vm::OpCode op);
  void PopulateResourceDataType(int op, DResource *res, DType *type);

  DGraph *graph_;
  DResource *assign_;
  DResource *br_;
  DResource *funcall_;
  DResource *function_entry_;
  DResource *task_entry_;
  DResource *task_finish_;
  DResource *mem_if_;

  class ResourceEntry {
  public:
    ResourceEntry() {
      type = NULL;
    }
    vm::OpCode op;
    DType *type;
    DResource *resource;
  };
  vector<ResourceEntry> resources_;

  vector<SubModuleCallEntry> sub_module_resources_;

  vector<DResource *> imported_resources_;
  vector<DResource *> array_resources_;
  vector<DResource *> channel_resources_;
  vector<DResource *> ext_io_resources_;
};

}  // namespace synth

#endif  // _synth_resource_set_h_
