// -*- C++ -*-
#ifndef _messages_h_
#define _messages_h_

#include <sstream>

using std::ostringstream;
using std::string;

// Usage:
//  Message::os(Message::INFO) << "something happened.";
//  // let the destructor flush info messages.
//  MessageFlush::Get(Message::INFO);

class Message {
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
  MessageFlush(Message::Type t) : t_(t) {
  }
  ~MessageFlush() {
    Message::Check(t_);
  }
  static MessageFlush Get(Message::Type t) {
    MessageFlush m(t);
    return m;
  }
  Message::Type t_;
};

#endif  // _messages_h_
