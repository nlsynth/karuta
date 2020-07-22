#include "base/arg_parser.h"

#include "base/status.h"

#include <string.h>

ArgParser::ArgParser() : enable_logging_(false) {
}

void ArgParser::RegisterBoolFlag(const char *name, const char *canonical) {
  if (canonical == nullptr) {
    canonical = name;
  }
  registered_flags_[string(name)] = string(canonical);
}

void ArgParser::RegisterValueFlag(const char *name, const char *canonical) {
  RegisterBoolFlag(name, canonical);
  flags_with_value_.insert(string(name));
}

void ArgParser::RegisterModeArg(const char *name, const char *canonical) {
  if (canonical == nullptr) {
    canonical = name;
  }
  mode_flags_[string(name)] = string(canonical);
}

bool ArgParser::Parse(int argc, char **argv) {
  for (int i = 1; i < argc; i++) {
    char *arg = argv[i];
    char *next_arg = nullptr;
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
    } else if (mode_flags_.find(arg) != mode_flags_.end()) {
      const string &canonical_flag_name = mode_flags_[arg];
      flag_values_[canonical_flag_name] = "";
    } else if (registered_flags_.find(flag_name) != registered_flags_.end()) {
      const string &canonical_flag_name = registered_flags_[flag_name];
      if (flags_with_value_.find(flag_name) != flags_with_value_.end()) {
	if (has_value) {
	  flag_values_[canonical_flag_name] = flag_value;
	} else {
	  if (next_arg == nullptr) {
	    Status::os(Status::USER_ERROR) << "Missing value for:" << flag_name;
	    MessageFlush::Get(Status::USER_ERROR);
	    return false;
	  }
	  flag_values_[canonical_flag_name] = next_arg;
	  i++;
	}
      } else {
	flag_values_[canonical_flag_name] = "";
      }
    } else {
      if (arg[0] == '-') {
	Status::os(Status::USER_ERROR) << "Unknown command line flag:" << arg;
	MessageFlush::Get(Status::USER_ERROR);
	return false;
      }
      source_files.push_back(arg);
    }
    if (!strcmp(arg, "--iroha")) {
      // Stop parsing other flags.
      return true;
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
