#include "vm/object.h"

#include "dump_stream.h"
#include "vm/array_wrapper.h"
#include "vm/int_array.h"
#include "vm/string_wrapper.h"
#include "vm/vm.h"

namespace vm {

ObjectSpecificData::~ObjectSpecificData() {
}

const char *ObjectSpecificData::ObjectTypeKey() {
  return NULL;
}

void Object::Dump() {
  DumpStream ds(cout);
  Dump(ds);
}

const char *Object::ObjectTypeKey() {
  if (object_specific_.get()) {
    return object_specific_->ObjectTypeKey();
  }
  return NULL;
}

void Object::Dump(DumpStream &ds) {
  ds.os << "dump called " << std::hex << (unsigned long)this
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
    return NULL;
  }
  return &(members_[name]);
}

void Object::LookupMemberNames(Object *obj, vector<sym_t> *slots) {
  for (map<sym_t, Value>::iterator it = members_.begin();
       it != members_.end(); ++it) {
    Value &value = it->second;
    // Can be object, array, string or other wrapped type.
    if (value.object_ == obj) {
      slots->push_back(it->first);
    }
  }
}

Object *Object::Clone(VM *vm) {
  Object *new_obj = vm->NewObject();
  new_obj->members_ = members_;
  for (auto it : new_obj->members_) {
    Value &value = it.second;
    if (value.type_ == Value::INT_ARRAY) {
      value.object_ = ArrayWrapper::Copy(vm, value.object_);
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

}  // namespace vm
