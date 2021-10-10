// -*- C++ -*-
#ifndef _vm_executor_decl_h_
#define _vm_executor_decl_h_

#include "vm/executor/base.h"

namespace vm {
namespace executor {

class Decl : public Base {
 public:
  Decl(Thread *thread, MethodFrame *frame) : Base(thread, frame) {}

 protected:
  void ExecVardecl();
  void ExecChannelDecl();
  void ExecMailboxDecl();
  void ExecFuncdecl();
  void PushCurrentObject();
  void PopCurrentObject();

  void AddThreadEntry(const string &name, int num, bool is_soft);
  void ClearThreadEntry();
  void ExecImport();

  Object *CreateMemoryObject(const iroha::NumericWidth &width,
                             fe::ArrayShape *shape,
                             fe::ArrayInitializer *array_initializer,
                             Annotation *an);
  Object *CreateObjectArray(fe::ArrayShape *shape);
  Object *CreateIOObject(fe::VarDecl *decl, sym_t member_name, bool is_output,
                         const iroha::NumericWidth &width);
  void InitializeArray(IntArray *array,
                       fe::ArrayInitializer *array_initializer);
};

}  // namespace executor
}  // namespace vm

#endif  // _vm_executor_decl_h_
