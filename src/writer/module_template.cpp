#include "writer/module_template.h"

namespace writer {

ostream &ModuleTemplate::GetStream(enum TemplatePoint point) {
  return streams_[point];
}

string ModuleTemplate::GetContents(enum TemplatePoint point) {
  return streams_[point].str();
}

}  // namespace writer
