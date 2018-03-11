// -*- C++ -*-
// Common definition for all the components of Karuta.
#ifndef _karuta_h_
#define _karuta_h_

#include <iostream>
#include <memory>
#include <stdint.h>
#include <vector>

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
  static const char *GetKarutaDir();
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
  static bool IsSandboxMode();
  static void SetIrohaBinPath(const string &iroha);
  static const string &GetIrohaBinPath();

private:
  static const char *karuta_dir_;
  static string output_root_;
  static string output_marker_;
  static bool sandbox_mode_;
  static string module_prefix_;
  static string argv0_;
  static string iroha_bin_path_;
};

#endif  // _karuta_h_
