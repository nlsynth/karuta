#include "vm/value.h"

#include "vm/array_wrapper.h"
#include "vm/int_array.h"
#include "vm/string_wrapper.h"

#include <map>

namespace vm {

  Value::Value() : type_(NONE), is_const_(false), method_(NULL), object_(NULL), local_int_array_(NULL) {
}

void Value::Dump() const {
  Dump(cout);
}

void Value::Dump(ostream &os) const {
  switch (type_) {
  case NONE:
    os << "(unknown)";
    break;
  case METHOD:
    os << "(method)";
    break;
  case NUM:
    num_.Dump(os);
    break;
  case ENUM_TYPE:
    os << sym_cstr(enum_type_->name_) << " "
       << enum_type_->items_.size() << "items";
    break;
  case ENUM_ITEM:
    os << enum_val_.val << " in " << sym_cstr(enum_val_.enum_type->name_);
    break;
  case DMODULE:
    os << "dmodule";
    break;
  case OBJECT:
    if (StringWrapper::IsString(object_)) {
      os << StringWrapper::String(object_);
    } else {
      os << "object";
    }
    break;
  case INT_ARRAY:
    if (local_int_array_) {
      os << "array[" << local_int_array_->GetLength() << "]";
    }
    // fall through.
  case OBJECT_ARRAY:
    os << "object_array[" << ArrayWrapper::ToString(object_) << "]";
    break;
  default:
    CHECK(false) << "unknown value type" << type_;
    break;
  }
  if (is_const_) {
    os << "(const)";
  }
}

// static
const char *Value::TypeName(ValueType type) {
  static std::map<ValueType, const char *> names =
    {{NONE, "none"},
     {NUM, "num"},
     {METHOD, "method"},
     {ENUM_ITEM, "enum_item"},
     {ENUM_TYPE, "enum_type"},
     {DMODULE, "dmodule"},
     {OBJECT, "object"},
     {INT_ARRAY, "int_array"},
     {OBJECT_ARRAY, "array"}};
  auto it = names.find(type);
  CHECK(it != names.end()) << "invalid value type.";
  return it->second;
}

void Value::SetBool(bool b) {
  if (b) {
    enum_val_.val = 1;
  } else {
    enum_val_.val = 0;
  }
}

}  // namespace vm
