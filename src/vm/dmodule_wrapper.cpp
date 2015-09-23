#include "vm/dmodule_wrapper.h"

#include "vm/object.h"
#include "vm/vm.h"

namespace vm {

static const char *kDModuleObjectKey = "dmodule";

class DModuleWrapperData : public ObjectSpecificData {
public:
  DModuleWrapperData(DModule *mod) : dmod_(mod) {}
  DModule *dmod_;

  virtual const char *ObjectTypeKey() {
    return kDModuleObjectKey;
  }
};

bool DModuleWrapper::IsDModule(Object *obj) {
  return (obj->ObjectTypeKey() == kDModuleObjectKey);
}

Object *DModuleWrapper::NewDModuleWrapper(VM *vm, dfg::DModule *module) {
  Object *dmod_obj = vm->string_object_->Clone(vm);
  DModuleWrapperData *data = new DModuleWrapperData(module);
  dmod_obj->object_specific_.reset(data);
  return dmod_obj;
}

dfg::DModule *DModuleWrapper::GetDModule(Object *obj) {
  DModuleWrapperData *data = (DModuleWrapperData *)obj->object_specific_.get();
  return data->dmod_;
}

}  // namespace vm
