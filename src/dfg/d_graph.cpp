#include "dfg/d_graph.h"

#include "dfg/d_module.h"
#include "dfg/imported_resource.h"

DArray::DArray() {
  may_write_ = false;
}

DChannel::DChannel(int data_width) : writer_module_(NULL), reader_module_(NULL),
				     data_width_(data_width) {
}

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

DOperator::DOperator(sym_t type) {
  type_ = type;
  is_exclusive_ = true;
  has_side_effect_ = false;
}

DResource::DResource(DOperator *opr) {
  opr_ = opr;
  imported_resource_ = NULL;
  annotation_ = NULL;
  array_ = NULL;
  module_ = NULL;
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
