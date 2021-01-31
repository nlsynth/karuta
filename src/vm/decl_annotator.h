// -*- C++ -*-
#ifndef _vm_decl_annotator_h_
#define _vm_decl_annotator_h_

#include "vm/common.h"

namespace vm {

class DeclAnnotator {
 public:
  // Add declared type by the compiler.
  static void AnnotateByDecl(VM *vm, fe::VarDecl *decl, Register *reg);

  // Sets the type of the result from OP_MEMBER_READ.
  static void AnnotateByValue(Value *value, Register *reg);
  // top level executor to set type of declared member dynamically
  static void AnnotateValueType(VM *vm, fe::VarDecl *decl, Value *value);
};

}  // namespace vm

#endif  // _vm_insn_annotator_h_
