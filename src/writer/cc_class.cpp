#include "writer/cc_class.h"

namespace writer {

ClassWriter::ClassWriter(const char *name, const char *parent_name,
			 const char *parent_initializer)
  : class_name_(name), parent_name_(parent_name),
    parent_initializer_(parent_initializer) {
}

void ClassWriter::Output(ostream &os) const {
  // class definitions.
  os << "class " << class_name_;
  if (!parent_name_.empty()) {
    os << " : public " << parent_name_;
  }
  os << " {\npublic:\n";
  os << "  " << class_name_ << "()\n";
  bool first_initializer = true;
  if (!parent_name_.empty()) {
    os << " : " << parent_name_ << "(";
    if (!parent_initializer_.empty()) {
      os << parent_initializer_;
    }
    os << ")";
  }
  for (const MemberInfo &mi : members_) {
    if (!mi.initializer.empty()) {
      if (first_initializer) {
	os << "  : ";
      } else {
	os << ", ";
      }
      os << mi.decl << "(" << mi.initializer << ")";
      first_initializer = false;
    }
  }
  os << "  {}\n\n";

  // local variables.
  for (const MemberInfo &mi : members_) {
    os << "  ";
    if (!mi.modifier.empty()) {
      os << mi.modifier << " ";
    }
    os << mi.type << " " << mi.decl << ";\n";
  }
  os << "};\n\n";

  // method bodies.
  for (const MemberInfo &mi : members_) {
    if (mi.body.empty()) {
      continue;
    }
    os << mi.type << " " << class_name_ << "::" << mi.decl << " {\n";
    os << mi.body;
    os << "}\n\n";
  }
}

void ClassWriter::EndMethod() {
  MemberInfo &mi = *(members_.rbegin());
  mi.body += ss_.str();
  ss_.str("");
}

ostringstream &ClassWriter::os() {
  return ss_;
}

void ClassWriter::AddMember(const string &modifier,
			    const string &type, const string &decl,
			    const string &initializer) {
  MemberInfo mi;
  mi.modifier = modifier;
  mi.type = type;
  mi.decl = decl;
  mi.initializer = initializer;
  members_.push_back(mi);
}
}  // namespace writer
