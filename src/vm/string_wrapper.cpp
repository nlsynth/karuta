#include "vm/string_wrapper.h"

#include "vm/object.h"
#include "vm/vm.h"

namespace vm {

static const char *kStringObjectKey = "string";

class StringWrapperData : public ObjectSpecificData {
public:
  StringWrapperData(const string &str) : str_(str) {}
  string str_;

  virtual const char *ObjectTypeKey() {
    return kStringObjectKey;
  }
};

bool StringWrapper::IsString(Object *obj) {
  return (obj->ObjectTypeKey() == kStringObjectKey);
}

Object *StringWrapper::NewStringWrapper(VM *vm, const string &str) {
  Object *str_obj = vm->string_object_->Clone(vm);
  StringWrapperData *data = new StringWrapperData(str);
  str_obj->object_specific_.reset(data);
  return str_obj;
}

const string &StringWrapper::String(Object *obj) {
  StringWrapperData *data = (StringWrapperData *)obj->object_specific_.get();
  return data->str_;
}

}  // namespace vm
