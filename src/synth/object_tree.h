// -*- C++ -*-
#ifndef _synth_object_tree_h_
#define _synth_object_tree_h_

#include "synth/common.h"

#include <list>
#include <map>
#include <set>

namespace synth {

class ObjectTree {
public:
  ObjectTree(vm::Object *root_obj);
  virtual ~ObjectTree();

  void Build();

  std::map<vm::Object *, string> GetChildObjects(vm::Object *o);
  string GetObjectName(vm::Object *o);

private:
  void CheckObject(vm::Object *o, std::set<vm::Object *> &seen,
		   std::list<vm::Object *> *q);

  vm::Object *root_obj_;
  // DAG of objects.
  std::map<vm::Object *, std::map<vm::Object *, string> > obj_children_map_;
  std::map<vm::Object *, vm::Object *> parent_map_;
};

}  // namespace synth

#endif  // _synth_object_tree_h_
