// -*- C++ -*-
#ifndef _synth_thread_synth_h_
#define _synth_thread_synth_h_

#include "nli.h"

#include <map>

using std::map;

namespace dfg {
class DGraph;
class DInsn;
class DModule;
class DRegister;
class DState;
}  // namespace dfg
using namespace dfg;

namespace vm {
class Object;
class VM;
}  // namespace vm

namespace synth {

class MethodSynth;
class ResourceSet;

struct CopiedFunctionStates {
  DState *initial;
  DState *final;
};

class ThreadSynth {
public:
  ThreadSynth(vm::VM *vm, vm::Object *obj, DModule *module,
	      const char *method_name);
  virtual ~ThreadSynth();

  bool Synth();

  void ExpandFunctions();
  void AddMemberInitializers();

  DModule *GetModule();
  ResourceSet *GetResource();

private:
  vm::VM *vm_;
  vm::Object *obj_;
  DModule *module_;
  const string method_name_;
  DGraph *graph_;
  MethodSynth *root_method_synth_;
  std::unique_ptr<ResourceSet> resource_;
  map<sym_t, MethodSynth *> function_map_;

  bool ExpandOneFunction(MethodSynth *func);

  CopiedFunctionStates CopyFunction(MethodSynth *func, DInsn *call_insn);
  void CopyStates(map<DState *, DState *> &state_mapping, MethodSynth *func,
		  map<DRegister *, DRegister *> *reg_mapping);
  void RewriteArgs(DInsn *call_insn, DState *callee_state,
		   map<DRegister *, DRegister *> *reg_mapping);
  void CopyInsnRegs(DInsn *src, vector<DRegister *> *orig_regs,
		    vector<DRegister *> *new_regs,
		    map<DRegister *, DRegister *> *reg_map);
};

}  // namespace synth

#endif  // _synth_thread_synth_h_
