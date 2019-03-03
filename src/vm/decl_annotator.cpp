#include "vm/decl_annotator.h"

#include "fe/var_decl.h"
#include "vm/insn_annotator.h"
#include "vm/numeric_object.h"
#include "vm/register.h"
#include "vm/vm.h"

namespace vm {

void DeclAnnotator::AnnotateByDecl(VM *vm, fe::VarDecl *decl,
				   Register *reg) {
  reg->SetIsDeclaredType(true);
  if (decl->GetArrayShape() != nullptr) {
    CHECK(false);
  } else {
    reg->type_.value_type_ = InsnAnnotator::SymToType(decl->GetType());
    if (decl->GetType() == sym_bool) {
      reg->type_.enum_type_ = vm->bool_type_;
    }
  }
  reg->type_.width_ = decl->GetWidth();
  reg->type_.object_name_ = decl->GetObjectName();
  if (reg->type_.object_name_ != sym_null) {
    reg->type_object_ = NumericObject::Get(vm, reg->type_.object_name_);
    // type_object_ can be null for top level decl.
    if (reg->type_object_ != nullptr) {
      int w = NumericObject::Width(reg->type_object_);
      reg->type_.width_ = iroha::NumericWidth(false, w);
    }
  }
  CHECK(reg->type_.value_type_ != Value::NONE) << sym_cstr(decl->GetType());
}

void DeclAnnotator::AnnotateByValue(Value *value, Register *reg) {
  reg->type_.value_type_ = value->type_;
  if (value->type_ == Value::NUM) {
    reg->type_.width_ = value->num_.type_;
  }
  reg->type_.object_name_ = value->type_object_name_;
}

void DeclAnnotator::AnnotateValueType(VM *vm, fe::VarDecl *decl, Value *value) {
  value->type_ = InsnAnnotator::SymToType(decl->GetType());
  if (decl->GetArrayShape() != nullptr) {
    if (value->type_ == Value::OBJECT) {
      value->type_ = Value::OBJECT_ARRAY;
    } else {
      CHECK(value->type_ == Value::NUM);
      value->type_ = Value::INT_ARRAY;
    }
  }
  value->num_.type_ = decl->GetWidth();
  sym_t object_name = decl->GetObjectName();
  if (object_name != sym_null) {
    CHECK(!value->IsObjectType());
    value->type_object_name_ = object_name;
    value->object_ = NumericObject::Get(vm, value->type_object_name_);
  }
}

}  // namespace vm
