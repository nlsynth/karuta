#include "vm/numeric_object.h"

#include "vm/object.h"
#include "vm/value.h"
#include "vm/vm.h"

namespace vm {

Object *NumericObject::Get(VM *vm, sym_t name) {
  if (name == sym_null) {
    return nullptr;
  }
  Value *n = vm->numerics_object_->LookupValue(name, false);
  if (n == nullptr) {
    return nullptr;
  }
  CHECK(n->type_ == Value::OBJECT);
  return n->object_;
}

bool NumericObject::IsNumericObject(VM *vm, Object *obj) {
  vector<sym_t> slots;
  vm->numerics_object_->LookupMemberNames(obj, &slots);
  return (slots.size() > 0);
}

int NumericObject::Width(Object *obj) {
  // TODO: Get width from methods.
  return 32;
}

}  // namespace vm
