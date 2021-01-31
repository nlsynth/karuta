// -*- C++ -*-
#ifndef _vm_insn_annotator_h_
#define _vm_insn_annotator_h_

#include <map>
#include <set>

#include "vm/common.h"
#include "vm/value.h"

namespace vm {

class InsnAnnotator {
 public:
  InsnAnnotator(VM *vm, Object *obj, Method *method);
  // Called from compiler.
  static void AnnotateMethod(VM *vm, Object *obj, Method *method);

  // Called from AnnotateMethod()
  void DoAnnotate();

  // Annotate for top level execution.
  static void AnnotateBitRangeInsn(Insn *insn);
  static void AnnotateConcatInsn(Insn *insn);
  static void AnnotateNumCalculationOp(Insn *insn);

  static Value::ValueType SymToType(sym_t sym);

 private:
  void ClearType();

  static bool IsTyped(Insn *insn);
  static bool IsTypedReg(Register *reg);
  void TryType(Insn *insn);
  void TypeReturnValues(Insn *insn);
  void TypeMemberAccess(Insn *insn);
  void TypeArrayRead(Insn *insn);
  void PropagateType();
  void TryPropagate(Insn *insn, std::set<Register *> *propagated);

  void SetDstRegType(Value::ValueType vtype, Insn *insn, int idx);

  static void PropagateRegWidth(Register *src1, Register *src2, Register *dst);

  VM *vm_;
  Object *obj_;
  Method *method_;
  std::map<Register *, Object *> objs_;
};

}  // namespace vm

#endif  // _vm_insn_annotator_h_
