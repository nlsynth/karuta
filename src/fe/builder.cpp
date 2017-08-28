#include "fe/builder.h"

#include "base/pool.h"
#include "fe/common.h"
#include "fe/enum_decl.h"
#include "fe/expr.h"
#include "fe/nodecode.h"
#include "fe/stmt.h"
#include "fe/var_decl.h"
#include "numeric/numeric_op.h"  // from iroha

namespace fe {

static vector<iroha::NumericWidth *> Width_list;
static Pool<iroha::NumericWidth> pool;

WidthSpec WidthSpec::Int(bool is_signed, int width, bool is_ptr) {
  WidthSpec s;
  s.width = WidthSpec::MakeIntPtr(is_signed, width);
  s.name = sym_null;
  s.is_primitive = false;
  s.is_ptr = is_ptr;
  return s;
}

WidthSpec WidthSpec::Name(sym_t name, bool is_primitive, bool is_ptr) {
  WidthSpec s;
  s.width = WidthSpec::MakeIntPtr(false, 32);
  s.name = name;
  s.is_primitive = is_primitive;
  s.is_ptr = is_ptr;
  return s;
}

const iroha::NumericWidth *WidthSpec::MakeIntPtr(bool is_signed, int int_part) {
  for (auto *nw : Width_list) {
    if (nw->IsSigned() == is_signed &&
	nw->GetWidth() == int_part) {
      return nw;
    }
  }
  auto *nw = new iroha::NumericWidth(is_signed, int_part);
  pool.Add(nw);
  Width_list.push_back(nw);
  return nw;
}

const iroha::NumericWidth *WidthSpec::ToPtr(const iroha::NumericWidth &w) {
  return MakeIntPtr(w.IsSigned(), w.GetWidth());
}

const iroha::NumericWidth WidthSpec::GetWidth(sym_t name,
					      const iroha::NumericWidth *w) {
  if (w != nullptr) {
    return *w;
  }
  if (name == sym_bool) {
    return iroha::NumericWidth(false, 0);
  }
  // sym_int.
  return iroha::NumericWidth(false, 32);
}

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

Expr *Builder::NumExpr(NumericLiteral num) {
  Expr *expr = NewExpr(EXPR_NUM);
  iroha::Op::MakeConst(num.value, &expr->num_);
  if (num.width > -1) {
    expr->num_.type_.SetWidth(num.width);
  }
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

VarDecl *Builder::BuildVarDecl(Expr *var_expr, bool is_primitive, bool is_ptr,
			       sym_t type, const iroha::NumericWidth *w) {
  VarDecl *var = new VarDecl;
  NodePool::AddVarDecl(var);
  var->SetNameExpr(var_expr);
  if (is_ptr) {
    var->SetPtr(true);
  }
  sym_t obj_name = sym_null;
  sym_t type_name = sym_null;
  if (is_primitive) {
    type_name = type;
  } else {
    obj_name = type;
  }
  var->SetType(type_name);
  var->SetWidth(WidthSpec::GetWidth(type_name, w));
  var->SetObjectName(obj_name);
  return var;
}

void Builder::SetVarDeclAnnotation(VarDecl *decl, Annotation *an) {
  decl->SetAnnotation(an);
}

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

Expr *Builder::TriTerm(Expr *cond, Expr *lhs, Expr *rhs) {
  Expr *expr = NewExpr(EXPR_TRI_TERM);
  expr->args_ = cond;
  expr->lhs_ = lhs;
  expr->rhs_ = rhs;
  return expr;
}

Expr *Builder::ElmSymRefExpr(Expr *arg, sym_t sym) {
  Expr *expr = NewExpr(EXPR_ELM_SYM_REF);
  expr->args_ = arg;
  expr->sym_ = sym;
  return expr;
}

Expr *Builder::LogicInvertExpr(Expr *arg) {
  Expr *expr = NewExpr(UNIOP_LOGIC_INV);
  expr->args_ = arg;
  return expr;
}

Expr *Builder::BitInvertExpr(Expr *arg) {
  Expr *expr = NewExpr(UNIOP_BIT_INV);
  expr->args_ = arg;
  return expr;
}

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

ExprSet *Builder::ExprList(ExprSet *exprs, Expr *expr) {
  if (exprs == nullptr) {
    exprs = new ExprSet;
    NodePool::AddExprSet(exprs);
  }
  exprs->exprs.push_back(expr);
  return exprs;
}

EnumDecl *Builder::EnumItemList(EnumDecl *decl, sym_t item) {
  if (decl == nullptr) {
    decl = new EnumDecl;
    NodePool::AddEnumDecl(decl);
  }
  decl->items.push_back(item);
  return decl;
}

VarDeclSet *Builder::VarDeclList(VarDeclSet *decls, VarDecl *decl) {
  return ArgDeclList(decls, decl);
}

VarDeclSet *Builder::ReturnDeclList(VarDeclSet *decls, VarDecl *decl) {
  return ArgDeclList(decls, decl);
}

VarDecl *Builder::ReturnType(bool is_primitive, sym_t type,
			     const iroha::NumericWidth *w) {
  VarDecl *v = new VarDecl;
  NodePool::AddVarDecl(v);
  sym_t type_name = sym_null;
  sym_t obj_name = sym_null;
  if (is_primitive) {
    type_name = type;
  } else {
    obj_name = type;
  }
  v->SetType(type_name);
  v->SetWidth(WidthSpec::GetWidth(type_name, w));
  v->SetObjectName(obj_name);
  return v;
}

void Builder::SetArrayLength(VarDecl *decl, int length) {
  decl->SetArrayLength(length);
}

void Builder::SetArrayInitializer(VarDecl *decl,
				  ArrayInitializer *initializer) {
  decl->SetArrayInitializer(initializer);
  if (decl->GetArrayLength() == 0) {
    decl->SetArrayLength(initializer->num_.size());
  }
}

Expr *Builder::ArrayRefExpr(Expr *array, Expr *index) {
  Expr *expr = NewExpr(BINOP_ARRAY_REF);
  expr->lhs_ = array;
  expr->rhs_ = index;
  return expr;
}

Expr *Builder::BitRangeRefExpr(Expr *val, Expr *msb, Expr *lsb) {
  Expr *expr = NewExpr(EXPR_BIT_RANGE);
  expr->args_ = val;
  expr->lhs_ = msb;
  expr->rhs_ = lsb;
  return expr;
}

Expr *Builder::RefExpr(Expr *addr) {
  Expr *expr = NewExpr(UNIOP_REF);
  expr->args_ = addr;
  return expr;
}

Stmt *Builder::DoWhileStmt() {
  // Similar to Emitter::EmitForStmt(), but this doesn't emit.
  Stmt *stmt = NewStmt(STMT_IF);
  stmt->label_t_ = sym_alloc_tmp_sym("_t");
  stmt->label_f_ = sym_alloc_tmp_sym("_f");
  stmt->label_join_ = sym_alloc_tmp_sym("_join");
  return stmt;
}

}  // namespace fe
