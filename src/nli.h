// -*- C++ -*-
// Common definition for all nli components.
#ifndef _nli_h_
#define _nli_h_

#include <iostream>
#include <memory>
#include <stdint.h>
#include <vector>

#include "initializer.h"
#include "logging.h"
#include "sym.h"
#include "stl_util.h"

using std::cout;
using std::ostream;
using std::ostringstream;
using std::string;
using std::vector;

class Env {
public:
  static string GetVersion();
  static const char *GetNliDir();
  static bool GetOutputPath(const char *fn, string *path);
  static void SearchPathList(const char *fn,
			     vector<string> *paths);

  static void SetOutputRootPath(const char *fn);

private:
  static const char *nli_dir_;
  static const char *output_root_;
  static bool sandbox_mode_;
};

class Util {
public:
  static string GetBaseName(const char *fn);
  static string GetDirName(const char *fn);
  static bool IsHtmlFileName(const char* fn);
  static bool IsCCFileName(const char* fn);
  static bool CopyFile(const char *fn, ostream &os);
  static bool RewriteFile(const char *fn, const char *tag,
			  const char *content);
};

#endif  // _nli_h_
