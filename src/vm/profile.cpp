#include "vm/profile.h"

#include <map>
#include <tuple>

using std::map;
using std::tuple;

namespace vm {

class ProfileData {
public:
  ~ProfileData() {}

  map<tuple<Method *, int>, int> count_;
};

Profile::Profile() : enabled_(false), has_info_(false) {
  data_.reset(new ProfileData);
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
  data_->count_.clear();
  has_info_ = false;
}

void Profile::Mark(Method *method, int pc) {
  // For now this doesn't consider multiple inlined instances of a
  // same method. Probably I might change to store current trace or
  // whole the stack.
  auto k = std::make_tuple(method, pc);
  ++(data_->count_[k]);
  has_info_ = true;
}

int Profile::GetCount(Method *method, int pc) {
  auto k = std::make_tuple(method, pc);
  return data_->count_[k];
}

bool Profile::HasInfo() {
  return has_info_;
}

}  // namespace vm
