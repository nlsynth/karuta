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
    RESET_STATE,
    SUB_STATE_REGS,
    SUB_MODULE_CONTROL_WIRES,
    SUB_MODULE_INSTANCES,
  };

  ostream &GetStream(enum TemplatePoint point);
  string GetContents(enum TemplatePoint point);

private:
  std::map<TemplatePoint, std::ostringstream> streams_;
};

}  // namespace writer

#endif  // _writer_module_template_h_
