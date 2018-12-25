#include "vm/object.h"

#include "base/annotation.h"
#include "base/dump_stream.h"
#include "vm/array_wrapper.h"
#include "vm/int_array.h"
#include "vm/object_util.h"
#include "vm/string_wrapper.h"
#include "vm/tls_wrapper.h"
#include "vm/vm.h"

namespace vm {

ObjectSpecificData::~ObjectSpecificData() {
}

const char *ObjectSpecificData::ObjectTypeKey() {
  return nullptr;
}

void ObjectSpecificData::Scan(GC *gc) {
}

void Object::Dump() {
  DumpStream ds(cout);
  Dump(ds);
}

Object::Object() {
}

const char *Object::ObjectTypeKey() {
  if (object_specific_.get()) {
    return object_specific_->ObjectTypeKey();
  }
  return nullptr;
}

void Object::Dump(DumpStream &ds) {
  ds.os << "dump called [" << ToString() << "] "
	<< std::hex << (unsigned long)this
	<< std::dec << "\n";
  ds.push_indent();
  for (const std::pair<sym_t, Value> &it : members_) {
    ds.indent();
    ds.os << sym_cstr(it.first) << ":";
    it.second.Dump(ds.os);
    ds.os << "\n";
  }
  ds.pop_indent();
}

void Object::InstallValue(sym_t name, const Value &value) {
  members_.insert(std::make_pair(name, value));
}

Value *Object::LookupValue(sym_t name, bool cr) {
  map<sym_t, Value>::iterator it = members_.find(name);
  if (it != members_.end()) {
    return &it->second;
  }
  if (!cr) {
    return nullptr;
  }
  return &(members_[name]);
}

void Object::LookupMemberNames(Object *obj, vector<sym_t> *slots) {
  for (auto it : members_) {
    Value &value = it.second;
    // Can be object, array, string or other wrapped type.
    if (value.object_ == obj) {
      slots->push_back(it.first);
    }
  }
}

void Object::GetAllMemberObjs(map<sym_t, Object *> *member_objs) {
  for (auto it : members_) {
    Value &value = it.second;
    if (value.IsObjectType()) {
      (*member_objs)[it.first] = value.object_;
    }
  }
}

void Object::GetAllMemberMethods(map<sym_t, Method *> *member_objs) {
  for (auto it : members_) {
    Value &value = it.second;
    if (value.type_ == Value::METHOD) {
      (*member_objs)[it.first] = value.method_;
    }
  }
}

Object *Object::Clone(VM *vm) {
  Object *new_obj = vm->NewObject();
  // This does shallow copy for most of data types.
  new_obj->members_ = members_;
  for (auto it : new_obj->members_) {
    Value &value = it.second;
    if (value.type_ == Value::INT_ARRAY) {
      value.object_ = ArrayWrapper::Copy(vm, value.object_);
    }
    if (TlsWrapper::IsTlsValue(&value)) {
      value.object_ = TlsWrapper::Copy(vm, value.object_);
    }
    if (value.type_ == Value::ANNOTATION) {
      value.annotation_ =
	Annotation::Copy(value.annotation_);
    }
  }
  return new_obj;
}

const string &Object::ToString() {
  if (StringWrapper::IsString(this)) {
    return StringWrapper::String(this);
  }
  static string empty;
  return empty;
}

bool Object::Compare(Object *obj) {
  if (object_specific_.get()) {
    auto *od = obj->object_specific_.get();
    if (!od) {
      return false;
    }
    if (object_specific_->ObjectTypeKey() != od->ObjectTypeKey()) {
      return false;
    }
    return object_specific_->Compare(obj);
  }
  return (this == obj);
}

void Object::Scan(GC *gc) {
  auto *od = object_specific_.get();
  if (od != nullptr) {
    od->Scan(gc);
  }
}

}  // namespace vm
