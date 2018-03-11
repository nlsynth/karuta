// -*- C++ -*-
#ifndef _synth_common_h_
#define _synth_common_h_

#include "karuta.h"

class Annotation;

namespace fe {
class VarDecl;
class VarDeclSet;
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
class DesignSynth;
class InsnWalker;
class MethodContext;
class MethodSynth;
class ObjectSynth;
class ObjectTree;
class ThreadSynth;
class ResourceSet;
class ResourceSynth;
class StateWrapper;
class SharedResource;
class SharedResourceSet;

// Sub obj call, data flow call or ext stub call.
// MethodExpander populates this.
struct TableCall {
  TableCall() : is_sub_obj_call(false),	is_data_flow_call(false),
		is_ext_stub_call(false), is_ext_flow_stub_call(false) {}
  IInsn *call_insn;
  IState *call_state;
  ThreadSynth *caller_thread;
  vm::Object *callee_obj;
  string callee_func;
  vm::Method *callee_method;
  // type
  bool is_sub_obj_call;
  bool is_data_flow_call;
  bool is_ext_stub_call;
  bool is_ext_flow_stub_call;
};

}  // namespace synth

#endif  // _synth_common_h_
