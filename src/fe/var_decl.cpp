#include "fe/var_decl.h"

#include "base/annotation.h"
#include "base/dump_stream.h"
#include "fe/expr.h"

namespace fe {

VarDecl::VarDecl() : name_expr_(nullptr), type_(nullptr), width_(nullptr),
		     object_name_(sym_null),
		     initial_val_(nullptr),
		     array_length_(-1), array_initializer_(nullptr),
		     annotation_(nullptr) {
}

void VarDecl::Dump() {
  DumpStream ds(cout);
  Dump(ds);
}

void VarDecl::Dump(DumpStream &ds) {
  if (type_) {
    ds.indent();
    ds.os << "type: " << sym_cstr(type_) << " ";
  }
  if (name_expr_) {
    ds.os << "\n";
    ds.indent();
    ds.os << "name:\n";
    ds.push_indent();
    name_expr_->Dump(ds);
    ds.pop_indent();
  } else {
    ds.indent();
    ds.os << "{null}\n";
  }
  if (width_) {
    ds.indent();
    numeric::WidthUtil::Dump(width_, ds.os);
    ds.os << "\n";
  }
  if (object_name_) {
    ds.indent();
    ds.os << "#" << sym_cstr(object_name_) << "\n";
  }
  if (array_length_ >= 0) {
    ds.indent();
    ds.os << "[" << array_length_ << "]\n";
  }
  if (array_initializer_) {
    array_initializer_->Dump(ds);
  }
  if (initial_val_) {
    ds.indent();
    ds.os << "initial:\n";
    ds.push_indent();
    initial_val_->Dump(ds);
    ds.pop_indent();
  }
  if (annotation_) {
    ds.indent();
    annotation_->Dump(ds.os);
    ds.os << "\n";
  }
}

void VarDeclSet::Dump(DumpStream &ds) {
  for (size_t i = 0; i < decls.size(); ++i) {
    decls[i]->Dump(ds);
  }
}

Expr *VarDecl::GetNameExpr() const {
  return name_expr_;
}

void VarDecl::SetNameExpr(Expr *name) {
  name_expr_ = name;
}

sym_t VarDecl::GetType() const {
  return type_;
}
  
void VarDecl::SetType(sym_t type) {
  type_ = type;
}

const iroha::NumericWidth *VarDecl::GetWidth() const {
  return width_;
}

void VarDecl::SetWidth(const iroha::NumericWidth *width) {
  width_ = width;
}

sym_t VarDecl::GetObjectName() const {
  return object_name_;
}

void VarDecl::SetObjectName(sym_t object_name) {
  object_name_ = object_name;
}

Expr *VarDecl::GetInitialVal() const {
  return initial_val_;
}

void VarDecl::SetInitialVal(Expr *initial_val) {
  initial_val_ = initial_val;
}

int VarDecl::GetArrayLength() {
  return array_length_;
}

void VarDecl::SetArrayLength(int array_length) {
  array_length_ = array_length;
}

ArrayInitializer *VarDecl::GetArrayInitializer() const {
  return array_initializer_;
}

void VarDecl::SetArrayInitializer(ArrayInitializer *array) {
  array_initializer_ = array;
}

Annotation *VarDecl::GetAnnotation() const{
  return annotation_;
}

void VarDecl::SetAnnotation(Annotation *an) {
  annotation_ = an;
}

void ArrayInitializer::Dump(DumpStream &ds) const {
  ds.indent();
  ds.os << "[";
  for (size_t i = 0; i < num_.size(); ++i) {
    if (i > 0) {
      ds.os << ",";
    }
    ds.os << num_[i];
  }
  ds.os << "]\n";
}

}  // namespace fe
