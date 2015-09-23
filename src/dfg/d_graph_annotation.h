// -*- C++ -*-
#ifndef _dfg_d_graph_annotation_h_
#define _dfg_d_graph_annotation_h_

#include "nli.h"

#include <map>

using std::map;

namespace dfg {

class DRegister;
class DState;

// for debug messages.
class DGraphAnnotation {
public:
  DGraphAnnotation();

  ostream &RegisterAnnotation(const DRegister *reg);
  ostream &StateAnnotation(const DState *state);
  ostream &SummaryAnnotation();

  void Flush();
  const string GetRegisterAnnotation(const DRegister *reg) const;
  const string GetStateAnnotation(const DState *state) const;
  const string GetSummary() const;

private:
  ostringstream os;
  string summary_;
  const DRegister *reg_;
  const DState *state_;
  map<const DRegister *, string> register_annotations_;
  map<const DState *, string> state_annotations_;
  void ClearTargets();
};
}  // namespace dfg

#endif  // _dfg_d_graph_annotation_h_
