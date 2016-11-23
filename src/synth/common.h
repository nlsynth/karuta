// -*- C++ -*-
#ifndef _synth_common_h_
#define _synth_common_h_

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
}  // namespace vm

namespace synth {
class ResourceParams;
}  // namespace synth

namespace synth {
class ChannelSynth;
class MethodContext;
class MethodSynth;
class ObjectSynth;
class ThreadSynth;
class ResourceSet;
class StateWrapper;

struct SubObjCall {
  IInsn *call_insn;
  IState *call_state;
  vm::Object *callee_obj;
  string callee_func;
  string callee_obj_name;
};

}  // namespace synth

#endif  // _synth_common_h_
