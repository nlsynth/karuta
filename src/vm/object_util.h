// -*- C++ -*-
#ifndef _vm_object_util_h_
#define _vm_object_util_h_

#include <set>

#include "vm/common.h"

namespace vm {

class ObjectUtil {
 public:
  static int GetAddressWidth(Object *obj);
  static void SetAddressWidth(Object *obj, int width);
  static int GetDataWidth(Object *obj);
  static void SetDataWidth(Object *obj, int width);
  static string GetStringMember(Object *obj, const string &key);
  static void SetStringMember(Object *obj, const string &key,
                              const string &str);
  static int GetIntMember(Object *obj, const string &key, int dflt);
  static void SetIntMember(Object *obj, const string &key, int val);
  static void CollectReachableObjects(Object *obj, vector<Object *> *objs);

 private:
  static void CollectReachableObjectsRec(Object *obj, std::set<Object *> *seen,
                                         vector<Object *> *objs);
};

}  // namespace vm

#endif  // _vm_object_util_h_
