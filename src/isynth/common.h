// -*- C++ -*-
#ifndef _isynth_common_h_
#define _isynth_common_h_

#include "nli.h"

namespace fe {
class VarDecl;
}  // namespace fe

namespace iroha {
class IDesign;
class IInsn;
class IModule;
class IRegister;
class IResource;
class IState;
class ITable;
class ResourceParams;
}  // namespace iroha

using namespace iroha;

namespace vm {
class Insn;
class Method;
class Object;
class Register;
class VM;
}  // namespace vm

namespace dfg {
class ResourceParams;
}  // namespace dfg

namespace isynth {
class MethodContext;
class MethodSynth;
class ObjectSynth;
class ThreadSynth;
class ResourceSet;
class StateWrapper;
}  // namespace isynth

#endif  // _isynth_common_h_
