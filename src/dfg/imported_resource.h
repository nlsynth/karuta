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

  sym_t GetResourceName();
  sym_t GetCopyFileName();
  sym_t GetModuleName();
  sym_t GetClockPinName();
  sym_t GetResetPinName();

  void AddPinDecl(sym_t name, bool is_out, int width);
  int GetNrPinDecls();
  bool GetNthPinDecl(int nth, ImportedResource_pin *decl);

private:
  sym_t LookupSymParam(sym_t key, sym_t dflt);
  ImportParam *LookupParam(sym_t key);

  ImportParamSet *params_;
  vector<ImportedResource_pin> pins_;
};

}  // namespace dfg
using namespace dfg;

#endif  // _dfg_imported_resource_h_
