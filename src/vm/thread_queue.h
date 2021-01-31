// -*- C++ -*-
#ifndef _vm_thread_queue_h_
#define _vm_thread_queue_h_

#include <set>

#include "vm/common.h"

namespace vm {

class ThreadQueue {
 public:
  void AddThread(Thread *thr);
  void ResumeOne();
  void ResumeAll();
  bool ClearIfNotified(Thread *thr);

 private:
  std::set<Thread *> waiters;
  std::set<Thread *> notified;
};

}  // namespace vm

#endif  // _vm_thread_queue_h_
