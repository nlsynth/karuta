#include "dfg/d_graph.h"

#include "dfg/d_module.h"
#include "dfg/resource_params.h"

DRegister::DRegister(enum RegType reg_type, DType *val_type) {
  data_type_ = val_type;
  reg_type_ = reg_type;
  num_ = 0;
  has_initial_ = false;
}

DType::DType(enum TypeClass type, int size) {
  type_ = type;
  size_ = size;
}

DState::DState(int id) : state_id_(id),
			 text_annotation_(NULL),
			 annotation_(NULL) {
}

DAnnotation::~DAnnotation() {
}

namespace dfg {

DGraph::DGraph(DModule *mod) : owner_module_(mod), pool_(new DGraphPool) {
  initial_state_ = NULL;
  last_state_ = NULL;
  last_tmp_reg_id_ = 0;
  last_resource_id_ = 0;
  last_insn_id_ = 0;
  last_state_id_ = 0;
  annotation_ = NULL;
  mod->graph_ = this;
}

DGraph::~DGraph() {
  delete annotation_;
}

}  // namespace dfg
