#include "vm/thread_queue.h"

#include "vm/thread.h"

namespace vm {

void ThreadQueue::AddThread(Thread *thr) {
  CHECK(thr->IsRunnable());
  waiters.insert(thr);
  thr->Suspend();
}

void ThreadQueue::ResumeOne() {
  if (waiters.size() == 0) {
    return;
  }
  Thread *thr = *(waiters.begin());
  CHECK(!thr->IsRunnable());
  waiters.erase(thr);
  thr->Resume();
}

void ThreadQueue::ResumeAll() {
  notified.clear();
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
