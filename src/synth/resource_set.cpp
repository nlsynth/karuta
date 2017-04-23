#include "synth/resource_set.h"

#include "iroha/iroha.h"
#include "fe/expr.h"
#include "fe/method.h"
#include "fe/var_decl.h"
#include "synth/resource_params.h"
#include "vm/array_wrapper.h"
#include "vm/insn.h"
#include "vm/int_array.h"
#include "vm/method.h"

namespace synth {

ResourceSet::ResourceSet(ITable *tab) : tab_(tab) {
  assign_ = nullptr;
  pseudo_ = nullptr;
  mem_if_ = nullptr;
  task_entry_ = nullptr;
  br_ = DesignTool::GetOneResource(tab, resource::kTransition);
  print_ = nullptr;
  dataflow_in_ = nullptr;
  task_return_reg_ = nullptr;
  task_return_reg_writer_ = nullptr;
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

IResource *ResourceSet::PseudoResource() {
  if (!pseudo_) {
    pseudo_ = DesignTool::GetOneResource(tab_, resource::kPseudo);
  }
  return pseudo_;
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
    int data_bits = numeric::Width::GetWidth(memory->GetWidth());
    IValueType data_type;
    data_type.SetWidth(data_bits);
    IArray *array = new IArray(res, address_bits, data_type, false, true);
    res->SetArray(array);
  }
  tab_->resources_.push_back(res);
  (*m)[obj] = res;
  return res;
}

IResource *ResourceSet::GetAxiPort(vm::Object *obj) {
  IResource *array_res = GetSharedArray(obj, true, true);
  auto it = axi_ports_.find(obj);
  if (it != axi_ports_.end()) {
    return it->second;
  }
  IResourceClass *rc =
    DesignUtil::FindResourceClass(tab_->GetModule()->GetDesign(),
				  resource::kAxiPort);
  IResource *res = new IResource(tab_, rc);
  res->SetParentResource(array_res);
  tab_->resources_.push_back(res);
  axi_ports_[obj] = res;
  return res;
}

IResource *ResourceSet::GetMailbox(vm::Object *obj, bool is_owner, bool is_put) {
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
  tab_->resources_.push_back(res);
  (*m)[obj] = res;
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

IResource *ResourceSet::GetImportedResource(vm::Method *method) {
  synth::ResourceParams *dparams =
    method->parse_tree_->imported_resource_;

  string name = dparams->GetResourceName();
  for (IResource *res : imported_resources_) {
    iroha::ResourceParams *iparams = res->GetParams();
    if (iparams->GetEmbeddedModuleName() == name) {
      return res;
    }
  }
  string fn = dparams->GetCopyFileName();
  IResource *res =
    DesignTool::CreateEmbedResource(tab_, name, fn);
  iroha::ResourceParams *iparams = res->GetParams();

  vector<string> args;
  fe::VarDeclSet *a = method->parse_tree_->args_;
  if (a) {
    for (fe::VarDecl *vd : a->decls) {
      args.push_back(sym_cstr(vd->GetNameExpr()->sym_));
      IValueType vt;
      if (vd->GetType() == sym_bool) {
	vt.SetWidth(0);
      } else {
	vt.SetWidth(numeric::Width::GetWidth(vd->GetWidth()));
      }
      res->input_types_.push_back(vt);
    }
  }
  iparams->SetValues(resource::kEmbeddedModuleArgs, args);
  args.clear();
  args.push_back("req");
  iparams->SetValues(resource::kEmbeddedModuleReq, args);
  string ack = dparams->GetAckPinName();
  if (!ack.empty()) {
    args.clear();
    args.push_back(ack);
    iparams->SetValues(resource::kEmbeddedModuleAck, args);
  }
  return res;
}

IResource *ResourceSet::GetExternalArrayResource() {
  if (mem_if_ == nullptr) {
    mem_if_ = DesignTool::CreateArrayResource(tab_, 32, 32, true, true);
  }
  return mem_if_;
}

IResource *ResourceSet::GetInternalArrayResource(vm::Object *obj) {
  CHECK(vm::ArrayWrapper::IsIntArray(obj));
  auto it = array_resources_.find(obj);
  if (it != array_resources_.end()) {
    return it->second;
  }
  vm::IntArray *memory = vm::ArrayWrapper::GetIntArray(obj);
  int address_bits = memory->GetAddressWidth();
  int data_bits = numeric::Width::GetWidth(memory->GetWidth());
  IResource *res =
    DesignTool::CreateArrayResource(tab_, address_bits, data_bits, false, true);
  if (memory->GetLength() > 0) {
    IDesign *design = tab_->GetModule()->GetDesign();
    IArrayImage *image = new IArrayImage(design);
    design->array_images_.push_back(image);
    for (int i = 0; i < memory->GetLength(); ++i) {
      image->values_.push_back(numeric::Numeric::GetInt(memory->Read(i)));
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
  ResourceEntry res;
  string rcn = GetResourceClassName(op);
  IResourceClass *rc =
    DesignUtil::FindResourceClass(tab_->GetModule()->GetDesign(), rcn);
  IResource *ires = new IResource(tab_, rc);
  tab_->resources_.push_back(ires);
  PopulateResourceDataType(op, vt, ires);
  res.op = op;
  res.vt = key_vt;
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

IResource *ResourceSet::GetChannelResource(vm::Object *obj, bool is_write,
					   int data_width) {
  auto it = channel_resources_.find(obj);
  if (it != channel_resources_.end()) {
    return it->second;
  }
  string k;
  if (is_write) {
    k = resource::kChannelWrite;
  } else {
    k = resource::kChannelRead;
  }
  IResourceClass *rc =
    DesignUtil::FindResourceClass(tab_->GetModule()->GetDesign(), k);
  IResource *res = new IResource(tab_, rc);
  tab_->resources_.push_back(res);
  channel_resources_[obj] = res;
  IValueType vt;
  vt.SetWidth(data_width);
  if (is_write) {
    res->input_types_.push_back(vt);
  } else {
    res->output_types_.push_back(vt);
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
