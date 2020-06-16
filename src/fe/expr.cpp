#include "fe/expr.h"

#include "base/dump_stream.h"
#include "fe/nodecode.h"

namespace fe {

Expr::Expr(NodeCode type)
  : type_(type), sym_(sym_null),
    func_(nullptr), args_(nullptr), lhs_(nullptr), rhs_(nullptr) {
}

enum NodeCode Expr::GetType() const {
  return type_;
}

ScannerPos &Expr::GetPos() {
  return pos_;
}

const iroha::Numeric &Expr::GetNum() const {
  return num_;
}

void Expr::SetNum(const iroha::Numeric &num) {
  num_ = num;
}

sym_t Expr::GetSym() const {
  return sym_;
}

void Expr::SetSym(sym_t sym) {
  sym_ = sym;
}

const string &Expr::GetString() {
  return str_;
}

void Expr::SetString(const string &str) {
  str_ = str;
}
  
Expr *Expr::GetFunc() const {
  return func_;
}

void Expr::SetFunc(Expr *func) {
  func_ = func;
}

Expr *Expr::GetArgs() const {
  return args_;
}

void Expr::SetArgs(Expr *args) {
  args_ = args;
}

Expr *Expr::GetLhs() const {
  return lhs_;
}

void Expr::SetLhs(Expr *lhs) {
  lhs_ = lhs;
}

Expr *Expr::GetRhs() const {
  return rhs_;
}

void Expr::SetRhs(Expr *rhs) {
  rhs_ = rhs;
}

void Expr::Dump() {
  DumpStream ds(cout);
  Dump(ds);
}

void Expr::Dump(DumpStream &ds) {
  if (IsBinOpNode(type_)) {
    ds.indent();
    ds.os << NodeName(type_) << "\n";
    ds.push_indent();
    lhs_->Dump(ds);
    rhs_->Dump(ds);
    ds.pop_indent();
    return;
  }
  switch (type_) {
  case EXPR_SYM:
    ds.indent();
    ds.os << sym_cstr(sym_);
    ds.os << "\n";
    break;
  case EXPR_STR:
    ds.indent();
    ds.os << "\"" << str_ << "\"\n";
    break;
  case EXPR_NUM:
    ds.indent();
    ds.os << num_.Format() << " " << num_.type_.Format() << "\n";
    break;
  case EXPR_FUNCALL:
    ds.indent();
    ds.os << "funcall\n";
    ds.push_indent();
    func_->Dump(ds);
    if (args_) {
      args_->Dump(ds);
    }
    ds.pop_indent();
    break;
  case UNIOP_BIT_INV:
  case UNIOP_LOGIC_INV:
  case UNIOP_POST_INC:
  case UNIOP_POST_DEC:
  case UNIOP_PRE_INC:
  case UNIOP_PRE_DEC:
  case UNIOP_PLUS:
  case UNIOP_MINUS:
    ds.indent();
    ds.os << NodeName(type_) << "\n";
    if (args_) {
      ds.push_indent();
      args_->Dump(ds);
      ds.pop_indent();
    }
    break;
  case EXPR_ELM_SYM_REF:
    ds.indent();
    ds.os << "elm_ref args:\n";
    ds.push_indent();
    args_->Dump(ds);
    ds.indent();
    ds.pop_indent();
    ds.os << "." << sym_cstr(sym_) << "\n";
    break;
  case EXPR_BIT_RANGE:
    ds.push_indent();
    ds.indent();
    ds.os << "bit_range:\n";
    args_->Dump(ds);
    ds.push_indent();
    lhs_->Dump(ds);
    rhs_->Dump(ds);
    ds.pop_indent();
    ds.pop_indent();
    break;
  case EXPR_TRI_TERM:
    ds.push_indent();
    ds.indent();
    ds.os << "tri_term:\n";
    args_->Dump(ds);
    ds.push_indent();
    ds.pop_indent();
    lhs_->Dump(ds);
    rhs_->Dump(ds);
    ds.pop_indent();
    break;
  case STMT_THREAD_DECL:
    ds.push_indent();
    ds.indent();
    ds.os << "thread_decl:\n";
    lhs_->Dump(ds);
    func_->Dump(ds);
    ds.pop_indent();
    break;
  default:
    CHECK(false) << "Unknown expr:" << NodeName(type_);
    break;
  }
}

void ExprSet::Dump(DumpStream &ds) {
  for (size_t i = 0; i < exprs.size(); ++i) {
    exprs[i]->Dump(ds);
  }
}

}  // namespace fe
