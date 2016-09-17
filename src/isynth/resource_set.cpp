#include "isynth/resource_set.h"

#include "iroha/iroha.h"
#include "dfg/resource_params.h"
#include "fe/expr.h"
#include "fe/method.h"
#include "fe/var_decl.h"
#include "vm/insn.h"
#include "vm/method.h"

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

IResource *ResourceSet::GetImportedResource(vm::Method *method) {
  dfg::ResourceParams *dparams =
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
  // Assumes print() for now.
  vector<string> args;
  fe::VarDeclSet *a = method->parse_tree_->args_;
  if (a) {
    for (fe::VarDecl *vd : a->decls) {
      args.push_back(sym_cstr(vd->name_expr->sym_));
      IValueType vt;
      if (vd->type == sym_bool) {
	vt.SetWidth(0);
      } else {
	vt.SetWidth(numeric::Width::GetWidth(vd->width));
      }
      res->input_types_.push_back(vt);
    }
  }
  iparams->SetValues(resource::kEmbeddedModuleArgs, args);
  args.clear();
  args.push_back("req");
  iparams->SetValues(resource::kEmbeddedModuleReq, args);
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
  if (!(op == vm::OP_CONCAT || op == vm::OP_BIT_RANGE)) {
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
