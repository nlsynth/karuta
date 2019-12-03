// -*- C++ -*-
#ifndef _vm_executor_executor_h_
#define _vm_executor_executor_h_

#include "vm/executor/decl.h"

namespace vm {
namespace executor {

class Executor : public Decl {
public:
  Executor(Thread *thread, MethodFrame *frame) : Decl(thread, frame) {
  }

  bool ExecInsn(Insn *insn);

private:
};

}  // namespace executor
}  // namespace vm

#endif  // _vm_executor_executor_h_
