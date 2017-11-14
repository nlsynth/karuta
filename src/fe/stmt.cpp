#include "fe/stmt.h"

#include "base/annotation.h"
#include "base/dump_stream.h"
#include "fe/enum_decl.h"
#include "fe/expr.h"
#include "fe/method.h"
#include "fe/nodecode.h"
#include "fe/var_decl.h"

namespace fe {

Stmt::Stmt(enum NodeCode type) : type_(type), annotation_(nullptr) {
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
    ds.os << "import: " << str_ << "\n";
    break;
  case STMT_SPAWN:
    ds.os << "spawn:\n";
    ds.push_indent();
    expr_->Dump(ds);
    ds.pop_indent();
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

void Stmt::SetAnnotation(Annotation *an) {
  annotation_ = an;
}

Annotation *Stmt::GetAnnotation() {
  return annotation_;
}

}  // namespace fe
