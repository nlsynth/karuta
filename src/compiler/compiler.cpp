// Compiles a parse tree into vm instructions.
#include "compiler/compiler.h"

#include "base/status.h"
#include "compiler/method_compiler.h"
#include "fe/method.h"
#include "vm/method.h"
#include "vm/vm.h"

namespace compiler {

void Compiler::CompileMethod(vm::VM *vm, vm::Object *obj,
			     vm::Method *method) {
  CompileOptions opts;
  CompileMethodWithOpts(vm, obj, opts, method);
}

vm::Method *Compiler::CompileParseTree(vm::VM *vm, vm::Object *obj,
				       const CompileOptions &opts,
				       const fe::Method *parse_tree) {
  vm::Method *method = vm->NewMethod(true /* toplevel */);
  method->SetParseTree(parse_tree);
  CompileMethodWithOpts(vm, obj, opts, method);
  return method;
}

void Compiler::SetByteCodeDebug(string flags) {
  MethodCompiler::SetByteCodeDebug(flags);
}

void Compiler::CompileMethodWithOpts(vm::VM *vm, vm::Object *obj,
				     const CompileOptions &opts,
				     vm::Method *method) {
  if (method->GetParseTree() == nullptr) {
    // native method.
    return;
  }
  std::unique_ptr<MethodCompiler>
    compiler(new MethodCompiler(opts, vm, obj, method));
  compiler->Compile();
  if (Status::CheckAllErrors(false)) {
    auto *parse_tree = method->GetParseTree();
    Status::os(Status::USER_ERROR)
      << "Failed in compilation of method: "
      << parse_tree->GetName();
  }
}

}  // namespace compiler
