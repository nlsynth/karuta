// -*- C++ -*-
#ifndef _vm_insn_annotator_h_
#define _vm_insn_annotator_h_

#include "vm/common.h"
#include "vm/value.h"

namespace vm {

class InsnAnnotator {
public:
  static void Annotate(VM *vm, Object *obj, Method *method);
  static void AnnotateByDecl(VM *vm, fe::VarDecl *decl,
			     Register *reg);
  static void AnnotateValueType(fe::VarDecl *decl, Value *value);
  static void AnnotateByValue(Value *value, Register *reg);

private:
  static void AnnotateType(VM *vm, Object *obj, Method *method);
  static void AnnotateWidth(VM *vm, Object *obj, Method *method);

  static void AnnotateCalcWidth(VM *vm, Object *obj, Method *method);
  static void EnforceValueWidth(VM *vm, Object *obj, Method *method);
  static void PropagateVarWidthAll(VM *vm, Object *obj, Method *method);
  static void PropagateRegWidth(Register *src1, Register *src2, Register *dst);
  static Value::ValueType SymToType(sym_t sym);
  static void PropagateDeclaredWidth(Insn *insn);
};

}  // namespace vm

#endif  // _vm_insn_annotator_h_
