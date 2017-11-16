// -*- c++ -*-
#ifndef _base_util_h_
#define _base_util_h_

#include "nli.h"

class Util {
public:
  static string BaseName(const string &fn);
  static string BaseNameWithoutSuffix(const string &fn);
  static bool IsHtmlFileName(const string &fn);
  static bool IsCCFileName(const string &fn);
  static bool IsIrFileName(const string &fn);
  static bool CopyFile(const char *fn, ostream &os);
  static bool RewriteFile(const char *fn, const char *tag,
			  const char *content);
};

#endif  // _base_util_h_
