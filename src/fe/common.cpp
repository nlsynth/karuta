#include "fe/common.h"

#include "fe/enum_decl.h"
#include "fe/expr.h"
#include "fe/method.h"
#include "fe/stmt.h"
#include "fe/var_decl.h"

namespace fe {

Pool<EnumDecl> *NodePool::enums_;
Pool<Expr> *NodePool::exprs_;
Pool<ExprSet> *NodePool::expr_sets_;
Pool<Method> *NodePool::methods_;
Pool<Stmt> *NodePool::stmts_;
Pool<VarDecl> *NodePool::decls_;
Pool<VarDeclSet> *NodePool::decl_sets_;

void NodePool::Init() {
  enums_ = new Pool<EnumDecl>();
  exprs_ = new Pool<Expr>();
  expr_sets_ = new Pool<ExprSet>();
  methods_ = new Pool<Method>();
  stmts_ = new Pool<Stmt>();
  decls_ = new Pool<VarDecl>();
  decl_sets_ = new Pool<VarDeclSet>();
}

void NodePool::Release() {
  delete enums_;
  delete exprs_;
  delete expr_sets_;
  delete methods_;
  delete stmts_;
  delete decls_;
  delete decl_sets_;
}

void NodePool::AddEnumDecl(EnumDecl *decl) {
  enums_->Add(decl);
}

void NodePool::AddExpr(Expr *expr) {
  exprs_->Add(expr);
}

void NodePool::AddExprSet(ExprSet *expr_set) {
  expr_sets_->Add(expr_set);
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
