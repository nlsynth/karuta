// -*- C++ -*-
#ifndef _opt_resource_annotation_h_
#define _opt_resource_annotation_h_

namespace dfg {
class DGraph;
}  // namespace dfg

namespace opt {

void ll_optimize_graph(dfg::DGraph *g, int level);

}  // namespace opt

#endif  // _opt_resource_annotation_h_
