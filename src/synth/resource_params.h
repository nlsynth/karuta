// -*- C++ -*-
#ifndef _synth_resource_params_h_
#define _synth_resource_params_h_

#include "nli.h"

namespace synth {

class ResourceParamValue;
class ResourceParamValueSet;
class ResourceParams;

class Importer {
public:
  static void Init();

  // Called mainly from parser
  static ResourceParams *Import(ResourceParamValueSet *params);
  static ResourceParamValue *BuildStrParam(sym_t key, const char *str);
  static void AddStrParam(ResourceParamValue *p, const char *str);
  static ResourceParamValueSet *BuildParamSet(ResourceParamValueSet *lst,
					      ResourceParamValue *p);
};

class ResourceParams_pin {
public:
  sym_t name;
  bool is_out;
  int width;
};

class ResourceParams {
public:
  explicit ResourceParams(ResourceParamValueSet *params);
  ResourceParams(const ResourceParams &that);
  ~ResourceParams();

  void Dump(ostream &os) const;
  static ResourceParams *Copy(ResourceParams *params);

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
  string GetAckPinName();

  // For external resource.
  string GetOutputPinName();
  string GetInputPinName();

  string GetThreadEntry();
  string GetDataFlowEntry();

  bool ResetPolarity();

  void AddPinDecl(sym_t name, bool is_out, int width);
  int GetNrPinDecls();
  bool GetNthPinDecl(int nth, ResourceParams_pin *decl);

  void AddParam(const string &key, const string &value);

private:
  string LookupStrParam(sym_t key, string dflt);
  ResourceParamValue *LookupParam(sym_t key);

  ResourceParamValueSet *params_;
  vector<ResourceParams_pin> pins_;
};

}  // namespace synth
using namespace synth;

#endif  // _synth_resource_params_h_
