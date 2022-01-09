// -*- C++ -*-
#ifndef _fe_scanner_interface_h_
#define _fe_scanner_interface_h_

#include "fe/common.h"

namespace fe {

// Interface to access current Scanner instance from the parser.
class ScannerInterface {
 public:
  static Scanner *CreateScanner();
  static int GetToken(ScannerToken *tk);
  static void GetPosition(ScannerPos *pos);
  static void EnterSemiColonStatement();
  static void EndSemiColonStatement();
  static void InArrayElmDecl();
  static void EndArrayElmDecl();
};

}  // namespace fe

#endif  // _fe_scanner_interface_h_
