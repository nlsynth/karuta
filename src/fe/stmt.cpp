#include "fe/stmt.h"

#include "base/dump_stream.h"
#include "fe/enum_decl.h"
#include "fe/expr.h"
#include "fe/method.h"
#include "fe/nodecode.h"
#include "fe/var_decl.h"
#include "karuta/annotation.h"

namespace fe {

Stmt::Stmt(enum NodeCode type)
  : type_(type), expr_(nullptr), sym_(sym_null), decl_(nullptr),
    enum_(nullptr), annotation_(nullptr), method_def_(nullptr) {
  label_t_ = sym_null;
  label_f_ = sym_null;
  label_join_ = sym_null;
}

void Stmt::Dump() {
  DumpStream ds(cout);
  Dump(ds);
}

void Stmt::Dump(DumpStream &ds) {
  ds.indent();
  switch (type_) {
  case STMT_EXPR:
    ds.os << "expr_stmt:\n";
    ds.push_indent();
    expr_->Dump(ds);
    ds.pop_indent();
    break;
  case STMT_FUNCDECL:
    ds.os << "funcdecl:\n";
    ds.push_indent();
    expr_->Dump(ds);
    method_def_->Dump(ds);
    ds.pop_indent();
    break;
  case STMT_IMPORT:
    ds.os << "import:";
    if (sym_ != sym_null) {
      ds.os << " " << str_ << " as " << sym_cstr(sym_);
    }
    ds.os << "\n";
    break;
  case STMT_VARDECL:
    ds.os << "vardecl:\n";
    ds.push_indent();
    decl_->Dump(ds);
    ds.pop_indent();
    break;
  case STMT_THREAD_DECL:
    ds.os << "thread_decl:\n";
    ds.push_indent();
    expr_->Dump(ds);
    ds.pop_indent();
    break;
  case STMT_CHANNEL_DECL:
  case STMT_MAILBOX_DECL:
    if (type_ == STMT_CHANNEL_DECL) {
      ds.os << "channel_decl:\n";
    } else {
      ds.os << "mailbox_decl:\n";
    }
    ds.push_indent();
    ds.indent();
    ds.os << sym_cstr(sym_) << "\n";
    expr_->Dump(ds);
    ds.indent();
    ds.os << width_.Format();
    ds.os << "\n";
    ds.pop_indent();
    break;
  case STMT_ENUM_DECL:
    ds.os << "enum:\n";
    ds.push_indent();
    expr_->Dump(ds);
    enum_->Dump(ds);
    ds.pop_indent();
    break;
  case STMT_IF:
    ds.os << "if:\n";
    ds.indent();
    ds.os << " " << sym_cstr(label_t_) << " " << sym_cstr(label_f_)
	  << " " << sym_cstr(label_join_) << "\n";
    ds.push_indent();
    expr_->Dump(ds);
    ds.pop_indent();
    break;
  case STMT_LABEL:
    ds.os << "label:" << sym_cstr(sym_) << "\n";
    break;
  case STMT_GOTO:
    ds.os << "goto:" << sym_cstr(sym_) << "\n";
    break;
  case STMT_RETURN:
    ds.os << "return:\n";
    if (expr_) {
      ds.push_indent();
      expr_->Dump(ds);
      ds.pop_indent();
    }
    break;
  case STMT_PUSH_BINDING:
    ds.os << "{\n";
    break;
  case STMT_POP_BINDING:
    ds.os << "}\n";
    break;
  default:
    CHECK(false) << "Unknown stmt:" << NodeName(type_);
    break;
  }
  if (annotation_ != nullptr) {
    ds.push_indent();
    ds.indent();
    annotation_->Dump(ds.os);
    ds.os << "\n";
    ds.pop_indent();
  }
}

enum NodeCode Stmt::GetType() const {
  return type_;
}

void Stmt::SetAnnotation(Annotation *an) {
  annotation_ = an;
}

Annotation *Stmt::GetAnnotation() {
  return annotation_;
}

Expr *Stmt::GetExpr() const {
  return expr_;
}

void Stmt::SetExpr(Expr *expr) {
  expr_ = expr;
}

sym_t Stmt::GetSym() const {
  return sym_;
}

void Stmt::SetSym(sym_t sym) {
  sym_ = sym;
}

Method *Stmt::GetMethodDef() const {
  return method_def_;
}

void Stmt::SetMethodDef(Method *method_def) {
  method_def_ = method_def;
}

const string &Stmt::GetString() {
  return str_;
}

void Stmt::SetString(const string &str) {
  str_ = str;
}

VarDecl *Stmt::GetVarDecl() {
  return decl_;
}

void Stmt::SetVarDecl(VarDecl *decl) {
  decl_ = decl;
}

EnumDecl *Stmt::GetEnumDecl() {
  return enum_;
}

void Stmt::SetEnumDecl(EnumDecl *decl) {
  enum_ = decl;
}

iroha::NumericWidth &Stmt::GetWidth() {
  return width_;
}

void Stmt::SetWidth(iroha::NumericWidth &width) {
  width_ = width;
}

sym_t Stmt::GetLabel(bool is_join, bool is_t) {
  if (is_join) {
    return label_join_;
  } else {
    if (is_t) {
      return label_t_;
    } else {
      return label_f_;
    }
  }
}

void Stmt::SetLabel(bool is_join, bool is_t, sym_t label) {
  if (is_join) {
    label_join_ = label;
  } else {
    if (is_t) {
      label_t_ = label;
    } else {
      label_f_ = label;
    }
  }
}

}  // namespace fe
