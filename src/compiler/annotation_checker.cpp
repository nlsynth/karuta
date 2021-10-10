#include "compiler/annotation_checker.h"

#include "vm/insn.h"
#include "vm/opcode.h"

namespace compiler {

void AnnotationChecker::Check(vm::Insn *insn) {
  vm::OpCode op = insn->op_;
  switch (op) {
    case vm::OP_TL_FUNCDECL:
      CheckMethodDecl(insn);
      break;
    case vm::OP_TL_CHANNEL_DECL:
      CheckChannelDecl(insn);
      break;
    case vm::OP_TL_MAILBOX_DECL:
      CheckMailboxDecl(insn);
      break;
    case vm::OP_TL_VARDECL:
      CheckVarDecl(insn);
      break;
    default:
      break;
  }
}

void AnnotationChecker::CheckMethodDecl(vm::Insn *insn) {}
void AnnotationChecker::CheckThreadDecl(vm::Insn *insn) {}
void AnnotationChecker::CheckChannelDecl(vm::Insn *insn) {}
void AnnotationChecker::CheckMailboxDecl(vm::Insn *insn) {}
void AnnotationChecker::CheckVarDecl(vm::Insn *insn) {}

}  // namespace compiler
