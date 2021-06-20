// -*- C++ -*-
#ifndef _karuta_embedded_data_h_
#define _karuta_embedded_data_h_

#include <map>
#include <string>

std::map<std::string, std::string> get_embedded_file_images() {
  // This is a placeholder to embed data located under embedded_data/.
  // Real data should be located in a directory with higher include priority.
  std::map<std::string, std::string> m = {
      {"internal-placeholder.karuta", "print(\"" PACKAGE "-" VERSION "\")\n"},
  };
  return m;
}

#endif  // _karuta_embedded_data_h_