// -*- C++ -*-
#ifndef _fe_scanner_pos_h_
#define _fe_scanner_pos_h_

#include <string>

namespace fe {

struct ScannerPos {
  ScannerPos();

  int line;
  int pos;
  std::string file;
};

}  // namespace fe

#endif  // _fe_scanner_pos_h_
