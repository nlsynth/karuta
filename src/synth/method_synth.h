// -*- C++ -*-
#ifndef _synth_method_synth_h_
#define _synth_method_synth_h_

#include "nli.h"

#include <map>
#include <set>

using std::map;
using std::set;

namespace dfg {
class DGraph;
class DInsn;
class DRegister;
class DResource;
class DState;
class DType;
class ImportedResource;
}  // namespace dfg
using namespace dfg;

namespace vm { 
class Insn;
class Method;
class Object;
class Register;
class VM;
}  // namespace vm

namespace fe {
class VarDecl;
}  // namespace fe

namespace synth {

class ObjectSynth;
class ResourceSet;

class MethodSynth {
public:
  MethodSynth(vm::VM *vm, vm::Object *obj,
	      const char *method_name,
	      bool is_task_root,
	      ResourceSet *resource, 
	      DGraph *graph);
  virtual ~MethodSynth();

  bool Synth();

  DState *InitialState();
  DState *LastState();

  vector<DState *> &AllStates();

  set<sym_t> GetCalledFunctions();

private:
  vm::VM *vm_;
  vm::Object *obj_;
  const char *method_name_;
  bool is_task_root_;
  ResourceSet *resource_;
  DGraph *graph_;

  // VM -> D mapping.
  map<vm::Register *, DRegister *> local_reg_map_;
  map<sym_t, DRegister *> member_reg_map_;
  map<vm::Register *, sym_t> orig_name_map_;

  map<vm::Register *, vm::Object *> member_reg_to_obj_map_;

  vm::Method *method_;
  int current_zinsn_index_;
  map<int, DState *> zinsn_dstate_map_;
  vector<DState *> all_states_;

  struct JumpEntry {
    DInsn *insn;
    int target;
  };
  vector<JumpEntry> jumps_;

  set<sym_t> called_functions_;

  DRegister *FindLocalVarRegister(vm::Register *reg);
  DRegister *FindArgRegister(fe::VarDecl *arg_decl);
  DState *AllocState();
  void ResolveJumps();
  void LinkStates();

  void SynthInsn(vm::Insn *insn);

  void SynthNum(vm::Insn *insn);
  void SynthFuncall(vm::Insn *insn);
  void SynthIf(vm::Insn *insn);
  void SynthGoto(vm::Insn *insn);
  void SynthPreIncDec(vm::Insn *insn);
  void SynthLoadObj(vm::Insn *insn);

  void SynthAssign(vm::Insn *insn);
  void SynthBinCalcExpr(vm::Insn *insn);
  void SynthShiftExpr(vm::Insn *insn);
  void SynthConcat(vm::Insn *insn);
  void SynthBitRange(vm::Insn *insn);
  void SynthLogicInv(vm::Insn *insn);
  void SynthMemberAccess(vm::Insn *insn, bool is_store);
  void SynthArrayAccess(vm::Insn *insn, bool is_write, bool is_memory);
  void SynthChannelRead(vm::Insn *insn);
  void SynthChannelWrite(vm::Insn *insn);

  DInsn *EmitEntryInsn(vm::Method *method);
  void EmitTaskFinishInsn();
  void EmitOneAssign(vm::Register *lhs, vm::Register *rhs);
  void RequestFunction(vm::Object *callee_obj, sym_t name);
  void InitializeArrayResource(DResource *res, vm::Insn *insn,
			       sym_t array_name);

  void SynthNativeMethod(vm::Method *method);

  void GenNeg(DRegister *src, DRegister *dst);
  // used for shift and range select operator.
  void GenBitSelect(DRegister *src, int src_msb, int src_lsb,
		    int dst_width, DRegister *res_reg);
  DRegister *GenConcat(DRegister *lhs, DRegister *rhs, DRegister *res);
  DType *InsnToCalcDType(vm::Insn *insn);
};

}  // namespace synth

#endif  // _synth_method_synth_h_
