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

class ImportParam {
public:
  sym_t GetNthSym(int nth);

  sym_t key_;
  vector <string> values_;
};

class ImportParamSet {
public:
  ~ImportParamSet();
  vector<ImportParam *> params_;
};

sym_t ImportParam::GetNthSym(int nth) {
  if (nth < values_.size()) {
    return sym_lookup(values_[nth].c_str());
  }
  return sym_null;
}

ImportParamSet::~ImportParamSet() {
  STLDeleteValues(&params_);
}

ImportedResource::ImportedResource(ImportParamSet *params) {
  imported_resource_pool.Add(this);
  params_ = params;
}

ImportedResource::~ImportedResource() {
  delete params_;
}

sym_t ImportedResource::LookupSymParam(sym_t key, sym_t dflt) {
  ImportParam *p = LookupParam(key);
  if (!p) {
    return dflt;
  }
  return p->GetNthSym(0);
}

ImportParam *ImportedResource::LookupParam(sym_t key) {
  for (ImportParam *param : params_->params_) {
    if (key == param->key_) {
      return param;
    }
  }
  return NULL;
}

sym_t ImportedResource::GetResourceName() {
  return LookupSymParam(sym_resource, sym_null);
}

sym_t ImportedResource::GetCopyFileName() {
  sym_t file = LookupSymParam(sym_file, sym_null);
  if (file != sym_copy) {
    return sym_null;
  }
  ImportParam *p = LookupParam(sym_verilog);
  if (!p) {
    std::cout << "source file to be copied is not specified.\n";
    abort();
    return sym_null;
  }
  return p->GetNthSym(0);
}

sym_t ImportedResource::GetModuleName() {
  return LookupSymParam(sym_module, sym_null);
}

sym_t ImportedResource::GetClockPinName() {
  return LookupSymParam(sym_clock, sym_lookup("clk"));
}

sym_t ImportedResource::GetResetPinName() {
  return LookupSymParam(sym_reset, sym_lookup("rst"));
}

void ImportedResource::AddPinDecl(sym_t name, bool is_out, int width) {
  ImportedResource_pin pin;
  pin.name = name;
  pin.is_out = is_out;
  pin.width = width;

  pins_.push_back(pin);
}

int ImportedResource::GetNrPinDecls() {
  return pins_.size();
}

bool ImportedResource::GetNthPinDecl(int nth, ImportedResource_pin *decl) {
  if (nth >= 0 && nth < static_cast<int>(pins_.size())) {
    *decl = pins_[nth];
    return true;
  }
  return false;
}

void Importer::AddStrParam(ImportParam *p, const char *str) {
  p->values_.push_back(string(str));
}

ImportParam *Importer::BuildStrParam(sym_t key, const char *str) {
  ImportParam *p = new ImportParam();
  p->key_ = key;
  AddStrParam(p, str);
  return p;
}

ImportParamSet *Importer::BuildParamSet(ImportParamSet *params,
					ImportParam *p) {
  if (!params) {
    params = new ImportParamSet();
  }
  params->params_.push_back(p);
  return params;
}

ImportedResource *Importer::Import(ImportParamSet *params) {
  return new ImportedResource(params);
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
