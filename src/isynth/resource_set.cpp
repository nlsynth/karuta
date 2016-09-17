#include "isynth/resource_set.h"

#include "iroha/iroha.h"
#include "dfg/resource_params.h"
#include "vm/insn.h"

namespace isynth {

ResourceSet::ResourceSet(ITable *tab) : tab_(tab) {
  assign_ = nullptr;
  pseudo_ = nullptr;
  br_ = DesignTool::GetOneResource(tab, resource::kTransition);
}

ResourceSet::~ResourceSet() {
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

IResource *ResourceSet::GetImportedResource(dfg::ResourceParams *dparams) {
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
  // Assumes print() for now.
  vector<string> args;
  args.push_back("v");
  iparams->SetValues(resource::kEmbeddedModuleArgs, args);
  args[0] = "req";
  iparams->SetValues(resource::kEmbeddedModuleReq, args);
  IValueType vt;
  vt.SetWidth(32);
  res->input_types_.push_back(vt);
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
  for (auto &res : resources_) {
    if (res.op == op && vt.GetWidth() == res.vt.GetWidth()) {
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
  res.vt = vt;
  return ires;
}

string ResourceSet::GetResourceClassName(vm::OpCode op) {
  switch (op) {
  case vm::OP_GT: return resource::kGt;
  case vm::OP_ADD: return resource::kAdd;
  case vm::OP_BIT_INV: return resource::kBitInv;
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

}  // namespace isynth
