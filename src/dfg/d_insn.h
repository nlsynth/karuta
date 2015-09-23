// -*- C++ -*-
#ifndef _dfg_d_insn_h_
#define _dfg_d_insn_h_

#include <string>
#include <vector>

using std::string;
using std::vector;

namespace dfg {

class DAnnotation;
class DResource;
class DRegister;
class DState;

class DInsn {
public:
  DInsn(DResource *r, int id);
  ~DInsn();

  int insn_id_;
  DResource *resource_;
  vector<DRegister *> inputs_;
  vector<DRegister *> outputs_;
  // for branch unit
  vector<DState *> targets_;
  // for function call unit
  string func_name_;

  DAnnotation *annotation_;
};

class DInsnUtil {
public:
  static bool HasSideEffect(DInsn *insn);
};

}  // namespace dfg

#endif  // _dfg_d_insn_h_
