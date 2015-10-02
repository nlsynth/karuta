#include "writer/cc_graph.h"

#include "dfg/dfg.h"
#include "stl_util.h"
#include "writer/cc_class.h"
#include "writer/cc_state.h"
#include "writer/cc_writer.h"
#include "writer/module_template.h"
#include "writer/writer.h"

namespace writer {

CCGraph::CCGraph(DGraph *graph, ClassWriter *cw,
		 ModuleTemplate *tmpl, ostream &os)
  : graph_(graph), tmpl_(tmpl), os_(os), cw_(cw) {
}
 
CCGraph::~CCGraph() {
  STLDeleteSecondElements(&state_writers_);
}

void CCGraph::PreProcess() {
  for (DState *ds : graph_->states_) {
    state_writers_[ds] = new CCState(ds, cw_);
    state_writers_[ds]->PreProcess(tmpl_);
  }

  ostream &ss =
    tmpl_->GetStream(ModuleTemplate::STATE_SWITCH);
  ss << "  switch (state) {\n";
  for (DState *ds : graph_->states_) {
    ss << "    case " << ds->state_id_ << ":\n"
       << "      s_" << ds->state_id_ << "();\n"
       << "      break;\n";
  }
  ss << "    case kIdleState:\n"
     << "      break;\n";
  ss << "  }\n";

  ostream &sr = tmpl_->GetStream(ModuleTemplate::RESET_STATE);
  sr << "  state = ";
  if (graph_->owner_module_->module_type_ == DModule::MODULE_TASK) {
    sr << "kIdleState";
  } else {
    sr << graph_->initial_state_->state_id_;
  }
  sr << ";\n";
  if (graph_->owner_module_->module_type_ == DModule::MODULE_TASK) {
    sr << "  task_req_ = false;\n";
  }

  ostream &sd = tmpl_->GetStream(ModuleTemplate::STATE_DUMPER);
  sd << "  printf(\"st=%d\\n\", state);\n";

  if (graph_->owner_module_->module_type_ == DModule::MODULE_TASK) {
    ostream &ps = tmpl_->GetStream(ModuleTemplate::POST_STATE);
    ps << "  if (task_req_ && state == kIdleState) {\n"
       << "    task_req_ = false;\n"
       << "    state = " << graph_->initial_state_->state_id_ << ";\n"
       << "  }\n";
  }
}

void CCGraph::Output() {
  // state variable
  cw_->AddMember("", "int", "state");
  if (graph_->owner_module_->module_type_ == DModule::MODULE_TASK) {
    cw_->AddMember("", "bool", "task_req_");
  }
  OutputRegisters();
  OutputArrayInstantiation();

  for (DState *st : graph_->states_) {
    state_writers_[st]->Output();
  }
}

void CCGraph::OutputRegisters() {
  for (DRegister *reg : graph_->registers_) {
    if (reg->reg_type_ == DRegister::REG_NORMAL) {
      cw_->AddMember("", "uint64_t", reg->reg_name_);
    }
  }
}

void CCGraph::OutputArrayInstantiation() {
  for (DResource *r : graph_->resources_) {
    if (r->array_) {
      const string name = r->name_;
      cw_->AddMember("", name, name + "_inst");
    }
  }
}

}  // namespace writer
