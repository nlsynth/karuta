// -*- C++ -*-
#ifndef _synth_common_h_
#define _synth_common_h_

#include "nli.h"

class Annotation;

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
class IValueType;
class ResourceParams;
}  // namespace iroha

using namespace iroha;

namespace vm {
class Insn;
class Method;
class Object;
class Register;
class VM;
class Value;
}  // namespace vm

namespace synth {
class ChannelSynth;
class DesignSynth;
class InsnWalker;
class MethodContext;
class MethodSynth;
class ObjectSynth;
class ThreadSynth;
class ResourceSet;
class ResourceSynth;
class StateWrapper;
class SharedResource;
class SharedResourceSet;

struct SubObjCall {
  IInsn *call_insn;
  IState *call_state;
  vm::Object *callee_obj;
  string callee_func;
};

}  // namespace synth

#endif  // _synth_common_h_
