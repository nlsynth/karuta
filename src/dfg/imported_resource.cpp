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
  string GetNthValue(int nth);

  sym_t key_;
  vector <string> values_;
};

class ImportParamSet {
public:
  ~ImportParamSet();
  vector<ImportParam *> params_;
};

string ImportParam::GetNthValue(int nth) {
  if (nth < values_.size()) {
    return values_[nth];
  }
  return "";
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

bool ImportedResource::IsImportedModule() {
  if (LookupParam(sym_verilog)) {
    return true;
  }
  return false;
}

string ImportedResource::GetOutputPinName() {
  return LookupStrParam(sym_output, "");
}

string ImportedResource::GetInputPinName() {
  return LookupStrParam(sym_input, "");
}

bool ImportedResource::IsExtIO() {
  if (LookupParam(sym_output) || LookupParam(sym_input)) {
    return true;
  }
  return false;
}

bool ImportedResource::IsExtInput() {
  if (LookupParam(sym_input)) {
    return true;
  }
  return false;
}

bool ImportedResource::IsExtOutput() {
  if (LookupParam(sym_output)) {
    return true;
  }
  return false;
}

string ImportedResource::LookupStrParam(sym_t key, string dflt) {
  ImportParam *p = LookupParam(key);
  if (!p) {
    return dflt;
  }
  return p->GetNthValue(0);
}

ImportParam *ImportedResource::LookupParam(sym_t key) {
  for (ImportParam *param : params_->params_) {
    if (key == param->key_) {
      return param;
    }
  }
  return NULL;
}

string ImportedResource::GetResourceName() {
  return LookupStrParam(sym_resource, "");
}

string ImportedResource::GetCopyFileName() {
  string file = LookupStrParam(sym_file, "");
  if (file != "copy") {
    return "";
  }
  ImportParam *p = LookupParam(sym_verilog);
  if (!p) {
    std::cout << "source file to be copied is not specified.\n";
    abort();
    return "";
  }
  return p->GetNthValue(0);
}

string ImportedResource::GetModuleName() {
  return LookupStrParam(sym_module, "");
}

string ImportedResource::GetClockPinName() {
  return LookupStrParam(sym_clock, "clk");
}

string ImportedResource::GetResetPinName() {
  return LookupStrParam(sym_reset, "rst");
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
