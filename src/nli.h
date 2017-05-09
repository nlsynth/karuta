// -*- C++ -*-
// Common definition for all nli components.
#ifndef _nli_h_
#define _nli_h_

#include <iostream>
#include <memory>
#include <stdint.h>
#include <vector>

#include "base/initializer.h"
#include "base/stl_util.h"
#include "base/logging.h"
#include "base/sym.h"

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
  static void SetModulePrefix(const string &name);
  static const string &GetModulePrefix();
  static void SetArgv0(const string &c);
  static const string &GetArgv0();

private:
  static const char *nli_dir_;
  static string output_root_;
  static string output_marker_;
  static bool sandbox_mode_;
  static string module_prefix_;
  static string argv0_;
  static bool use_dfg_;
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
