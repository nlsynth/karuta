// -*- C++ -*-
#ifndef _messages_h_
#define _messages_h_

#include <sstream>

using std::ostringstream;
using std::string;

class Message {
public:
  enum Type {
    // Maybe user's issue.
    USER,
    // Debug message.
    INFO,
    ICE
  };

  static Message *CreateMessage(Type t);

  explicit Message(Type t);
  ~Message();
  void SetLineNumber(int ln);
  string Get();

  ostringstream &os();

private:
  ostringstream ss_;
  int ln_;
  Type type_;
};

#endif  // _messages_h_
