#include "vm/register.h"

#include "dump_stream.h"
#include "vm/value.h"

namespace vm {

RegisterType::RegisterType(Value::ValueType type, const EnumType *enum_type,
			   const NumberWidth *width, bool is_const)
  : value_type_(type), enum_type_(enum_type), width_(width),
    is_const_(is_const) {
}

void RegisterType::Dump() {
  DumpStream ds(cout);
  Dump(ds);
}

void RegisterType::Dump(DumpStream &ds) {
  ds.os << Value::TypeName(value_type_);
  if (enum_type_) {
    ds.os << ":" << sym_cstr(enum_type_->name_);
  }
  if (width_) {
    ds.os << " #";
    NumberWidth::Dump(width_, ds.os);
  }
}

Register::Register() : type_(Value::NONE, NULL, NULL, false),
		       orig_name_(NULL),
		       array_length_(-1), array_initializer_(NULL) {
}

void Register::Dump() {
  DumpStream ds(cout);
  Dump(ds);
}

void Register::Dump(DumpStream &ds) {
  type_.Dump(ds);
  if (type_.is_const_) {
    ds.os << " ";
    initial_num_.Dump(ds.os);
  }
  if (orig_name_) {
    ds.os << "(" << sym_cstr(orig_name_) << ")";
  }
  if (array_length_ > -1) {
    ds.os << " [" << array_length_ << "]";
    if (array_initializer_) {
      ds.os << "={...}";
    }
  }
}

}  // namespace vm

