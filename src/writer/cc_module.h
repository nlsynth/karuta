// -*- C++ -*-
#ifndef _writer_cc_module_h_
#define _writer_cc_module_h_

#include "writer/writer.h"

namespace dfg {
class DArray;
class DGraph;
class DInsn;
class DModule;
class DState;
}  // namespace dfg
using namespace dfg;

namespace writer {

class CCWriter;
class ClassWriter;
class ModuleTemplate;

class CCModule {
public:
  CCModule(const string &path, DModule *mod, ostream &os);
  virtual ~CCModule();

  void Output();

private:
  void OutputModule();
  void OutputArrayDecl(const string &name, const DArray *array);
  void OutputChannelInstantiation(const DModule *dm);
  void OutputDispatcher();
  void OutputPostState();
  void OutputStateDumper();
  void OutputResetHandler();
  void OutputTaskEntry();

  string TaskEntryFunctionName(DModule *mod);
  string SubModuleName(DModule *mod);

  DModule *mod_;
  ostream &os_;
  CCWriter *writer_;
  std::unique_ptr<ClassWriter> cw_;
  string path_;
  vector<string> sub_instances_;
  std::unique_ptr<ModuleTemplate> template_;
};

}  // namespace writer

#endif  // _writer_cc_module_h_
