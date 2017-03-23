#include "vm/numeric_object.h"

#include "vm/object.h"
#include "vm/value.h"
#include "vm/vm.h"

namespace vm {

Object *NumericObject::Get(VM *vm, sym_t name) {
  if (name == sym_null) {
    return nullptr;
  }
  Value *v =
    vm->kernel_object_->LookupValue(sym_lookup("Numerics"), false);
  if (v == nullptr) {
    return nullptr;
  }
  CHECK(v->type_ == Value::OBJECT);
  Value *n = v->object_->LookupValue(name, false);
  if (n == nullptr) {
    return nullptr;
  }
  CHECK(n->type_ == Value::OBJECT);
  return n->object_;
}

int NumericObject::Width(Object *obj) {
  // TODO: Get width from methods.
  return 32;
}

}  // namespace vm
