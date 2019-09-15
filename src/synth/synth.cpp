// Front end of the synthesizer.
//
//  Synth
//    DesignSynth IDesign
//    -> ObjectSynth IModule
//       -> ThreadSynth ITable, IResource
//         -> MethodSynth
//
#include "synth/synth.h"

#include <sys/types.h>
#include <unistd.h>

#include "base/util.h"
#include "iroha/iroha.h"
#include "synth/design_synth.h"
#include "synth/object_attr_names.h"
#include "vm/object.h"
#include "vm/object_util.h"
#include "vm/string_wrapper.h"

namespace synth {

bool Synth::Synthesize(vm::VM *vm, vm::Object *obj, const string &ofn) {
  DesignSynth design_synth(vm, obj);
  LOG(INFO) << "Synthesize start";
  if (!design_synth.Synth()) {
    return false;
  }
  LOG(INFO) << "Synthesize done";

  WriterAPI *writer = Iroha::CreateWriter(design_synth.GetIDesign());
  writer->SetLanguage("");
  writer->Write(ofn);
  return true;
}

string Synth::IrPath(vm::Object *obj) {
  string fn = vm::ObjectUtil::GetStringMember(obj, kIrFileName);
  if (!fn.empty()) {
    string path;
    if (Env::GetOutputPath(fn.c_str(), &path)) {
      return path;
    }
  }
  char buf[128];
  sprintf(buf, "/tmp/karuta-%d-%ld.iroha", getpid(), (long)obj);
  return string(buf);
}

string Synth::GetIrohaCommand(vm::Object *obj) {
  string cmd = vm::ObjectUtil::GetStringMember(obj, kIrohaPath);
  if (cmd.empty()) {
    const string &bin = Env::GetIrohaBinPath();
    if (!bin.empty()) {
      return bin;
    }
    return Env::GetArgv0();
  }
  return cmd;
}

int Synth::RunIroha(vm::Object *obj, const string &args) {
  string cmd = GetIrohaCommand(obj);
  if (cmd.empty()) {
    return -1;
  }
  string path = IrPath(obj);
  string iopt = "--iroha";
  auto dirs = Env::SearchDirList();
  for (auto &d : dirs) {
    iopt += " -I " + d;
  }
  string d = GetDumpPath(obj);
  if (!d.empty()) {
    iopt += " -d " + d;
  }
  string e = cmd + " " + iopt + " " +
    path + " " + args;
  cout << "command=" << e << "\n";
  LOG(INFO) << "Executing iroha";
  int r = system(e.c_str());
  LOG(INFO) << "Done";
  return r;
}
  
void Synth::WriteHdl(const string &fn, vm::Object *obj) {
  string lang = "-v";
  if (::Util::IsHtmlFileName(fn)) {
    lang = "-h";
  } else if (::Util::IsDotFileName(fn)) {
    lang = "-dot";
  } else if (::Util::IsIrFileName(fn)) {
    lang = "";
  }
  string ofn;
  Env::GetOutputPath(fn.c_str(), &ofn);
  string arg = lang;
  if (Env::GetWithSelfShell()) {
    arg += " -S";
  } else {
    arg += " -s";
  }
  if (Env::GetVcdOutput()) {
    arg += " -vcd";
  }

  arg += " -o " + ofn;
  RunIroha(obj, arg);
  const string &marker = Env::GetOutputMarker();
  if (!marker.empty()) {
    cout << marker << fn << "\n";
  }
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

string Synth::GetDumpPath(vm::Object *obj) {
  return vm::ObjectUtil::GetStringMember(obj, kDumpFileName);
}

}  // namespace synth
