// -*- C++ -*-
#ifndef _pool_h_included_
#define _pool_h_included_

#include <vector>

template<class T>
class Pool {
public:
  ~Pool() {
    for (int i = 0; i < (int)ptrs_.size(); ++i) {
      delete ptrs_[i];
    }
  }
  void Add(T *p) {
    ptrs_.push_back(p);
  }
  std::vector<T *> ptrs_;
};

#endif // _pool_h_included_
