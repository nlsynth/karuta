// Copyright (C) Yusuke Tabata 2007-2021
/*
  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
*/
#include "karuta/karuta_main.h"

#include <errno.h>
#include <signal.h>
#include <string.h>
#include <sys/time.h>

#include "base/arg_parser.h"
#include "base/status.h"
#include "fe/fe.h"
#include "iroha/base/file.h"
#include "iroha/base/util.h"
#include "iroha/iroha.h"
#include "iroha/iroha_main.h"
#include "iroha/numeric.h"
#include "karuta/karuta.h"

KarutaMain::KarutaMain()
    : dbg_scanner_(false),
      dbg_parser_(false),
      timeout_(0),
      print_exit_status_(false),
      vanilla_(false) {}

void KarutaMain::PrintUsage() {
  cout << "karuta-" << Env::GetVersion() << "\n";
  cout << " karuta <command> [FILE]...\n"
       << "\n"
       << "   Commands(optional) are: complie, run, sim\n"
       << "   e.g. $ karuta compile mydesign.karuta\n"
       << "\n"
       << "   -d[spb] scanner,parser,byte code compiler\n"
       << "   -l\n"
       << "   -l=[modules]\n"
       << "   --compile\n"
       << "   --duration\n"
       << "   --dot\n"
       << "   --iroha_binary [iroha]\n"
       << "   --module_prefix [mod]\n"
       << "   --output_marker [marker]\n"
       << "   --flavor [flavor]\n"
       << "   --print_exit_status\n"
       << "   --root [path]\n"
       << "   --run\n"
       << "   --timeout [ms]\n"
       << "   --vanilla\n"
       << "   --vcd\n"
       << "   --version\n"
       << "   --with_shell\n"
       << "\n"
       << " Please see https://karuta.readthedocs.io/en/latest/ or "
          "https://twitter.com/karutalang for more information.\n\n";
  exit(0);
}

void KarutaMain::RunFiles(bool with_run, bool with_compile,
                          vector<string> &files) {
  fe::FE fe(dbg_parser_, dbg_scanner_, dbg_bytecode_);

  fe.Run(with_run, with_compile, vanilla_, files);
}

void KarutaMain::ProcDebugArgs(vector<char *> &dbg_flags) {
  for (char *flag : dbg_flags) {
    switch (*flag) {
      case 'b':
        dbg_bytecode_ = string(flag);
        break;
      case 's':
        dbg_scanner_ = true;
        break;
      case 'p':
        dbg_parser_ = true;
        break;
      default:
        break;
    }
  }
}

void KarutaMain::InstallTimeout() {
  struct sigaction sa;
  memset(&sa, 0, sizeof(sa));
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  sigaction(SIGALRM, &sa, nullptr);
  struct itimerval ival;
  timeout_ *= 1000;
  int sec = timeout_ / 1000000;
  int usec = timeout_ % 1000000;
  ival.it_interval.tv_sec = 0;
  ival.it_interval.tv_usec = 0;
  ival.it_value.tv_sec = sec;
  ival.it_value.tv_usec = usec;
  // ITIMER_VIRTUAL doesn't work on WSL (as of 2018/06).
  if (setitimer(ITIMER_VIRTUAL, &ival, nullptr) == -1 && errno == EINVAL) {
    setitimer(ITIMER_REAL, &ival, nullptr);
  }
}

void KarutaMain::ParseArgs(int argc, char **argv, ArgParser *parser) {
  parser->RegisterBoolFlag("compile", nullptr);
  parser->RegisterBoolFlag("dot", nullptr);
  parser->RegisterBoolFlag("h", "help");
  parser->RegisterBoolFlag("help", nullptr);
  parser->RegisterBoolFlag("iroha", nullptr);
  parser->RegisterBoolFlag("print_exit_status", nullptr);
  parser->RegisterBoolFlag("run", nullptr);
  parser->RegisterBoolFlag("with_shell", nullptr);
  parser->RegisterBoolFlag("vanilla", nullptr);
  parser->RegisterBoolFlag("vcd", nullptr);
  parser->RegisterBoolFlag("version", "help");
  parser->RegisterValueFlag("duration", nullptr);
  parser->RegisterValueFlag("iroha_binary", nullptr);
  parser->RegisterValueFlag("module_prefix", nullptr);
  parser->RegisterValueFlag("output_marker", nullptr);
  parser->RegisterValueFlag("flavor", nullptr);
  parser->RegisterValueFlag("root", nullptr);
  parser->RegisterValueFlag("timeout", nullptr);
  parser->RegisterModeArg("compile", nullptr);
  parser->RegisterModeArg("run", nullptr);
  parser->RegisterModeArg("sim", nullptr);
  if (!parser->Parse(argc, argv)) {
    exit(0);
  }
}

void KarutaMain::LoadEmbeddedFiles(const map<string, string> &images) {
  for (auto it : images) {
    iroha::File::RegisterFile(it.first, it.second);
  }
}

int KarutaMain::main(int argc, char **argv) {
  ArgParser args;
  ParseArgs(argc, argv, &args);
  if (args.GetBoolFlag("iroha", false)) {
    // Run as Iroha.
    return iroha::main(argc, argv);
  }
  if (args.GetBoolFlag("help", false) || argc == 1) {
    PrintUsage();
  }
  vanilla_ = args.GetBoolFlag("vanilla", false);
  print_exit_status_ = args.GetBoolFlag("print_exit_status", false);

  string arg;
  if (args.GetFlagValue("timeout", &arg)) {
    timeout_ = atoi(arg.c_str());
  } else {
    timeout_ = 0;
  }

  // Actually initialize modules and params.
  ::sym_table_init();
  iroha::Iroha::Init();
  iroha::Iroha::SetImportPaths(Env::SearchDirList());
  Env::SetArgv0(argv[0]);
  if (args.GetFlagValue("root", &arg)) {
    Env::SetOutputRootPath(arg);
  }
  if (args.GetFlagValue("flavor", &arg)) {
    Env::SetFlavor(arg);
  }
  if (args.GetFlagValue("output_marker", &arg)) {
    Env::SetOutputMarker(arg);
  }
  if (args.GetFlagValue("module_prefix", &arg)) {
    Env::SetModulePrefix(arg);
  }
  if (args.GetFlagValue("iroha_binary", &arg)) {
    Env::SetIrohaBinPath(arg);
  }
  if (args.GetFlagValue("duration", &arg)) {
    long d = iroha::Util::AtoULL(arg);
    Env::SetDuration(d);
  }
  if (args.GetBoolFlag("dot", false)) {
    Env::EnableDotOutput(true);
  }
  if (args.GetBoolFlag("with_shell", false)) {
    Env::SetWithSelfShell(true);
  }
  if (args.GetBoolFlag("vcd", false)) {
    Env::EnableVcdOutput(true);
  }

  if (timeout_) {
    InstallTimeout();
  }
  Logger::Init(args.enable_logging_, args.log_modules);

  ProcDebugArgs(args.debug_flags);
  string exit_status;
  LOG(INFO) << "KARUTA-" << Env::GetVersion();
  bool with_compile = args.GetBoolFlag("compile", false);
  bool with_run = args.GetBoolFlag("run", false);
  bool with_sim = args.GetBoolFlag("sim", false);
  if (with_sim) {
    with_compile = true;
    Env::SetWithSelfShell(true);
  }
  RunFiles(with_run, with_compile, args.source_files);
  iroha::Numeric::ReleaseDefaultManager();
  if (Status::CheckAllErrors(true)) {
    exit_status = "error";
  }
  if (print_exit_status_) {
    // Used to confirm this program was finished normally.
    // (without SEGV and so on)
    cout << "KARUTA DONE: " << exit_status << "\n";
  }
  return 0;
}
