#include "vm/enum_type_wrapper.h"

#include "vm/object.h"
#include "vm/vm.h"

namespace vm {

static const char *kEnumTypeObjectKey = "enum_type";

class EnumTypeWrapperData : public ObjectSpecificData {
public:
  sym_t name_;
  vector<sym_t> items_;

  virtual const char *ObjectTypeKey() {
    return kEnumTypeObjectKey;
  }
};

bool EnumTypeWrapper::IsEnumType(Object *obj) {
  return (obj->ObjectTypeKey() == kEnumTypeObjectKey);
}

Object *EnumTypeWrapper::NewEnumTypeWrapper(VM *vm, sym_t name) {
  Object *et = vm->root_object_->Clone(vm);
  EnumTypeWrapperData *d = new EnumTypeWrapperData();
  d->name_ = name;
  et->object_specific_.reset(d);
  return et;
}

void EnumTypeWrapper::AddItem(Object *obj, sym_t item) {
  EnumTypeWrapperData *d = (EnumTypeWrapperData *)obj->object_specific_.get();
  d->items_.push_back(item);
}

string EnumTypeWrapper::GetName(const Object *obj) {
  EnumTypeWrapperData *d = (EnumTypeWrapperData *)obj->object_specific_.get();
  return string(sym_cstr(d->name_));
}

int EnumTypeWrapper::GetNumItems(const Object *obj) {
  EnumTypeWrapperData *d = (EnumTypeWrapperData *)obj->object_specific_.get();
  return d->items_.size();
}

}  // namespace vm
