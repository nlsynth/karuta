// Optimization depending on hardware implementation details.
#include "opt/resource_annotation.h"

#include "dfg/dfg.h"

namespace opt {

class resource_annotation : public DAnnotation {
public:
  resource_annotation(bool is_root);
  virtual ~resource_annotation() {};
  virtual void Output(std::ostream &os);

  int area;
  int latency;
private:
  bool is_root_;
};

resource_annotation::resource_annotation(bool is_root) {
  area = 0;
  latency = 0;
  is_root_ = is_root;
}

void resource_annotation::Output(std::ostream &os) {
  if (area) {
    os << "area:" << area;
  }
  if (latency) {
    if (area) {
      os << ", ";
    }
    os <<" latency:" << latency;
  }
  if (!is_root_) {
    return ;
  }
  int mhz = 1000000 / latency;
  os << " " << mhz << "MHz";
}

static int get_area(DAnnotation *a) {
  resource_annotation *r = (resource_annotation *)a;
  return r->area;
}

static void set_area(DAnnotation *a, int area) {
  resource_annotation *r = (resource_annotation *)a;
  r->area = area;
}

static int get_latency(DAnnotation *a) {
  resource_annotation *r = (resource_annotation *)a;
  return r->latency;
}

static void set_latency(DAnnotation *a, int latency) {
  resource_annotation *r = (resource_annotation *)a;
  r->latency = latency;
}

static void update_module(DGraph *g) {
  int total_area = 0;
  std::list<DResource *>::iterator it;
  for (it = g->resources_.begin(); it != g->resources_.end(); it++) {
    total_area += get_area((*it)->annotation_);
  }
  set_area(g->annotation_, total_area);
  //
  int max_latency = 0;
  std::list<DState *>::iterator jt;
  for (jt = g->states_.begin(); jt != g->states_.end(); jt++) {
    int latency = get_latency((*jt)->annotation_);
    if (latency > max_latency) {
      max_latency = latency;
    }
  }
  set_latency(g->annotation_, max_latency);
}

static void annotate_graph(DGraph *g) {
  // graph it self
  g->annotation_ = new resource_annotation(true);
  // states
  for (list<DState *>::iterator it = g->states_.begin(); it != g->states_.end(); it++) {
    DState *s = (*it);
    s->annotation_ = new resource_annotation(false);
    set_latency(s->annotation_, 1000);
  }
  // resources
  std::list<DResource *>::iterator jt;
  for (jt = g->resources_.begin(); jt != g->resources_.end(); jt++) {
    DResource *r = (*jt);
    r->annotation_ = new resource_annotation(false);
    set_area(r->annotation_, 1);
  }

  update_module(g);
}

void ll_optimize_graph(DGraph *g, int level) {
  annotate_graph(g);
}

resource_annotation *get_resource_annotation(DAnnotation *a) {
  return (resource_annotation *)a;
}

}  // namespace opt
