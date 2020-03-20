// -*- C++ -*-
#ifndef _compiler_loop_marker_h_
#define _compiler_loop_marker_h_

#include "compiler/common.h"

namespace compiler {

class LoopMarker {
public:
  LoopMarker(const fe::Method *method, LoopMarker *parent, int start);
  ~LoopMarker();

  static LoopMarker *Scan(const fe::Method *tree);

  void ScanOne();
  int GetEnd();
  bool CollectLoops(vector<LoopMarker *> *loops);
  vector<LoopMarker *> &GetLoops();

private:
  const fe::Method *method_;
  LoopMarker *parent_;
  int start_;
  int end_;
  vector<LoopMarker *> children_;
  vector<LoopMarker *> loops_;
};

}  // namespace compiler

#endif  // _compiler_loop_marker_h_
