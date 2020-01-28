#include "base/logging.h"

#include <iomanip>
#include <stdlib.h>
#include <string.h>

#include <sys/time.h>

using std::ostream;
using std::set;
using std::string;

std::stringstream Logger::os_;
bool Logger::is_enabled_;
set<std::string> Logger::modules_;

static string TimeStamp() {
  std::stringstream ss;
  struct timeval tv;
  gettimeofday(&tv, NULL);
  double us = (tv.tv_sec % 1000) + tv.tv_usec / (double)1000000;
  ss << std::setprecision(2) << std::fixed << us;
  return ss.str();
}

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
    std::cout << TimeStamp() << " " << fn << ":" << line << ":" << os_.str() << "\n";
  }
  os_.str("");
  if (sev == FATAL) {
    std::cout << std::flush;
    abort();
  }
}

LogFinalizer::LogFinalizer(LogSeverity sev, const char *fn, int line)
  : sev_(sev), fn_(fn), line_(line) {
}

LogFinalizer::~LogFinalizer() {
  Logger::Finalize(sev_, fn_, line_);
}
