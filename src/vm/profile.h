// -*- C++ -*-
#ifndef _vm_profile_h_
#define _vm_profile_h_

#include "vm/common.h"

namespace vm {

class ProfileData;

class Profile {
 public:
  Profile();
  ~Profile();

  void Mark(Method *method, int pc);
  int GetCount(Method *method, int pc);
  bool IsEnabled() const;
  void SetEnable(bool enable);
  void Clear();
  bool HasInfo();

 private:
  bool enabled_;
  bool has_info_;
  std::unique_ptr<ProfileData> data_;
};

}  // namespace vm

#endif  // _vm_profile_h_
