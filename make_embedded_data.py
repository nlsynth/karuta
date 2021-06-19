# -*- coding: utf-8 -*-
# generates to embed files.

import os
import sys

files = sys.argv[1:]

if len(files) == 0:
    files = ["lib/default-isynth.karuta",
             "lib/karuta_exit.v", "lib/karuta_wait.v"]

ofn = "embedded_data/embedded_data.h"

ofh = open(ofn, "w")
ofh.write("""
#include <string>
#include <map>

std::map<std::string, std::string> get_embedded_file_images() {
  // This is a placeholder to embed data located under embedded_data/.
  // Real data should be located in a directory with higher include priority.
  std::map<std::string, std::string> m = {
""")
ofh.write(
    """    {\"internal-placeholder.karuta\", "print(\\"" PACKAGE "-" VERSION "*\\")\\n"},
""")


for fn in files:
    bn = os.path.basename(fn)
    s = open(fn).read()
    s = s.replace("\"", "\\\"")
    s = s.replace("\n", "\\n")
    ofh.write("    {\"%s\", \"%s\"},\n" % (bn, s))


ofh.write("""  };
  return m;
}
""")
ofh.close()
