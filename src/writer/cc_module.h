// -*- C++ -*-
#ifndef _writer_cc_module_h_
#define _writer_cc_module_h_

#include "writer/writer.h"

namespace dfg {
class DGraph;
class DInsn;
class DModule;
class DState;
}  // namespace dfg
using namespace dfg;

namespace writer {

class ClassWriter;

class CCModule : public Writer {
public:
  CCModule(const string &path, DModule *mod, ostream &os);
  void Output();

private:
  void OutputModule();
  void OutputArrayDecl(const string &name, const DArray *array);
  void OutputChannelInstantiation(const DModule *dm);
  void OutputDispatcher(const DGraph *g);
  void OutputStateDumper(const DGraph *g);
  void OutputResetHandler(const DGraph *g);

  std::unique_ptr<ClassWriter> cw_;
  string path_;
  vector<string> sub_instances_;
};

}  // namespace writer

#endif  // _writer_cc_module_h_
