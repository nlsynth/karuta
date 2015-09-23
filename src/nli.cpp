#include "nli.h"

#include <fstream>
#include <set>
#include <string.h>

using std::set;

const char *Env::nli_dir_;
const char *Env::output_root_;
bool Env::sandbox_mode_;

string Env::GetVersion() {
  return VERSION;
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

string Util::GetBaseName(const char *fn) {
  const char *s = strrchr(fn, '/');
  if (s) {
    s++;
    return string(s);
  }
  return string(fn);
}

string Util::GetDirName(const char *fn) {
  string path(fn);
  size_t pos = path.rfind("/");
  if (pos == string::npos) {
    return string("");
  }
  return string(fn, pos);
}

bool Util::IsHtmlFileName(const char* fn) {
  int len = strlen(fn);
  if (len > 5 && !strcmp(&fn[len-5], ".html")) {
    return true;
  }
  return false;
}

bool Util::IsCCFileName(const char* fn) {
  static set<string> suffixes;
  if (suffixes.size() == 0) {
    suffixes.insert("cc");
    suffixes.insert("cpp");
    suffixes.insert("cxx");
  }
  const char *p = strrchr(fn, '.');
  if (!p) {
    return false;
  }
  ++p;
  if (suffixes.find(p) != suffixes.end()) {
    return true;
  }
  return false;
}

bool Util::CopyFile(const char *fn, ostream &os) {
  vector<string> paths;
  Env::SearchPathList(fn, &paths);

  FILE *fp = NULL;
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
  if (ifs.get() == NULL) {
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
  if (!output_root_) {
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
  *path = std::string(output_root_) + std::string("/") + std::string(fn);
  return true;
}

void Env::SetOutputRootPath(const char *path) {
  output_root_ = path;
  sandbox_mode_ = true;
}
