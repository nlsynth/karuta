// -*- C++ -*-
#ifndef _writer_cc_class_h_
#define _writer_cc_class_h_

#include "nli.h"

namespace writer {

struct MemberInfo {
  string modifier;
  string type;
  string decl;
  string body;
  string initializer;
};

class ClassWriter {
public:
  ClassWriter(const char *name, const char *parent_name,
	      const char *parent_initializer = "");

  void Output(ostream &os) const;
  void AddMember(const string &modifier,
		 const string &type, const string &decl,
		 const string &initializer = "");
  void EndMethod();
  const string &ClassName() const;

  ostringstream& os();

private:

  string class_name_;
  string parent_name_;
  string parent_initializer_;
  vector<MemberInfo> members_;
  ostringstream ss_;
};

}  // namespace writer

#endif  // _writer_cc_class_h_
