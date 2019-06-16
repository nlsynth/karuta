// -*- C++ -*-
#ifndef _karuta_karuta_main_h_
#define _karuta_karuta_main_h_

#include "karuta/karuta.h"

class ArgParser;

class Main {
public:
  int main(int argc, char **argv);

private:
  void InstallTimeout();
  void ParseArgs(int argc, char **argv, ArgParser *arg_parser);
  void ProcDebugArgs(vector<char *> &dbg_flags);
  void RunFiles(bool with_run, bool with_compile, vector<string> &files);
  void PrintUsage();

  bool dbg_scanner_;
  bool dbg_parser_;
  string dbg_bytecode_;
  int timeout_;
  bool print_exit_status_;
  bool vanilla_;
};

#endif  // _karuta_karuta_main_h_
