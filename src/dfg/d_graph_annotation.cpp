#include "dfg/d_graph_annotation.h"

namespace dfg {

DGraphAnnotation::DGraphAnnotation() {
  ClearTargets();
}

void DGraphAnnotation::Flush() {
  if (reg_) {
    register_annotations_[reg_] += os.str();
  } else if (state_) {
    state_annotations_[state_] += os.str();
  } else {
    summary_ += os.str();
  }
  os.str("");
  ClearTargets();
}

const string DGraphAnnotation::GetRegisterAnnotation(const DRegister *reg)
  const {
  map<const DRegister *, string>::const_iterator it =
    register_annotations_.find(reg);
  if (it == register_annotations_.end()) {
    return string();
  }
  return it->second;
}

const string DGraphAnnotation::GetStateAnnotation(const DState *state)
  const {
  map<const DState *, string>::const_iterator it =
    state_annotations_.find(state);
  if (it == state_annotations_.end()) {
    return string();
  }
  return it->second;
}

const string DGraphAnnotation::GetSummary() const {
  return summary_;
}

void DGraphAnnotation::ClearTargets() {
  reg_ = NULL;
  state_ = NULL;
}

ostream &DGraphAnnotation::RegisterAnnotation(const DRegister *reg) {
  ClearTargets();
  reg_ = reg;
  return os;
}

ostream &DGraphAnnotation::StateAnnotation(const DState *state) {
  ClearTargets();
  state_ = state;
  return os;
}

ostream &DGraphAnnotation::SummaryAnnotation() {
  ClearTargets();
  return os;
}
}  // namespace dfg
