// -*- C++ -*-
#ifndef _synth_synth_h_
#define _synth_synth_h_

#include "nli.h"

namespace dfg {
class DGraph;
class DModule;
}  // namespace dfg
using namespace dfg;

namespace vm {
class Object;
class VM;
}  // namespace vm

namespace synth {

class Synth {
public:
  Synth(vm::VM *vm, vm::Object *obj);

  bool Compile(const string &phase);

  static bool Synthesize(vm::VM *vm, const string &phase, vm::Object *obj);
  static void WriteHdl(const string &fn, vm::Object *obj);
  static string IrPath(vm::Object *obj);

private:
  DModule *SynthModule();
  void SetDumpFileName(DModule *module);
  void SetSynthParams(DModule *module);

  vm::VM *vm_;
  vm::Object *obj_;
};

}  // namespace synth

#endif  // _synth_synth_h_
