#include "fe/common.h"

#include "fe/expr.h"
#include "fe/method.h"
#include "fe/stmt.h"
#include "fe/var_decl.h"

namespace fe {

Pool<Expr> *NodePool::exprs_;
Pool<Method> *NodePool::methods_;
Pool<Stmt> *NodePool::stmts_;
Pool<VarDecl> *NodePool::decls_;
Pool<VarDeclSet> *NodePool::decl_sets_;

void NodePool::Init() {
  exprs_ = new Pool<Expr>();
  methods_ = new Pool<Method>();
  stmts_ = new Pool<Stmt>();
  decls_ = new Pool<VarDecl>();
  decl_sets_ = new Pool<VarDeclSet>();
}

void NodePool::Release() {
  delete exprs_;
  delete methods_;
  delete stmts_;
  delete decls_;
  delete decl_sets_;
}

void NodePool::AddExpr(Expr *expr) {
  exprs_->Add(expr);
}

void NodePool::AddMethod(Method *method) {
  methods_->Add(method);
}

void NodePool::AddVarDecl(VarDecl *decl) {
  decls_->Add(decl);
}

void NodePool::AddVarDeclSet(VarDeclSet *decl_set) {
  decl_sets_->Add(decl_set);
}

void NodePool::AddStmt(Stmt *stmt) {
  stmts_->Add(stmt);
}

}  // namespace fe
