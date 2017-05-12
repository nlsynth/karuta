#include "base/annotation_builder.h"

#include "base/annotation.h"

void AnnotationBuilder::AddStrParam(AnnotationValue *p, const char *str) {
  p->values_.push_back(string(str));
}

AnnotationValue *AnnotationBuilder::BuildStrParam(sym_t key, const char *str) {
  AnnotationValue *p = new AnnotationValue();
  p->key_ = string(sym_cstr(key));
  AddStrParam(p, str);
  return p;
}

AnnotationValueSet *AnnotationBuilder::BuildParamSet(AnnotationValueSet *params,
						     AnnotationValue *p) {
  if (!params) {
    params = new AnnotationValueSet();
  }
  params->params_.push_back(p);
  return params;
}

Annotation *AnnotationBuilder::Build(sym_t name, AnnotationValueSet *values) {
  if (name == sym_null) {
    return nullptr;
  }
  if (values == nullptr) {
    values = new AnnotationValueSet;
  }
  Annotation *a = new Annotation(values);
  a->AddParam(annotation::kAnnotationKey, string(sym_cstr(name)));
  return a;
}
