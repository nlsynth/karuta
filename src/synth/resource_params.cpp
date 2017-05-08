#include "synth/resource_params.h"

#include <iostream>
#include <list>
#include <stdlib.h>
#include <string.h>
#include "nli.h"
#include "base/pool.h"

static sym_t sym_resource, sym_file, sym_copy, sym_verilog;
static sym_t sym_module, sym_clock, sym_reset;

namespace synth {

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

ResourceParams::ResourceParams(const ResourceParams &that) {
  resource_params_pool.Add(this);
  pins_ = that.pins_;
  params_ = new ResourceParamValueSet;
  for (ResourceParamValue *param : that.params_->params_) {
    ResourceParamValue *value = new ResourceParamValue;
    *value = *param;
    params_->params_.push_back(value);
  }
}

ResourceParams::~ResourceParams() {
  delete params_;
}

void ResourceParams::Dump(ostream &os) const {
  bool is_first_param = true;
  for (ResourceParamValue *param : params_->params_) {
    if (!is_first_param) {
      os << ",";
    }
    os << "[" << sym_cstr(param->key_) << "]=";
    bool is_first_value = true;
    for (string &value : param->values_) {
      if (!is_first_value) {
	os << ",";
      }
      os << value;
      is_first_value = false;
    }
    is_first_param = false;
  }
  if (params_->params_.size()) {
    os << " ";
  }
  for (const ResourceParams_pin &pin : pins_) {
    os << sym_cstr(pin.name) << ":";
    if (pin.is_out) {
      os << "out:";
    } else {
      os << "in:";
    }
    os << pin.width;
  }
}

ResourceParams *ResourceParams::Copy(ResourceParams *params) {
  return new ResourceParams(*params);
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

string ResourceParams::GetAckPinName() {
  return LookupStrParam(sym_lookup("ack"), "");
}

bool ResourceParams::ResetPolarity() {
  return (LookupStrParam(sym_lookup("resetPolarity"), "1") == "1");
}

string ResourceParams::GetThreadEntry() {
  return LookupStrParam(sym_lookup("thread_entry"), "");
}

string ResourceParams::GetDataFlowEntry() {
  return LookupStrParam(sym_lookup("dataflow_entry"), "");
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
  return nullptr;
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

void ResourceParams::AddParam(const string &key, const string &value) {
  ResourceParamValue *param = LookupParam(sym_lookup(key.c_str()));
  if (param) {
    param->values_.push_back(value);
  } else {
    param = Importer::BuildStrParam(sym_lookup(key.c_str()), value.c_str());
    params_->params_.push_back(param);
  }
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
  if (!params) {
    params = new ResourceParamValueSet;
  }
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
}  // namespace synth

