// -*- C++ -*-
#ifndef _vm_insn_annotator_h_
#define _vm_insn_annotator_h_

#include "vm/common.h"
#include "vm/value.h"

#include <map>
#include <set>

namespace vm {

class InsnAnnotator {
public:
  InsnAnnotator(VM *vm, Object *obj, Method *method);
  // Called from compiler.
  static void AnnotateMethod(VM *vm, Object *obj, Method *method);

  // Called from AnnotateMethod()
  void DoAnnotate();

  // Add declared type by the compiler.
  static void AnnotateByDecl(VM *vm, fe::VarDecl *decl,
			     Register *reg);
  // Sets the type of the result from OP_MEMBER_READ.
  static void AnnotateByValue(Value *value, Register *reg);
  // top level executor to set type of declared member dynamically
  static void AnnotateValueType(VM *vm, fe::VarDecl *decl, Value *value);

private:
  void ClearType();

  static bool IsTyped(Insn *insn);
  static bool IsTypedReg(Register *reg);
  void TryType(Insn *insn);
  void TypeReturnValues(Insn *insn);
  void PropagateType();
  void TryPropagate(Insn *insn, std::set<Register *> *propagated);

  void SetDstRegType(Value::ValueType vtype, Insn *insn, int idx);

  static void PropagateRegWidth(Register *src1, Register *src2, Register *dst);
  static Value::ValueType SymToType(sym_t sym);

  VM *vm_;
  Object *obj_;
  Method *method_;
  std::map<Register *, Object *> objs_;
};

}  // namespace vm

#endif  // _vm_insn_annotator_h_
