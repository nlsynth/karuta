#include "logging.h"

#include <stdlib.h>
#include <string.h>

using std::ostream;
using std::set;
using std::string;

std::stringstream Logger::os_;
bool Logger::is_enabled_;
set<std::string> Logger::modules_;

void Logger::Init(bool on, const set<string> &modules) {
  is_enabled_ = on;
  modules_ = modules;
}

ostream &Logger::GetStream(LogSeverity sev) {
  return os_;
}

void Logger::Finalize(LogSeverity sev, const char *fn, int line) {
  if (sev == LOG_NONE) {
    os_.str("");
    return;
  }
  if (sev == PHASE) {
    string module;
    const char *e = strrchr(fn, '.');
    if (e) {
      module = string(fn, e - fn);
    } else {
      module = string(fn);
    }
    if (modules_.find(module) == modules_.end()) {
      os_.str("");
      return;
    }
  }
  if (is_enabled_ || sev == FATAL || sev == DEBUG) {
    std::cout << fn << ":" << line << ":" << os_.str() << "\n";
  }
  os_.str("");
  if (sev == FATAL) {
    abort();
  }
}

LogFinalizer::LogFinalizer(LogSeverity sev, const char *fn, int line)
  : sev_(sev), fn_(fn), line_(line) {
}

LogFinalizer::~LogFinalizer() {
  Logger::Finalize(sev_, fn_, line_);
}
