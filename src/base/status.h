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
    USER_ERROR,
    // Internal Compiler Error.
    ICE,
    // Debug message.
    INFO,
    NUM_TYPES,
  };

  static void SetLineNumber(int ln, Type t);

  // Called from MessageFlush.
  static void Flush(Type t);
  // true if there are messages.
  static bool Check(Type t, bool clear);
  // Checks if there are USER_ERROR, ICE
  static bool CheckAllErrors(bool clear);
  static ostringstream &os(Type t);

 private:
  class Context {
   public:
    Context() : ln_(-1), has_message_(false) {}
    ostringstream ss_;
    int ln_;
    bool has_message_;
  };

  static Context context_[NUM_TYPES];

  static Context *GetContext(Type t);
};

class MessageFlush {
 public:
  MessageFlush(Status::Type t) : t_(t) {}
  ~MessageFlush() { Status::Flush(t_); }
  static MessageFlush Get(Status::Type t) {
    MessageFlush m(t);
    return m;
  }
  Status::Type t_;
};

#endif  // _base_status_h_
