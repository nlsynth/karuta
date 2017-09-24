#include "compiler/reg_checker.h"

#include "vm/insn.h"
#include "vm/method.h"
#include "vm/opcode.h"

#include <list>
#include <set>
using std::list;
using std::set;

namespace compiler {

RegChecker::RegChecker(vm::Method *method) : method_(method) {
}

void RegChecker::Check() {
  if (method_->GetNumReturnRegisters() == 0) {
    return;
  }
  // Collects all return registers.
  set<vm::Register *> rets;
  int num_args = method_->GetNumArgRegisters();
  int num_rets = method_->GetNumReturnRegisters();
  for (int i = 0; i < num_rets; ++i) {
    rets.insert(method_->method_regs_[i + num_args]);
  }
  // Traverses from initial insn.
  list<int> frontier;
  frontier.push_back(0);
  set<vm::Insn *> visited;
  while (frontier.size() > 0) {
    int f = *(frontier.begin());
    frontier.pop_front();
    if (f >= method_->insns_.size()) {
      continue;
    }
    vm::Insn *insn = method_->insns_[f];
    if (visited.find(insn) != visited.end()) {
      continue;
    }
    visited.insert(insn);
    // Stops traversal, if the insn assigns to one of return regs.
    // (assuming other return regs are also assigned)
    bool has_assign = false;
    for (vm::Register *dst : insn->dst_regs_) {
      if (rets.find(dst) != rets.end()) {
	has_assign = true;
      }
    }
    if (has_assign) {
      continue;
    }
    // Pushes next state for further traversal.
    if (insn->op_ == vm::OP_GOTO) {
      frontier.push_back(insn->jump_target_);
    } else if (insn->op_ == vm::OP_IF) {
      frontier.push_back(insn->jump_target_);
      frontier.push_back(f + 1);
    } else {
      frontier.push_back(f + 1);
    }
  }
  // There is at least one path to reach the last insn.
  if (visited.find(method_->insns_[method_->insns_.size() - 1])
      != visited.end()) {
    // TODO: Fail softly and show the function name.
    CHECK(false) << "0 return values...\n";
  }
}

}  // namespace compiler
