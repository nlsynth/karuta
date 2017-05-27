#include "fe/builder.h"

#include "base/pool.h"
#include "fe/common.h"
#include "fe/enum_decl.h"
#include "fe/expr.h"
#include "fe/nodecode.h"
#include "fe/stmt.h"
#include "fe/var_decl.h"
#include "numeric/numeric.h"

namespace fe {

static vector<iroha::NumericWidth *> Width_list;
static Pool<iroha::NumericWidth> pool;

WidthSpec WidthSpec::Int(bool is_signed, int width) {
  WidthSpec s;
  s.width = WidthSpec::MakeIntPtr(is_signed, width);
  s.name = sym_null;
  return s;
}

WidthSpec WidthSpec::Name(sym_t name) {
  WidthSpec s;
  s.width = WidthSpec::MakeIntPtr(false, 32);
  s.name = name;
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

const iroha::NumericWidth WidthSpec::DeRef(const iroha::NumericWidth *w) {
  if (w == nullptr) {
    return iroha::NumericWidth(false, 32);
  }
  return *w;
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

Expr *Builder::NumExpr(uint64_t num) {
  Expr *expr = NewExpr(EXPR_NUM);
  iroha::Op::MakeConst(num, &expr->num_);
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

VarDecl *Builder::ModifiedVar(Expr *var, bool is_ptr, sym_t ns) {
  VarDecl *mv = new VarDecl;
  NodePool::AddVarDecl(mv);
  mv->SetNameExpr(var);
  return mv;
}

VarDecl *Builder::BuildVarDecl(sym_t type, const iroha::NumericWidth *w,
			       sym_t object_name, Annotation *an,
			       VarDecl *var) {
  var->SetType(type);
  var->SetWidth(WidthSpec::DeRef(w));
  var->SetObjectName(object_name);
  var->SetAnnotation(an);
  return var;
}

sym_t Builder::TypeNameFromVarDeclSet(VarDeclSet *vds) {
  CHECK(vds->decls.size() > 0);
  return vds->decls[vds->decls.size() - 1]->GetType();
}

WidthSpec Builder::GetWidthSpecFromVarDeclSet(VarDeclSet *vds) {
  CHECK(vds->decls.size() > 0);
  auto *vdd = vds->decls[vds->decls.size() - 1];
  WidthSpec ws;
  ws.width = WidthSpec::ToPtr(vdd->GetWidth());
  ws.name = vdd->GetObjectName();
  return ws;
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

VarDecl *Builder::ReturnType(sym_t type_name, const iroha::NumericWidth *w,
			     sym_t object_name) {
  VarDecl *v = new VarDecl;
  NodePool::AddVarDecl(v);
  v->SetType(type_name);
  v->SetWidth(WidthSpec::DeRef(w));
  v->SetObjectName(object_name);
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
