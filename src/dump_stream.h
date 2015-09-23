// -*- C++ -*-
#ifndef _dump_stream_h_
#define _dump_stream_h_

#include "nli.h"

class DumpStream {
public:
  DumpStream(ostream &os);
  void push_indent();
  void pop_indent();
  void indent();
  ostream &os;

private:
  int indent_;
};

#endif  // _dump_stream_h_
