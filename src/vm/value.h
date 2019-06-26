// -*- C++ -*-
#ifndef _vm_value_h_
#define _vm_value_h_

#include "vm/common.h"
#include "numeric/numeric_type.h"  // from iroha

namespace vm {

class EnumVal {
public:
  int val;
  const Object *enum_type;
};

class Value {
public:
  Value();
  void Dump() const;
  void Dump(ostream &os) const;
  void SetBool(bool b);
  bool IsObjectType() const;
  void CopyDataFrom(const Value &src, const iroha::NumericWidth &width);

  enum ValueType {
    NONE,
    NUM,
    METHOD,
    ENUM_ITEM,
    ANNOTATION,

    // In object_.
    OBJECT,
    ENUM_TYPE,
    INT_ARRAY,
    OBJECT_ARRAY,
  };

  static const char *TypeName(enum ValueType type);

  enum ValueType type_;
  bool is_const_;

  // for NUM
  iroha::NumericValue num_;
  iroha::NumericWidth num_type_;
  // for METHOD
  Method *method_;
  // for ENUM_ITEM
  EnumVal enum_val_;
  // for ANNOTATION
  Annotation *annotation_;
  // object itself for OBJECT, ENUM_TYPE, INT_ARRAY and OBJECT_ARRAY
  // (IsObjectType()==true).
  // can be numeric type object for NUM.
  Object *object_;
  sym_t type_object_name_;
};

}  // namespace vm

#endif  // _vm_value_h_
