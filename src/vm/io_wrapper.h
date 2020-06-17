// -*- C++ -*-
#ifndef _vm_io_wrapper_h_
#define _vm_io_wrapper_h_

#include "vm/common.h"

namespace vm {

class IOWrapper {
public:
  static Object *NewIOWrapper(VM *vm, sym_t name, bool is_output,
			      const iroha::NumericWidth &width);
};

}  // namespace vm

#endif  // _vm_io_wrapper_h_
