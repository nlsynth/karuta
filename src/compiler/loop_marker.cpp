#include "compiler/loop_marker.h"

#include "fe/method.h"
#include "fe/stmt.h"

namespace compiler {

LoopMarker::LoopMarker(const fe::Method *method, LoopMarker *parent, int start)
  : method_(method), parent_(parent), start_(start), end_(-1) {
}

LoopMarker::~LoopMarker() {
}

LoopMarker *LoopMarker::Scan(const fe::Method *tree) {
  LoopMarker *m = new LoopMarker(tree, nullptr, 0);
  m->ScanOne();
  auto &loops = m->GetLoops();
  m->CollectLoops(&loops);
  return m;
}

void LoopMarker::ScanOne() {
  auto &stmts = method_->GetStmts();
  for (size_t i = start_; i < stmts.size(); ++i) {
    Stmt *stmt = stmts[i];
    int type = stmt->GetType();
    if (type == fe::STMT_POP_BINDING) {
      end_ = i;
      return;
    }
    if (type == fe::STMT_PUSH_BINDING) {
      LoopMarker *m = new LoopMarker(method_, this, i + 1);
      children_.push_back(m);
      m->ScanOne();
      i = m->GetEnd();
    }
  }
}

int LoopMarker::GetEnd() {
  return end_;
}

bool LoopMarker::CollectLoops(vector<LoopMarker *> *loops) {
  bool hasInner = false;
  if (children_.size() > 0) {
    for (auto *c : children_) {
      hasInner |= c->CollectLoops(loops);
    }
  }
  if (start_ == 0) {
    return hasInner;
  }
  if (hasInner) {
    return true;
  }
  auto &stmts = method_->GetStmts();
  auto &push = stmts[start_ - 1];
  auto *an = push->GetAnnotation();
  if (an != nullptr) {
    loops->push_back(this);
    hasInner = true;
  }
  return hasInner;
}

vector<LoopMarker *> &LoopMarker::GetLoops() {
  return loops_;
}

}  // namespace compiler
