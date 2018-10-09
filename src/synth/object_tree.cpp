#include "synth/object_tree.h"

#include "vm/distance_wrapper.h"
#include "vm/object.h"

#include <list>
#include <set>

using std::list;
using std::set;

namespace synth {

ObjectTree::ObjectTree(vm::VM *vm, vm::Object *root_obj) : vm_(vm), root_obj_(root_obj) {
}

ObjectTree::~ObjectTree() {
}

void ObjectTree::Build() {
  list<vm::Object *> q;
  q.push_back(root_obj_);
  set<vm::Object *> seen;
  // BFS traversal.
  while (q.size() > 0) {
    vm::Object *o = *(q.begin());
    q.pop_front();
    if (seen.find(o) != seen.end()) {
      continue;
    }
    seen.insert(o);
    CheckObject(o, seen, &q);
    PopulateDistance(o);
  }
  // Builds parent_map_.
  for (auto it : obj_children_map_) {
    for (auto jt : it.second) {
      parent_map_[jt.first] = it.first;
    }
  }
}

std::map<vm::Object *, string> ObjectTree::GetChildObjects(vm::Object *o) {
  return obj_children_map_[o];
}

string ObjectTree::GetObjectName(vm::Object *o) {
  vm::Object *parent = parent_map_[o];
  if (parent == nullptr) {
    return "";
  }
  auto m = obj_children_map_[parent];
  return m[o];
}

int ObjectTree::GetDistance(vm::Object *src, vm::Object *dst) {
  auto it = latency_map_.find(src);
  if (it == latency_map_.end()) {
    return 0;
  }
  auto &m = it->second;
  auto jt = m.find(dst);
  if (jt == m.end()) {
    return 0;
  }
  return jt->second;
}

void ObjectTree::CheckObject(vm::Object *o, std::set<vm::Object *> &seen,
			     std::list<vm::Object *> *q) {
  map<sym_t, vm::Object *> member_objs;
  o->GetAllMemberObjs(&member_objs);
  for (auto it : member_objs) {
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
    auto &m = latency_map_[o];
    m[it.second] = dist;
  }
}

}  // namespace synth
