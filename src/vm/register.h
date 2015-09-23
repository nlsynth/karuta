// -*- C++ -*-
#ifndef _vm_register_h_
#define _vm_register_h_

#include "nli.h"

#include "numeric.h"
#include "vm/value.h"

class DumpStream;
class NumberWidth;

namespace fe {
class ArrayInitializer;
}  // namespace fe

namespace vm {

class EnumType;

class RegisterType {
public:
  RegisterType(Value::ValueType value_type, const EnumType *enum_type,
	       const NumberWidth *width, bool is_const);
  void Dump();
  void Dump(DumpStream &ds);

  // VALUE_*
  enum Value::ValueType value_type_;
  // when value_type_ == ENUM_ITEM
  const EnumType *enum_type_;
  const NumberWidth *width_;
  bool is_const_;
};

// Register definition. Actual value will be stored in
// MethodFrame.reg_values_.
class Register {
public:
  Register();
  void Dump();
  void Dump(DumpStream &ds);

  int id_;
  RegisterType type_;
  Number initial_num_;
  sym_t orig_name_;
  // local array.
  int array_length_;
  fe::ArrayInitializer *array_initializer_;
};

}  // namespace vm

#endif  // _vm_register_h_
