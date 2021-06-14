// -*- C++ -*-
#ifndef _karuta_annotation_h_
#define _karuta_annotation_h_

map<string, string> get_embedded_file_images() {
  // This is a placeholder to embed data located under embedded_data/.
  // Real data should be located in a directory with higher include priority.
  map<string, string> m = {
      {"internal-placeholder.karuta", "print(\"" PACKAGE "-" VERSION "\")\n"},
  };
  return m;
}

#endif  // _karuta_embedded_data_h_