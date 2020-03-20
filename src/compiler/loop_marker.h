// -*- C++ -*-
#ifndef _compiler_loop_marker_h_
#define _compiler_loop_marker_h_

#include "compiler/common.h"

#include <map>

namespace compiler {

// LoopMarker is a tree where each node corresponds to a block.
// The root marker collects valid loops and responds to LookUp()
class LoopMarker {
public:
  LoopMarker(const fe::Method *method, LoopMarker *parent, int start);
  ~LoopMarker();

  static LoopMarker *Scan(const fe::Method *tree);
  LoopMarker *LookUp(const fe::Stmt *stmt);

  void ScanOne();
  int GetStart();
  int GetEnd();
  bool CollectLoops(vector<LoopMarker *> *loops);

  fe::VarDecl *GetVarDecl();

private:
  void BuildMap();

  const fe::Method *method_;
  LoopMarker *parent_;
  int start_;
  int end_;
  vector<LoopMarker *> children_;
  // for root node.
  vector<LoopMarker *> loops_;
  std::map<const fe::Stmt *, LoopMarker *> loop_map_;
  // loop description.
  fe::VarDecl *var_decl_;
};

}  // namespace compiler

#endif  // _compiler_loop_marker_h_
