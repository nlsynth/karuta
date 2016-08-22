// -*- C++ -*-
#ifndef _dfg_d_resource_h_
#define _dfg_d_resource_h_

#include "nli.h"

namespace dfg {

class DAnnotation;
class DArray;
class DModule;
class DType;
class ResourceParams;
  
// class of operation
class DOperator {
public:
  DOperator(sym_t type);
  sym_t type_;
  // e.g. assign resource can have multiple insn-s in a state. so
  // it is not exclusive.
  bool is_exclusive_;
  // has affect other than the output registers of the insn.
  bool has_side_effect_;
};

class DResource {
public:
  DResource(DOperator *opr);
  // key for this resource
  string name_; // for imported resource, array and sub module.
  int resource_id_;
  // class of operation.
  DOperator *opr_;
  ResourceParams *imported_resource_;
  DArray *array_;
  // for sub module call.
  DModule *module_;

  vector<DType *> input_types_;
  vector<DType *> output_types_;

  DAnnotation *annotation_;
};

class DArray {
public:
  DArray();

  int address_width;
  int data_width;
  vector<int> num_;
  bool may_write_;
};

class DChannel {
public:
  DChannel(int data_width);

  string channel_name_;
  DModule *writer_module_;
  DModule *reader_module_;
  int data_width_;
  // is_root (internal channel) or source (external channel).
  bool is_root_or_source_;
};

}  // namespace dfg
using namespace dfg;

#endif  // _dfg_d_graph_h_
