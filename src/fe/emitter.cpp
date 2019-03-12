#include "fe/emitter.h"

#include "base/annotation.h"
#include "base/annotation_builder.h"
#include "base/status.h"
#include "fe/builder.h"
#include "fe/common.h"
#include "fe/expr.h"
#include "fe/method.h"
#include "fe/nodecode.h"
#include "fe/stmt.h"
#include "fe/var_decl.h"

namespace fe {

vector<MethodDecl> Emitter::method_stack_;
Annotation *Emitter::annotation_;
Annotation *Emitter::func_annotation_;

void Emitter::BeginFunction(Expr *name) {
  string formatted_name = FormatMethodName(name);
  Method *method = new Method(formatted_name);
  MethodDecl decl;
  decl.method_ = method;
  decl.name_expr_ = name;
  decl.name_ = formatted_name;
  method_stack_.push_back(decl);
  NodePool::AddMethod(method);
}

MethodDecl Emitter::EndFunction() {
  MethodDecl new_decl = CurrentMethod();
  method_stack_.pop_back();
  if (new_decl.name_expr_) {
    Stmt *stmt = BuildFuncDeclStmt(&new_decl);
    EmitStmt(stmt);
  }
  return new_decl;
}

string Emitter::GetFunctionName() {
  MethodDecl &decl = CurrentMethod();
  return decl.name_;
}

void Emitter::SetCurrentFunctionParams() {
  if (func_annotation_ == nullptr) {
    return;
  }
  MethodDecl &decl = CurrentMethod();
  decl.method_->SetAnnotation(func_annotation_);
  fe::VarDeclSet *args = decl.method_->GetArgs();
  if (args) {
    for (size_t i = 0; i < args->decls.size(); ++i) {
      fe::VarDecl *arg = args->decls[i];
      int width = 1;
      if (arg->GetType() == sym_int) {
	width = arg->GetWidth().GetWidth();
      } else {
	CHECK(arg->GetType() == sym_bool);
      }
      decl.method_->GetAnnotation()->AddPinDecl(arg->GetNameExpr()->GetSym(),
						false,
						width);
    }
  }
}

void Emitter::SetCurrentFunctionArgs(VarDeclSet *args) {
  MethodDecl &decl = CurrentMethod();
  decl.method_->SetArgs(args);
}

void Emitter::SetCurrentFunctionReturns(VarDeclSet *returns) {
  MethodDecl &decl = CurrentMethod();
  decl.method_->SetReturns(returns);
}

Annotation *Emitter::SetAnnotation(sym_t key, AnnotationKeyValueSet *values) {
  annotation_ = AnnotationBuilder::Build(key, values);
  return annotation_;
}

void Emitter::SetCurrentFunctionAnnotation(Annotation *an) {
  func_annotation_ = an;
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

void Emitter::EmitNop() {
  NumericLiteral nl;
  nl.value = 0;
  EmitExprStmt(Builder::NumExpr(nl));
}

void Emitter::EmitExprStmt(Expr *expr) {
  CHECK(expr);
  Stmt *stmt = NewStmt(STMT_EXPR);
  stmt->SetExpr(expr);
  EmitStmt(stmt);
}

Stmt *Emitter::BuildFuncDeclStmt(MethodDecl *decl) {
  Stmt *stmt = NewStmt(STMT_FUNCDECL);
  stmt->SetExpr(decl->name_expr_);
  stmt->SetMethodDef(decl->method_);
  return stmt;
}

void Emitter::EmitImportStmt(const char *str, sym_t name) {
  Stmt *stmt = NewStmt(STMT_IMPORT);
  stmt->SetString(string(str));
  stmt->SetSym(name);
  EmitStmt(stmt);
}

void Emitter::EmitVarDeclStmtSet(VarDeclSet *vds) {
  for (size_t i = 0; i < vds->decls.size(); ++i) {
    VarDecl *vd = vds->decls[i];
    ArrayShape *shape = vd->GetArrayShape();
    if (shape != nullptr) {
      if (method_stack_.size() > 1) {
	Status::os(Status::USER_ERROR)
	  << "Array declaration is allowed only in the top level.";
      }
    }
    Stmt *stmt = NewStmt(STMT_VARDECL);
    stmt->SetVarDecl(vd);
    EmitStmt(stmt);
  }
}

void Emitter::EmitEnumTypeDeclStmt(Expr *name, EnumDecl *decl) {
  Stmt *stmt = NewStmt(STMT_ENUM_DECL);
  stmt->SetExpr(name);
  stmt->SetEnumDecl(decl);
  EmitStmt(stmt);
}
  
Stmt *Emitter::EmitIfStmt(Expr *cond) {
  Stmt *stmt = NewStmt(STMT_IF);
  stmt->SetExpr(cond);
  stmt->SetLabel(false, true, sym_alloc_tmp_sym("_t"));
  stmt->SetLabel(false, false, sym_alloc_tmp_sym("_f"));
  stmt->SetLabel(true, false, sym_alloc_tmp_sym("_join"));
  EmitStmt(stmt);
  return stmt;
}

Stmt *Emitter::EmitForStmt(Expr *cond) {
  // ditto for If.
  Stmt *stmt = NewStmt(STMT_IF);
  stmt->SetExpr(cond);
  stmt->SetLabel(false, true, sym_alloc_tmp_sym("_t"));
  stmt->SetLabel(false, false, sym_alloc_tmp_sym("_f"));
  stmt->SetLabel(true, false, sym_alloc_tmp_sym("_join"));
  EmitLabel(stmt->GetLabel(true, false));
  EmitStmt(stmt);
  return stmt;
}

Stmt *Emitter::EmitWhileStmt(Expr *cond) {
  // ditto for For.
  return EmitForStmt(cond);
}

void Emitter::EmitDoWhileStmt(Stmt *stmt, Expr *cond) {
  stmt->SetExpr(cond);
  EmitStmt(stmt);
}

void Emitter::EmitLabel(sym_t label) {
  Stmt *stmt = NewStmt(STMT_LABEL);
  stmt->SetSym(label);
  EmitStmt(stmt);
}

void Emitter::EmitGoto(sym_t label) {
  Stmt *stmt = NewStmt(STMT_GOTO);
  stmt->SetSym(label);
  EmitStmt(stmt);
}

void Emitter::EmitReturnStmt(Expr *expr) {
  Stmt *stmt = NewStmt(STMT_RETURN);
  stmt->SetExpr(expr);
  EmitStmt(stmt);
}

void Emitter::EmitThreadDeclStmt(Expr *var, Expr *funcall) {
  Stmt *stmt = NewStmt(STMT_THREAD_DECL);
  Expr *expr = Builder::NewExpr(STMT_THREAD_DECL);
  expr->SetLhs(var);
  expr->SetFunc(funcall);
  stmt->SetExpr(expr);
  EmitStmt(stmt);
}

void Emitter::EmitChannelDeclStmt(Expr *var, bool is_primitive,
				  sym_t name,
				  const iroha::NumericWidth *width) {
  Stmt *stmt = NewStmt(STMT_CHANNEL_DECL);
  stmt->SetAnnotation(annotation_);
  EmitTypedObjStmt(stmt, var, is_primitive, name, width);
}

void Emitter::EmitMailboxDeclStmt(Expr *var, bool is_primitive,
				  sym_t name,
				  const iroha::NumericWidth *width) {
  Stmt *stmt = NewStmt(STMT_MAILBOX_DECL);
  EmitTypedObjStmt(stmt, var, is_primitive, name, width);
}

void Emitter::EmitTypedObjStmt(Stmt *stmt, Expr *var,
			       bool is_primitive, sym_t name,
			       const iroha::NumericWidth *width) {
  sym_t type_name = sym_null;
  sym_t obj_name = sym_null;
  if (is_primitive) {
    type_name = name;
  } else {
    obj_name = name;
  }
  stmt->SetSym(obj_name);
  stmt->SetExpr(var);
  auto w = WidthSpec::GetWidth(type_name, width);
  stmt->SetWidth(w);
  EmitStmt(stmt);
}

void Emitter::EmitStmt(Stmt *stmt) {
  MethodDecl &decl = CurrentMethod();
  auto &stmts = decl.method_->GetMutableStmts();
  stmts.push_back(stmt);
}

Stmt *Emitter::NewStmt(int type) {
  return Builder::NewStmt(type);
}

string Emitter::FormatMethodName(Expr *name) {
  if (name == nullptr) {
    return "{Top Level}";
  }
  string n;
  Expr *e = name;
  while (e->GetType() == EXPR_ELM_SYM_REF) {
    if (n.empty()) {
      n = sym_str(e->GetSym());
    } else {
      n = sym_str(e->GetSym()) + "." + n;
    }
    e = e->GetArgs();
  }
  if (n.empty()) {
    n = sym_cstr(e->GetSym());
  } else {
    n = sym_str(e->GetSym()) + "." + n;
  }
  return n;
}

}  // namespace fe
