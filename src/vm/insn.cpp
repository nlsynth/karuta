#include "vm/insn.h"

#include "dump_stream.h"
#include "fe/expr.h"
#include "fe/stmt.h"
#include "vm/opcode.h"
#include "vm/register.h"
#include "vm/value.h"

namespace vm {

Insn::Insn() : obj_reg_(NULL), method_(NULL), jump_target_(-1), label_(NULL),
	       insn_expr_(NULL), insn_stmt_(NULL) {
}

void Insn::Dump() const {
  DumpStream ds(cout);
  Dump(ds);
}

void Insn::Dump(DumpStream &ds) const {
  if (dst_regs_.size() > 0) {
    for (size_t i = 0; i < dst_regs_.size(); ++i) {
      if (i > 0) {
	ds.os << " ";
      }
      ds.os << "r" << dst_regs_[i]->id_;
    }
    ds.os << " <- ";
  }
  if (obj_reg_) {
    ds.os << "r" << obj_reg_->id_ << "...";
  }
  ds.os << OpCodeName(op_);
  if (src_regs_.size() > 0) {
    ds.os << "(";
    for (size_t i = 0; i < src_regs_.size(); ++i) {
      if (i > 0) {
	ds.os << " ";
      }
      ds.os << "r" << src_regs_[i]->id_;
    }
    ds.os << ")";
  }
  if (jump_target_ > -1) {
    ds.os << " -> next, " << jump_target_;
  }
  if (method_) {
    ds.os << " method";
  }
  if (label_) {
    ds.os << " " << sym_cstr(label_) << ":";
  }
  if (op_ == OP_ARRAY_WRITE) {
    ds.os << sym_cstr(insn_expr_->sym_) << "[]";
  }
  if (op_ == OP_ARRAY_READ) {
    ds.os << sym_cstr(insn_expr_->sym_) << "[]";
  }
  if (op_ == OP_FUNCALL || op_ == OP_FUNCALL_DONE) {
    ds.os << " " << sym_cstr(insn_expr_->func_->sym_) << "()";
  }
}

bool InsnType::IsComparison(int op) {
  if (op == OP_LT || op == OP_GT ||
      op == OP_LTE || op == OP_GTE ||
      op == OP_EQ || op == OP_NE) {
    return true;
  }
  return false;
}

bool InsnType::IsNumCalculation(int op) {
  if (op == OP_ADD || op == OP_SUB ||
      op == OP_MUL) {
    return true;
  }
  return false;
}

const string &InsnOpUtils::Str(Insn *insn) {
  return insn->insn_expr_->str_;
}

}  // namespace vm
