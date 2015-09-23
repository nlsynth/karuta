#include "fe/emitter.h"

#include "fe/builder.h"
#include "fe/common.h"
#include "fe/expr.h"
#include "fe/method.h"
#include "fe/nodecode.h"
#include "fe/stmt.h"
#include "fe/var_decl.h"
#include "dfg/imported_resource.h"

namespace fe {

vector<MethodDecl> Emitter::method_stack_;

void Emitter::BeginFunction(Expr *name) {
  Method *method = new Method;
  MethodDecl decl;
  decl.method_ = method;
  decl.name_ = name;
  method_stack_.push_back(decl);
  NodePool::AddMethod(method);
}

MethodDecl Emitter::EndFunction() {
  MethodDecl new_decl = CurrentMethod();
  method_stack_.pop_back();
  if (new_decl.name_) {
    Stmt *stmt = BuildFuncDeclStmt(&new_decl);
    EmitStmt(stmt);
  }
  return new_decl;
}

void Emitter::SetCurrentFunctionArgs(VarDeclSet *args) {
  MethodDecl &decl = CurrentMethod();
  decl.method_->args_ = args;
}

void Emitter::SetCurrentFunctionReturns(VarDeclSet *returns) {
  MethodDecl &decl = CurrentMethod();
  decl.method_->returns_ = returns;
}

void Emitter::SetImportedResource(import_params *params) {
  MethodDecl &decl = CurrentMethod();
  decl.method_->imported_resource_ = import_resource(params);
  fe::VarDeclSet *args = decl.method_->args_;
  if (args) {
    for (size_t i = 0; i < args->decls.size(); ++i) {
      fe::VarDecl *arg = args->decls[i];
      int width = 1;
      if (arg->type == sym_int) {
	width = 32;
      } else {
	CHECK(arg->type == sym_bool);
      }
      decl.method_->imported_resource_->AddPinDecl(arg->name_expr->sym_,
						   false,
						   width);
    }
  }
}

void Emitter::BeginBlock() {
  Stmt *stmt = NewStmt(STMT_PUSH_BINDING);
  EmitStmt(stmt);
}

void Emitter::EndBlock() {
  Stmt *stmt = NewStmt(STMT_POP_BINDING);
  EmitStmt(stmt);
}

MethodDecl &Emitter::CurrentMethod() {
  return *(method_stack_.rbegin());
}

void Emitter::EmitExprStmt(Expr *expr) {
  CHECK(expr);
  Stmt *stmt = NewStmt(STMT_EXPR);
  stmt->expr_ = expr;
  EmitStmt(stmt);
}

Stmt *Emitter::BuildFuncDeclStmt(MethodDecl *decl) {
  Stmt *stmt = NewStmt(STMT_FUNCDECL);
  stmt->expr_ = decl->name_;
  stmt->method_def_ = decl->method_;
  return stmt;
}

void Emitter::EmitImportStmt(const char *str) {
  Stmt *stmt = NewStmt(STMT_IMPORT);
  stmt->str_ = string(str);
  EmitStmt(stmt);
}

void Emitter::EmitSpawnStmt(Expr *expr){
  Stmt *stmt = NewStmt(STMT_SPAWN);
  stmt->expr_ = expr;
  EmitStmt(stmt);
}

void Emitter::EmitVarDeclStmtSet(VarDeclSet *vds) {
  for (size_t i = 0; i < vds->decls.size(); ++i) {
    VarDecl *vd = vds->decls[i];
    Stmt *stmt = NewStmt(STMT_VARDECL);
    stmt->decl_ = vd;
    EmitStmt(stmt);
  }
}

Stmt *Emitter::EmitIfStmt(Expr *cond) {
  Stmt *stmt = NewStmt(STMT_IF);
  stmt->expr_ = cond;
  stmt->label_t_ = sym_alloc_tmp_sym("_t");
  stmt->label_f_ = sym_alloc_tmp_sym("_f");
  stmt->label_join_ = sym_alloc_tmp_sym("_join");
  EmitStmt(stmt);
  return stmt;
}

Stmt *Emitter::EmitForStmt(Expr *cond) {
  // ditto for If.
  Stmt *stmt = NewStmt(STMT_IF);
  stmt->expr_ = cond;
  stmt->label_t_ = sym_alloc_tmp_sym("_t");
  stmt->label_f_ = sym_alloc_tmp_sym("_f");
  stmt->label_join_ = sym_alloc_tmp_sym("_join");
  EmitLabel(stmt->label_join_);
  EmitStmt(stmt);
  return stmt;
}

void Emitter::EmitLabel(sym_t label) {
  Stmt *stmt = NewStmt(STMT_LABEL);
  stmt->sym_ = label;
  EmitStmt(stmt);
}

void Emitter::EmitGoto(sym_t label) {
  Stmt *stmt = NewStmt(STMT_GOTO);
  stmt->sym_ = label;
  EmitStmt(stmt);
}

void Emitter::EmitReturnStmt(Expr *expr) {
  Stmt *stmt = NewStmt(STMT_RETURN);
  stmt->expr_ = expr;
  EmitStmt(stmt);
}

void Emitter::EmitThreadDeclStmt(Expr *var, Expr *funcall) {
  Stmt *stmt = NewStmt(STMT_THREAD_DECL);
  Expr *expr = Builder::NewExpr(STMT_THREAD_DECL);
  expr->lhs_ = var;
  expr->func_ = funcall;
  stmt->expr_ = expr;
  EmitStmt(stmt);
}

void Emitter::EmitChannelDeclStmt(Expr *var, sym_t type_name,
				  const NumberWidth *width) {
  Stmt *stmt = NewStmt(STMT_CHANNEL_DECL);
  stmt->sym_ = type_name;
  stmt->expr_ = var;
  stmt->width_ = width;
  EmitStmt(stmt);
}

void Emitter::EmitStmt(Stmt *stmt) {
  MethodDecl &decl = CurrentMethod();
  decl.method_->stmts_.push_back(stmt);
}

Stmt *Emitter::NewStmt(int type) {
  return Builder::NewStmt(type);
}

}  // namespace fe
