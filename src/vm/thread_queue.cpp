#include "vm/thread_queue.h"

#include "vm/thread.h"

namespace vm {

void ThreadQueue::AddThread(Thread *thr) {
  waiters.insert(thr);
}

void ThreadQueue::ResumeOne() {
  if (waiters.size() == 0) {
    return;
  }
  Thread *t = *(waiters.begin());
  waiters.erase(t);
  t->Resume();
}

void ThreadQueue::ResumeAll() {
  for (Thread *t : waiters) {
    t->Resume();
    notified.insert(t);
  }
  waiters.clear();
}

bool ThreadQueue::ClearIfNotified(Thread *thr) {
  if (notified.find(thr) != notified.end()) {
    notified.erase(thr);
    return true;
  }
  return false;
}

}  // namespace vm
