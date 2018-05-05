#include "vm/thread_wrapper.h"

#include "vm/object.h"
#include "vm/vm.h"

namespace vm {

static const char *kThreadObjectKey = "thread";

class ThreadWrapperData : public ObjectSpecificData {
public:
  ThreadWrapper::ThreadEntry entry;

  virtual const char *ObjectTypeKey() {
    return kThreadObjectKey;
  }
};

Object *ThreadWrapper::NewThreadWrapper(VM *vm, sym_t method_name,
					bool is_soft) {
  Object *thr = vm->root_object_->Clone(vm);
  ThreadWrapperData *data = new ThreadWrapperData;
  data->entry.method_name = sym_str(method_name);
  data->entry.thread_obj = thr;
  data->entry.is_soft_thread = is_soft;

  thr->object_specific_.reset(data);

  return thr;
}

void ThreadWrapper::Run(VM *vm, Object *obj) {
  vector<ThreadEntry> methods;
  GetThreadEntryMethods(obj, &methods, true);
  for (size_t i = 0; i < methods.size(); ++i) {
    string &name = methods[i].method_name;
    Value *method_value =
      obj->LookupValue(sym_lookup(name.c_str()), false);
    CHECK(method_value && method_value->type_ == Value::METHOD) << name;
    vm->AddThreadFromMethod(nullptr, obj, method_value->method_);
  }
}

void ThreadWrapper::GetThreadEntryMethods(Object *obj,
					  vector<ThreadEntry> *methods,
					  bool with_soft_thread) {
  for (map<sym_t, Value>::iterator it = obj->members_.begin();
       it != obj->members_.end(); ++it) {
    Value &value = it->second;
    if (value.type_ != Value::OBJECT) {
      continue;
    }
    Object *member_obj = value.object_;
    if (member_obj->ObjectTypeKey() != kThreadObjectKey) {
      continue;
    }
    ThreadWrapperData *data =
      (ThreadWrapperData *)member_obj->object_specific_.get();
    if (!with_soft_thread && data->entry.is_soft_thread) {
      continue;
    }
    ThreadEntry entry = data->entry;
    entry.thread_name = sym_str(it->first);
    methods->push_back(entry);
  }
}

}  // namespace vm
