// -*- C++ -*-
#ifndef _vm_string_wrapper_h_
#define _vm_string_wrapper_h_

#include "nli.h"

namespace vm {

class Object;
class VM;

class StringWrapper {
public:
  static bool IsString(Object *obj);
  static Object *NewStringWrapper(VM *vm, const string &str);
  static const string &String(Object *obj);
};

}  // namespace vm

#endif  // _vm_string_wrapper_h_
