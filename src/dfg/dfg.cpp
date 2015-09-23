// Copyright (C) Yusuke Tabata 2009-2015
//
// Basic data structures to represent the circuit behaviour.
//
#include "dfg/dfg.h"

#include <iostream>

namespace dfg {

string DFG::RegisterName(const DRegister *reg) {
  ostringstream os;
  if (!reg) {
    os << "ice:null";
  } else if (reg->reg_type_ == DRegister::REG_NORMAL) {
    os << "var:" << reg->reg_name_;
  } else if (reg->reg_type_ == DRegister::REG_WIRE) {
    os << "wire:" << reg->reg_name_;
  } else if (reg->reg_type_ == DRegister::REG_CONST) {
    os << "const:" << reg->num_;
  }
  return os.str();
}

string DFG::StateName(const DState *st) {
  ostringstream os;
  os << "s" << st->state_id_;
  return os.str();
}

void DFG::Init() {
  DOperatorUtil::InstallOperatorWithSideEffect(sym_branch);
  DOperatorUtil::InstallOperatorWithSideEffect(sym_memory);
  DOperatorUtil::InstallOperator(sym_assign, false);
  // Exclusive resource.
  DOperatorUtil::InstallOperator(sym_gt, true);
  DOperatorUtil::InstallOperator(sym_add, true);
  DOperatorUtil::InstallOperator(sym_sub, true);
  DOperatorUtil::InstallOperator(sym_mul, true);
  DOperatorUtil::InstallOperator(sym_array_ref, true);
  // Non exclusive resource.
  DOperatorUtil::InstallOperator(sym_eq, false);
  DOperatorUtil::InstallOperator(sym_or_reduce, false);
  DOperatorUtil::InstallOperator(sym_logic_inv, false);
  DOperatorUtil::InstallOperator(sym_bit_and, false);
  DOperatorUtil::InstallOperator(sym_bit_or, false);
  DOperatorUtil::InstallOperator(sym_bit_xor, false);
  DOperatorUtil::InstallOperator(sym_bit_not, false);
  DOperatorUtil::InstallOperator(sym_logic_and, false);
  DOperatorUtil::InstallOperator(sym_logic_or, false);
  DOperatorUtil::InstallOperator(sym_bit_sel, false);
  DOperatorUtil::InstallOperator(sym_bit_concat, false);
  // Side effect.
  DOperatorUtil::InstallOperatorWithSideEffect(sym_imported);
  DOperatorUtil::InstallOperatorWithSideEffect(sym_sub_module_call);
  DOperatorUtil::InstallOperatorWithSideEffect(sym_read_channel);
  DOperatorUtil::InstallOperatorWithSideEffect(sym_write_channel);
  DOperatorUtil::InstallOperatorWithSideEffect(sym_task_entry);
  // Target specific.
  DOperatorUtil::InstallOperatorWithSideEffect(sym_sram_if);
  DOperatorUtil::InstallOperator(sym_phi, true);
  DOperatorUtil::InstallOperator(sym_selector, false);
  // Pseudo resource for Phylo script.
  DOperatorUtil::InstallOperator(sym_lookup("funcall"), true);
  DOperatorUtil::InstallOperator(sym_lookup("transition"), true);
  DOperatorUtil::InstallOperator(sym_lookup("function_entry"), true);
  DOperatorUtil::InstallOperatorWithSideEffect(sym_sub_module_call);
}

}  // namespace dfg
