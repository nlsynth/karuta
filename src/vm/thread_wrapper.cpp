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
					bool is_soft, int index) {
  Object *thr = vm->root_object_->Clone();
  ThreadWrapperData *data = new ThreadWrapperData;
  data->entry.method_name = sym_str(method_name);
  data->entry.thread_obj = thr;
  data->entry.is_soft_thread = is_soft;
  data->entry.index = index;

  thr->object_specific_.reset(data);

  return thr;
}

void ThreadWrapper::Run(VM *vm, Object *obj) {
  vector<ThreadEntry> methods;
  GetThreadEntryMethods(obj, &methods, true);
  for (auto &m : methods) {
    string &name = m.method_name;
    Value *method_value =
      obj->LookupValue(sym_lookup(name.c_str()), false);
    CHECK(method_value && method_value->type_ == Value::METHOD) << name;
    vm->AddThreadFromMethod(nullptr, obj, method_value->method_, m.index);
  }
}

void ThreadWrapper::GetThreadEntryMethods(Object *obj,
					  vector<ThreadEntry> *methods,
					  bool with_soft_thread) {
  for (auto it : obj->members_) {
    Value &value = it.second;
    if (value.type_ == Value::OBJECT && value.object_ == obj) {
      // excluding self.
      continue;
    }
    ThreadWrapperData *data = GetData(value);
    if (data == nullptr) {
      continue;
    }
    if (!with_soft_thread && data->entry.is_soft_thread) {
      continue;
    }
    ThreadEntry entry = data->entry;
    entry.thread_name = sym_str(it.first);
    methods->push_back(entry);
  }
}

void ThreadWrapper::DeleteThreadByMethodName(Object *obj, const string &name) {
  auto members = obj->members_;
  for (auto it : members) {
    Value &value = it.second;
    ThreadWrapperData *data = GetData(value);
    if (data == nullptr) {
      continue;
    }
    if (data->entry.method_name == name) {
      obj->members_.erase(it.first);
    }
  }
}

ThreadWrapperData *ThreadWrapper::GetData(Value &value) {
  if (value.type_ != Value::OBJECT) {
    return nullptr;
  }
  Object *member_obj = value.object_;
  if (member_obj == nullptr ||
      member_obj->ObjectTypeKey() != kThreadObjectKey) {
    return nullptr;
  }
  return (ThreadWrapperData *)member_obj->object_specific_.get();
}

}  // namespace vm
