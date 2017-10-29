#include "fe/expr.h"

#include "base/dump_stream.h"
#include "fe/nodecode.h"

namespace fe {

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
