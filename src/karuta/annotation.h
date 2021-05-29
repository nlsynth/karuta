// -*- C++ -*-
#ifndef _karuta_annotation_h_
#define _karuta_annotation_h_

#include "karuta/karuta.h"

namespace annotation {
const char kAnnotationKey[] = "ANNOTATION-KEY";
}  // namespace annotation

class AnnotationKeyValue {
 public:
  AnnotationKeyValue() : has_str_(true) {}

  string key_;
  bool has_str_;
  string str_value_;
  uint64_t int_value_;
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
  bool IsExtCombinational();
  bool IsExternal();

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
  bool IsSoftThreadEntry();
  bool IsDataFlowEntry();
  bool IsExtEntry();
  bool IsExtMethodStub();
  bool IsExtFlowStub();
  string GetName();
  int GetNum();
  bool IsThreadLocal();
  int GetDistance();
  bool IsPipeline();
  // With experimental features.
  bool IsPipelineX();

  // resetPolarity 1 or not.
  bool ResetPolarity();

  int MaxDelayPs();

  // For AXI port.
  bool IsAxiMaster();
  bool IsAxiSlave();
  // 64 or 32.
  int GetAddrWidth();
  bool IsAxiExclusive();
  bool IsAxiMasterAndExport();
  bool IsAxiSlaveAndExport();
  // For ram.
  bool IsExportSramIf();
  // For mailbox.
  bool IsExportMailbox();
  // For fifo.
  int GetDepth();
  bool IsNoWait();

  string GetWenSuffix();
  string GetNotifySuffix();
  string GetPutSuffix();

  void AddPinDecl(sym_t name, bool is_out, int width);
  int GetNrPinDecls();
  bool GetNthPinDecl(int nth, ResourceParams_pin *decl);

  string GetPlatformFamily();
  string GetPlatformName();

  void AddStrParam(const string &key, const string &value);
  void AddIntParam(const string &key, uint64_t value);

 private:
  string LookupStrParam(const string &key, const string &dflt);
  uint64_t LookupIntParam(const string &key, uint64_t dflt);
  AnnotationKeyValue *LookupParam(const string &key);
  bool CheckAnnotation(const vector<string> &kws);

  std::unique_ptr<AnnotationKeyValueSet> params_;
  vector<ResourceParams_pin> pins_;

  static std::unique_ptr<Annotation> empty_annotation_;
};

#endif  // _karuta_annotation_h_
