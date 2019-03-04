// -*- C++ -*-
#ifndef _base_arg_parser_h_
#define _base_arg_parser_h_

#include <map>
#include <set>
#include <string>
#include <vector>

using std::map;
using std::set;
using std::string;
using std::vector;

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

#endif  // _base_arg_parser_h_
