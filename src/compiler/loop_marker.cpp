#include "compiler/loop_marker.h"

#include "fe/method.h"
#include "fe/stmt.h"

namespace compiler {

LoopMarker::LoopMarker(const fe::Method *method, LoopMarker *parent, int start)
  : method_(method), parent_(parent), start_(start), end_(-1),
    var_decl_(nullptr), annotation_(nullptr) {
}

LoopMarker::~LoopMarker() {
  for (auto *m : children_) {
    delete m;
  }
}

LoopMarker *LoopMarker::Scan(const fe::Method *tree) {
  LoopMarker *rootMarker = new LoopMarker(tree, nullptr, 0);
  rootMarker->ScanOne();
  rootMarker->CollectLoops(nullptr);
  return rootMarker;
}

LoopMarker *LoopMarker::LookUp(const fe::Stmt *stmt) {
  auto it = loop_map_.find(stmt);
  if (it == loop_map_.end()) {
    return nullptr;
  }
  return it->second;
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

int LoopMarker::GetStart() {
  return start_;
}

int LoopMarker::GetEnd() {
  return end_;
}

bool LoopMarker::CollectLoops(vector<LoopMarker *> *loops) {
  if (loops == nullptr) {
    loops = &loops_;
  }
  bool hasInner = false;
  if (children_.size() > 0) {
    for (auto *c : children_) {
      hasInner |= c->CollectLoops(loops);
    }
  }
  if (start_ == 0) {
    BuildMap();
    return hasInner;
  }
  if (hasInner) {
    return true;
  }
  auto &stmts = method_->GetStmts();
  auto *push = stmts[start_ - 1];
  auto *an = push->GetAnnotation();
  if (an == nullptr) {
    return hasInner;
  }
  auto *vd = stmts[start_];
  if (vd->GetType() != fe::STMT_VARDECL) {
    return hasInner;
  }
  var_decl_ = vd->GetVarDecl();
  annotation_ = an;
  loops->push_back(this);
  return true;
}

void LoopMarker::BuildMap() {
  for (auto *m : loops_) {
    auto &stmts = method_->GetStmts();
    fe::Stmt *stmt = stmts[m->GetStart() - 1];
    loop_map_[stmt] = m;
  }
}

fe::VarDecl *LoopMarker::GetVarDecl() {
  return var_decl_;
}

Annotation *LoopMarker::GetAnnotation() {
  return annotation_;
}

}  // namespace compiler
