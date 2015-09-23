#include "fe/builder.h"

#include "numeric.h"
#include "fe/nodecode.h"
#include "fe/common.h"
#include "fe/expr.h"
#include "fe/stmt.h"
#include "fe/var_decl.h"

namespace fe {

Expr *Builder::NewExpr(NodeCode type) {
  Expr *expr = new Expr;
  expr->type_ = type;
  NodePool::AddExpr(expr);
  return expr;
}

Stmt *Builder::NewStmt(int type) {
  Stmt *stmt = new Stmt;
  NodePool::AddStmt(stmt);
  stmt->type_ = static_cast<NodeCode>(type);
  return stmt;
}

Expr *Builder::StrExpr(const string &str) {
  Expr *expr = NewExpr(EXPR_STR);
  expr->str_ = str;
  return expr;
}

Expr *Builder::SymExpr(sym_t sym) {
  Expr *expr = NewExpr(EXPR_SYM);
  expr->sym_ = sym;
  return expr;
}

Expr *Builder::NumExpr(uint64_t num) {
  Expr *expr = NewExpr(EXPR_NUM);
  Numeric::MakeConst(num, 0, &expr->num_);
  return expr;
}

Expr *Builder::BinopExpr(Expr *lhs, Expr *rhs, int op) {
  Expr *expr = NewExpr(static_cast<NodeCode>(op));
  expr->lhs_ = lhs;
  expr->rhs_ = rhs;
  return expr;
}

Expr *Builder::FuncallExpr(Expr *func, Expr *args) {
  Expr *expr = NewExpr(EXPR_FUNCALL);
  expr->func_ = func;
  expr->args_ = args;
  return expr;
}

// static
VarDecl *Builder::ModifiedVar(Expr *var, bool is_ptr, sym_t ns) {
  VarDecl *mv = new VarDecl;
  NodePool::AddVarDecl(mv);
  mv->name_expr = var;
  return mv;
}

// static
VarDecl *Builder::BuildVarDecl(sym_t type, const NumberWidth *w,
			       VarDecl *var) {
  var->type = type;
  var->width = w;
  return var;
}

sym_t Builder::TypeNameFromVarDeclSet(VarDeclSet *vds) {
  CHECK(vds->decls.size() > 0);
  return vds->decls[vds->decls.size() - 1]->type;
}

// static
Expr *Builder::IncDecExpr(Expr *val, int op, bool is_post) {
  if (!is_post) {
    if (op == UNIOP_POST_INC) {
      op = UNIOP_PRE_INC;
    } else {
      op = UNIOP_PRE_DEC;
    }
  }
  Expr* expr = NewExpr(static_cast<NodeCode>(op));
  expr->args_ = val;
  return expr;
}

// static
Expr *Builder::SignedExpr(int sign, Expr *arg) {
  if (sign == BINOP_ADD) {
    sign = UNIOP_PLUS;
  } else {
    sign = UNIOP_MINUS;
  }
  Expr *expr = NewExpr(static_cast<NodeCode>(sign));
  expr->args_ = arg;
  return expr;
}

// static
Expr *Builder::TriTerm(Expr *cond, Expr *lhs, Expr *rhs) {
  Expr *expr = NewExpr(EXPR_TRI_TERM);
  expr->args_ = cond;
  expr->lhs_ = lhs;
  expr->rhs_ = rhs;
  return expr;
}

// static
Expr *Builder::ElmRefExpr(Expr *arg, sym_t sym) {
  Expr *expr = NewExpr(EXPR_ELM_REF);
  expr->args_ = arg;
  expr->sym_ = sym;
  return expr;
}

// static
Expr *Builder::LogicInvertExpr(Expr *arg) {
  Expr *expr = NewExpr(UNIOP_LOGIC_INV);
  expr->args_ = arg;
  return expr;
}

// static
Expr *Builder::BitInvertExpr(Expr *arg) {
  Expr *expr = NewExpr(UNIOP_BIT_INV);
  expr->args_ = arg;
  return expr;
}

// static
VarDeclSet *Builder::ArgDeclList(VarDeclSet *decls, VarDecl *decl) {
  if (!decls) {
    decls = new VarDeclSet;
    NodePool::AddVarDeclSet(decls);
  }
  if (decl) {
    decls->decls.push_back(decl);
  }
  return decls;
}

// static
VarDeclSet *Builder::VarDeclList(VarDeclSet *decls, VarDecl *decl) {
  return ArgDeclList(decls, decl);
}

// static
VarDeclSet *Builder::ReturnDeclList(VarDeclSet *decls, VarDecl *decl) {
  return ArgDeclList(decls, decl);
}

// static
VarDecl *Builder::ReturnType(sym_t type_name, const NumberWidth *w) {
  VarDecl* v = new VarDecl;
  v->type = type_name;
  return v;
}

// static
void Builder::SetArrayLength(VarDecl *decl, int length) {
  decl->array_length = length;
}

// static
void Builder::SetArrayInitializer(VarDecl *decl,
				  ArrayInitializer *initializer) {
  decl->array_initializer = initializer;
  if (decl->array_length == 0) {
    decl->array_length = initializer->num_.size();
  }
}

// static
Expr *Builder::ArrayRefExpr(Expr *array, Expr *index) {
  Expr *expr = NewExpr(BINOP_ARRAY_REF);
  expr->lhs_ = array;
  expr->rhs_ = index;
  return expr;
}

// static
Expr *Builder::BitRangeRefExpr(Expr *val, Expr *msb, Expr *lsb) {
  Expr *expr = NewExpr(EXPR_BIT_RANGE);
  expr->args_ = val;
  expr->lhs_ = msb;
  expr->rhs_ = lsb;
  return expr;
}

// static
Expr *Builder::RefExpr(Expr *addr) {
  Expr *expr = NewExpr(UNIOP_REF);
  expr->args_ = addr;
  return expr;
}

}  // namespace fe
