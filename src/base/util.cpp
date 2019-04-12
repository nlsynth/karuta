#include "base/util.h"

#include "iroha/util.h"

#include <fstream>
#include <set>
#include <string.h>

using std::set;

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

string Util::DirName(const string &fn) {
  const char *s = strrchr(fn.c_str(), '/');
  if (s == nullptr) {
    return "";
  }
  int len = s - fn.c_str();
  return string(fn.c_str(), len + 1);
}

string Util::BaseNameWithoutSuffix(const string &fn) {
  string bn = iroha::Util::BaseName(fn);
  int pos = bn.rfind(".");
  if (pos == string::npos) {
    return bn;
  }
  return string(bn.c_str(), pos);
}

bool Util::IsHtmlFileName(const string &fn) {
  const char *s = fn.c_str();
  int len = fn.size();
  if (len > 5 && !strcmp(&s[len-5], ".html")) {
    return true;
  }
  return false;
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

int Util::Log2(int x) {
  x--;
  int n;
  for (n = 0; x > 0; ++n) {
    x /= 2;
  }
  return n;
}

uint64_t Util::RoundUp2(uint64_t x) {
  for (int i = 0; i < 32; ++i) {
    int s = (1 << i);
    if (s >= x) {
      return s;
    }
  }
  return 0;
}
