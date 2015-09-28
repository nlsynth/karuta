// -*- C++ -*-
#ifndef _writer_module_template_h_
#define _writer_module_template_h_

#include "nli.h"

#include <sstream>
#include <map>

namespace writer {

class ModuleTemplate {
public:
  enum TemplatePoint {
    // Some of them are language dependent.
    RESET_STATE,
    SUB_STATE_REGS,
    SUB_MODULE_CONTROL_WIRES,
    SUB_MODULE_INSTANCES,
    STATE_SWITCH,
    STATE_DUMPER,
    POST_STATE,
  };

  ostream &GetStream(enum TemplatePoint point);
  string GetContents(enum TemplatePoint point);

private:
  std::map<TemplatePoint, std::ostringstream> streams_;
};

}  // namespace writer

#endif  // _writer_module_template_h_
