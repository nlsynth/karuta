#include "fe/scanner_pos.h"

#include "iroha/base/util.h"

using std::string;

namespace fe {

ScannerPos::ScannerPos() {
  line = -1;
  pos = -1;
  file = nullptr;
}

string ScannerPos::Format() {
  string s;
  if (file != nullptr) {
    s += "in file: " + file->file;
  }
  s += " line " + iroha::Util::Itoa(line);
  return s;
}

}  // namespace fe
