#include "base/annotation.h"

#include <iostream>
#include <list>
#include <stdlib.h>
#include <string.h>
#include "nli.h"
#include "base/annotation_builder.h"
#include "base/pool.h"

static const char kResource[] = "RESOURCE";
static const char kFile[] = "FILE";
static const char kCopy[] = "COPY";
static const char kVerilog[] = "VERILOG";
static const char kModule[] = "MODULE";
static const char kClock[] = "CLOCK";
static const char kReset[] = "RESET";

static Pool<Annotation> resource_params_pool;

string AnnotationValue::GetNthValue(int nth) {
  if (nth < (int)values_.size()) {
    return values_[nth];
  }
  return "";
}

AnnotationValueSet::~AnnotationValueSet() {
  STLDeleteValues(&params_);
}

Annotation::Annotation(AnnotationValueSet *params) {
  resource_params_pool.Add(this);
  params_ = params;
}

Annotation::Annotation(const Annotation &that) {
  resource_params_pool.Add(this);
  pins_ = that.pins_;
  params_ = new AnnotationValueSet;
  for (AnnotationValue *param : that.params_->params_) {
    AnnotationValue *value = new AnnotationValue;
    *value = *param;
    params_->params_.push_back(value);
  }
}

Annotation::~Annotation() {
  delete params_;
}

void Annotation::Dump(ostream &os) const {
  bool is_first_param = true;
  for (AnnotationValue *param : params_->params_) {
    if (!is_first_param) {
      os << ",";
    }
    os << "[" << param->key_ << "]=";
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

Annotation *Annotation::Copy(Annotation *params) {
  return new Annotation(*params);
}

bool Annotation::IsImportedModule() {
  if (LookupParam(kVerilog)) {
    return true;
  }
  return false;
}

string Annotation::GetOutputPinName() {
  return LookupStrParam(sym_cstr(sym_output), "");
}

string Annotation::GetInputPinName() {
  return LookupStrParam(sym_cstr(sym_input), "");
}

string Annotation::GetAckPinName() {
  return LookupStrParam("ack", "");
}

bool Annotation::ResetPolarity() {
  return (LookupStrParam("resetPolarity", "1") == "1");
}

string Annotation::GetThreadEntry() {
  return LookupStrParam("thread_entry", "");
}

string Annotation::GetDataFlowEntry() {
  return LookupStrParam("dataflow_entry", "");
}

bool Annotation::IsExtIO() {
  if (LookupParam(sym_cstr(sym_output)) || LookupParam(sym_cstr(sym_input))) {
    return true;
  }
  return false;
}

bool Annotation::IsExtInput() {
  if (LookupParam(sym_cstr(sym_input))) {
    return true;
  }
  return false;
}

bool Annotation::IsExtOutput() {
  if (LookupParam(sym_cstr(sym_output))) {
    return true;
  }
  return false;
}

string Annotation::LookupStrParam(const string &key, const string &dflt) {
  AnnotationValue *p = LookupParam(key);
  if (!p) {
    return dflt;
  }
  return p->GetNthValue(0);
}

AnnotationValue *Annotation::LookupParam(const string &key) {
  for (AnnotationValue *param : params_->params_) {
    if (key == param->key_) {
      return param;
    }
  }
  return nullptr;
}

string Annotation::GetResourceName() {
  return LookupStrParam(kResource, "");
}

string Annotation::GetCopyFileName() {
  string file = LookupStrParam(kFile, "");
  if (file != "copy") {
    return "";
  }
  AnnotationValue *p = LookupParam(kVerilog);
  if (!p) {
    std::cout << "source file to be copied is not specified.\n";
    abort();
    return "";
  }
  return p->GetNthValue(0);
}

string Annotation::GetModuleName() {
  return LookupStrParam(kModule, "");
}

string Annotation::GetClockPinName() {
  return LookupStrParam(kClock, "clk");
}

string Annotation::GetResetPinName() {
  return LookupStrParam(kReset, "rst");
}

void Annotation::AddPinDecl(sym_t name, bool is_out, int width) {
  ResourceParams_pin pin;
  pin.name = name;
  pin.is_out = is_out;
  pin.width = width;

  pins_.push_back(pin);
}

int Annotation::GetNrPinDecls() {
  return pins_.size();
}

bool Annotation::GetNthPinDecl(int nth, ResourceParams_pin *decl) {
  if (nth >= 0 && nth < static_cast<int>(pins_.size())) {
    *decl = pins_[nth];
    return true;
  }
  return false;
}

void Annotation::AddParam(const string &key, const string &value) {
  AnnotationValue *param = LookupParam(key);
  if (param) {
    param->values_.push_back(value);
  } else {
    param = AnnotationBuilder::BuildStrParam(sym_lookup(key.c_str()), value.c_str());
    params_->params_.push_back(param);
  }
}
