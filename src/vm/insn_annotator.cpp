#include "vm/insn_annotator.h"

#include "fe/expr.h"
#include "fe/method.h"
#include "fe/stmt.h"
#include "fe/var_decl.h"
#include "vm/insn.h"
#include "vm/method.h"
#include "vm/numeric_object.h"
#include "vm/object.h"
#include "vm/opcode.h"
#include "vm/value.h"
#include "vm/vm.h"

using std::set;

namespace vm {

InsnAnnotator::InsnAnnotator(VM *vm, Object *obj, Method *method)
  : vm_(vm), obj_(obj), method_(method) {
}

void InsnAnnotator::AnnotateMethod(VM *vm, Object *obj, Method *method) {
  InsnAnnotator annotator(vm, obj, method);
  annotator.DoAnnotate();
}

void InsnAnnotator::DoAnnotate() {
  if (!method_->IsTopLevel()) {
    ClearType();
  }
  vector<Insn *> insns;
  for (auto *insn : method_->insns_) {
    if (!IsTyped(insn)) {
      insns.push_back(insn);
    }
  }
  int n;
  do {
    n = 0;
    vector<Insn *> tmp_insns;
    for (auto *insn : insns) {
      TryType(insn);
      if (IsTyped(insn)) {
	++n;
      } else {
	tmp_insns.push_back(insn);
      }
    }
    insns = tmp_insns;
  } while (n > 0);
  PropagateType();
}

void InsnAnnotator::PropagateType() {
  // propagate dst to source.
  set<Register *> source_regs;
  for (auto *insn : method_->insns_) {
    for (auto *reg : insn->dst_regs_) {
      if (reg->GetIsDeclaredType()) {
	source_regs.insert(reg);
      }
    }
  }
  set<Register *> processed_regs;
  do {
    set<Register *> propagated;
    set<Register *> tmp_processed;
    for (auto *insn : method_->insns_) {
      bool b = false;
      for (auto *reg : insn->dst_regs_) {
	if (source_regs.find(reg) != source_regs.end() &&
	    processed_regs.find(reg) == processed_regs.end()) {
	  tmp_processed.insert(reg);
	  b = true;
	}
      }
      if (b) {
	TryPropagate(insn, &propagated);
      }
    }
    for (auto *reg : tmp_processed) {
      processed_regs.insert(reg);
    }
    source_regs = propagated;
  } while (source_regs.size() > 0);
}

void InsnAnnotator::TryPropagate(Insn *insn, set<Register *> *propagated) {
  if (insn->op_ == OP_ASSIGN) {
    if (insn->dst_regs_[0]->GetIsDeclaredType() &&
	insn->dst_regs_[0]->type_.value_type_ == Value::NUM &&
	!insn->src_regs_[1]->GetIsDeclaredType()) {
      propagated->insert(insn->src_regs_[1]);
      insn->src_regs_[1]->type_.width_ =
	insn->dst_regs_[0]->type_.width_;
    }
  }
  if (insn->op_ == OP_BIT_INV) {
    if (!insn->src_regs_[0]->GetIsDeclaredType()) {
      propagated->insert(insn->src_regs_[0]);
      insn->src_regs_[0]->type_.width_ =
	insn->dst_regs_[0]->type_.width_;
    }
  }
}

void InsnAnnotator::ClearType() {
  for (auto *reg : method_->method_regs_) {
    if (!reg->GetIsDeclaredType()) {
      reg->type_.value_type_ = Value::NONE;
      reg->type_.width_ = iroha::NumericWidth(false, 32);
    }
  }
}

void InsnAnnotator::TryType(Insn *insn) {
  if (insn->op_ == OP_LOAD_OBJ) {
    if (insn->obj_reg_ == nullptr) {
      objs_[insn->dst_regs_[0]] = obj_;
    } else {
      Value *obj_value = obj_->LookupValue(insn->label_, false);
      CHECK(obj_value);
      CHECK(obj_value->object_);
      objs_[insn->dst_regs_[0]] = obj_value->object_;
    }
    insn->dst_regs_[0]->type_.value_type_ = Value::OBJECT;
    return;
  }
  if (insn->op_ == OP_STR || insn->op_ == OP_NUM) {
    // This may not happen because compiler should have assigned the type.
    return;
  }
  if (insn->op_ == OP_ASSIGN) {
    if (insn->src_regs_[0]->type_.value_type_ != Value::NONE) {
      if (insn->dst_regs_[0]->GetIsDeclaredType()) {
	CHECK(insn->dst_regs_[0]->type_.value_type_ ==
	      insn->src_regs_[0]->type_.value_type_);
      } else {
	insn->dst_regs_[0]->type_ = insn->src_regs_[0]->type_;
      }
      return;
    }
  }
  if (InsnType::IsNumCalculation(insn->op_) ||
      insn->op_ == OP_LSHIFT || insn->op_ == OP_RSHIFT) {
    if (insn->src_regs_[0]->type_.value_type_ == Value::NUM &&
	insn->src_regs_[1]->type_.value_type_ == Value::NUM) {
      if (!insn->dst_regs_[0]->GetIsDeclaredType()) {
	insn->dst_regs_[0]->type_.value_type_ = Value::NUM;
	PropagateRegWidth(insn->src_regs_[0], insn->src_regs_[1],
			  insn->dst_regs_[0]);
      }
      return;
    }
  }
  if (insn->op_ == OP_CONCAT) {
    if (insn->src_regs_[0]->type_.value_type_ == Value::NUM &&
	insn->src_regs_[1]->type_.value_type_ == Value::NUM) {
      insn->dst_regs_[0]->type_.value_type_ = Value::NUM;
      int w = insn->src_regs_[0]->type_.width_.GetWidth() +
	insn->src_regs_[1]->type_.width_.GetWidth();
      insn->dst_regs_[0]->type_.width_ = iroha::NumericWidth(false, w);
      return;
    }
  }
  if (insn->op_ == OP_BIT_RANGE) {
    if (insn->src_regs_[0]->type_.value_type_ == Value::NUM) {
      insn->dst_regs_[0]->type_.value_type_ = Value::NUM;
      int w = insn->src_regs_[1]->initial_num_.GetValue() -
	insn->src_regs_[2]->initial_num_.GetValue() + 1;
      insn->dst_regs_[0]->type_.width_ = iroha::NumericWidth(false, w);
      return;
    }
  }
  if (insn->op_ == OP_LOGIC_INV ||
      insn->op_ == OP_LAND || insn->op_ == OP_LOR ||
      InsnType::IsComparison(insn->op_)) {
    insn->dst_regs_[0]->type_.value_type_ = Value::ENUM_ITEM;
    insn->dst_regs_[0]->type_.enum_type_ =
      vm_->bool_type_;
    return;
  }
  if (insn->op_ == OP_BIT_INV) {
    if (insn->src_regs_[0]->type_.value_type_ != Value::NONE) {
      insn->dst_regs_[0]->type_.value_type_ =
	insn->src_regs_[0]->type_.value_type_;
      insn->dst_regs_[0]->type_.enum_type_ =
	insn->src_regs_[0]->type_.enum_type_;
      return;
    }
  }
  if (insn->op_ == OP_FUNCALL) {
    return;
  }
  if (insn->op_ == OP_FUNCALL_DONE) {
    // TODO: Look up return type(s).
    insn->dst_regs_[0]->type_.value_type_ = Value::NUM;
    insn->dst_regs_[0]->type_.width_ = iroha::NumericWidth(false, 32);
    return;
  }
  if (insn->op_ == OP_GENERIC_READ || insn->op_ == OP_CHANNEL_READ ||
      insn->op_ == OP_MEMORY_READ) {
    insn->dst_regs_[0]->type_.value_type_ = Value::NUM;
    return;
  }
  if (insn->op_ == OP_ARRAY_READ) {
    insn->dst_regs_[0]->type_.value_type_ = Value::NUM;
    return;
  }
  if (insn->op_ == OP_MEMBER_READ ||
      insn->op_ == OP_MEMBER_WRITE) {
    Value *value = obj_->LookupValue(insn->label_, false);
    if (value) {
      insn->dst_regs_[0]->type_.value_type_ = value->type_;
    }
    // else, the type should be determined in the compiler.
  }
}

bool InsnAnnotator::IsTyped(Insn *insn) {
  for (Register *reg : insn->dst_regs_) {
    if (!IsTypedReg(reg)) {
      return false;
    }
  }
  for (Register *reg : insn->src_regs_) {
    if (!IsTypedReg(reg)) {
      return false;
    }
  }
  return true;
}

bool InsnAnnotator::IsTypedReg(Register *reg) {
  return (reg->type_.value_type_ != Value::NONE);
}

void InsnAnnotator::PropagateRegWidth(Register *src1, Register *src2,
				      Register *dst) {
  if (dst->orig_name_) {
    return;
  }
  iroha::NumericWidth width =
    iroha::NumericWidth::CommonWidth(src1->type_.width_, src2->type_.width_);
  dst->type_.width_ = iroha::NumericWidth::CommonWidth(dst->type_.width_, width);
}

void InsnAnnotator::AnnotateByDecl(VM *vm, fe::VarDecl *decl,
				   Register *reg) {
  reg->SetIsDeclaredType(true);
  if (decl->GetArrayLength() >= 0) {
    CHECK(decl->GetType() == sym_int);
    reg->type_.value_type_ = Value::INT_ARRAY;
    reg->SetArrayLength(decl->GetArrayLength());
    if (reg->GetArrayLength() == 0 &&
	decl->GetArrayInitializer() != nullptr) {
      reg->SetArrayLength(decl->GetArrayInitializer()->num_.size());
    }
    reg->SetArrayInitializer(decl->GetArrayInitializer());
  } else {
    reg->type_.value_type_ = SymToType(decl->GetType());
    if (decl->GetType() == sym_bool) {
      reg->type_.enum_type_ = vm->bool_type_;
    }
  }
  reg->type_.width_ = decl->GetWidth();
  reg->type_.object_name_ = decl->GetObjectName();
  if (reg->type_.object_name_ != sym_null) {
    reg->type_object_ = vm::NumericObject::Get(vm, reg->type_.object_name_);
  }
  CHECK(reg->type_.value_type_ != Value::NONE) << sym_cstr(decl->GetType());
}

Value::ValueType InsnAnnotator::SymToType(sym_t sym) {
  if (sym == sym_int) {
    return Value::NUM;
  } else if (sym == sym_object) {
    return Value::OBJECT;
  } else if (sym == sym_bool) {
    return Value::ENUM_ITEM;
  } else if (sym == sym_string) {
    return Value::OBJECT;
  }
  return Value::NONE;
}

void InsnAnnotator::AnnotateValueType(VM *vm, fe::VarDecl *decl, Value *value) {
  value->type_ = SymToType(decl->GetType());
  if (decl->GetArrayLength() > -1) {
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

void InsnAnnotator::AnnotateByValue(Value *value, Register *reg) {
  reg->type_.value_type_ = value->type_;
  if (value->type_ == Value::NUM) {
    reg->type_.width_ = value->num_.type_;
  }
  reg->type_.object_name_ = value->type_object_name_;
}

void InsnAnnotator::SetDstRegType(Value::ValueType vtype, Insn *insn, int idx) {
  insn->dst_regs_[idx]->type_.value_type_ = vtype;
  CHECK(insn->dst_regs_[idx] ==
	method_->method_regs_[insn->dst_regs_[idx]->id_]);
}

}  // namespace vm
