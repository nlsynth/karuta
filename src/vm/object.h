// -*- C++ -*-
#ifndef _vm_object_h_
#define _vm_object_h_

#include <map>

#include "vm/common.h"
#include "vm/value.h"

using std::map;

namespace vm {

class ObjectSpecificData {
 public:
  virtual ~ObjectSpecificData();
  virtual bool Compare(Object *obj) { return false; };
  virtual const char *ObjectTypeKey();
  virtual void Scan(GC *gc);
};

class Object {
 public:
  Object(VM *vm);

  void Dump();
  void Dump(DumpStream &ds);

  const char *ObjectTypeKey();

  VM *GetVM();
  void InstallValue(sym_t name, const Value &value);
  Value *LookupValue(sym_t name, bool cr);
  // Finds synonyms of specified member object.
  void LookupMemberNames(Object *obj, vector<sym_t> *slots);
  void GetAllMemberObjs(map<sym_t, Object *> *member_objs);
  void GetAllMemberMethods(map<sym_t, Method *> *member_objs);
  Object *Clone();
  const string &ToString();
  bool Compare(Object *obj);
  // Object type specific GC hook.
  void Scan(GC *gc);

  map<sym_t, Value> members_;

  std::unique_ptr<ObjectSpecificData> object_specific_;

 private:
  VM *vm_;
};

}  // namespace vm

#endif  // _vm_object_h_
