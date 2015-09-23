#include "writer/cc_module.h"

#include "dfg/dfg.h"
#include "writer/cc_class.h"
#include "writer/cc_graph.h"

namespace writer {

CCModule::CCModule(const string &path, DModule *mod, ostream &os)
  : Writer("cc", mod, os), path_("Mod_" + path) {
}

void CCModule::Output() {
  if (mod_->graph_) {
    for (DResource *r : mod_->graph_->resources_) {
      if (r->array_) {
	OutputArrayDecl(r->name_, r->array_);
      }
    }
  }

  OutputModule();
}

void CCModule::OutputModule() {
  for (DModule *sub_module : mod_->sub_modules_) {
    string sub_module_name = path_ + "_" +  sub_module->module_name_ + "_inst";
    sub_instances_.push_back(sub_module_name);
  }

  cw_.reset(new ClassWriter(path_.c_str(), "NliCCRTBase"));
  OutputChannelInstantiation(mod_);
  cw_->AddMember("", "bool", "finish");
  OutputResetHandler(mod_->graph_);

  for (DModule *sub_module : mod_->sub_modules_) {
    string sub_module_name = path_ + "_" +  sub_module->module_name_;
    cw_->AddMember("", sub_module_name, sub_module_name + "_inst");
  }

  if (mod_->graph_) {
    CCGraph graph_writer(mod_->graph_, cw_.get(), this, os_);
    graph_writer.OutputGraph();
  }
  OutputDispatcher(mod_->graph_);
  OutputStateDumper(mod_->graph_);
  cw_->Output(os_);
}

void CCModule::OutputDispatcher(const DGraph *g) {
  cw_->AddMember("", "bool", "dispatcher()");
  ostream &os = cw_->os();
  if (g) {
    os << "  switch (state) {\n";
    for (DState *ds : g->states_) {
      os << "    case " << ds->state_id_ << ":\n";
      os << "      s_" << ds->state_id_ << "();\n";
      os << "      break;\n";
    }
    os << "  }\n";
  }
  for (vector<string>::iterator it = sub_instances_.begin();
       it != sub_instances_.end(); it++) {
    os << "  finish |= " << *it << ".dispatcher();\n";
  }
  os << "  return finish;\n";
  cw_->EndMethod();
}

void CCModule::OutputStateDumper(const DGraph *g) {
  cw_->AddMember("", "void", "DumpState()");
  if (g) {
    cw_->os() << "  // dumper;\n"
	      << "  printf(\"st=%d\\n\", state);\n";
  } else {
    cw_->os() << "  // dumper;\n";
  }
  cw_->EndMethod();
}

void CCModule::OutputResetHandler(const DGraph *g) {
  cw_->AddMember("", "void", "reset()");
  for (vector<string>::iterator it = sub_instances_.begin();
       it != sub_instances_.end(); it++) {
    cw_->os() << "  " << *it << ".reset();\n";
  }
  if (g) {
    cw_->os() << "  state = "<< g->initial_state_->state_id_ <<";\n";
  }
  cw_->os() << "  finish = false;\n";
  cw_->EndMethod();
}

void CCModule::OutputArrayDecl(const string &name, const DArray *array) {
  char buf[10];
  int len = (1 << array->address_width);
  sprintf(buf, "%d", len);
  ClassWriter cw(name.c_str(), "NliArray", buf);
  ostringstream dtor;
  dtor << "~" <<  name << "() {}";
  cw.AddMember("", "", dtor.str());
  cw.AddMember("", "void", "Init()");
  cw.os() << "  //\n";
  for (int i = 0; i < (int)array->num_.size(); ++i) {;
    if (array->num_[i]) {
      cw.os() << "  image_[" << i << "] = "<< array->num_[i] << ";\n";
    }
  }
  cw.EndMethod();
  cw.Output(os_);
}

void CCModule::OutputChannelInstantiation(const DModule *dmod) {
  for (size_t i = 0; i < dmod->channels_.size(); ++i) {
    DChannel *chan = dmod->channels_[i];
    cw_->AddMember("", "NliChannel", chan->name_ + "_channel_inst",
		   "\"" + chan->name_ + "\"");
  }
}

}  // namespace writer
