#include "writer/cc_module.h"

#include "dfg/dfg.h"
#include "writer/cc_class.h"
#include "writer/cc_graph.h"
#include "writer/module_template.h"

namespace writer {

CCModule::CCModule(const string &path, DModule *mod, ostream &os)
  : mod_(mod), os_(os), path_("Mod_" + path) {
  template_.reset(new ModuleTemplate);
}

CCModule::~CCModule() {
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
    string sub_module_name = SubModuleName(sub_module) + "_inst";
    sub_instances_.push_back(sub_module_name);
  }

  cw_.reset(new ClassWriter(path_.c_str(), "NliCCRTBase"));

  std::unique_ptr<CCGraph> graph_writer;
  if (mod_->graph_) {
    graph_writer.reset(new CCGraph(mod_->graph_, cw_.get(),
				   template_.get()));
    graph_writer->PreProcess();
  }

  OutputChannelInstantiation(mod_);

  for (DModule *sub_module : mod_->sub_modules_) {
    string sub_module_class = path_ + "_" + sub_module->module_name_;
    cw_->AddMember("", sub_module_class, sub_module->module_name_ + "_inst");
  }

  if (mod_->graph_) {
    graph_writer->Output();
  }
  OutputResetHandler();
  OutputTaskEntry();
  OutputPostState();
  OutputDispatcher();
  OutputStateDumper();
  cw_->Output(os_);
}

void CCModule::OutputDispatcher() {
  cw_->AddMember("", "bool", "Dispatch()");
  ostream &os = cw_->os();
  os << template_->GetContents(ModuleTemplate::STATE_SWITCH);
  for (const string &inst : sub_instances_) {
    os << "  finish_ |= " << inst << ".Dispatch();\n";
  }
  os << "  return finish_;\n";
  cw_->EndMethod();
}

void CCModule::OutputPostState() {
  cw_->AddMember("", "void", "PostState()");
  cw_->os() << "  //\n"
	    << template_->GetContents(ModuleTemplate::POST_STATE);
  for (const string &inst : sub_instances_) {
    cw_->os() << "  " << inst << ".PostState();\n";
  }
  cw_->EndMethod();
}

void CCModule::OutputStateDumper() {
  cw_->AddMember("", "void", "DumpState()");
  cw_->os() << "  // dumper;\n"
	    << template_->GetContents(ModuleTemplate::STATE_DUMPER);
  for (const string &inst : sub_instances_) {
    cw_->os() << "  " << inst << ".DumpState();\n";
  }
  cw_->EndMethod();
}

void CCModule::OutputResetHandler() {
  cw_->AddMember("", "void", "reset()");
  for (const string &inst : sub_instances_) {
    cw_->os() << "  " << inst << ".reset();\n";
  }
  cw_->os() << template_->GetContents(ModuleTemplate::RESET_STATE);
  cw_->os() << "  finish_ = false;\n";
  cw_->EndMethod();
}

void CCModule::OutputTaskEntry() {
  if (mod_->module_type_ == DModule::MODULE_TASK) {
    cw_->AddMember("", "bool", TaskEntryFunctionName(mod_) + "_Ready()");
    ostream &os = cw_->os();
    os << "  return (state == kIdleState);\n";
    cw_->EndMethod();

    cw_->AddMember("", "void", TaskEntryFunctionName(mod_) + "_En()");
    os << "  task_req_ = true;\n";
    cw_->EndMethod();
  }
  if (mod_->module_type_ == DModule::MODULE_CONTAINER) {
    for (DModule *sub_module : mod_->sub_modules_) {
      string entry_func = TaskEntryFunctionName(sub_module) + "_Ready()";
      cw_->AddMember("", "bool", entry_func);
      ostream &os = cw_->os();
      os << "  return " << SubModuleName(sub_module) << "_inst."
	 << entry_func << ";\n";
      cw_->EndMethod();

      string req_func = TaskEntryFunctionName(sub_module) + "_En()";
      cw_->AddMember("", "void", req_func);
      os << "  return " << SubModuleName(sub_module) << "_inst."
	 << req_func << ";\n";
      cw_->EndMethod();
    }
  }
}

string CCModule::TaskEntryFunctionName(DModule *mod) {
  return "Task_" + mod->parent_mod_->module_name_ + "_" +
    mod->module_name_;
}

string CCModule::SubModuleName(DModule *mod) {
  return mod->module_name_;
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
