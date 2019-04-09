// -*- C++ -*-
#ifndef _compiler_common_h_
#define _compiler_common_h_

#include "karuta.h"

namespace fe {
class Expr;
class Method;
class Stmt;
class VarDecl;
class VarDeclSet;
}  // namespace fe

namespace vm {
class Insn;
class Method;
class Object;
class Register;
class RegisterType;
class VM;
class Value;
}  // namespace vm

namespace compiler {
class Compiler;
class CompileOptions;
class ExprCompiler;
class MethodCompiler;

class RegisterTuple {
public:
  RegisterTuple() {
  }
  explicit RegisterTuple(vm::Register *reg) {
    if (reg != nullptr) {
      regs.push_back(reg);
    }
  }
  // only for transition period from one vm::Register to RegisterTuple.
  vm::Register *GetOne() {
    if (regs.size() == 1) {
      return regs[0];
    }
    return nullptr;
  }
  vector<vm::Register *> regs;
};

}  // namespace compiler

#endif  // _compiler_common_h_
