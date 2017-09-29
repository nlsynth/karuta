#include "nli.h"

#include <fstream>
#include <set>
#include <string.h>

using std::set;

const char *Env::nli_dir_;
string Env::output_root_;
string Env::output_marker_;
string Env::module_prefix_;
bool Env::sandbox_mode_;
string Env::argv0_;

namespace {

bool CheckFileSuffix(const string &fn,
		     const set<string> &suffixes) {
  const char *p = strrchr(fn.c_str(), '.');
  if (!p) {
    return false;
  }
  ++p;
  if (suffixes.find(p) != suffixes.end()) {
    return true;
  }
  return false;
}

}  // namespace

const string &Env::GetVersion() {
  static string v(VERSION);
  return v;
}

const char *Env::GetNliDir() {
  if (!nli_dir_) {
    nli_dir_ = getenv("NLI_DIR");
  }
  if (!nli_dir_) {
#ifdef NLI_DIR
    nli_dir_ = NLI_DIR;
#else
    nli_dir_ = ".";
#endif
  }
  return nli_dir_;
}

string Util::BaseName(const string &fn) {
  const char *s = strrchr(fn.c_str(), '/');
  if (s) {
    s++;
    return string(s);
  }
  return string(fn);
}

string Util::BaseNameWithoutSuffix(const string &fn) {
  string base_name = BaseName(fn);
  const char *s = strrchr(base_name.c_str(), '.');
  if (!s) {
    return base_name;
  }
  int len = s - base_name.c_str();
  return string(base_name.c_str(), len);
}

bool Util::IsHtmlFileName(const string &fn) {
  const char *s = fn.c_str();
  int len = fn.size();
  if (len > 5 && !strcmp(&s[len-5], ".html")) {
    return true;
  }
  return false;
}

bool Util::IsCCFileName(const string &fn) {
  static set<string> suffixes;
  if (suffixes.size() == 0) {
    suffixes.insert("cc");
    suffixes.insert("cpp");
    suffixes.insert("cxx");
  }
  return CheckFileSuffix(fn, suffixes);
}

bool Util::IsIrFileName(const string &fn) {
  static set<string> suffixes;
  if (suffixes.size() == 0) {
    suffixes.insert("ir");
    suffixes.insert("iroha");
  }
  return CheckFileSuffix(fn, suffixes);
}

bool Util::CopyFile(const char *fn, ostream &os) {
  vector<string> paths;
  Env::SearchPathList(fn, &paths);

  FILE *fp = nullptr;
  for (string &path : paths) {
    fp = fopen(path.c_str(), "r");
    if (fp) {
      break;
    }
  }
  LOG(INFO) << "Copying " << fn;
  os << "// copied from " << fn << " -- begin --\n";
  if (!fp) {
    return false;
  }
  char buf[1024];
  while (fgets(buf, 1024, fp)) {
    os << buf;
  }
  os << "// copied from " << fn << " -- end --\n\n";
  fclose(fp);
  return true;
}

bool Util::RewriteFile(const char *fn, const char *tag,
		       const char *content) {
  std::unique_ptr<std::ifstream> ifs;
  ifs.reset(new std::ifstream(fn));
  if (ifs.get() == nullptr) {
    return false;
  }
  string output;
  string line;
  while (std::getline(*ifs.get(), line)) {
    if (line.find(tag) == string::npos) {
      output += line;
    } else {
      output += string(tag) + content;
    }
    output += "\n";
  }
  std::unique_ptr<std::ofstream> ofs;
  ofs.reset(new std::ofstream(fn));
  if (!ofs->fail()) {
    // overwrite with new content.
    *ofs << output;
  }
  return true;
}

void Env::SearchPathList(const char *fn,
			 vector<string> *paths) {
  if (fn[0] != '/' && fn[0] != '.') {
    string fn1 = Env::GetNliDir() +
      string("/") + string(fn);
    paths->push_back(fn1);
  }
  paths->push_back(string(fn));
}

bool Env::GetOutputPath(const char *fn, string *path) {
  if (output_root_.empty()) {
    *path = string(fn);
    return true;
  }
  if (sandbox_mode_) {
    if (!strncmp(fn, "../", 3)) {
      return false;
    }
    if (strstr(fn, "/../")) {
      return false;
    }
  }
  *path = output_root_ + string("/") + fn;
  return true;
}

const string &Env::GetOutputMarker() {
  return output_marker_;
}

void Env::SetOutputRootPath(const string &path) {
  output_root_ = path;
  sandbox_mode_ = true;
}

void Env::SetOutputMarker(const string &marker) {
  output_marker_ = marker;
}

void Env::SetModulePrefix(const string &name) {
  module_prefix_ = name;
}

const string & Env::GetModulePrefix() {
  return module_prefix_;
}

void Env::SetArgv0(const string &c) {
  argv0_ = c;
}

const string &Env::GetArgv0() {
  return argv0_;
}

bool Env::IsSandboxMode() {
  return sandbox_mode_;
}
