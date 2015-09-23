// -*- C++ -*-
//
#ifndef _fe_fe_h_
#define _fe_fe_h_

#include "nli.h"

namespace vm {
class Method;
class VM;
}  // namespace vm

namespace fe {

class FileImage;
class Method;
class ScannerInfo;

class FE {
 public:
  FE(bool dbg_parser, bool dbg_scanner, bool dbg_bytecode);

  void Run(bool vanilla, const vector<string> &files);

  static vm::Method *CompileFile(const string &file, bool dbg_parser,
				 vm::VM *vm);
  static FileImage *GetFileImage(const string &fn);

 private:
  void RunFile(const string &file, vm::VM *vm);

  static Method *ReadFile(const string &file);

  bool dbg_parser_;

  static std::unique_ptr<ScannerInfo> scanner_info_;
  static string dirname_;
};

}  // namespace fe

#endif  // _fe_fe_h_
