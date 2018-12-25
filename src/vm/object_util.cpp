#include "vm/object_util.h"

#include "numeric/numeric_op.h"  // from iroha
#include "vm/object.h"
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
  iroha::Op::MakeConst(width, &value->num_);
}

}  // namespace vm
