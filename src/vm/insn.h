// -*- C++ -*-
#ifndef _vm_insn_h_
#define _vm_insn_h_

#include "vm/common.h"
#include "vm/opcode.h"

namespace vm {

class Insn {
 public:
  Insn();
  void Dump() const;
  void Dump(DumpStream &ds) const;

  enum OpCode op_;
  vector<Register *> dst_regs_;
  vector<Register *> src_regs_;
  Register *obj_reg_;
  Method *method_;
  int jump_target_;
  // Extra information from the parse tree.
  sym_t label_;
  fe::Expr *insn_expr_;
  fe::Stmt *insn_stmt_;
};

class InsnType {
 public:
  // (int or enum), (int or enum) -> bool
  static bool IsComparison(int op);
  // int, int -> int (same width)
  static bool IsSameWidthNumBinOp(int op);
  // int, int' -> int
  static bool IsShift(int op);
};

class InsnOpUtils {
 public:
  static const string Str(Insn *insn);
};

class ByteCodeDebugMode {
 public:
  // Dumps before the execution and the type annotation.
  static bool PreExec(const string &flags);
  static bool IsEnabled(const string &flags);
};

}  // namespace vm

#endif  // _vm_insn_h_
