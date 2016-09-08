// -*- C++ -*-
#ifndef _isynth_method_synth_h_
#define _isynth_method_synth_h_

#include "isynth/common.h"

#include <map>

using std::map;

namespace isynth {

class MethodSynth {
public:
  MethodSynth(ThreadSynth *thr_synth,
	      const string &method_name, ITable *tab, ResourceSet *res);
  virtual ~MethodSynth();

  bool Synth();
  MethodContext *GetContext();

private:
  void SynthNativeMethod(vm::Method *method);
  void SynthEmbeddedMethod(vm::Method *method);

  void SynthInsn(vm::Insn *insn);

  void SynthNop(vm::Insn *insn);
  void SynthNum(vm::Insn *insn);
  void SynthAssign(vm::Insn *insn);
  void SynthLoadObj(vm::Insn *insn);
  void SynthFuncall(vm::Insn *insn);
  void SynthBinCalcExpr(vm::Insn *insn);
  void SynthGoto(vm::Insn *insn);

  void EmitEntryInsn(vm::Method *method);

  ThreadSynth *thr_synth_;
  const string method_name_;
  ITable *tab_;
  ResourceSet *res_;
  vm::VM *vm_;
  vm::Object *obj_;
  std::unique_ptr<MethodContext> context_;

  // VM -> Iroha mapping.
  map<vm::Register *, IRegister *> local_reg_map_;
  map<vm::Register *, sym_t> orig_name_map_;
  map<vm::Register *, vm::Object *> member_reg_to_obj_map_;

  IRegister *FindLocalVarRegister(vm::Register *vreg);
  IRegister *FindArgRegister(int nth, fe::VarDecl *arg_decl);
  StateWrapper *AllocState();
  void LinkStates();
};

}  // namespace isynth

#endif  // _isynth_method_synth_h_
