// -*- C++ -*-
#ifndef _annotation_checker_h_
#define _annotation_checker_h_
#include "compiler/common.h"

namespace compiler {
class AnnotationChecker {
 public:
  static void Check(vm::Insn *insn);
};
}  // namespace compiler

#endif  // _annotation_checker_h_
