// -*- C++ -*-
#ifndef _vm_method_frame_h_
#define _vm_method_frame_h_

#include "vm/common.h"

namespace vm {

class MethodFrame {
public:
  Method *method_;
  size_t pc_;
  Object *obj_;
  vector<Value> reg_values_;
  // callee writes here.
  vector<Value> returns_;
};

}  // namespace vm

#endif  // _vm_method_frame_h_
