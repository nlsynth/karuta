// -*- C++ -*-
#ifndef _karuta_env_h_
#define _karuta_env_h_

#include <string>
#include <vector>

using std::string;
using std::vector;

// Dummy defines for VERSION and PACKAGE to silent VSCode.
#ifndef VERSION
#define VERSION "0.0.0-undefined"
#endif

#ifndef PACKAGE
#define PACKAGE "karuta-undefined"
#endif

class Env {
 public:
  static const string &GetVersion();
  static const char *GetKarutaDir();
  static const char *GetIrohaDataDir();
  static bool GetOutputPath(const string &fn, string *path);
  static const string &GetOutputMarker();
  static void SearchPathList(const char *fn, vector<string> *paths);
  static vector<string> SearchDirList();

  static void SetOutputRootPath(const string &fn);
  static void SetOutputMarker(const string &marker);
  static void SetModulePrefix(const string &name);
  static const string &GetModulePrefix();
  static void SetArgv0(const string &c);
  static const string &GetArgv0();
  static void SetCurrentFile(const string &fn);
  static const string &GetCurrentFile();
  static bool IsSandboxMode();
  static void SetIrohaBinPath(const string &iroha);
  static const string &GetIrohaBinPath();
  static long GetDuration();
  static void SetDuration(long duration);
  static void EnableDotOutput(bool en);
  static bool DotOutput();
  static const string &GetFlavor();
  static void SetFlavor(const string &flavor);
  static bool GetWithSelfShell();
  static void SetWithSelfShell(bool with_self_shell);
  static void EnableVcdOutput(bool en);
  static bool GetVcdOutput();

 private:
  static const char *karuta_dir_;
  static string output_root_;
  static string output_marker_;
  static bool sandbox_mode_;
  static string module_prefix_;
  static string argv0_;
  static string iroha_bin_path_;
  static vector<string> source_dirs_;
  static string current_file_;
  static long duration_;
  static bool dot_output_;
  static string flavor_;
  static bool with_self_shell_;
  static bool vcd_output_;
};

#endif  // _karuta_env_h_
