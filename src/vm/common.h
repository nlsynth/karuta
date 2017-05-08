// -*- C++ -*-
#ifndef _vm_common_h_
#define _vm_common_h_

#include "nli.h"

class Annotation;
class DumpStream;

namespace fe {
class ArrayInitializer;
class Expr;
class Method;
class VarDecl;
class Stmt;
}  // namespace fe

namespace numeric {
class Width;
}  // namespace numeric

namespace vm {

class EnumType;
class Executor;
class ExecutorToplevel;
class Insn;
class IntArray;
class Method;
class MethodFrame;
class Object;
class Register;
class Thread;
class Value;
class VM;

}  // namespace vm

#endif  // _vm_common_h_
