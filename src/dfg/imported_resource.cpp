#include "dfg/imported_resource.h"

#include <iostream>
#include <list>
#include <stdlib.h>
#include <string.h>
#include "nli.h"
#include "pool.h"

static sym_t sym_resource, sym_file, sym_copy, sym_verilog;
static sym_t sym_module, sym_clock, sym_reset;

namespace dfg {

static Pool<ImportedResource> imported_resource_pool;

class import_param {
public:
  sym_t key;
  vector <string> values;
  sym_t nthSym(int nth);
};

class import_params {
public:
  ~import_params();
  vector<import_param *> param_list;
};

sym_t import_param::nthSym(int nth) {
  for (string &s : values) {
    if (nth == 0) {
      return sym_lookup(s.c_str());
    }
    nth --;
  }
  return sym_null;
}

import_params::~import_params() {
  STLDeleteValues(&param_list);
}

ImportedResource::ImportedResource(import_params *params) {
  imported_resource_pool.Add(this);
  m_params = params;
}

ImportedResource::~ImportedResource() {
  delete m_params;
}

sym_t ImportedResource::lookup_sym_param(sym_t key, sym_t dflt) {
  import_param *p = lookup_param(key);
  if (!p) {
    return dflt;
  }
  return p->nthSym(0);
}

import_param *ImportedResource::lookup_param(sym_t key) {
  const char *key_cstr = sym_cstr(key);
  LOG(INFO) << "lookup: " << key_cstr;
  for (vector<import_param *>::iterator it = m_params->param_list.begin();
       it != m_params->param_list.end(); it++) {
    if (!strcmp(sym_cstr((*it)->key), key_cstr)) {
      return *it;
    }
  }
  return NULL;
}

sym_t ImportedResource::GetResourceName() {
  return lookup_sym_param(sym_resource, sym_null);
}

sym_t ImportedResource::GetCopyFileName() {
  sym_t file = lookup_sym_param(sym_file, sym_null);
  if (file != sym_copy) {
    return sym_null;
  }
  import_param *p = lookup_param(sym_verilog);
  if (!p) {
    std::cout << "source file to be copied is not specified.\n";
    abort();
    return sym_null;
  }
  return p->nthSym(0);
}

sym_t ImportedResource::GetModuleName() {
  return lookup_sym_param(sym_module, sym_null);
}

sym_t ImportedResource::GetClockPinName() {
  return lookup_sym_param(sym_clock, sym_lookup("clk"));
}

sym_t ImportedResource::GetResetPinName() {
  return lookup_sym_param(sym_reset, sym_lookup("rst"));
}

void ImportedResource::AddPinDecl(sym_t name, bool is_out, int width) {
  ImportedResource_pin pin;
  pin.name = name;
  pin.is_out = is_out;
  pin.width = width;

  m_pins.push_back(pin);
}

int ImportedResource::GetNrPinDecls() {
  return m_pins.size();
}

bool ImportedResource::GetNthPinDecl(int nth, ImportedResource_pin *decl) {
  if (nth >= 0 && nth < static_cast<int>(m_pins.size())) {
    *decl = m_pins[nth];
    return true;
  }
  return false;
}

void import_param_add_str(import_param *p, const char *str) {
  p->values.push_back(string(str));
}

import_param *build_str_import_param(sym_t key, const char *str) {
  import_param *p = new import_param();
  p->key = key;
  import_param_add_str(p, str);
  return p;
}

import_params *build_import_params(import_params *params, import_param *p) {
  if (!params) {
    params = new import_params();
  }
  params->param_list.push_back(p);
  return params;
}

ImportedResource *import_resource(import_params *params) {
  ImportedResource *res = new ImportedResource(params);
  return res;
}

void Importer::Init() {
  sym_resource = sym_lookup("resource");
  sym_file = sym_lookup("file");
  sym_copy = sym_lookup("copy");
  sym_verilog = sym_lookup("verilog");
  sym_module = sym_lookup("module");
  sym_clock = sym_lookup("clock");
  sym_reset = sym_lookup("reset");
}

STATIC_INITIALIZER(importer , Importer::Init());
}  // namespace dfg
