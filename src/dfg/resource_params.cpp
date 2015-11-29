#include "dfg/resource_params.h"

#include <iostream>
#include <list>
#include <stdlib.h>
#include <string.h>
#include "nli.h"
#include "pool.h"

static sym_t sym_resource, sym_file, sym_copy, sym_verilog;
static sym_t sym_module, sym_clock, sym_reset;

namespace dfg {

static Pool<ResourceParams> resource_params_pool;

class ResourceParamValue {
public:
  string GetNthValue(int nth);

  sym_t key_;
  vector <string> values_;
};

class ResourceParamValueSet {
public:
  ~ResourceParamValueSet();
  vector<ResourceParamValue *> params_;
};

string ResourceParamValue::GetNthValue(int nth) {
  if (nth < (int)values_.size()) {
    return values_[nth];
  }
  return "";
}

ResourceParamValueSet::~ResourceParamValueSet() {
  STLDeleteValues(&params_);
}

ResourceParams::ResourceParams(ResourceParamValueSet *params) {
  resource_params_pool.Add(this);
  params_ = params;
}

ResourceParams::~ResourceParams() {
  delete params_;
}

bool ResourceParams::IsImportedModule() {
  if (LookupParam(sym_verilog)) {
    return true;
  }
  return false;
}

string ResourceParams::GetOutputPinName() {
  return LookupStrParam(sym_output, "");
}

string ResourceParams::GetInputPinName() {
  return LookupStrParam(sym_input, "");
}

bool ResourceParams::IsExtIO() {
  if (LookupParam(sym_output) || LookupParam(sym_input)) {
    return true;
  }
  return false;
}

bool ResourceParams::IsExtInput() {
  if (LookupParam(sym_input)) {
    return true;
  }
  return false;
}

bool ResourceParams::IsExtOutput() {
  if (LookupParam(sym_output)) {
    return true;
  }
  return false;
}

string ResourceParams::LookupStrParam(sym_t key, string dflt) {
  ResourceParamValue *p = LookupParam(key);
  if (!p) {
    return dflt;
  }
  return p->GetNthValue(0);
}

ResourceParamValue *ResourceParams::LookupParam(sym_t key) {
  for (ResourceParamValue *param : params_->params_) {
    if (key == param->key_) {
      return param;
    }
  }
  return NULL;
}

string ResourceParams::GetResourceName() {
  return LookupStrParam(sym_resource, "");
}

string ResourceParams::GetCopyFileName() {
  string file = LookupStrParam(sym_file, "");
  if (file != "copy") {
    return "";
  }
  ResourceParamValue *p = LookupParam(sym_verilog);
  if (!p) {
    std::cout << "source file to be copied is not specified.\n";
    abort();
    return "";
  }
  return p->GetNthValue(0);
}

string ResourceParams::GetModuleName() {
  return LookupStrParam(sym_module, "");
}

string ResourceParams::GetClockPinName() {
  return LookupStrParam(sym_clock, "clk");
}

string ResourceParams::GetResetPinName() {
  return LookupStrParam(sym_reset, "rst");
}

void ResourceParams::AddPinDecl(sym_t name, bool is_out, int width) {
  ResourceParams_pin pin;
  pin.name = name;
  pin.is_out = is_out;
  pin.width = width;

  pins_.push_back(pin);
}

int ResourceParams::GetNrPinDecls() {
  return pins_.size();
}

bool ResourceParams::GetNthPinDecl(int nth, ResourceParams_pin *decl) {
  if (nth >= 0 && nth < static_cast<int>(pins_.size())) {
    *decl = pins_[nth];
    return true;
  }
  return false;
}

void Importer::AddStrParam(ResourceParamValue *p, const char *str) {
  p->values_.push_back(string(str));
}

ResourceParamValue *Importer::BuildStrParam(sym_t key, const char *str) {
  ResourceParamValue *p = new ResourceParamValue();
  p->key_ = key;
  AddStrParam(p, str);
  return p;
}

ResourceParamValueSet *Importer::BuildParamSet(ResourceParamValueSet *params,
					       ResourceParamValue *p) {
  if (!params) {
    params = new ResourceParamValueSet();
  }
  params->params_.push_back(p);
  return params;
}

ResourceParams *Importer::Import(ResourceParamValueSet *params) {
  return new ResourceParams(params);
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
