#include "messages.h"

#include <iostream>

using std::cout;

Message::Context Message::context_[Message::NUM_TYPES];

void Message::SetLineNumber(int ln, Type t) {
  Context *context = GetContext(t);
  context->ln_ = ln;
}

ostringstream &Message::os(Type t) {
  Context *context = GetContext(t);
  if (!context->ss_.str().empty()) {
    context->ss_ << "\n";
  }
  return context->ss_;
}

bool Message::Check(Type t) {
  Context *context = GetContext(t);
  if (context->ss_.str().empty()) {
    return false;
  }
  string s;
  if (t == USER) {
    s += "U:";
  } else if (t == INFO) {
     s += "I:";
  }
  char buf[10];
  if (context->ln_ > -1) {
    sprintf(buf, "%d", context->ln_);
    s += string("(line: ") + buf + ")";
  }
  s += context->ss_.str();
  cout << s << "\n";

  context->ss_.str("");
  context->ln_ = -1;
  return true;
}

bool Message::CheckAll() {
  bool b = false;
  b |= Check(USER);
  b |= Check(INFO);
  b |= Check(ICE);
  return b;
}

Message::Context *Message::GetContext(Type t) {
  return &context_[t];
}
