// -*- C++ -*-
#ifndef _base_annotation_builder_h_
#define _base_annotation_builder_h_

#include "nli.h"

class AnnotationKeyValue;
class AnnotationKeyValueSet;
class Annotation;

class AnnotationBuilder {
public:
  static void Init();

  // Called mainly from parser
  static Annotation *Build(sym_t key, AnnotationKeyValueSet *values);
  static AnnotationKeyValue *BuildStrParam(sym_t key, const char *str);
  static void AddStrParam(AnnotationKeyValue *p, const char *str);
  static AnnotationKeyValueSet *BuildParamSet(AnnotationKeyValueSet *lst,
					      AnnotationKeyValue *p);
};

#endif  // _base_annotation_builder_h_
