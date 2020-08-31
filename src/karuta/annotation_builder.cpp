#include "karuta/annotation_builder.h"

#include "karuta/annotation.h"

void AnnotationBuilder::AddStrParam(AnnotationKeyValue *p, const char *str) {
  p->str_value_ = string(str);
  p->has_str_ = true;
}

void AnnotationBuilder::AddIntParam(AnnotationKeyValue *p, uint64_t num) {
  p->int_value_ = num;
  p->has_str_ = false;
}

AnnotationKeyValue *AnnotationBuilder::BuildStrParam(sym_t key,
                                                     const char *str) {
  AnnotationKeyValue *p = new AnnotationKeyValue();
  p->key_ = sym_str(key);
  AddStrParam(p, str);
  return p;
}

AnnotationKeyValue *AnnotationBuilder::BuildIntParam(sym_t key, uint64_t num) {
  AnnotationKeyValue *p = new AnnotationKeyValue();
  p->key_ = sym_str(key);
  AddIntParam(p, num);
  return p;
}

AnnotationKeyValueSet *AnnotationBuilder::BuildParamSet(
    AnnotationKeyValueSet *params, AnnotationKeyValue *p) {
  if (params == nullptr) {
    params = new AnnotationKeyValueSet();
  }
  if (p != nullptr) {
    params->params_.push_back(p);
  }
  return params;
}

Annotation *AnnotationBuilder::Build(sym_t name,
                                     AnnotationKeyValueSet *values) {
  if (name == sym_null) {
    return nullptr;
  }
  if (values == nullptr) {
    values = new AnnotationKeyValueSet;
  }
  Annotation *a = new Annotation(values);
  a->AddStrParam(annotation::kAnnotationKey, sym_str(name));
  return a;
}
