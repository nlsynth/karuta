// -*- C++ -*-
#ifndef _vm_profile_h_
#define _vm_profile_h_

#include "vm/common.h"

namespace vm {

class Profile {
public:
  Profile();
  ~Profile();

  void Mark(Method *method, int pc);
  bool IsEnabled() const;
  void SetEnable(bool enable);
  void Clear();

private:
  bool enabled_;
};

}  // namespace vm

#endif  // _vm_profile_h_

