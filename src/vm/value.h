// -*- C++ -*-
#ifndef _vm_value_h_
#define _vm_value_h_

#include "nli.h"

#include "numeric/numeric.h"

namespace dfg {
class ResourceParams;
}  // namespace dfg
using namespace dfg;

namespace vm {

class IntArray;
class Method;
class Object;

class EnumType {
public:
  sym_t name_;
  vector<sym_t> items_;
};

class EnumVal {
public:
  int val;
  const EnumType *enum_type;
};

class Value {
public:
  Value();
  void Dump() const;
  void Dump(ostream &os) const;
  void SetBool(bool b);

  enum ValueType {
    NONE,
    NUM,
    METHOD,
    ENUM_ITEM,
    ENUM_TYPE,
    RESOURCE_PARAMS,

    // In object_.
    DMODULE,
    OBJECT,
    INT_ARRAY,
    OBJECT_ARRAY,
  };

  static const char *TypeName(enum ValueType type);

  enum ValueType type_;
  bool is_const_;

  numeric::Number num_;
  Method *method_;
  // for ENUM_ITEM
  EnumVal enum_val_;
  // for ENUM_TYPE
  const EnumType *enum_type_;
  // for RESOURCE_PARAMS
  dfg::ResourceParams *resource_params_;
  Object *object_;
  IntArray *local_int_array_;
};

}  // namespace vm

#endif  // _vm_value_h_
