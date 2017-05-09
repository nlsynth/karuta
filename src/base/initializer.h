// -*- C++ -*-
#ifndef _base_initializer_h_
#define _base_initializer_h_

class SIEntry {
public:
  SIEntry(const char *name, void (*initializer)(), void (*finalizer)());
};

#define STATIC_INITIALIZER(name, code)	\
  static void si_##name() {code;} \
  static SIEntry si_##name_inst(#name, si_##name, NULL);

#define STATIC_FINALIZER(name, code)	\
  static void sf_##name() {code;} \
  static SIEntry sf_##name_inst(#name, NULL, sf_##name);

#define STATIC_MODULE(name, ini, fini) \
  static void smi_##name() {(void)ini;} \
  static void smf_##name() {(void)fini;} \
  static SIEntry smi_##name_inst(#name, smi_##name, smf_##name);

class StaticInitializer {
public:
  static void RunInitializers();
  static void RunFinalizers();
};

#endif  // _base_initializer_h_
