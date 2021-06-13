// -*- C++ -*-
#ifndef _karuta_annotation_h_
#define _karuta_annotation_h_

#include "iroha/base/file.h"

void init_embedded_data() {
  // This is a placeholder to embed data located under src/.
  // Real data should be located in a directory with higher include priority.
  iroha::File::RegisterFile("internal-placeholder.karuta",
                            "print(\"" VERSION "\")\n");
}

#endif  // _karuta_embedded_data_h_