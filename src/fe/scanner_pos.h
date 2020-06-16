// -*- C++ -*-
#ifndef _fe_scanner_pos_h_
#define _fe_scanner_pos_h_

#include <string>

namespace fe {

struct ScannerFile {
  std::string file;
};

struct ScannerPos {
  ScannerPos();

  std::string Format();

  int line;
  int pos;
  ScannerFile *file;
};

}  // namespace fe

#endif  // _fe_scanner_pos_h_
