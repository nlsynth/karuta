#include "vm/profile.h"

namespace vm {

Profile::Profile() : enabled_(false), has_info_(false) {
}

Profile::~Profile() {
}

bool Profile::IsEnabled() const {
  return enabled_;
}

void Profile::SetEnable(bool enable) {
  enabled_ = enable;
}

void Profile::Clear() {
  has_info_ = false;
}

void Profile::Mark(Method *method, int pc) {
  has_info_ = true;
}

int Profile::GetCount(Method *method, int pc) {
  return 0;
}

bool Profile::HasInfo() {
  return has_info_;
}

}  // namespace vm
