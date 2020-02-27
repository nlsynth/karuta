#include "vm/object_util.h"

#include "numeric/numeric_op.h"  // from iroha
#include "vm/object.h"
#include "vm/string_wrapper.h"
#include "vm/value.h"

namespace vm {

int ObjectUtil::GetAddressWidth(Object *obj) {
  return GetIntMember(obj, "$address_width", 32);
}

void ObjectUtil::SetAddressWidth(Object *obj, int width) {
  SetIntMember(obj, "$address_width", width);
}

string ObjectUtil::GetStringMember(Object *obj, const string &key) {
  Value *value = obj->LookupValue(sym_lookup(key.c_str()), false);
  if (value == nullptr || value->type_ != Value::OBJECT ||
      !StringWrapper::IsString(value->object_)) {
    return "";
  }
  return StringWrapper::String(value->object_);
}

void ObjectUtil::SetStringMember(Object *obj, const string &key,
				 const string &str) {
  Value *value = obj->LookupValue(sym_lookup(key.c_str()), true);
  value->type_ = Value::OBJECT;
  value->object_ = StringWrapper::NewStringWrapper(obj->GetVM(), str);
}

int ObjectUtil::GetIntMember(Object *obj, const string &key, int dflt) {
  Value *value = obj->LookupValue(sym_lookup(key.c_str()), false);
  if (value != nullptr && value->type_ == Value::NUM) {
    return value->num_.GetValue0();
  }
  return dflt;
}

void ObjectUtil::SetIntMember(Object *obj, const string &key, int val) {
  Value *value = obj->LookupValue(sym_lookup(key.c_str()), true);
  value->type_ = Value::NUM;
  iroha::Op::MakeConst0(val, &value->num_);
}

}  // namespace vm
