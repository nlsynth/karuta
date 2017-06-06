// -*- C++ -*-
#ifndef _compiler_common_h_
#define _compiler_common_h_

#include "nli.h"

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
class ExprCompiler;
}  // namespace compiler

#endif  // _compiler_common_h_
