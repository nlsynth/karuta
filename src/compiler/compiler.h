// -*- C++ -*-
#ifndef _compiler_compiler_h_
#define _compiler_compiler_h_

#include "compiler/common.h"

namespace compiler {

struct CompileOptions {
  CompileOptions() : run(false) {
  }
  // Calls run() at the end.
  bool run;
  // Calls compile() and writeHdl(output).
  string output;
};

class Compiler {
public:
  static void CompileMethod(vm::VM *vm, vm::Object *obj,
			    vm::Method *method);
  // Compiles toplevel.
  static vm::Method *CompileParseTree(vm::VM *vm, vm::Object *obj,
				      const CompileOptions &opts,
				      const fe::Method *parse_tree);

  static void SetByteCodeDebug(string flags);

private:
  static void CompileMethodWithOpts(vm::VM *vm, vm::Object *obj,
				    const CompileOptions &opts,
				    vm::Method *method);
};

}  // namespace compiler

#endif  // _compiler_compiler_h_
