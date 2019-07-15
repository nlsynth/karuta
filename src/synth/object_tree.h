// -*- C++ -*-
#ifndef _synth_object_tree_h_
#define _synth_object_tree_h_

#include "synth/common.h"

#include <list>
#include <map>
#include <set>

namespace synth {

// Builds a DAG which covers all of the objects in the given graph and
// assigns an unique name to each object.
// This also holds distances between objects (specified by annotations).
class ObjectTree {
public:
  ObjectTree(vm::VM *vm, vm::Object *root_obj);
  virtual ~ObjectTree();

  void Build();

  vm::Object *GetRootObject() const;
  std::map<vm::Object *, string> GetChildObjects(vm::Object *o);
  string GetObjectName(vm::Object *o);
  int GetDistance(vm::Object *src, vm::Object *dst);
  const std::map<vm::Object *, std::map<vm::Object *, int> > GetDistanceMap() const;

private:
  void CheckObject(vm::Object *o, std::set<vm::Object *> &seen,
		   std::list<vm::Object *> *q);
  void PopulateDistance(vm::Object *o);
  string GetSpecifiedName(vm::Object *o);
  void AssignNames(std::vector<vm::Object *> &objs);
  string GenerateUniqueName(const string &name);

  vm::VM *vm_;
  vm::Object *root_obj_;
  // DAG of objects.
  std::map<vm::Object *, std::map<vm::Object *, string> > obj_children_map_;
  std::map<vm::Object *, vm::Object *> parent_map_;
  std::map<vm::Object *, std::map<vm::Object *, int> > distance_map_;
  // Name assignment.
  std::map<vm::Object *, string> obj_to_name_;
  std::set<string> names_;
};

}  // namespace synth

#endif  // _synth_object_tree_h_
