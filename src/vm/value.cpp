#include "vm/value.h"

#include "base/annotation.h"
#include "vm/array_wrapper.h"
#include "vm/enum_type_wrapper.h"
#include "vm/int_array.h"
#include "vm/string_wrapper.h"

#include <map>

namespace vm {

Value::Value() : type_(NONE), pointee_width_(-1),
		 is_const_(false), method_(nullptr),
		 object_(nullptr), local_int_array_(nullptr),
		 type_object_name_(sym_null) {
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
    if (type_object_name_ != sym_null) {
      os << "[" << sym_cstr(type_object_name_);
      if (object_ == nullptr) {
	os << "?";
      } else {
	os << "*";
      }
      os << "]";
    }
    if (pointee_width_ > -1) {
      os << " *" << pointee_width_ << " ";
    }
    os << num_.Format();
    break;
  case ENUM_TYPE:
    os << EnumTypeWrapper::GetName(object_) << " "
       << EnumTypeWrapper::GetNumItems(object_) << "items";
    break;
  case ENUM_ITEM:
    os << enum_val_.val << " in " << EnumTypeWrapper::GetName(enum_val_.enum_type);
    break;
  case ANNOTATION:
    os << "annotation: ";
    annotation_->Dump(os);
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

bool Value::IsObjectType() const {
  return type_ == OBJECT || type_ == ENUM_TYPE ||
    type_ == INT_ARRAY || type_ == OBJECT_ARRAY;
}

}  // namespace vm
