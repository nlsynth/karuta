// -*- C++ -*-
#ifndef _base_annotation_h_
#define _base_annotation_h_

#include "nli.h"

namespace annotation {
const char kAnnotationKey[] = "ANNOTATION-KEY";
}  // namespace annotation

class AnnotationValue {
public:
  string GetNthValue(int nth);

  string key_;
  vector <string> values_;
};

class AnnotationValueSet {
public:
  ~AnnotationValueSet();
  vector<AnnotationValue *> params_;
};

class ResourceParams_pin {
public:
  sym_t name;
  bool is_out;
  int width;
};

class Annotation {
public:
  explicit Annotation(AnnotationValueSet *params);
  Annotation(const Annotation &that);
  ~Annotation();

  void Dump(ostream &os) const;
  static Annotation *Copy(Annotation *params);

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

  bool IsThreadEntry();
  bool IsDataFlowEntry();
  string GetName();

  bool ResetPolarity();

  bool IsAxiMaster();
  bool IsAxiSlave();

  void AddPinDecl(sym_t name, bool is_out, int width);
  int GetNrPinDecls();
  bool GetNthPinDecl(int nth, ResourceParams_pin *decl);

  void AddParam(const string &key, const string &value);

private:
  string LookupStrParam(const string &key, const string &dflt);
  AnnotationValue *LookupParam(const string &key);

  AnnotationValueSet *params_;
  vector<ResourceParams_pin> pins_;
};

#endif  // _base_annotation_h_
