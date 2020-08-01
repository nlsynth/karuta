#include "synth/resource_set.h"

#include "base/util.h"
#include "fe/expr.h"
#include "fe/fe_method.h"
#include "fe/var_decl.h"
#include "iroha/iroha.h"
#include "karuta/annotation.h"
#include "synth/object_attr_names.h"
#include "vm/array_wrapper.h"
#include "vm/channel_wrapper.h"
#include "vm/insn.h"
#include "vm/int_array.h"
#include "vm/io_wrapper.h"
#include "vm/mailbox_wrapper.h"
#include "vm/method.h"
#include "vm/object_util.h"

namespace synth {

ResourceSet::ResourceSet(ITable *tab) : tab_(tab) {
  assign_ = nullptr;
  assert_ = nullptr;
  pseudo_call_ = nullptr;
  task_entry_ = nullptr;
  br_ = DesignTool::GetOneResource(tab, resource::kTransition);
  print_ = nullptr;
  dataflow_in_ = nullptr;
  task_return_reg_ = nullptr;
  task_return_reg_writer_ = nullptr;
  ext_task_ = nullptr;
  ext_task_done_ = nullptr;
}

ResourceSet::~ResourceSet() {
}

IResource *ResourceSet::AssertResource() {
  if (!assert_) {
    assert_ = DesignTool::GetOneResource(tab_, resource::kAssert);
  }
  return assert_;
}

IResource *ResourceSet::AssignResource() {
  if (!assign_) {
    assign_ = DesignTool::GetOneResource(tab_, resource::kSet);
  }
  return assign_;
}

IResource *ResourceSet::BranchResource() {
  return br_;
}

IResource *ResourceSet::PseudoCallResource() {
  if (pseudo_call_ == nullptr) {
    pseudo_call_ = DesignTool::GetOneResource(tab_, resource::kPseudo);
  }
  return pseudo_call_;
}

IResource *ResourceSet::PrintResource() {
  if (!print_) {
    print_ = DesignTool::GetOneResource(tab_, resource::kPrint);
  }
  return print_;
}

IResource *ResourceSet::GetMemberSharedReg(sym_t name, bool is_owner,
					   bool is_write) {
  map<sym_t, IResource *> *m;
  const char *n;
  if (is_owner) {
    n = resource::kSharedReg;
    m = &member_shared_reg_;
  } else {
    n = is_write ?
      resource::kSharedRegWriter : resource::kSharedRegReader;
    m = is_write ? &member_shared_reg_writer_ : &member_shared_reg_reader_;
  }
  auto it = m->find(name);
  if (it != m->end()) {
    return it->second;
  }
  IResourceClass *rc =
    DesignUtil::FindResourceClass(tab_->GetModule()->GetDesign(), n);
  IResource *res = new IResource(tab_, rc);
  tab_->resources_.push_back(res);
  (*m)[name] = res;
  return res;
}

IResource *ResourceSet::GetSharedArray(vm::Object *obj, bool is_owner,
				       bool is_write) {
  CHECK(vm::ArrayWrapper::IsIntArray(obj));
  map<vm::Object *, IResource *> *m;
  const char *n;
  if (is_owner) {
    m = &shared_array_;
    n = resource::kSharedMemory;
  } else {
    m = is_write ? &shared_array_writer_ : &shared_array_reader_;
    n = is_write ?
      resource::kSharedMemoryWriter : resource::kSharedMemoryReader;
  }
  auto it = m->find(obj);
  if (it != m->end()) {
    return it->second;
  }
  IResourceClass *rc =
    DesignUtil::FindResourceClass(tab_->GetModule()->GetDesign(), n);
  IResource *res = new IResource(tab_, rc);
  if (is_owner) {
    vm::IntArray *memory = vm::ArrayWrapper::GetIntArray(obj);
    int address_bits = memory->GetAddressWidth();
    int data_bits = memory->GetDataWidth().GetWidth();
    IValueType data_type;
    data_type.SetWidth(data_bits);
    IArray *array = new IArray(res, address_bits, data_type, false, true);
    res->SetArray(array);
  }
  tab_->resources_.push_back(res);
  (*m)[obj] = res;
  return res;
}

IResource *ResourceSet::GetSharedArrayReplica(vm::Object *obj, int index) {
  IResource *master = GetSharedArray(obj, true, false);
  auto &m = shared_array_replicas_[master];
  auto it = m.find(index);
  if (it != m.end()) {
    return it->second;
  }
  IResourceClass *rc =
    DesignUtil::FindResourceClass(tab_->GetModule()->GetDesign(),
				  resource::kSharedMemoryReplica);
  IResource *res = new IResource(tab_, rc);
  res->SetParentResource(master);
  tab_->resources_.push_back(res);
  m[index] = res;
  return res;
}

IResource *ResourceSet::GetAxiMasterPort(vm::Object *obj) {
  return GetPortResource(obj, resource::kAxiMasterPort, &axi_master_ports_);
}

IResource *ResourceSet::GetAxiSlavePort(vm::Object *obj) {
  return GetPortResource(obj, resource::kAxiSlavePort, &axi_slave_ports_);
}

IResource *ResourceSet::GetSramIfPort(vm::Object *obj) {
  return GetPortResource(obj, resource::kSramIf, &sram_if_ports_);
}

IResource *ResourceSet::GetPortResource(vm::Object *obj, const string &name,
					map<vm::Object *, IResource *> *resources) {
  IResource *array_res = GetSharedArray(obj, true, true);
  auto it = resources->find(obj);
  if (it != resources->end()) {
    return it->second;
  }
  IResourceClass *rc =
    DesignUtil::FindResourceClass(tab_->GetModule()->GetDesign(), name);
  IResource *res = new IResource(tab_, rc);
  res->SetParentResource(array_res);
  tab_->resources_.push_back(res);
  (*resources)[obj] = res;
  return res;
}

IResource *ResourceSet::GetMailbox(vm::Object *obj, bool is_owner,
				   bool is_put) {
  map<vm::Object *, IResource *> *m;
  const char *n;
  if (is_owner) {
    m = &mailbox_shared_reg_;
    n = resource::kSharedReg;
  } else {
    m = is_put ? &mailbox_putters_ : &mailbox_getters_;
    n = is_put ?
      resource::kSharedRegWriter : resource::kSharedRegReader;
  }
  auto it = m->find(obj);
  if (it != m->end()) {
    return it->second;
  }
  IResourceClass *rc =
    DesignUtil::FindResourceClass(tab_->GetModule()->GetDesign(),
				  n);
  IResource *res = new IResource(tab_, rc);
  if (vm::MailboxWrapper::IsMailbox(obj)) {
    // Caller should set width if this isn't a mailbox.
    res->GetParams()->SetWidth(vm::MailboxWrapper::GetWidth(obj));
  }
  tab_->resources_.push_back(res);
  (*m)[obj] = res;
  return res;
}

IResource *ResourceSet::GetMailboxExtWriter(vm::Object *obj) {
  auto it = mailbox_shared_reg_ext_writers_.find(obj);
  if (it != mailbox_shared_reg_ext_writers_.end()) {
    return it->second;
  }
  IResource *mb = GetMailbox(obj, true, false);
  IResourceClass *rc =
    DesignUtil::FindResourceClass(tab_->GetModule()->GetDesign(),
				  resource::kSharedRegExtWriter);
  IResource *res = new IResource(tab_, rc);
  res->SetParentResource(mb);
  tab_->resources_.push_back(res);
  mailbox_shared_reg_ext_writers_[obj] = res;
  return res;
}

IResource *ResourceSet::GetTaskReturnRegWriter(int width) {
  if (task_return_reg_ == nullptr) {
    task_return_reg_ = DesignTool::CreateSharedRegResource(tab_, width);
    task_return_reg_writer_ =
      DesignTool::CreateSharedRegWriterResource(tab_, task_return_reg_);
  }
  return task_return_reg_writer_;
}

IResource *ResourceSet::GetExtIOByName(const string &name,
				       bool is_output, int width,
				       int distance) {
  if (ext_io_by_name_.find(name) != ext_io_by_name_.end()) {
    return ext_io_by_name_[name];
  }
  IResource *res = BuildExtIO(name, is_output, width, distance);
  ext_io_by_name_[name] = res;
  return res;
}

IResource *ResourceSet::GetExtIOByObject(vm::Object *obj, bool is_owner) {
  map<vm::Object *, IResource *> *m;
  if (is_owner) {
    m = &ext_io_by_object_;
  } else {
    m = &ext_io_accessor_by_object_;
  }
  auto it = m->find(obj);
  if (it != m->end()) {
    return it->second;
  }
  bool is_output = vm::IOWrapper::IsOutput(obj);
  int width = vm::IOWrapper::GetWidth(obj);
  if (is_owner) {
    string name = vm::IOWrapper::GetName(obj);
    int width = vm::IOWrapper::GetWidth(obj);
    int distance = vm::IOWrapper::GetDistance(obj);
    IResource *res = BuildExtIO(name, is_output, width, distance);
    ext_io_by_object_[obj] = res;
    return res;
  } else {
    IResourceClass *rc =
      DesignUtil::FindResourceClass(tab_->GetModule()->GetDesign(),
				    (is_output ?
				     resource::kExtOutputAccessor :
				     resource::kExtInputAccessor));
    IResource *res = new IResource(tab_, rc);
    IValueType vt;
    vt.SetWidth(width);
    if (is_output) {
      res->input_types_.push_back(vt);
    } else {
      res->output_types_.push_back(vt);
    }
    tab_->resources_.push_back(res);
    ext_io_accessor_by_object_[obj] = res;
    return res;
  }
}

IResource *ResourceSet::BuildExtIO(const string &name, bool is_output,
				   int width, int distance) {
  IResourceClass *rc =
    DesignUtil::FindResourceClass(tab_->GetModule()->GetDesign(),
				  (is_output ?
				   resource::kExtOutput :
				   resource::kExtInput));
  IResource *res = new IResource(tab_, rc);
  if (is_output) {
    res->GetParams()->SetExtOutputPort(name, width);
  } else {
    res->GetParams()->SetExtInputPort(name, width);
  }
  if (distance > 0) {
    res->GetParams()->SetDistance(distance);
  }
  tab_->resources_.push_back(res);
  IValueType vt;
  vt.SetWidth(width);
  if (is_output) {
    res->input_types_.push_back(vt);
  } else {
    res->output_types_.push_back(vt);
  }
  return res;
}

IResource *ResourceSet::GetExtTaskResource() {
  if (ext_task_ == nullptr) {
    ext_task_ = DesignTool::GetOneResource(tab_, resource::kExtTask);
  }
  return ext_task_;
}

IResource *ResourceSet::GetExtTaskDoneResource() {
  if (ext_task_done_ == nullptr) {
    ext_task_done_ = DesignTool::GetOneResource(tab_, resource::kExtTaskDone);
  }
  return ext_task_done_;
}

IResource *ResourceSet::GetTicker(vm::Object *obj, bool is_owner) {
  map<vm::Object *, IResource *> *m;
  if (is_owner) {
    m = &tickers_;
  } else {
    m = &ticker_accessors_;
  }
  auto it = m->find(obj);
  if (it != m->end()) {
    return it->second;
  }
  string n;
  if (is_owner) {
    n = resource::kTicker;
  } else {
    n = resource::kTickerAccessor;
  }
  IResourceClass *rc =
    DesignUtil::FindResourceClass(tab_->GetModule()->GetDesign(), n);
  IResource *res = new IResource(tab_, rc);
  tab_->resources_.push_back(res);
  tickers_[obj] = res;
  return res;
}

IResource *ResourceSet::GetImportedResource(vm::Method *method) {
  Annotation *dparams =
    method->GetAnnotation();

  string name = dparams->GetResourceName();
  for (IResource *res : imported_resources_) {
    iroha::ResourceParams *iparams = res->GetParams();
    if (iparams->GetEmbeddedModuleName() == name) {
      return res;
    }
  }
  string fn = dparams->GetCopyFileName();
  IResource *res = nullptr;
  if (dparams->IsExtCombinational()) {
    res =
      DesignTool::CreateExtCombinationalResource(tab_,
						 dparams->GetModuleName(),
						 fn);
  } else {
    res = DesignTool::CreateExtTaskCallResource(tab_,
						dparams->GetModuleName(), fn);
  }

  fe::VarDeclSet *a = method->GetParseTree()->GetArgs();
  PopulateIOTypes(a, false, res);
  fe::VarDeclSet *r = method->GetParseTree()->GetReturns();
  PopulateIOTypes(r, true, res);
  return res;
}

void ResourceSet::PopulateIOTypes(fe::VarDeclSet *vds, bool is_output,
				  IResource *res) {
  if (vds == nullptr) {
    return;
  }
  for (fe::VarDecl *vd : vds->decls) {
    IValueType vt;
    if (vd->GetType() == sym_bool) {
      vt.SetWidth(0);
    } else {
      vt.SetWidth(vd->GetWidth().GetWidth());
    }
    if (is_output) {
      res->output_types_.push_back(vt);
    } else {
      res->input_types_.push_back(vt);
    }
  }
}

IResource *ResourceSet::GetExternalArrayResource(vm::Object *obj) {
  auto it = ext_sram_if_.find(obj);
  if (it != ext_sram_if_.end()) {
    return it->second;
  }
  int aw = vm::ObjectUtil::GetAddressWidth(obj);
  int dw = vm::ObjectUtil::GetDataWidth(obj);
  auto *mem_if = DesignTool::CreateArrayResource(tab_, aw, dw, true, true);
  string n = vm::ObjectUtil::GetStringMember(obj, kSramName);
  if (!n.empty()) {
    mem_if->GetParams()->SetPortNamePrefix(n);
  }
  ext_sram_if_[obj] = mem_if;
  return mem_if;
}

IResource *ResourceSet::GetInternalArrayResource(vm::Object *obj) {
  CHECK(vm::ArrayWrapper::IsIntArray(obj));
  auto it = array_resources_.find(obj);
  if (it != array_resources_.end()) {
    return it->second;
  }
  vm::IntArray *memory = vm::ArrayWrapper::GetIntArray(obj);
  int address_bits = memory->GetAddressWidth();
  int data_bits = memory->GetDataWidth().GetWidth();
  IResource *res =
    DesignTool::CreateArrayResource(tab_, address_bits, data_bits, false, true);
  if (memory->GetLength() > 0) {
    IDesign *design = tab_->GetModule()->GetDesign();
    IArrayImage *image = new IArrayImage(design);
    design->array_images_.push_back(image);
    for (int i = 0; i < memory->GetLength(); ++i) {
      image->values_.push_back(memory->ReadSingle(i).GetValue0());
    }
    res->GetArray()->SetArrayImage(image);
  }
  array_resources_[obj] = res;
  return res;
}

IResource *ResourceSet::GetOpResource(vm::OpCode op, IValueType &vt) {
  // Remap.
  switch (op) {
  case vm::OP_LT:
  case vm::OP_LTE:
  case vm::OP_GTE:
    op = vm::OP_GT;
    break;
  case vm::OP_NE:
    op = vm::OP_EQ;
    break;
  default:
    break;
  }
  // Use default type value as the key.
  IValueType key_vt;
  if (!(op == vm::OP_CONCAT || op == vm::OP_BIT_RANGE ||
	op == vm::OP_LSHIFT || op == vm::OP_RSHIFT)) {
    key_vt = vt;
  }
  for (auto &res : resources_) {
    if (res.op == op && key_vt.GetWidth() == res.vt.GetWidth()) {
      return res.resource;
    }
  }
  string rcn = GetResourceClassName(op);
  IResourceClass *rc =
    DesignUtil::FindResourceClass(tab_->GetModule()->GetDesign(), rcn);
  IResource *ires = new IResource(tab_, rc);
  tab_->resources_.push_back(ires);
  PopulateResourceDataType(op, vt, ires);
  ResourceEntry res;
  res.op = op;
  res.vt = key_vt;
  res.resource = ires;
  resources_.push_back(res);
  return ires;
}

string ResourceSet::GetResourceClassName(vm::OpCode op) {
  switch (op) {
  case vm::OP_GT: return resource::kGt;
  case vm::OP_EQ: return resource::kEq;
  case vm::OP_ADD: return resource::kAdd;
  case vm::OP_SUB: return resource::kSub;
  case vm::OP_MUL: return resource::kMul;
  case vm::OP_BIT_INV: return resource::kBitInv;
  case vm::OP_AND: return resource::kBitAnd;
  case vm::OP_OR: return resource::kBitOr;
  case vm::OP_LAND: return resource::kBitAnd;
  case vm::OP_LOR: return resource::kBitOr;
  case vm::OP_XOR: return resource::kBitXor;
  case vm::OP_CONCAT: return resource::kBitConcat;
  case vm::OP_BIT_RANGE: return resource::kBitSel;
  case vm::OP_LSHIFT: return resource::kShift;
  case vm::OP_RSHIFT: return resource::kShift;
  default:
    CHECK(false) << "unknown resource type: " << vm::OpCodeName(op);
  }
  return "";
}

void ResourceSet::PopulateResourceDataType(int op, IValueType &vt,
					   IResource *res) {
  if (vm::InsnType::IsNumCalculation(op)) {
    res->input_types_.push_back(vt);
    res->input_types_.push_back(vt);
    res->output_types_.push_back(vt);
  } else if (vm::InsnType::IsComparison(op)) {
    res->input_types_.push_back(vt);
    res->input_types_.push_back(vt);
    IValueType b;
    b.SetWidth(0);
    res->output_types_.push_back(b);
  }
}

IResource *ResourceSet::GetChannelResource(vm::Object *obj, bool is_owner,
					   bool is_write,
					   int data_width, int depth) {
  map<vm::Object *, IResource *> *m;
  const char *n;
  if (is_owner) {
    m = &fifo_resources_;
    n = resource::kFifo;
  } else {
    if (is_write) {
      n = resource::kFifoWriter;
      m = &fifo_writers_;
    } else {
      n = resource::kFifoReader;
      m = &fifo_readers_;
    }
  }
  auto it = m->find(obj);
  if (it != m->end()) {
    return it->second;
  }
  IResourceClass *rc =
    DesignUtil::FindResourceClass(tab_->GetModule()->GetDesign(), n);
  IResource *res = new IResource(tab_, rc);
  tab_->resources_.push_back(res);
  (*m)[obj] = res;
  if (is_owner) {
    res->GetParams()->SetWidth(data_width);
    int dl = ::Util::Log2(depth);
    if (dl == 0) {
      dl = 1;
    }
    res->GetParams()->SetAddrWidth(dl);
  } else {
    IValueType vt;
    vt.SetWidth(data_width);
    if (is_write) {
      res->input_types_.push_back(vt);
    } else {
      res->output_types_.push_back(vt);
    }
  }
  return res;
}

IResource *ResourceSet::GetSubModuleTaskResource() {
  if (task_entry_ == nullptr) {
    task_entry_ = DesignTool::CreateTaskResource(tab_);
  }
  return task_entry_;
}

IResource *ResourceSet::GetDataFlowInResource() {
  if (dataflow_in_ == nullptr) {
    dataflow_in_ = DesignTool::CreateDataFlowInResource(tab_);
  }
  return dataflow_in_;
}

}  // namespace synth
