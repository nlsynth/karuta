// -*- C++ -*-
#ifndef _base_annotation_builder_h_
#define _base_annotation_builder_h_

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

#endif  // _base_annotation_builder_h_
