#include "vm/insn_annotator.h"

#include "base/status.h"
#include "fe/expr.h"
#include "fe/fe_method.h"
#include "fe/stmt.h"
#include "fe/var_decl.h"
#include "vm/array_wrapper.h"
#include "vm/insn.h"
#include "vm/method.h"
#include "vm/numeric_object.h"
#include "vm/object.h"
#include "vm/opcode.h"
#include "vm/tls_wrapper.h"
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
  vector<Insn *> untyped_insns;
  for (auto *insn : method_->insns_) {
    if (!IsTyped(insn)) {
      untyped_insns.push_back(insn);
    }
  }
  int n;
  do {
    n = 0;
    vector<Insn *> tmp_insns;
    for (auto *insn : untyped_insns) {
      TryType(insn);
      if (Status::CheckAllErrors(false)) {
	return;
      }
      if (IsTyped(insn)) {
	++n;
      } else {
	tmp_insns.push_back(insn);
      }
    }
    untyped_insns = tmp_insns;
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
      // Sets the narrowest width so that CommonWidth() will not confuse.
      reg->type_.width_ = iroha::NumericWidth(false, 0);
    }
  }
}

void InsnAnnotator::TryType(Insn *insn) {
  if (insn->op_ == OP_LOAD_OBJ) {
    vm::Object *obj;
    if (insn->obj_reg_ == nullptr) {
      obj = obj_;
    } else {
      obj = objs_[insn->obj_reg_];
    }
    if (insn->label_ != sym_null) {
      Value *obj_value = obj->LookupValue(insn->label_, false);
      if (obj_value == nullptr) {
	if (method_->IsTopLevel()) {
	  return;
	}
      }
      CHECK(obj_value) << sym_cstr(insn->label_) << "\n";
      CHECK(obj_value->object_);
      obj = obj_value->object_;
    }
    objs_[insn->dst_regs_[0]] = obj;
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
  if (InsnType::IsNumCalculation(insn->op_)) {
    AnnotateNumCalculationOp(insn);
  }
  if (insn->op_ == OP_LSHIFT || insn->op_ == OP_RSHIFT) {
    if (insn->src_regs_[0]->type_.value_type_ == Value::NUM &&
	insn->src_regs_[1]->type_.value_type_ == Value::NUM) {
      insn->dst_regs_[0]->type_.value_type_ = Value::NUM;
      insn->dst_regs_[0]->type_.width_ =
	insn->src_regs_[0]->type_.width_;
      return;
    }
  }
  if (insn->op_ == OP_CONCAT) {
    AnnotateConcatInsn(insn);
  }
  if (insn->op_ == OP_BIT_RANGE) {
    AnnotateBitRangeInsn(insn);
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
    TypeReturnValues(insn);
    return;
  }
  if (insn->op_ == OP_ARRAY_READ) {
    TypeArrayRead(insn);
    return;
  }
  if (insn->op_ == OP_MEMBER_READ ||
      insn->op_ == OP_MEMBER_WRITE) {
    TypeMemberAccess(insn);
    return;
  }
}

void InsnAnnotator::TypeMemberAccess(Insn *insn) {
  Object *obj;
  if (insn->op_ == OP_MEMBER_READ) {
    obj = objs_[insn->src_regs_[0]];
  } else {
    obj = objs_[insn->src_regs_[1]];
  }
  if (obj == nullptr) {
    if (!method_->IsTopLevel()) {
      Status::os(Status::USER_ERROR) << "Failed to find object: "
				     << sym_cstr(insn->label_);
      MessageFlush::Get(Status::USER_ERROR);
      method_->SetCompileFailure();
    }
    return;
  }
  Value *value = obj->LookupValue(insn->label_, false);
  if (value != nullptr) {
    if (TlsWrapper::IsTlsValue(value)) {
      value = TlsWrapper::GetValue(value->object_, nullptr);
    }
    insn->dst_regs_[0]->type_.value_type_ = value->type_;
    if (value->IsObjectType()) {
      CHECK(value->object_ != nullptr);
      objs_[insn->dst_regs_[0]] = value->object_;
    }
    if (value->type_ == Value::NUM) {
      insn->dst_regs_[0]->type_.width_ = value->num_type_;
    }
  } else {
    if (!method_->IsTopLevel()) {
      Status::os(Status::USER_ERROR) << "Failed to find object: "
				     << sym_cstr(insn->label_);
      MessageFlush::Get(Status::USER_ERROR);
      method_->SetCompileFailure();
    }
    // else, the type should be determined in the compiler.
  }
}

void InsnAnnotator::AnnotateBitRangeInsn(Insn *insn) {
  if (insn->src_regs_[0]->type_.value_type_ == Value::NUM) {
    insn->dst_regs_[0]->type_.value_type_ = Value::NUM;
    int w = insn->src_regs_[1]->initial_num_.GetValue0() -
      insn->src_regs_[2]->initial_num_.GetValue0() + 1;
    insn->dst_regs_[0]->type_.width_ = iroha::NumericWidth(false, w);
  }
}

void InsnAnnotator::AnnotateConcatInsn(Insn *insn) {
  if (insn->src_regs_[0]->type_.value_type_ == Value::NUM &&
      insn->src_regs_[1]->type_.value_type_ == Value::NUM) {
    insn->dst_regs_[0]->type_.value_type_ = Value::NUM;
    int w = insn->src_regs_[0]->type_.width_.GetWidth() +
      insn->src_regs_[1]->type_.width_.GetWidth();
    insn->dst_regs_[0]->type_.width_ = iroha::NumericWidth(false, w);
  }
}

void InsnAnnotator::AnnotateNumCalculationOp(Insn *insn) {
  if (insn->src_regs_[0]->type_.value_type_ == Value::NUM &&
      insn->src_regs_[1]->type_.value_type_ == Value::NUM) {
    if (!insn->dst_regs_[0]->GetIsDeclaredType()) {
      insn->dst_regs_[0]->type_.value_type_ = Value::NUM;
      PropagateRegWidth(insn->src_regs_[0], insn->src_regs_[1],
			insn->dst_regs_[0]);
    }
  }
}

void InsnAnnotator::TypeArrayRead(Insn *insn) {
  Object *array_obj = objs_[insn->obj_reg_];
  if (array_obj == nullptr) {
    CHECK(method_->IsTopLevel());
    return;
  }
  if (TlsWrapper::IsTls(array_obj)) {
    Value *value = TlsWrapper::GetValue(array_obj, nullptr);
    array_obj = value->object_;
  }
  if (ArrayWrapper::IsIntArray(array_obj)) {
    insn->dst_regs_[0]->type_.value_type_ = Value::NUM;
    insn->dst_regs_[0]->type_.width_ =
      iroha::NumericWidth(false, ArrayWrapper::GetDataWidth(array_obj));
  } else {
    CHECK(ArrayWrapper::IsObjectArray(array_obj));
    insn->dst_regs_[0]->type_.value_type_ = Value::OBJECT;
    CHECK(insn->src_regs_.size() == 1);
    Register *idx_reg = insn->src_regs_[0];
    CHECK(idx_reg->type_.is_const_);
    int idx = idx_reg->initial_num_.GetValue0();
    Object *elm_obj = ArrayWrapper::Get(array_obj, idx);
    objs_[insn->dst_regs_[0]] = elm_obj;
  }
}

void InsnAnnotator::TypeReturnValues(Insn *insn) {
  Object *obj = obj_;
  if (insn->obj_reg_ != nullptr) {
    obj = objs_[insn->obj_reg_];
    if (obj == nullptr) {
      if (!method_->IsTopLevel()) {
	Status::os(Status::USER_ERROR)
	  << "Can't get object to determine the return types: "
	  << sym_cstr(insn->label_);
      }
      return;
    }
  }
  Value *value = obj->LookupValue(insn->label_, false);
  if (value != nullptr && value->type_ == Value::METHOD) {
    Method *method = value->method_;
    auto *parse_tree = method->GetParseTree();
    if (parse_tree == nullptr) {
      // native
      CHECK(method->return_types_.size() <= insn->dst_regs_.size());
      for (int i = 0; i < method->return_types_.size(); ++i) {
	auto &ret = method->return_types_[i];
	if (ret.value_type_ == Value::OBJECT) {
	  insn->dst_regs_[i]->type_.value_type_ = Value::OBJECT;
	} else {
	  CHECK(ret.value_type_ == Value::NUM);
	  insn->dst_regs_[i]->type_.value_type_ = Value::NUM;
	  insn->dst_regs_[i]->type_.width_ = ret.width_;
	}
      }
    } else {
      // non native
      CHECK(parse_tree->GetReturns()->decls.size() <= insn->dst_regs_.size());
      for (int i = 0; i < parse_tree->GetReturns()->decls.size(); ++i) {
	auto *decl = parse_tree->GetReturns()->decls[i];
	// TODO: type object.
	sym_t type = decl->GetType();
	if (type == sym_object || type == sym_module) {
	  insn->dst_regs_[i]->type_.value_type_ = Value::OBJECT;
	} else if (type == sym_bool) {
	  insn->dst_regs_[i]->type_.value_type_ = Value::ENUM_ITEM;
	  insn->dst_regs_[i]->type_.enum_type_ = vm_->bool_type_;
	} else {
	  insn->dst_regs_[i]->type_.value_type_ = Value::NUM;
	  insn->dst_regs_[i]->type_.width_ = decl->GetWidth();
	}
      }
    }
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

Value::ValueType InsnAnnotator::SymToType(sym_t sym) {
  if (sym == sym_int || sym == sym_null) {
    // Assumes width is specified instead for sym_null.
    return Value::NUM;
  } else if (sym == sym_object || sym == sym_module) {
    return Value::OBJECT;
  } else if (sym == sym_bool) {
    return Value::ENUM_ITEM;
  } else if (sym == sym_string) {
    return Value::OBJECT;
  }
  return Value::NONE;
}

void InsnAnnotator::SetDstRegType(Value::ValueType vtype, Insn *insn, int idx) {
  insn->dst_regs_[idx]->type_.value_type_ = vtype;
  CHECK(insn->dst_regs_[idx] ==
	method_->method_regs_[insn->dst_regs_[idx]->id_]);
}

}  // namespace vm
