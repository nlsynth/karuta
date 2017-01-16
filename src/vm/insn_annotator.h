// -*- C++ -*-
#ifndef _vm_insn_annotator_h_
#define _vm_insn_annotator_h_

#include "vm/common.h"
#include "vm/value.h"

namespace vm {

class InsnAnnotator {
public:
  InsnAnnotator(VM *vm, Object *obj, Method *method);
  static void AnnotateMethod(VM *vm, Object *obj, Method *method);

  void DoAnnotate();

  // Add declared type by the compiler.
  static void AnnotateByDecl(VM *vm, fe::VarDecl *decl,
			     Register *reg);
  // Sets the type of the result from OP_MEMBER_READ.
  static void AnnotateByValue(Value *value, Register *reg);
  // top level executor to set type of declared member dynamically
  static void AnnotateValueType(fe::VarDecl *decl, Value *value);

private:
  void AnnotateType();
  void AnnotateWidth();

  void AnnotateInsnType(Insn *insn);

  void SetDstRegType(Value::ValueType vtype, Insn *insn, int idx);

  static void AnnotateCalcWidth(VM *vm, Object *obj, Method *method);
  static void EnforceValueWidth(VM *vm, Object *obj, Method *method);
  static void PropagateVarWidthAll(VM *vm, Object *obj, Method *method);
  static void PropagateRegWidth(Register *src1, Register *src2, Register *dst);
  static Value::ValueType SymToType(sym_t sym);
  static void PropagateDeclaredWidth(Insn *insn);

  VM *vm_;
  Object *obj_;
  Method *method_;
};

}  // namespace vm

#endif  // _vm_insn_annotator_h_
