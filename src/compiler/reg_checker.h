// -*- C++ -*-
#ifndef _compiler_reg_checker_h_
#define _compiler_reg_checker_h_

#include "compiler/common.h"

namespace compiler {

class RegChecker {
public:
  RegChecker(vm::Method *method);

  // Checks if return values are set.
  // NOTE: This check is performed against the byte code sequence.
  // This also can be possibly done with the parse tree.
  // (we might implement other checks with parse tree)
  void Check();

private:
  vm::Method *method_;
};

}  // namespace compiler

#endif  // _compiler_reg_checker_h_
