// -*- C++ -*-
#ifndef _dfg_d_graph_h_
#define _dfg_d_graph_h_

#include "nli.h"

#include "pool.h"
#include "dfg/d_insn.h"
#include "dfg/d_resource.h"

#include <list>

using std::list;

namespace dfg {

class DModule;
class DState;
class DRegister;

class DAnnotation {
public:
  virtual ~DAnnotation();
  virtual void Output(ostream &os) = 0;
};

class DGraphPool {
public:
  Pool<DRegister> registers_;
  Pool<DInsn> insns_;
  Pool<DState> states_;
  Pool<DResource> resources_;
};

class DType {
public:
  enum TypeClass {
    INT,
    ENUM,
  };

  DType(enum TypeClass type, int size);
  enum TypeClass type_;
  // width for INT, size for ENUM.
  int size_;
};

// register, constant, intermediate wire, I/O
//  declared variables and hidden variables to store intermediate variable.
class DRegister {
public:
  enum RegType {
    REG_NORMAL,
    // Variable in a state.
    REG_WIRE,
    REG_CONST,
  };

  DRegister(enum RegType reg_type, DType *val_type);
  enum RegType reg_type_;
  DType *data_type_;
  uint64_t num_;
  string reg_name_;
  // member sym
  bool has_initial_;
};

class DState {
public:
  DState(int id);
  int state_id_;
  list<DInsn *> insns_;
  const char *text_annotation_;
  DAnnotation *annotation_;
};

class DGraph {
public:
  DGraph(DModule *mod);
  ~DGraph();

  list<DState *> states_;
  list<DResource *> resources_;
  list<DRegister *> registers_;
  DState *initial_state_;
  DState *last_state_;

  int last_tmp_reg_id_;
  int last_resource_id_;
  int last_insn_id_;
  int last_state_id_;

  DModule *owner_module_;
  DAnnotation *annotation_;

  std::unique_ptr<DGraphPool> pool_;
};

}  // namespace dfg
using namespace dfg;

#endif  // _dfg_d_graph_h_
