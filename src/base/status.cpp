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
  context->has_message_ = true;
  if (!context->ss_.str().empty()) {
    context->ss_ << "\n";
  }
  return context->ss_;
}

void Status::Flush(Type t) {
  Context *context = GetContext(t);
  if (context->ss_.str().empty()) {
    return;
  }
  string s;
  if (t == USER_ERROR) {
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
}

bool Status::Check(Type t, bool clear) {
  Context *context = GetContext(t);
  bool had_message = context->has_message_;
  if (clear) {
    context->has_message_ = false;
  }
  Flush(t);
  return had_message;
}

bool Status::CheckAllErrors(bool clear) {
  bool b = false;
  // Ignores INFO.
  Flush(INFO);
  b |= Check(USER_ERROR, clear);
  b |= Check(ICE, clear);
  return b;
}

Status::Context *Status::GetContext(Type t) { return &context_[t]; }
