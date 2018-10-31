#include "vm/profile.h"

namespace vm {

Profile::Profile() : enabled_(false) {
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
}

void Profile::Mark(Method *method, int pc) {
}

}  // namespace vm
