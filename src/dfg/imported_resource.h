// -*- C++ -*-
#ifndef _dfg_imported_resource_h_
#define _dfg_imported_resource_h_

#include "nli.h"

namespace dfg {

struct import_param;
struct import_params;

class Importer {
public:
  static void Init();
};

class ImportedResource_pin {
 public:
  sym_t name;
  bool is_out;
  int width;
};

class ImportedResource {
public:
  ImportedResource(import_params *params);
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
  sym_t lookup_sym_param(sym_t key, sym_t dflt);
  import_param *lookup_param(sym_t key);
  import_params *m_params;
  vector<ImportedResource_pin> m_pins;
};

// called parser
import_param *build_str_import_param(sym_t key, const char *str);
void import_param_add_str(import_param *p, const char *str);
import_params *build_import_params(import_params *lst, import_param *p);
ImportedResource *import_resource(import_params *params);

}  // namespace dfg
using namespace dfg;

#endif  // _dfg_imported_resource_h_
