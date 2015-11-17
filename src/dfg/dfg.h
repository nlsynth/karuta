// -*- C++ -*-
#ifndef _dfg_dfg_h_
#define _dfg_dfg_h_

#include "nli.h"

#include "dfg/dfg_dump.h"
#include "dfg/d_graph.h"
#include "dfg/d_graph_annotation.h"
#include "dfg/d_graph_util.h"
#include "dfg/d_resource.h"
#include "dfg/d_insn.h"
#include "dfg/d_module.h"

namespace dfg {

class DRegister;
class DState;

class DFG {
public:
  static void Init();

  // for debug
  static string RegisterName(const DRegister *reg);
  static string StateName(const DState *st);
};

}  // namespace dfg

#endif  // _dfg_h_
