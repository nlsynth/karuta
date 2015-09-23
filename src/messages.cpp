#include "messages.h"

#include <iostream>

using std::cout;

Message *Message::CreateMessage(Type t) {
  return new Message(t);
}

Message::Message(Type t) : ln_(-1), type_(t) {
}

Message::~Message() {
  if (ss_.str().empty()) {
    return;
  }
  string s = Get();
  cout << s << "\n";
}

void Message::SetLineNumber(int ln) {
  ln_ = ln;
}

ostringstream &Message::os() {
  return ss_;
}

string Message::Get() {
  string s;
  if (type_ == USER) {
    s += "U:";
  } else if (type_ == INFO) {
    s += "I:";
  }
  char buf[10];
  if (ln_ > -1) {
    sprintf(buf, "%d", ln_);
    s += string("(line: ") + buf + ")";
  }
  s += ss_.str();
  ss_.str("");
  return s;
}
