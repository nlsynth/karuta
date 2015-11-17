#include "dfg/d_module.h"

#include "dfg/d_graph.h"
#include "dfg/d_graph_util.h"
#include "opt/opt_context.h"

namespace dfg {

DModule::DModule(const char *name, enum ModuleType type, DModule *parent)
  : module_name_(name), module_type_(type), graph_(NULL), parent_mod_(parent) {
  optimize_context_.reset(new opt::OptimizeContext(this));
  graph_ = NULL;
}

DModule::~DModule() {
  DModuleUtil::ClearAnnotation(this);
  STLDeleteValues(&sub_modules_);
  delete graph_;
}

opt::OptimizeContext *DModule::GetOptimizeContext() {
  if (parent_mod_) {
    return parent_mod_->GetOptimizeContext();
  }
  return optimize_context_.get();
}

void DModuleUtil::ClearAnnotation(DModule *mod) {
  if (mod->graph_) {
    DGraphUtil::ClearAnnotation(mod->graph_);
  }
}

DModule *DModuleUtil::Create(DModule *parent, const char *name) {
  DModule *mod = new DModule(name, DModule::MODULE_NONE, parent);
  if (parent) {
    parent->sub_modules_.push_back(mod);
  }
  return mod;
}

DChannel *DModuleUtil::CreateChannel(DModule *mod, int data_width) {
  DChannel *chan = new DChannel(data_width);
  mod->channels_.push_back(chan);
  return chan;
}

}  // namespace dfg
