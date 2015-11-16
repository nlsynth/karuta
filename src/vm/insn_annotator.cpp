#include "vm/insn_annotator.h"

#include "vm/insn.h"
#include "fe/expr.h"
#include "fe/method.h"
#include "fe/stmt.h"
#include "fe/var_decl.h"
#include "vm/method.h"
#include "vm/object.h"
#include "vm/opcode.h"
#include "vm/value.h"
#include "vm/vm.h"

namespace vm {

void InsnAnnotator::Annotate(VM *vm, Object *obj, Method *method) {
  AnnotateType(vm, obj, method);
  AnnotateWidth(vm, obj, method);
}

void InsnAnnotator::AnnotateType(VM *vm, Object *obj, Method *method) {
  for (size_t i = 0; i < method->insns_.size(); ++i) {
    Insn *insn = method->insns_[i];
    if (insn->op_ == OP_NUM || insn->op_ == OP_ARRAY_READ) {
      method->method_regs_[insn->dst_regs_[0]->id_]->type_.value_type_ =
	Value::NUM;
    }
    if (insn->op_ == OP_STR || insn->op_ == OP_LOAD_OBJ) {
      method->method_regs_[insn->dst_regs_[0]->id_]->type_.value_type_ =
	Value::OBJECT;
    }
    if (insn->op_ == OP_GENERIC_READ || insn->op_ == OP_CHANNEL_READ ||
	insn->op_ == OP_MEMORY_READ) {
      method->method_regs_[insn->dst_regs_[0]->id_]->type_.value_type_ =
	Value::NUM;
    }
    if (insn->op_ == OP_GENERIC_WRITE || insn->op_ == OP_MEMORY_WRITE ||
	insn->op_ == OP_CHANNEL_WRITE) {
      // memory, array_ref
      if (insn->src_regs_.size() == 2) {
	insn->src_regs_[0]->type_.value_type_ = Value::NUM;
	insn->src_regs_[1]->type_.value_type_ = Value::NUM;
	method->method_regs_[insn->dst_regs_[0]->id_]->type_.value_type_ =
	  Value::NUM;
      } else {
	// elm_ref
      }
    }
    if (insn->op_ == OP_ASSIGN) {
      CHECK(insn->src_regs_.size() == 2);
      enum Value::ValueType value_type =
	insn->src_regs_[1]->type_.value_type_;
      if (value_type == Value::NONE) {
	continue;
      }
      if (method->method_regs_[insn->dst_regs_[0]->id_]->orig_name_) {
	continue;
      }
      method->method_regs_[insn->dst_regs_[0]->id_]->type_.value_type_ =
	value_type;
      insn->src_regs_[0]->type_.value_type_ = value_type;
    }
    if (insn->op_ == OP_ADD || insn->op_ == OP_SUB ||
	insn->op_ == OP_MUL ||
	insn->op_ == OP_LSHIFT || insn->op_ == OP_RSHIFT ||
	insn->op_ == OP_AND || insn->op_ == OP_OR ||
	insn->op_ == OP_XOR || insn->op_ == OP_CONCAT ||
	insn->op_ == OP_BIT_RANGE) {
      method->method_regs_[insn->dst_regs_[0]->id_]->type_.value_type_ =
	insn->src_regs_[1]->type_.value_type_;
      CHECK(insn->src_regs_[0]->type_.value_type_ ==
	    insn->src_regs_[1]->type_.value_type_);
    }
    if (insn->op_ == OP_LOGIC_INV ||
	insn->op_ == OP_LAND || insn->op_ == OP_LOR ||
	insn->op_ == OP_GT || insn->op_ == OP_LT ||
	insn->op_ == OP_GTE || insn->op_ == OP_LTE ||
	insn->op_ == OP_EQ || insn->op_ == OP_NE) {
      method->method_regs_[insn->dst_regs_[0]->id_]->type_.value_type_ =
	Value::ENUM_ITEM;
      method->method_regs_[insn->dst_regs_[0]->id_]->type_.enum_type_ =
	vm->bool_type_.get();
    }
    if (insn->op_ == OP_MEMBER_READ ||
	insn->op_ == OP_MEMBER_WRITE) {
      Value *value = obj->LookupValue(insn->label_, false);
      if (value) {
	method->method_regs_[insn->dst_regs_[0]->id_]->type_.value_type_ =
	  value->type_;
      }
      // else, the type should be determined in the compiler.
    }
  }
}

void InsnAnnotator::AnnotateWidth(VM *vm, Object *obj,
				  Method *method) {
  AnnotateCalcWidth(vm, obj, method);
  PropagateVarWidthAll(vm, obj, method);
  // Enforces width of argument and return values after possible
  // over writes.
  EnforceValueWidth(vm, obj, method);
}


void InsnAnnotator::AnnotateCalcWidth(VM *vm, Object *obj, Method *method) {
  // Literal numbers.
  for (size_t i = 0; i < method->method_regs_.size(); ++i) {
    Register *reg = method->method_regs_[i];
    if (reg->type_.value_type_ == Value::NUM && reg->type_.is_const_) {
      reg->type_.width_ =
	numeric::Width::CommonWidth(numeric::Numeric::ValueWidth(reg->initial_num_),
				    reg->type_.width_);
    }
  }
  for (size_t i = 0; i < method->insns_.size(); ++i) {
    Insn *insn = method->insns_[i];
    // member access.
    if (insn->op_ == OP_MEMBER_READ ||
	insn->op_ == OP_MEMBER_WRITE) {
      Value *value = obj->LookupValue(insn->label_, false);
      if (!value) {
	// determined in the compiler.
	continue;
      }
      insn->dst_regs_[0]->type_.value_type_ = value->type_;
      if (value->type_ == Value::NUM) {
	if (insn->op_ == OP_MEMBER_WRITE) {
	  insn->dst_regs_[0]->type_.width_ =
	    numeric::Width::CommonWidth(insn->src_regs_[0]->type_.width_,
					numeric::Width::DefaultInt());
	} else {
	  insn->dst_regs_[0]->type_.width_ = value->num_.type;
	}
      }
    }
    // propagates by assign.
    if (insn->op_ == OP_ASSIGN) {
      // src -> dst, rhs
      PropagateRegWidth(insn->src_regs_[0],
			insn->src_regs_[1],
			insn->dst_regs_[0]);
      PropagateRegWidth(insn->src_regs_[0],
			insn->src_regs_[1],
			insn->src_regs_[1]);
    }
    // propagate const -> dst
    if ((insn->op_ == OP_ADD || insn->op_ == OP_SUB ||
	 insn->op_ == OP_AND || insn->op_ == OP_OR ||
	 insn->op_ == OP_XOR ||
	 insn->op_ == OP_LSHIFT || insn->op_ == OP_RSHIFT ||
	 insn->op_ == OP_MUL) &&
	insn->src_regs_[0]->type_.value_type_ == Value::NUM) {
      PropagateRegWidth(insn->src_regs_[0], insn->src_regs_[1],
			insn->dst_regs_[0]);
    }
    if (insn->op_ == OP_BIT_RANGE) {
      CHECK(insn->src_regs_[1]->type_.value_type_ == Value::NUM);
      CHECK(insn->src_regs_[2]->type_.value_type_ == Value::NUM);
      int w = numeric::Numeric::GetInt(insn->src_regs_[1]->initial_num_) -
	numeric::Numeric::GetInt(insn->src_regs_[2]->initial_num_) + 1;
      insn->dst_regs_[0]->type_.width_ = numeric::Width::MakeInt(false, w, 0);
    }
    if (insn->op_ == OP_CONCAT) {
      CHECK(insn->src_regs_[0]->type_.value_type_ == Value::NUM);
      CHECK(insn->src_regs_[1]->type_.value_type_ == Value::NUM);
      int w = numeric::Width::GetWidth(insn->src_regs_[0]->type_.width_) +
	numeric::Width::GetWidth(insn->src_regs_[1]->type_.width_);
      insn->dst_regs_[0]->type_.width_ = numeric::Width::MakeInt(false, w, 0);
    }
  }
}

void InsnAnnotator::PropagateVarWidthAll(VM *vm, Object *obj, Method *method) {
  for (size_t i = 0; i < method->insns_.size(); ++i) {
    Insn *insn = method->insns_[i];
    PropagateDeclaredWidth(insn);
  }
}

void InsnAnnotator::EnforceValueWidth(VM *vm, Object *obj,
				      Method *method) {
  int num_args = 0;
  fe::VarDeclSet *args = method->parse_tree_->args_;
  if (args) {
    num_args = args->decls.size();
    for (size_t i = 0; i < num_args; ++i) {
      AnnotateByDecl(vm, args->decls[i], method->method_regs_[i]);
    }
  }
  fe::VarDeclSet *rets = method->parse_tree_->returns_;
  if (rets) {
    for (size_t i = 0; i < rets->decls.size(); ++i) {
      AnnotateByDecl(vm, rets->decls[i], method->method_regs_[num_args + i]);
    }
  }
}

void InsnAnnotator::PropagateDeclaredWidth(Insn *insn) {
  if (insn->dst_regs_.size() != 1) {
    // not support fow now.
    return;
  }
  Register *dst = insn->dst_regs_[0];
  if (InsnType::IsNumCalculation(insn->op_)) {
    for (size_t i = 0; i < insn->src_regs_.size(); ++i) {
      Register *src = insn->src_regs_[i];
      if (src->orig_name_) {
	continue;
      }
      PropagateRegWidth(src, dst, src);
    }
  }
  if (InsnType::IsNumCalculation(insn->op_) ||
      InsnType::IsComparison(insn->op_)) {
    for (size_t i = 0; i < insn->src_regs_.size(); ++i) {
      for (size_t j = 0; j < insn->src_regs_.size(); ++j) {
	if (i == j) {
	  continue;
	}
	Register *s1 = insn->src_regs_[i];
	Register *s2 = insn->src_regs_[j];
	if (s2->orig_name_) {
	  continue;
	}
	PropagateRegWidth(s1, s2, s2);
      }
    }
  }
}

void InsnAnnotator::PropagateRegWidth(Register *src1, Register *src2,
				      Register *dst) {
  if (dst->orig_name_) {
    return;
  }
  const numeric::Width *width =
    numeric::Width::CommonWidth(src1->type_.width_, src2->type_.width_);
  dst->type_.width_ = numeric::Width::CommonWidth(dst->type_.width_, width);
}

void InsnAnnotator::AnnotateByDecl(VM *vm, fe::VarDecl *decl,
				   Register *reg) {
  if (decl->array_length >= 0) {
    reg->type_.value_type_ = Value::INT_ARRAY;
    reg->array_length_ = decl->array_length;
    if (reg->array_length_ == 0 && decl->array_initializer) {
      reg->array_length_ = decl->array_initializer->num_.size();
    }
    reg->array_initializer_ = decl->array_initializer;
  } else {
    reg->type_.value_type_ = SymToType(decl->type);
    if (decl->type == sym_bool) {
      reg->type_.enum_type_ = vm->bool_type_.get();
    }
  }
  if (decl->width) {
    reg->type_.width_ = decl->width;
  } else {
    reg->type_.width_ = numeric::Width::DefaultInt();
  }
  CHECK(reg->type_.value_type_ != Value::NONE) << sym_cstr(decl->type);
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

void InsnAnnotator::AnnotateValueType(fe::VarDecl *decl, Value *value) {
  value->type_ = SymToType(decl->type);
  if (decl->array_length > -1) {
    value->type_ = Value::INT_ARRAY;
  }
  value->num_.type = decl->width;
}

void InsnAnnotator::AnnotateByValue(Value *value, Register *reg) {
  reg->type_.value_type_ = value->type_;
  if (value->type_ == Value::NUM) {
    reg->type_.width_ = value->num_.type;
  }
}

}  // namespace vm
