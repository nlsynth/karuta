// -*- C++ -*-
#ifndef _synth_method_synth_h_
#define _synth_method_synth_h_

#include "synth/insn_walker.h"

#include <map>

using std::map;

namespace synth {

class MethodSynth : public InsnWalker {
public:
  MethodSynth(ThreadSynth *thr_synth,
	      vm::Object *obj, const string &method_name,
	      ITable *tab, ResourceSynth *rsynth, ResourceSet *res);
  virtual ~MethodSynth();

  bool Synth();
  MethodContext *GetContext();
  void SetTaskEntry();
  void SetRoot(int thread_index);
  bool IsDataFlowEntry() const;
  bool IsExtEntry() const;
  bool IsThreadEntry() const;

  // for ObjectMethod
  ResourceSet *GetResourceSet();
  StateWrapper *AllocState();
  IRegister *FindLocalVarRegister(vm::Register *vreg);
  ITable *GetITable();
  ThreadSynth *GetThreadSynth();

private:
  bool SynthFromInsns();
  void SynthAlternativeImplMethod(vm::Method *method);
  void SynthEmbeddedMethod(vm::Method *method);
  void SynthExtIOMethod();
  void DoSynthExtIO(bool is_output);

  void SynthInsn(vm::Insn *insn);

  void SynthNop(vm::Insn *insn);
  void SynthNum(vm::Insn *insn);
  void SynthAssign(vm::Insn *insn);
  void SynthLoadObj(vm::Insn *insn);
  void SynthFuncall(vm::Insn *insn);
  void SynthFuncallDone(vm::Insn *insn);
  void SynthBinCalcExpr(vm::Insn *insn);
  void SynthBitInv(vm::Insn *insn);
  void SynthShiftExpr(vm::Insn *insn);
  void SynthIf(vm::Insn *insn);
  void SynthGoto(vm::Insn *insn);
  void SynthMemberAccess(vm::Insn *insn, bool is_store);
  void SynthMemberRegAccess(vm::Insn *insn, vm::Value *value, bool is_store);
  void SynthMemberSharedRegAccess(vm::Insn *insn, vm::Object *owner_obj,
				  vm::Value *value, bool is_store);
  void SynthArrayAccess(vm::Insn *insn, bool is_write);
  bool UseSharedArray(vm::Object *array_obj);
  void SynthSharedArrayAccess(vm::Insn *insn, bool is_write);
  void SynthBitRange(vm::Insn *insn);
  void SynthConcat(vm::Insn *insn);
  void SynthPreIncDec(vm::Insn *insn);
  void SynthNative(vm::Insn *insn);

  void GenNeg(IRegister *src, IRegister *dst);
  void EmitSignatureInsn(vm::Method *method);
  void EmitDataFlowEntry(IState *st);
  void EmitTaskEntry(IState *st);
  void EmitTaskReturn(IState *last);
  void EmitExtTaskEntry(IState *st);
  void EmitExtTaskDone(IState *last);
  void MayEmitThreadIndex(IState *st);
  // Data flow call uses one shared-reg to pass multiple arguments,
  // so the width of each argument should be exactly same as
  // the callee. This function allocate a register with appropriate width
  // and copies arguments, if necessary.
  // Ext-task and flow also requires exactly same width.
  // TODO: Fix this in compiler side.
  void AdjustArgWidth(vm::Insn *insn, vector<IRegister *> *args);

  ThreadSynth *thr_synth_;
  const string method_name_;
  ITable *tab_;
  ResourceSynth *rsynth_;
  ResourceSet *res_set_;
  std::unique_ptr<MethodContext> context_;
  vm::Method *method_;
  bool is_task_entry_;
  bool is_root_;
  int thread_index_;

  // VM -> Iroha mapping.
  map<vm::Register *, IRegister *> local_reg_map_;
  map<string, IRegister *> member_name_reg_map_;

  map<int, StateWrapper *> vm_insn_state_map_;

  IRegister *FindArgRegister(vm::Method *method, int nth,
			     fe::VarDecl *arg_decl);
  void ResolveJumps();
  void LinkStates();
  void InsnToCalcValueType(vm::Insn *insn, IValueType *vt);
};

}  // namespace synth

#endif  // _synth_method_synth_h_
