// -*- C++ -*-
#ifndef _base_pool_h_
#define _base_pool_h_

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

#endif  // _base_pool_h_
