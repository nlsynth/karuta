#include "base/dump_stream.h"

DumpStream::DumpStream(std::ostream &_os) : os(_os) {
  indent_ = 0;
}

void DumpStream::push_indent() {
  indent_++;
}

void DumpStream::pop_indent() {
  indent_--;
}

void DumpStream::indent() {
  int i;
  for (i = 0; i < indent_; i++) {
    os << "  ";
  }
}
