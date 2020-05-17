// -*- C++ -*-
#ifndef _vm_register_h_
#define _vm_register_h_

#include "iroha/numeric.h"
#include "vm/common.h"
#include "vm/value.h"

namespace vm {

class RegisterType {
public:
  RegisterType(Value::ValueType value_type, const Object *enum_type,
	       const iroha::NumericWidth &width, sym_t object_name,
	       bool is_const);
  void Dump();
  void Dump(DumpStream &ds);

  // VALUE_*
  enum Value::ValueType value_type_;
  // when value_type_ == ENUM_ITEM
  const Object *enum_type_;
  iroha::NumericWidth width_;
  sym_t object_name_;
  bool is_const_;

private:
  RegisterType();
};

// Register definition. Actual value will be stored in
// MethodFrame.reg_values_.
class Register {
public:
  Register();

  void Dump();
  void Dump(DumpStream &ds);

  void SetIsDeclaredType(bool is_declared_type);
  bool GetIsDeclaredType() const;

  void SetAnnotation(Annotation *an);
  Annotation *GetAnnotation();

  int id_;
  RegisterType type_;
  iroha::Numeric initial_num_;
  sym_t orig_name_;
  Object *type_object_;

private:
  bool is_declared_type_;
  Annotation *annotation_;
};

}  // namespace vm

#endif  // _vm_register_h_
