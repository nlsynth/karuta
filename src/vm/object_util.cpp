#include "vm/object_util.h"

#include "numeric/numeric_op.h"  // from iroha
#include "vm/object.h"
#include "vm/string_wrapper.h"
#include "vm/value.h"

namespace vm {

int ObjectUtil::GetAddressWidth(Object *obj) {
  Value *value = obj->LookupValue(sym_lookup("$address_width"), false);
  if (value != nullptr && value->type_ == Value::NUM) {
    return value->num_.GetValue0();
  }
  return 32;
}

void ObjectUtil::SetAddressWidth(Object *obj, int width) {
  Value *value = obj->LookupValue(sym_lookup("$address_width"), true);
  value->type_ = Value::NUM;
  iroha::Op::MakeConst0(width, &value->num_);
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

}  // namespace vm
