// -*- C++ -*-
//
// Manages per table resource objects.

#ifndef _synth_resource_set_h_
#define _synth_resource_set_h_

#include "synth/common.h"

// for IValueType
#include <map>

#include "iroha/i_design.h"
#include "vm/opcode.h"

using std::map;

namespace synth {

class ResourceSet {
 public:
  ResourceSet(ITable *tab);
  ~ResourceSet();

  IResource *AssertResource();
  IResource *AssignResource();
  IResource *BranchResource();
  IResource *PseudoCallResource();
  IResource *PrintResource();
  IResource *GetOpResource(vm::OpCode op, IValueType &vt);

  IResource *GetImportedResource(vm::Method *method);
  IResource *GetExternalArrayResource(vm::Object *obj);
  IResource *GetInternalArrayResource(vm::Object *obj);
  IResource *GetChannelResource(vm::Object *ch, bool is_owner, bool is_write,
                                int data_width, int depth);
  IResource *GetSubModuleTaskResource();
  IResource *GetDataFlowInResource();
  IResource *GetMemberSharedReg(sym_t name, bool is_owner, bool is_write);
  IResource *GetSharedArray(vm::Object *obj, bool is_owner, bool is_write);
  IResource *GetSharedArrayReplica(vm::Object *obj, int index);
  IResource *GetAxiMasterPort(vm::Object *obj);
  IResource *GetAxiSlavePort(vm::Object *obj);
  IResource *GetSramIfPort(vm::Object *obj);
  IResource *GetMailbox(vm::Object *obj, bool is_owner, bool is_put);
  IResource *GetMailboxExtWriter(vm::Object *obj);
  IResource *GetTaskReturnRegWriter(int width);
  IResource *GetExtIOByName(const string &name, bool is_output, int width,
                            int distance);
  IResource *GetExtIOByObject(vm::Object *obj, bool is_owner);
  IResource *GetExtTaskResource();
  IResource *GetExtTaskDoneResource();
  IResource *GetTicker(vm::Object *obj, bool is_owner);

 private:
  string GetResourceClassName(vm::OpCode op);
  void PopulateResourceDataType(int op, IValueType &vt, IResource *res);
  void PopulateIOTypes(fe::VarDeclSet *vds, bool is_output, IResource *res);
  IResource *GetRAMPortResource(vm::Object *obj, const string &name,
                                map<vm::Object *, IResource *> *resources);
  IResource *BuildExtIO(const string &name, bool is_output, int width,
                        int distance);

  ITable *tab_;
  IResource *assert_;
  IResource *assign_;
  IResource *br_;
  IResource *print_;
  IResource *pseudo_call_;
  IResource *task_entry_;
  IResource *dataflow_in_;
  IResource *task_return_reg_;
  IResource *task_return_reg_writer_;
  IResource *ext_task_;
  IResource *ext_task_done_;

  class ResourceEntry {
   public:
    vm::OpCode op;
    IValueType vt;
    IResource *resource;
  };
  vector<ResourceEntry> resources_;

  vector<IResource *> imported_resources_;
  map<vm::Object *, IResource *> array_resources_;
  map<vm::Object *, IResource *> ext_sram_if_;
  map<vm::Object *, IResource *> fifo_resources_;
  map<vm::Object *, IResource *> fifo_writers_;
  map<vm::Object *, IResource *> fifo_readers_;
  map<sym_t, IResource *> member_shared_reg_;
  map<sym_t, IResource *> member_shared_reg_writer_;
  map<sym_t, IResource *> member_shared_reg_reader_;
  map<vm::Object *, IResource *> shared_array_;
  map<vm::Object *, IResource *> shared_array_writer_;
  map<vm::Object *, IResource *> shared_array_reader_;
  map<IResource *, map<int, IResource *> > shared_array_replicas_;
  map<vm::Object *, IResource *> axi_master_ports_;
  map<vm::Object *, IResource *> axi_slave_ports_;
  map<vm::Object *, IResource *> sram_if_ports_;
  map<vm::Object *, IResource *> mailbox_shared_reg_;
  map<vm::Object *, IResource *> mailbox_putters_;
  map<vm::Object *, IResource *> mailbox_getters_;
  map<vm::Object *, IResource *> mailbox_shared_reg_ext_writers_;
  map<string, IResource *> ext_io_by_name_;
  map<vm::Object *, IResource *> ext_io_by_object_;
  map<vm::Object *, IResource *> ext_io_accessor_by_object_;
  map<vm::Object *, IResource *> tickers_;
  map<vm::Object *, IResource *> ticker_accessors_;
};

}  // namespace synth

#endif  // _synth_resource_set_h_
