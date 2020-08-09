#include "vm/object_util.h"

#include "iroha/numeric.h"
#include "vm/object.h"
#include "vm/string_wrapper.h"
#include "vm/value.h"

using std::set;

namespace vm {

int ObjectUtil::GetAddressWidth(Object *obj) {
  return GetIntMember(obj, "$address_width", 32);
}

void ObjectUtil::SetAddressWidth(Object *obj, int width) {
  SetIntMember(obj, "$address_width", width);
}

int ObjectUtil::GetDataWidth(Object *obj) {
  return GetIntMember(obj, "$data_width", 32);
}

void ObjectUtil::SetDataWidth(Object *obj, int width) {
  SetIntMember(obj, "$data_width", width);
}

string ObjectUtil::GetStringMember(Object *obj, const string &key) {
  Value *value = obj->LookupValue(sym_lookup(key.c_str()), false);
  if (value == nullptr || !value->IsString()) {
    return "";
  }
  return StringWrapper::String(value->object_);
}

void ObjectUtil::SetStringMember(Object *obj, const string &key,
				 const string &str) {
  Value *value = obj->LookupValue(sym_lookup(key.c_str()), true);
  value->type_ = Value::OBJECT;
  value->object_ = StringWrapper::NewStringWrapper(obj->GetVM(), str);
}

int ObjectUtil::GetIntMember(Object *obj, const string &key, int dflt) {
  Value *value = obj->LookupValue(sym_lookup(key.c_str()), false);
  if (value != nullptr && value->type_ == Value::NUM) {
    return value->num_.GetValue0();
  }
  return dflt;
}

void ObjectUtil::SetIntMember(Object *obj, const string &key, int val) {
  Value *value = obj->LookupValue(sym_lookup(key.c_str()), true);
  value->type_ = Value::NUM;
  iroha::Op::MakeConst0(val, &value->num_);
}

void ObjectUtil::CollectReachableObjects(Object *obj,
					 vector<Object *> *objs) {
  set<Object *> seen;
  CollectReachableObjectsRec(obj, &seen, objs);
}

void ObjectUtil::CollectReachableObjectsRec(Object *obj,
					    set<Object *> *seen,
					    vector<Object *> *objs) {
  if (seen->find(obj) != seen->end()) {
    return;
  }
  objs->push_back(obj);
  seen->insert(obj);
  map<sym_t, vm::Object *> member_objs;
  obj->GetAllMemberObjs(&member_objs);
  for (auto it : member_objs) {
    if (it.first == sym_parent) {
      continue;
    }
    CollectReachableObjectsRec(it.second, seen, objs);
  }
}

}  // namespace vm
