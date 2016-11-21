// Front end of the synthesizer.
//
//  Synth
//  -> ObjectSynth DModule
//     -> ThreadSynth DModule, DGraph, DResource
//         -> MethodSynth
//
#include "synth/synth.h"

#include <sys/types.h>
#include <unistd.h>

#include "dfg/resource_params.h"
#include "iroha/i_design.h"
#include "iroha/iroha.h"
#include "pool.h"
#include "synth/channel_synth.h"
#include "synth/object_synth.h"
#include "vm/dmodule_wrapper.h"
#include "vm/object.h"
#include "vm/string_wrapper.h"

namespace synth {

bool Synth::Synthesize(vm::VM *vm, vm::Object *obj, const string &ofn) {
  std::unique_ptr<IDesign> design(new IDesign());

  // Libraries of neon light assumes positive reset.
  iroha::ResourceParams *params = design->GetParams();
  params->SetResetPolarity(true);

  const string &prefix = Env::GetModulePrefix();
  if (!prefix.empty()) {
    params->SetModuleNamePrefix(prefix + "_");
  }

  ChannelSynth channel;

  vector<string> no_task;
  ObjectSynth o(vm, obj, "main", no_task, design.get(), &channel);
  if (!o.Synth()) {
    return false;
  }

  channel.Resolve(design.get());

  DesignTool::Validate(design.get());

  iroha::OptAPI *optimizer = iroha::Iroha::CreateOptimizer(design.get());
  optimizer->ApplyPhase("clean_pseudo_resource");

  WriterAPI *writer = Iroha::CreateWriter(design.get());
  writer->SetLanguage("");
  writer->Write(ofn);
  return true;
}

string Synth::IrPath(vm::Object *obj) {
  vm::Value *value = obj->LookupValue(sym_lookup("$ir_file_name"), false);
  if (value && value->type_ == vm::Value::OBJECT) {
    const string &fn = value->object_->ToString();
    string path;
    if (Env::GetOutputPath(fn.c_str(), &path)) {
      return path;
    }
  }
  char buf[64];
  sprintf(buf, "/tmp/nli-%d-%ld.iroha", getpid(), (long)obj);
  return string(buf);
}

string Synth::GetIrohaCommand(vm::Object *obj) {
  vm::Value *cmd = obj->LookupValue(sym_lookup("$iroha_path"), false);
  if (!cmd || cmd->type_ != vm::Value::OBJECT || !vm::StringWrapper::IsString(cmd->object_)) {
    return Env::GetArgv0();
  }
  return vm::StringWrapper::String(cmd->object_);
}

int Synth::RunIroha(vm::Object *obj, const string &args) {
  string cmd = GetIrohaCommand(obj);
  if (cmd.empty()) {
    return -1;
  }
  string path = IrPath(obj);
  string iopt = string("--iroha -I ") + Env::GetNliDir();
  string e = cmd + " " + iopt + " " +
    path + " " + args;
  cout << "command=" << e << "\n";
  return system(e.c_str());
}

void Synth::WriteHdl(const string &fn, vm::Object *obj) {
  string lang = "-v";
  if (::Util::IsHtmlFileName(fn)) {
    lang = "-h";
  } else if (::Util::IsCCFileName(fn)) {
    lang = "-c";
  }
  string ofn;
  Env::GetOutputPath(fn.c_str(), &ofn);
  string arg = lang + " -s -o " + ofn;
  RunIroha(obj, arg);
}

int Synth::RunIrohaOpt(const string &pass, vm::Object *obj) {
  LOG(DEBUG) << "pass: " << pass;
  string tmp = IrPath(obj) + "~";
  string arg = "-opt " + pass + " -o " + tmp;
  int res = RunIroha(obj, arg);
  if (res) {
    return res;
  }
  return rename(tmp.c_str(), IrPath(obj).c_str());
}

}  // namespace synth
