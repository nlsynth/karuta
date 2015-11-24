// -*- C++ -*-
#ifndef _dfg_imported_resource_h_
#define _dfg_imported_resource_h_

#include "nli.h"

namespace dfg {

class ImportParam;
class ImportParamSet;
class ImportedResource;

class Importer {
public:
  static void Init();

  // Called from parser
  static ImportedResource *Import(ImportParamSet *params);
  static ImportParam *BuildStrParam(sym_t key, const char *str);
  static void AddStrParam(ImportParam *p, const char *str);
  static ImportParamSet *BuildParamSet(ImportParamSet *lst,
				       ImportParam *p);
};

class ImportedResource_pin {
public:
  sym_t name;
  bool is_out;
  int width;
};

class ImportedResource {
public:
  ImportedResource(ImportParamSet *params);
  ~ImportedResource();

  bool IsImportedModule();
  bool IsExtIO();
  bool IsExtInput();
  bool IsExtOutput();

  // For imported Verilog module.
  string GetResourceName();
  string GetCopyFileName();
  string GetModuleName();
  string GetClockPinName();
  string GetResetPinName();

  // For external resource.
  string GetOutputPinName();
  string GetInputPinName();

  void AddPinDecl(sym_t name, bool is_out, int width);
  int GetNrPinDecls();
  bool GetNthPinDecl(int nth, ImportedResource_pin *decl);

private:
  string LookupStrParam(sym_t key, string dflt);
  ImportParam *LookupParam(sym_t key);

  ImportParamSet *params_;
  vector<ImportedResource_pin> pins_;
};

}  // namespace dfg
using namespace dfg;

#endif  // _dfg_imported_resource_h_
