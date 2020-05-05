#include "vm/numeric_object.h"

#include "base/status.h"
#include "fe/fe_method.h"
#include "fe/var_decl.h"
#include "vm/method.h"
#include "vm/object.h"
#include "vm/value.h"
#include "vm/vm.h"

namespace vm {

Object *NumericObject::Get(VM *vm, sym_t name) {
  if (name == sym_null) {
    return nullptr;
  }
  Value *n = vm->numerics_object_->LookupValue(name, false);
  if (n == nullptr) {
    return nullptr;
  }
  CHECK(n->type_ == Value::OBJECT);
  return n->object_;
}

bool NumericObject::IsNumericObject(VM *vm, Object *obj) {
  vector<sym_t> slots;
  vm->numerics_object_->LookupMemberNames(obj, &slots);
  return (slots.size() > 0);
}

int NumericObject::Width(Object *obj) {
  sym_t build = sym_lookup("Build");
  Value *v = obj->LookupValue(build, false);
  if (v == nullptr || v->type_ != Value::METHOD) {
    Status::os(Status::USER_ERROR) << "Failed to find Build() method";
    return 0;
  }
  CHECK(v != nullptr && v->type_ == Value::METHOD);
  // Acquires from the parse tree, since the method might not be compiled yet.
  const fe::Method *m = v->method_->GetParseTree();
  CHECK(m && m->GetReturns()->decls.size() == 1);
  fe::VarDecl *vd = m->GetReturns()->decls[0];
  return vd->GetWidth().GetWidth();
}

sym_t NumericObject::GetMethodName(Object *obj, enum OpCode op) {
  sym_t n = sym_null;
  if (op == OP_ADD || op == OP_ADD_MAY_WITH_TYPE) {
    n = sym_lookup("Add");
  } else if (op == OP_SUB || op == OP_SUB_MAY_WITH_TYPE) {
    n = sym_lookup("Sub");
  } else if (op == OP_MUL || op == OP_MUL_MAY_WITH_TYPE) {
    n = sym_lookup("Mul");
  } else if (op == OP_DIV || op == OP_DIV_MAY_WITH_TYPE) {
    n = sym_lookup("Div");
  }
  if (n == sym_null) {
    return sym_null;
  }
  auto *v = obj->LookupValue(n, false);
  if (v == nullptr || v->type_ != Value::METHOD) {
    return sym_null;
  }
  return n;
}

}  // namespace vm
