#include "fe/var_decl.h"

#include "base/dump_stream.h"
#include "fe/expr.h"
#include "karuta/annotation.h"

namespace fe {

VarDecl::VarDecl()
    : name_expr_(nullptr),
      type_(nullptr),
      object_name_(sym_null),
      is_shared_(false),
      is_const_(false),
      is_io_(false),
      is_output_(false),
      initial_val_(nullptr),
      array_initializer_(nullptr),
      annotation_(nullptr) {}

void VarDecl::Dump() {
  DumpStream ds(cout);
  Dump(ds);
}

void VarDecl::Dump(DumpStream &ds) {
  ds.indent();
  ds.os << "type: ";
  if (is_shared_) {
    ds.os << "shared ";
  }
  if (is_const_) {
    ds.os << "const ";
  }
  if (is_io_) {
    if (is_output_) {
      ds.os << "output ";
    } else {
      ds.os << "input ";
    }
  }
  if (type_) {
    ds.os << sym_cstr(type_) << " ";
  } else {
    ds.os << "(int) ";
  }
  if (name_expr_ != nullptr) {
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
  ds.indent();
  ds.os << width_.Format();
  ds.os << "\n";
  if (object_name_) {
    ds.indent();
    ds.os << "#" << sym_cstr(object_name_) << "\n";
  }
  if (array_shape_.get() != nullptr) {
    ds.indent();
    array_shape_->Dump(ds);
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

Expr *VarDecl::GetNameExpr() const { return name_expr_; }

void VarDecl::SetNameExpr(Expr *name) { name_expr_ = name; }

sym_t VarDecl::GetType() const { return type_; }

void VarDecl::SetType(sym_t type) { type_ = type; }

const iroha::NumericWidth &VarDecl::GetWidth() const { return width_; }

void VarDecl::SetWidth(const iroha::NumericWidth &width) { width_ = width; }

sym_t VarDecl::GetObjectName() const { return object_name_; }

void VarDecl::SetObjectName(sym_t object_name) { object_name_ = object_name; }

void VarDecl::SetIsShared(bool is_shared) { is_shared_ = is_shared; }

bool VarDecl::GetIsShared() const { return is_shared_; }

void VarDecl::SetIsConst(bool is_const) { is_const_ = is_const; }

bool VarDecl::GetIsConst() const { return is_const_; }

void VarDecl::SetIsIO(bool is_io, bool is_output) {
  is_io_ = is_io;
  is_output_ = is_output;
}

bool VarDecl::GetIsIO() const { return is_io_; }

bool VarDecl::GetIsOutput() const { return is_output_; }

Expr *VarDecl::GetInitialVal() const { return initial_val_; }

void VarDecl::SetInitialVal(Expr *initial_val) { initial_val_ = initial_val; }

ArrayInitializer *VarDecl::GetArrayInitializer() const {
  return array_initializer_.get();
}

void VarDecl::SetArrayInitializer(ArrayInitializer *array) {
  array_initializer_.reset(array);
}

ArrayShape *VarDecl::GetArrayShape() const { return array_shape_.get(); }

void VarDecl::SetArrayShape(ArrayShape *shape) { array_shape_.reset(shape); }

Annotation *VarDecl::GetAnnotation() const { return annotation_; }

void VarDecl::SetAnnotation(Annotation *an) { annotation_ = an; }

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

ArrayShape::ArrayShape(int l) { length.push_back(l); }

void ArrayShape::Dump(DumpStream &ds) const {
  for (int i = length.size() - 1; i >= 0; --i) {
    ds.os << "[" << length[i] << "]";
  }
  ds.os << "\n";
}

}  // namespace fe
