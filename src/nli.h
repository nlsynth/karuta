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

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
 TypeName(const TypeName&) = delete; \
 void operator=(const TypeName&) = delete

class Env {
public:
  static const string &GetVersion();
  static const char *GetNliDir();
  static bool GetOutputPath(const char *fn, string *path);
  static const string &GetOutputMarker();
  static void SearchPathList(const char *fn,
			     vector<string> *paths);

  static void SetOutputRootPath(const string &fn);
  static void SetOutputMarker(const string &marker);

private:
  static const char *nli_dir_;
  static string output_root_;
  static string output_marker_;
  static bool sandbox_mode_;
};

class Util {
public:
  static string BaseName(const string &fn);
  static string BaseNameWithoutSuffix(const string &fn);
  static bool IsHtmlFileName(const string &fn);
  static bool IsCCFileName(const string &fn);
  static bool CopyFile(const char *fn, ostream &os);
  static bool RewriteFile(const char *fn, const char *tag,
			  const char *content);
};

#endif  // _nli_h_
