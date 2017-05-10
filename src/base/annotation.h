// -*- C++ -*-
#ifndef _base_annotation_h_
#define _base_annotation_h_

#include "nli.h"

class AnnotationValue;
class AnnotationValueSet;
class Annotation;

class AnnotationBuilder {
public:
  static void Init();

  // Called mainly from parser
  static Annotation *Build(sym_t key, AnnotationValueSet *values);
  static AnnotationValue *BuildStrParam(sym_t key, const char *str);
  static void AddStrParam(AnnotationValue *p, const char *str);
  static AnnotationValueSet *BuildParamSet(AnnotationValueSet *lst,
					   AnnotationValue *p);
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

  string GetThreadEntry();
  string GetDataFlowEntry();

  bool ResetPolarity();

  void AddPinDecl(sym_t name, bool is_out, int width);
  int GetNrPinDecls();
  bool GetNthPinDecl(int nth, ResourceParams_pin *decl);

  void AddParam(const string &key, const string &value);

private:
  string LookupStrParam(sym_t key, string dflt);
  AnnotationValue *LookupParam(sym_t key);

  AnnotationValueSet *params_;
  vector<ResourceParams_pin> pins_;
};

#endif  // _base_annotation_h_
