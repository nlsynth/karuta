// -*- C++ -*-
#ifndef _vm_object_h_
#define _vm_object_h_

#include "vm/common.h"
#include "vm/value.h"

#include <map>

using std::map;

namespace vm {

class ObjectSpecificData {
public:
  virtual ~ObjectSpecificData();
  virtual bool Compare(Object *obj) { return false; };
  virtual const char *ObjectTypeKey();
};

class Object {
public:
  void Dump();
  void Dump(DumpStream &ds);

  const char *ObjectTypeKey();

  void InstallValue(sym_t name, const Value &value);
  Value *LookupValue(sym_t name, bool cr);
  void LookupMemberNames(Object *obj, vector<sym_t> *slots);
  Object *Clone(VM *vm);
  const string &ToString();
  bool Compare(Object *obj);

  map<sym_t, Value> members_;

  std::unique_ptr<ObjectSpecificData> object_specific_;
};

}  // namespace vm

#endif  // _vm_object_h_
