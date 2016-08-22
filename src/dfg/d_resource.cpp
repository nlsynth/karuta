#include "dfg/d_resource.h"

namespace dfg {

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

DArray::DArray() {
  may_write_ = false;
}

DChannel::DChannel(int data_width) : writer_module_(NULL), reader_module_(NULL),
				     data_width_(data_width),
				     is_root_or_source_(false) {
}

}  // namespace dfg
