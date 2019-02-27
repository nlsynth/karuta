// -*- C++ -*-
#ifndef _compiler_compiler_h_
#define _compiler_compiler_h_

#include "compiler/common.h"

namespace compiler {

class Compiler {
public:
  static void CompileMethod(vm::VM *vm, vm::Object *obj,
			    vm::Method *method);
  // Compiles toplevel.
  static vm::Method *CompileParseTree(vm::VM *vm, vm::Object *obj,
				      const fe::Method *parse_tree);

  static void SetByteCodeDebug(bool enable);
};

}  // namespace compiler

#endif  // _compiler_compiler_h_
