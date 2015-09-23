// -*- C++ -*-
#ifndef _logging_h_included_
#define _logging_h_included_

#include <iostream>
#include <set>
#include <sstream>

enum LogSeverity {
  LOG_NONE,
  DEBUG,
  // enabled by -l=modules,,
  PHASE,
  // enabled by -l
  INFO,
  FATAL,
};

class Logger {
public:
  static void Init(bool on, const std::set<std::string> &modules);
  static std::ostream &GetStream(LogSeverity sev);
  static void Finalize(LogSeverity sev, const char *fn, int line);
private:
  static std::stringstream os_;
  static bool is_enabled_;
  static std::set<std::string> modules_;
};

class LogFinalizer {
public:
  LogFinalizer(LogSeverity sev, const char *fn, int line);
  ~LogFinalizer();

  void operator&(std::ostream&none) {}
private:
  LogSeverity sev_;
  const char *fn_;
  int line_;
};

#define LOG(s) LogFinalizer(s, __FILE__, __LINE__) & Logger::GetStream(s)
#define CHECK(s) LogFinalizer((s ? LOG_NONE : FATAL), __FILE__, __LINE__) & Logger::GetStream((s ? LOG_NONE : FATAL))

#endif
