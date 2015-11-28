// Copyright (C) Yusuke Tabata 2007-2015
/*
  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
*/
#include <signal.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <string>
#include <map>

#include "dfg/dfg.h"
#include "fe/fe.h"
#include "nli.h"
#include "status.h"

using std::map;

class ArgParser {
public:
  ArgParser();

  void RegisterBoolFlag(const char *name, const char *canonical);
  void RegisterValueFlag(const char *name, const char *canonical);
  bool Parse(int argc, char **argv);
  bool GetBoolFlag(const char *name, bool default_value);
  bool GetFlagValue(const char *name, string *value);

public:
  bool enable_logging_;
  vector<char *> debug_flags;
  vector<string> source_files;
  set<string> log_modules;

private:
  void ParseLogModules(const char *s);
  bool StripFlagName(const char *arg, string *name, string *value);
  map<string, string> registered_flags_;
  map<string, string> flag_values_;
  set<string> flags_with_value_;
};

class Main {
public:
  void main(int argc, char **argv);

private:
  void InstallTimeout();
  void ParseArgs(int argc, char **argv, ArgParser *arg_parser);
  void ProcDebugArgs(vector<char *> &dbg_flags);
  void RunFiles(vector<string> &files);
  void PrintUsage();

  // common
  bool dbg_scanner;
  bool dbg_parser;
  int timeout;
  // nfe specific
  bool dbg_types;
  bool print_exit_status;
  bool vanilla;
  bool dbg_bytecode;
};

void Main::PrintUsage() {
  cout << "nli-" << Env::GetVersion() << "\n";
  cout << " nli [-d[spcg]] scanner,parser,compiler,graph,type\n"
       << "   -l\n"
       << "   -l=[modules]\n"
       << "   --module_prefix [mod]\n"
       << "   --output_marker [marker]\n"
       << "   --print_exit_status\n"
       << "   --root [path]\n"
       << "   --timeout [ms]\n"
       << "   --vanilla\n"
       << "   --version\n";
  exit(0);
}

void Main::RunFiles(vector<string> &files) {
  fe::FE fe(dbg_parser, dbg_scanner, dbg_bytecode);

  fe.Run(vanilla, files);
}

void Main::ProcDebugArgs(vector<char *> &dbg_flags) {
  for (char *flag : dbg_flags) {
    switch (*flag) {
    case 'b':
      dbg_bytecode = true;
      break;
    case 's':
      dbg_scanner = true;
      break;
    case 'p':
      dbg_parser = true;
      break;
    case 't':
      dbg_types = true;
      break;
    default:
      break;
    }
  }
}

ArgParser::ArgParser() : enable_logging_(false) {
}

void ArgParser::RegisterBoolFlag(const char *name, const char *canonical) {
  if (canonical == NULL) {
    canonical = name;
  }
  registered_flags_[string(name)] = string(canonical);
}

void ArgParser::RegisterValueFlag(const char *name, const char *canonical) {
  RegisterBoolFlag(name, canonical);
  flags_with_value_.insert(string(name));
}

bool ArgParser::Parse(int argc, char **argv) {
  for (int i = 1; i < argc; i++) {
    char *arg = argv[i];
    char *next_arg = NULL;
    string flag_name;
    string flag_value;
    bool has_value = StripFlagName(arg, &flag_name, &flag_value);
    if (i < argc - 1) {
      next_arg = argv[i+1];
    }
    if (!strcmp(arg, "-l")) {
      enable_logging_ = true;
    } else if (!strncmp(arg, "-l=", 3)) {
      ParseLogModules(&arg[3]);
      enable_logging_ = true;
    } else if (!strncmp(arg, "-d", 2)) {
      debug_flags.push_back(&arg[2]);
    } else if (registered_flags_.find(flag_name) != registered_flags_.end()) {
      const string &canonical_flag_name = registered_flags_[flag_name];
      if (flags_with_value_.find(flag_name) != flags_with_value_.end()) {
	if (has_value) {
	  flag_values_[canonical_flag_name] = flag_value;
	} else {
	  flag_values_[canonical_flag_name] = next_arg;
	  i++;
	}
      } else {
	flag_values_[canonical_flag_name] = "";
      }
    } else {
      if (arg[0] == '-') {
	Status::os(Status::USER) << "Unknown command line flag:" << arg;
	MessageFlush::Get(Status::USER);
	return false;
      }
      source_files.push_back(arg);
    }
  }
  return true;
}

bool ArgParser::GetBoolFlag(const char *name, bool dflt) {
  if (flag_values_.find(name) != flag_values_.end()) {
    return true;
  }
  return false;
}

bool ArgParser::GetFlagValue(const char *name, string *value) {
  if (flag_values_.find(name) != flag_values_.end()) {
    *value = flag_values_[name];
    return true;
  }
  return false;
}

void ArgParser::ParseLogModules(const char *s) {
  while (*s) {
    const char *e = strchr(s, ',');
    if (e) {
      log_modules.insert(string(s, e - s));
      s = e + 1;
    } else {
      log_modules.insert(s);
      return;
    }
  }
}

bool ArgParser::StripFlagName(const char *arg, string *name, string *value) {
  while (*arg == '-') {
    ++arg;
  }
  int i;
  for (i = 0; arg[i] && arg[i] != '='; ++i) {
  }
  *name = string(arg, i);
  if (arg[i] == '=') {
    *value = string(&arg[i + 1]);
    return true;
  }
  return false;
}

void Main::InstallTimeout() {
  struct sigaction sa;
  memset(&sa, 0, sizeof(sa));
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  sigaction(SIGALRM, &sa, NULL);
  struct itimerval ival;
  timeout *= 1000;
  int sec = timeout / 1000000;
  int usec = timeout % 1000000;
  ival.it_interval.tv_sec = 0;
  ival.it_interval.tv_usec = 0;
  ival.it_value.tv_sec = sec;
  ival.it_value.tv_usec = usec;
  setitimer(ITIMER_VIRTUAL, &ival, NULL);
}

void Main::ParseArgs(int argc, char **argv, ArgParser *parser) {
  parser->RegisterBoolFlag("h", "help");
  parser->RegisterBoolFlag("help", NULL);
  parser->RegisterBoolFlag("version", "help");
  parser->RegisterBoolFlag("vanilla", NULL);
  parser->RegisterBoolFlag("print_exit_status", NULL);
  parser->RegisterValueFlag("timeout", NULL);
  parser->RegisterValueFlag("root", NULL);
  parser->RegisterValueFlag("output_marker", NULL);
  parser->RegisterValueFlag("module_prefix", NULL);
  parser->RegisterBoolFlag("n", NULL);
  parser->RegisterBoolFlag("z", NULL);
  if (!parser->Parse(argc, argv)) {
    exit(0);
  }
}

void Main::main(int argc, char **argv) {
  dbg_scanner = false;
  dbg_parser = false;
  dbg_types = false;
  dbg_bytecode = false;
  ::sym_table_init();
  dfg::DFG::Init();
  StaticInitializer::RunInitializers();

  ArgParser args;
  ParseArgs(argc, argv, &args);
  if (args.GetBoolFlag("help", false)) {
    PrintUsage();
  }
  vanilla = args.GetBoolFlag("vanilla", false);
  print_exit_status = args.GetBoolFlag("print_exit_status", false);

  string arg;
  if (args.GetFlagValue("timeout", &arg)) {
    timeout = atoi(arg.c_str());
  } else {
    timeout = 0;
  }
  if (args.GetFlagValue("root", &arg)) {
    Env::SetOutputRootPath(arg);
  }
  if (args.GetFlagValue("output_marker", &arg)) {
    Env::SetOutputMarker(arg);
  }
  if (args.GetFlagValue("module_prefix", &arg)) {
    Env::SetModulePrefix(arg);
  }

  if (timeout) {
    InstallTimeout();
  }
  Logger::Init(args.enable_logging_, args.log_modules);

  ProcDebugArgs(args.debug_flags);
  string exit_status;
  LOG(INFO) << "NLI-" << Env::GetVersion();
  RunFiles(args.source_files);
  Status::CheckAll();
  StaticInitializer::RunFinalizers();
  if (print_exit_status) {
    // Used to confirm this program was finished normally.
    // (without SEGV and so on)
    cout << "NLI DONE: " << exit_status << "\n";
  }
}

int main(int argc, char **argv) {
  Main m;
  m.main(argc, argv);
  return 0;
}
