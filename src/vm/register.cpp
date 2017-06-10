#include "vm/register.h"

#include "base/dump_stream.h"
#include "vm/enum_type_wrapper.h"
#include "vm/value.h"

namespace vm {

RegisterType::RegisterType(Value::ValueType type, const Object *enum_type,
			   const iroha::NumericWidth &width, sym_t object_name,
			   bool is_const)
  : value_type_(type), enum_type_(enum_type),
    object_name_(object_name),
    is_const_(is_const), pointee_width_(-1) {
  width_ = width;
}

RegisterType::RegisterType() {
}

void RegisterType::Dump() {
  DumpStream ds(cout);
  Dump(ds);
}

void RegisterType::Dump(DumpStream &ds) {
  ds.os << Value::TypeName(value_type_);
  if (enum_type_) {
    ds.os << ":" << EnumTypeWrapper::GetName(enum_type_);
  }
  ds.os << " #" << width_.Format();
  if (pointee_width_ > -1) {
    ds.os << " *" << pointee_width_;
  }
  if (object_name_ != nullptr) {
    ds.os << "[" << sym_cstr(object_name_) << "]";
  }
}

Register::Register() : type_(Value::NONE, nullptr,
			     iroha::NumericWidth(false, 32), sym_null, false),
		       orig_name_(nullptr), type_object_(nullptr),
		       array_length_(-1), array_initializer_(nullptr),
		       is_declared_type_(false) {
}

void Register::Dump() {
  DumpStream ds(cout);
  Dump(ds);
}

void Register::Dump(DumpStream &ds) {
  type_.Dump(ds);
  if (type_.is_const_) {
    ds.os << " " << initial_num_.Format();
  }
  if (orig_name_) {
    ds.os << "(" << sym_cstr(orig_name_) << ")";
  }
  if (type_object_ == nullptr) {
    if (type_.object_name_ != nullptr) {
      ds.os << "?";
    }
  } else {
    ds.os << "*";
  }
  if (array_length_ > -1) {
    ds.os << " [" << array_length_ << "]";
    if (array_initializer_) {
      ds.os << "={...}";
    }
  }
  if (is_declared_type_) {
    ds.os << "!";
  }
}

void Register::SetArrayLength(int array_length) {
  array_length_ = array_length;
}

int Register::GetArrayLength() const {
  return array_length_;
}

void Register::SetArrayInitializer(fe::ArrayInitializer *initializer) {
  array_initializer_ = initializer;
}

fe::ArrayInitializer *Register::GetArrayInitializer() const {
  return array_initializer_;
}

void Register::SetIsDeclaredType(bool is_declared_type) {
  is_declared_type_ = is_declared_type;
}

bool Register::GetIsDeclaredType() const {
  return is_declared_type_;
}

}  // namespace vm

