// -*- C++ -*-
#ifndef _writer_vl_module_h_
#define _writer_vl_module_h_

#include "writer/writer.h"

#include <map>

using std::map;

namespace dfg {
class DArray;
class DGraph;
class DInsn;
class DModule;
class DRegister;
class DResource;
class DState;
class DType;
class ImportedResource_pin;
}  // namespace
using namespace dfg;

namespace writer {

class ModuleTemplate;
class VLChannelWriter;
class VLGraph;
class VLIOSet;

class VLModule {
public:
  VLModule(DModule *mod, const string &path_name,
	   VLChannelWriter *ch, ostream &os);
  virtual ~VLModule();

  void Output(vector<string> *copy_files);

private:
  void PreProcessModule(const string &path_name);
  void PreProcessSubModuleControl(const DModule *dm, bool has_graph,
				  ostream &os);

  void OutputVLModule(const string &name);
  void OutputExternalStuff(vector<string> *copy_files);
  void OutputModuleHead(const string &path);
  void OutputArray(const string &name, DArray *array);
  void CollectPinDecls();
  void CollectTaskPins(DModule *dm);
  void OutputRAM(const DArray *array);

  const string path_name_;
  std::unique_ptr<VLIOSet> pins_;
  std::unique_ptr<ModuleTemplate> template_;
  VLChannelWriter *ch_;
  DModule *mod_;
  ostream &os_;
};

}  // namespace writer

#endif  // _writer_vl_module_h_
