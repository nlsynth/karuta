// -*- C++ -*-
#ifndef _base_dump_stream_h_
#define _base_dump_stream_h_

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

#endif  // _base_dump_stream_h_
