#include "karuta/annotation.h"

#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <list>
#include <regex>

#include "base/pool.h"
#include "base/stl_util.h"
#include "iroha/base/util.h"
#include "karuta/annotation_builder.h"

static const char kResource[] = "resource";
static const char kFile[] = "file";
static const char kCopy[] = "copy";
static const char kVerilog[] = "verilog";
static const char kModule[] = "module";
static const char kClock[] = "clock";
static const char kReset[] = "reset";
static vector<string> kwsAxim = {
    "AxiMaster",
    "AxiMaster64",
    "AxiMaster32",
    "AxiManager",
    "AxiManager64",
    "AxiManager32",
    "ExportWithAxiMaster",
    "ExportWithAxiMaster64",
    "ExportWithAxiMaster32",
    "ExportWithAxiManager",
    "ExportWithAxiManager64",
    "ExportWithAxiManager32",
};
static vector<string> kwsAxis = {
    "AxiSlave",
    "AxiSlave64",
    "AxiSlave32",
    "AxiSubordinate",
    "AxiSubordinate64",
    "AxiSubordinate32",
    "ExportWithAxiSlave",
    "ExportWithAxiSlave64",
    "ExportWithAxiSlave32",
    "ExportWithAxiSubordinate",
    "ExportWithAxiSubordinate64",
    "ExportWithAxiSubordinate32",
};
static vector<string> kwsAximExport = {
    "ExportWithAxiMaster",  "ExportWithAxiMaster64",  "ExportWithAxiMaster32",
    "ExportWithAxiManager", "ExportWithAxiManager64", "ExportWithAxiManager32",
};
static vector<string> kwsAxisExport = {
    "ExportWithAxiSlave",         "ExportWithAxiSlave64",
    "ExportWithAxiSlave32",       "ExportWithAxiSubordinate",
    "ExportWithAxiSubordinate64", "ExportWithAxiSubordinate32"};
static vector<string> kws64 = {
    "AxiMaster64",
    "ExportWithAxiMaster64",
    "ExportWithAxiSlave64",
    "AxiSlave64",
    "AxiManager64",
    "ExportWithAxiManager64",
    "ExportWithAxiSubordinate64",
    "AxiSubordinate64",
};
static vector<string> kws32 = {
    "AxiMaster32",
    "ExportWithAxiMaster32",
    "ExportWithAxiSlave32",
    "AxiSlave32",
    "AxiManager32",
    "ExportWithAxiManager32",
    "ExportWithAxiSubordinate32",
    "AxiSubordinate32",
};
static vector<string> kwsExportSram = {"SramIf", "Export", "Public"};
static vector<string> kwsExportMailbox = {"Export", "public"};
static vector<string> kwsThreadEntry = {"ThreadEntry", "ProcessEntry"};
static vector<string> kwsPipeline = {"Pipeline", "PipelineX"};
static vector<string> kwsPipelineX = {"PipelineX"};
static vector<string> kwsSoftThreadEntry = {"SoftThreadEntry", "SoftProcess",
                                            "Soft"};
static vector<string> kwsThreadLocal = {"ThreadLocal", "ProcessLocal", "Local"};
static vector<string> kwsDataFlowEntry = {"DataFlowEntry", "dataflow_entry"};
static vector<string> kwsExtEntry = {"ExtEntry"};
static vector<string> kwsExtMethodStub = {"ExtStub"};
static vector<string> kwsExtFlowStub = {"ExtFlowStub"};
static vector<string> kwsExtCombinational = {"ExtCombinational"};
static vector<string> kwsExtIO = {"ExtIO"};
static vector<string> kwsExternal = {"External"};

static Pool<Annotation> resource_params_pool;
std::unique_ptr<Annotation> Annotation::empty_annotation_;

AnnotationKeyValueSet::~AnnotationKeyValueSet() { STLDeleteValues(&params_); }

Annotation::Annotation(AnnotationKeyValueSet *params) {
  if (params == nullptr) {
    params = new AnnotationKeyValueSet();
  } else {
    // the pool manages all non empty params instances.
    resource_params_pool.Add(this);
  }
  params_.reset(params);
}

Annotation::Annotation(const Annotation &that) {
  resource_params_pool.Add(this);
  pins_ = that.pins_;
  params_.reset(new AnnotationKeyValueSet);
  for (AnnotationKeyValue *param : that.params_->params_) {
    AnnotationKeyValue *value = new AnnotationKeyValue;
    *value = *param;
    params_->params_.push_back(value);
  }
}

Annotation::~Annotation() {}

void Annotation::Dump(ostream &os) const {
  bool is_first_param = true;
  for (AnnotationKeyValue *param : params_->params_) {
    if (!is_first_param) {
      os << ",";
    }
    os << "[" << param->key_ << "]=";
    if (param->has_str_) {
      os << param->str_value_;
    } else {
      os << param->int_value_;
    }
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

Annotation *Annotation::EmptyAnnotation() {
  if (empty_annotation_.get() == nullptr) {
    empty_annotation_.reset(new Annotation(nullptr));
  }
  return empty_annotation_.get();
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

string Annotation::GetAckPinName() { return LookupStrParam("ack", ""); }

bool Annotation::ResetPolarity() {
  string s = LookupStrParam("resetPolarity", "");
  if (s == "") {
    uint64_t p = LookupIntParam("resetPolarity", 1);
    return p > 0;
  } else {
    return s == "1";
  }
}

int Annotation::MaxDelayPs() { return LookupIntParam("maxDelayPs", -1); }

bool Annotation::IsAxiMaster() { return CheckAnnotation(kwsAxim); }

bool Annotation::IsAxiSlave() { return CheckAnnotation(kwsAxis); }

bool Annotation::IsAxiExclusive() {
  return (LookupStrParam("sramConnection", "exclusive") == "exclusive");
}

bool Annotation::IsAxiMasterAndExport() {
  if (CheckAnnotation(kwsAximExport)) {
    return true;
  }
  return IsAxiMaster() && (LookupIntParam("export", 0) > 0);
}

bool Annotation::IsAxiSlaveAndExport() {
  if (CheckAnnotation(kwsAxisExport)) {
    return true;
  }
  return IsAxiSlave() && (LookupIntParam("export", 0) > 0);
}

bool Annotation::IsExportSramIf() {
  if (CheckAnnotation(kwsExportSram)) {
    return true;
  }
  return IsAxiSlaveAndExport();
}

bool Annotation::IsExportMailbox() { return CheckAnnotation(kwsExportMailbox); }

int Annotation::GetAddrWidth() {
  if (CheckAnnotation(kws64)) {
    return 64;
  }
  if (CheckAnnotation(kws32)) {
    return 32;
  }
  uint64_t w = LookupIntParam("addrWidth", 0);
  if (w == 64 || w == 32) {
    return w;
  }
  string s = LookupStrParam("addrWidth", "32");
  if (s == "64") {
    return 64;
  }
  if (s == "32") {
    return 32;
  }
  return 0;
}

int Annotation::GetDepth() { return LookupIntParam("depth", 1); }

bool Annotation::IsThreadEntry() { return CheckAnnotation(kwsThreadEntry); }

int Annotation::GetDistance() { return LookupIntParam("distance", 0); }

bool Annotation::IsPipeline() { return CheckAnnotation(kwsPipeline); }

bool Annotation::IsPipelineX() { return CheckAnnotation(kwsPipelineX); }

bool Annotation::IsSoftThreadEntry() {
  return CheckAnnotation(kwsSoftThreadEntry);
}

string Annotation::GetName() { return LookupStrParam("name", ""); }

int Annotation::GetNum() { return LookupIntParam("num", 1); }

bool Annotation::IsThreadLocal() { return CheckAnnotation(kwsThreadLocal); }

bool Annotation::IsNoWait() {
  int nw = LookupIntParam("noWait", 0);
  return nw;
}

string Annotation::GetWenSuffix() { return LookupStrParam("wen", ""); }

string Annotation::GetNotifySuffix() { return LookupStrParam("notify", ""); }

string Annotation::GetPutSuffix() { return LookupStrParam("put", ""); }

bool Annotation::IsDataFlowEntry() { return CheckAnnotation(kwsDataFlowEntry); }

bool Annotation::IsExtEntry() { return CheckAnnotation(kwsExtEntry); }

bool Annotation::IsExtMethodStub() { return CheckAnnotation(kwsExtMethodStub); }

bool Annotation::IsExtFlowStub() { return CheckAnnotation(kwsExtFlowStub); }

bool Annotation::IsExtIO() { return CheckAnnotation(kwsExtIO); }

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

bool Annotation::IsExtCombinational() {
  return CheckAnnotation(kwsExtCombinational);
}

bool Annotation::IsExternal() { return CheckAnnotation(kwsExternal); }

string Annotation::LookupStrParam(const string &key, const string &dflt) {
  AnnotationKeyValue *p = LookupParam(key);
  if (!p) {
    return dflt;
  }
  return p->str_value_;
}

uint64_t Annotation::LookupIntParam(const string &key, uint64_t dflt) {
  AnnotationKeyValue *p = LookupParam(key);
  if (!p || p->has_str_) {
    return dflt;
  }
  return p->int_value_;
}

AnnotationKeyValue *Annotation::LookupParam(const string &key) {
  for (AnnotationKeyValue *param : params_->params_) {
    if (key == param->key_) {
      return param;
    }
  }
  return nullptr;
}

string Annotation::GetResourceName() { return LookupStrParam(kResource, ""); }

string Annotation::GetCopyFileName() {
  string file = LookupStrParam(kFile, "");
  if (file != "copy") {
    return "";
  }
  AnnotationKeyValue *p = LookupParam(kVerilog);
  if (!p) {
    std::cout << "source file to be copied is not specified.\n";
    abort();
    return "";
  }
  return p->str_value_;
}

string Annotation::GetModuleName() { return LookupStrParam(kModule, ""); }

string Annotation::GetClockPinName() { return LookupStrParam(kClock, "clk"); }

string Annotation::GetResetPinName() { return LookupStrParam(kReset, "rst"); }

void Annotation::AddPinDecl(sym_t name, bool is_out, int width) {
  ResourceParams_pin pin;
  pin.name = name;
  pin.is_out = is_out;
  pin.width = width;

  pins_.push_back(pin);
}

int Annotation::GetNrPinDecls() { return pins_.size(); }

bool Annotation::GetNthPinDecl(int nth, ResourceParams_pin *decl) {
  if (nth >= 0 && nth < static_cast<int>(pins_.size())) {
    *decl = pins_[nth];
    return true;
  }
  return false;
}

string Annotation::GetPlatformFamily() {
  return LookupStrParam("platformFamily", "");
}

string Annotation::GetPlatformName() {
  return LookupStrParam("platformName", "");
}

void Annotation::AddStrParam(const string &key, const string &value) {
  AnnotationKeyValue *param = LookupParam(key);
  if (param) {
    param->str_value_ = value;
    param->has_str_ = true;
  } else {
    param = AnnotationBuilder::BuildStrParam(sym_lookup(key.c_str()),
                                             value.c_str());
    params_->params_.push_back(param);
  }
}

void Annotation::AddIntParam(const string &key, uint64_t value) {
  AnnotationKeyValue *param = LookupParam(key);
  if (param) {
    param->int_value_ = value;
    param->has_str_ = false;
  } else {
    param = AnnotationBuilder::BuildIntParam(sym_lookup(key.c_str()), value);
    params_->params_.push_back(param);
  }
}

bool Annotation::CheckAnnotation(const vector<string> &kws) {
  // Allows FooBar foobar foo_bar.
  string s = LookupStrParam(annotation::kAnnotationKey, "");
  s = regex_replace(s, regex("_"), "");
  for (auto &kw : kws) {
    if (kw == s) {
      return true;
    }
    if (iroha::Util::ToLower(kw) == s) {
      return true;
    }
  }
  return false;
}