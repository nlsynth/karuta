// -*- C++ -*-
#ifndef _base_annotation_h_
#define _base_annotation_h_

#include "nli.h"

namespace annotation {
const char kAnnotationKey[] = "ANNOTATION-KEY";
}  // namespace annotation

class AnnotationKeyValue {
public:
  AnnotationKeyValue() : has_str_(false) {}

  string key_;
  bool has_str_;
  string str_value_;
};

class AnnotationKeyValueSet {
public:
  ~AnnotationKeyValueSet();
  vector<AnnotationKeyValue *> params_;
};

class ResourceParams_pin {
public:
  sym_t name;
  bool is_out;
  int width;
};

class Annotation {
public:
  // Takes ownership of params.
  explicit Annotation(AnnotationKeyValueSet *params);
  Annotation(const Annotation &that);
  ~Annotation();

  void Dump(ostream &os) const;
  static Annotation *Copy(Annotation *params);
  static Annotation *EmptyAnnotation();

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
  bool IsExtEntry();
  bool IsExtMethodStub();
  bool IsExtFlowStub();
  string GetName();

  bool ResetPolarity();

  bool IsAxiMaster();
  bool IsAxiSlave();
  int GetAddrWidth();
  bool IsAxiExclusive();

  void AddPinDecl(sym_t name, bool is_out, int width);
  int GetNrPinDecls();
  bool GetNthPinDecl(int nth, ResourceParams_pin *decl);

  void AddParam(const string &key, const string &value);

private:
  string LookupStrParam(const string &key, const string &dflt);
  AnnotationKeyValue *LookupParam(const string &key);

  std::unique_ptr<AnnotationKeyValueSet> params_;
  vector<ResourceParams_pin> pins_;

  static std::unique_ptr<Annotation> empty_annotation_;
};

#endif  // _base_annotation_h_
