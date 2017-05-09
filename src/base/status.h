// -*- C++ -*-
#ifndef _base_status_h_
#define _base_status_h_

#include <sstream>

using std::ostringstream;
using std::string;

// Usage:
//  Status::os(Status::INFO) << "something happened.";
//  // let the destructor flush info messages.
//  MessageFlush::Get(Status::INFO);

class Status {
public:
  enum Type {
    // Maybe user's issue.
    USER,
    // Debug message.
    INFO,
    ICE,
    NUM_TYPES,
  };

  static void SetLineNumber(int ln, Type t);

  static bool Check(Type t);
  static bool CheckAll();
  static ostringstream &os(Type t);

private:
  class Context {
  public:
    Context() : ln_(-1) {
    }
    ostringstream ss_;
    int ln_;
  };

  static Context context_[NUM_TYPES];

  static Context *GetContext(Type t);
};

class MessageFlush {
public:
  MessageFlush(Status::Type t) : t_(t) {
  }
  ~MessageFlush() {
    Status::Check(t_);
  }
  static MessageFlush Get(Status::Type t) {
    MessageFlush m(t);
    return m;
  }
  Status::Type t_;
};

#endif  // _base_status_h_
