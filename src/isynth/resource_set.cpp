#include "isynth/resource_set.h"

#include "iroha/iroha.h"
#include "dfg/resource_params.h"

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
  vector<string> req;
  req.push_back("req");
  iparams->SetValues(resource::kEmbeddedModuleReq, req);
  IValueType vt;
  vt.SetWidth(32);
  res->input_types_.push_back(vt);
  return res;
}

}  // namespace isynth
