#include "vm/insn.h"

#include "base/dump_stream.h"
#include "fe/expr.h"
#include "fe/stmt.h"
#include "vm/opcode.h"
#include "vm/register.h"
#include "vm/value.h"

namespace vm {

Insn::Insn()
    : obj_reg_(nullptr),
      method_(nullptr),
      jump_target_(-1),
      label_(nullptr),
      insn_expr_(nullptr),
      insn_stmt_(nullptr) {}

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
  if (op_ == OP_ARRAY_WRITE || op_ == OP_TL_ARRAY_WRITE_WITH_CHECK) {
    ds.os << sym_cstr(insn_expr_->GetSym()) << "[]";
  }
  if (op_ == OP_ARRAY_READ) {
    ds.os << sym_cstr(insn_expr_->GetSym()) << "[]";
  }
  if (op_ == OP_FUNCALL || op_ == OP_TL_FUNCALL_WITH_CHECK ||
      op_ == OP_FUNCALL_DONE || op_ == OP_TL_FUNCALL_DONE_WITH_CHECK) {
    if (insn_expr_ != nullptr) {
      ds.os << " " << sym_cstr(insn_expr_->GetFunc()->GetSym()) << "()";
    }
  }
}

bool InsnType::IsComparison(int op) {
  if (op == OP_LT || op == OP_GT || op == OP_LTE || op == OP_GTE ||
      op == OP_EQ || op == OP_NE) {
    return true;
  }
  return false;
}

bool InsnType::IsSameWidthNumBinOp(int op) {
  if (op == OP_ADD || op == OP_TL_ADD_MAY_WITH_TYPE || op == OP_SUB ||
      op == OP_TL_SUB_MAY_WITH_TYPE || op == OP_MUL ||
      op == OP_TL_MUL_MAY_WITH_TYPE || op == OP_DIV ||
      op == OP_TL_DIV_MAY_WITH_TYPE || op == OP_AND || op == OP_OR ||
      op == OP_XOR) {
    return true;
  }
  return false;
}

bool InsnType::IsShift(int op) {
  if (op == OP_LSHIFT || op == OP_RSHIFT) {
    return true;
  }
  return false;
}

const string InsnOpUtils::Str(Insn *insn) {
  if (insn->insn_expr_ != nullptr) {
    // This value is from the parse tree.
    return insn->insn_expr_->GetString();
  }
  // From compiler.
  return sym_str(insn->label_);
}

bool ByteCodeDebugMode::IsEnabled(const string &flags) {
  return !(flags.empty()) && !PreExec(flags);
}

bool ByteCodeDebugMode::PreExec(const string &flags) {
  return flags.find("c") != string::npos;
}

}  // namespace vm
