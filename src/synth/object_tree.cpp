#include "synth/object_tree.h"

#include "karuta/annotation.h"
#include "synth/object_attr_names.h"
#include "vm/distance_wrapper.h"
#include "vm/object.h"
#include "vm/value.h"

#include <list>

using std::list;
using std::set;

namespace synth {

ObjectTree::ObjectTree(vm::VM *vm, vm::Object *root_obj)
  : vm_(vm), root_obj_(root_obj) {
}

ObjectTree::~ObjectTree() {
}

vm::Object *ObjectTree::GetRootObject() const {
  return root_obj_;
}

void ObjectTree::Build() {
  list<vm::Object *> q;
  q.push_back(root_obj_);
  set<vm::Object *> seen;
  vector<vm::Object *> ordered_objs;
  // BFS traversal.
  while (q.size() > 0) {
    vm::Object *o = *(q.begin());
    q.pop_front();
    if (seen.find(o) != seen.end()) {
      continue;
    }
    seen.insert(o);
    ordered_objs.push_back(o);
    CheckObject(o, seen, &q);
    PopulateDistance(o);
  }
  // Builds parent_map_.
  for (auto it : obj_children_map_) {
    for (auto jt : it.second) {
      parent_map_[jt.first] = it.first;
    }
  }
  // Names.
  AssignNames(ordered_objs);
}

std::map<vm::Object *, string> ObjectTree::GetChildObjects(vm::Object *o) {
  return obj_children_map_[o];
}

string ObjectTree::GetObjectName(vm::Object *o) {
  return obj_to_name_[o];
}

int ObjectTree::GetDistance(vm::Object *src, vm::Object *dst) {
  auto it = distance_map_.find(src);
  if (it == distance_map_.end()) {
    return 0;
  }
  auto &m = it->second;
  auto jt = m.find(dst);
  if (jt == m.end()) {
    return 0;
  }
  return jt->second;
}

const std::map<vm::Object *, std::map<vm::Object *, int> >
ObjectTree::GetDistanceMap() const {
  return distance_map_;
}

void ObjectTree::CheckObject(vm::Object *o, std::set<vm::Object *> &seen,
			     std::list<vm::Object *> *q) {
  map<sym_t, vm::Object *> member_objs;
  o->GetAllMemberObjs(&member_objs);
  sym_t parent = sym_lookup("parent");
  for (auto it : member_objs) {
    if (it.second == o) {
      continue;
    }
    if (it.first == parent) {
      // Suppress to traverse enclosing objects (beyond root_obj_).
      continue;
    }
    auto &m = obj_children_map_[o];
    if (seen.find(it.second) != seen.end()) {
      continue;
    }
    m[it.second] = sym_str(it.first);
    q->push_back(it.second);
  }
}

void ObjectTree::PopulateDistance(vm::Object *o) {
  map<sym_t, vm::Object *> member_objs;
  o->GetAllMemberObjs(&member_objs);
  for (auto it : member_objs) {
    sym_t name = it.first;
    int dist = vm::DistanceWrapper::GetDistance(vm_, o, name);
    if (dist == 0) {
      continue;
    }
    auto &m = distance_map_[o];
    m[it.second] = dist;
  }
}

string ObjectTree::GetSpecifiedName(vm::Object *obj) {
  sym_t synth_params = sym_lookup(kSynthParams);
  vm::Value *value = obj->LookupValue(synth_params, false);
  if (value == nullptr || value->type_ != vm::Value::ANNOTATION ||
      value->annotation_ == nullptr) {
    return "";
  }
  return value->annotation_->GetName();
}

void ObjectTree::AssignNames(std::vector<vm::Object *> &objs) {
  // Try specified names.
  for (auto *obj : objs) {
    string n = GetSpecifiedName(obj);
    if (!n.empty()) {
      obj_to_name_[obj] = GenerateUniqueName(n);
    }
  }
  // Use member name.
  for (auto *obj : objs) {
    if (obj_to_name_.find(obj) != obj_to_name_.end()) {
      // already assigned.
      continue;
    }
    vm::Object *parent = parent_map_[obj];
    string n;
    if (parent == nullptr) {
      n = "main";
    } else {
      auto m = obj_children_map_[parent];
      n = m[obj];
    }
    obj_to_name_[obj] = GenerateUniqueName(n);
  }
}

string ObjectTree::GenerateUniqueName(const string &name) {
  if (name.empty()) {
    return name;
  }
  int idx = names_.size();
  string n = name;
  while (names_.find(n) != names_.end()) {
    char buf[10];
    ++idx;
    sprintf(buf, "%d", idx);
    n = name + string(buf);
  }
  names_.insert(n);
  return n;
}

}  // namespace synth
