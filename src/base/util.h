// -*- c++ -*-
#ifndef _base_util_h_
#define _base_util_h_

#include <iostream>
#include <string>

using std::ostream;
using std::string;

class Util {
public:
  static string DirName(const string &fn);
  static string BaseNameWithoutSuffix(const string &fn);
  static bool IsHtmlFileName(const string &fn);
  static bool IsIrFileName(const string &fn);
  static bool CopyFile(const char *fn, ostream &os);
  static bool RewriteFile(const char *fn, const char *tag,
			  const char *content);
  // 0,1,2,3,4 -> 0,0,1,2,2
  static int Log2(int x);
  static uint64_t RoundUp2(uint64_t x);
};

#endif  // _base_util_h_
