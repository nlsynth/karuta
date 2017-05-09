#include "base/status.h"

#include <iostream>

using std::cout;

Status::Context Status::context_[Status::NUM_TYPES];

void Status::SetLineNumber(int ln, Type t) {
  Context *context = GetContext(t);
  context->ln_ = ln;
}

ostringstream &Status::os(Type t) {
  Context *context = GetContext(t);
  if (!context->ss_.str().empty()) {
    context->ss_ << "\n";
  }
  return context->ss_;
}

bool Status::Check(Type t) {
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

bool Status::CheckAll() {
  bool b = false;
  // Ignores INFO.
  b |= Check(USER);
  b |= Check(ICE);
  return b;
}

Status::Context *Status::GetContext(Type t) {
  return &context_[t];
}
