// -*- C++ -*-
#ifndef _fe_scanner_h_
#define _fe_scanner_h_

#include "fe/common.h"
#include "iroha/numeric.h"

namespace fe {

class FileImage {
 public:
  string buf;
  string file_name;
};

struct OperatorTableEntry {
  const char *str;
  int op;
  int sub_op;
};

// This is passed to the Scannar's constructor.
// Passing this on Scanner's construction time to avoid static dependency on
// the parser from the scanner.
class ScannerInfo {
 public:
  int LookupKeyword(sym_t sym) const;

  // parser's token id.
  int num_token;
  int sym_token;
  int str_token;
};

struct ScannerToken {
  sym_t sym;
  iroha::NumericLiteral num;
  int sub_op;
  const string *str;
};

class Scanner {
 public:
  Scanner();

  static void Init(const ScannerInfo *si, OperatorTableEntry *ops, bool dbg);
  static FileImage *CreateFileImage(const string &fn, std::istream &is);

  void SetFileImage(FileImage *im);
  void ReleaseFileImage();

  int GetToken(int *sub);
  iroha::NumericLiteral GetNum();
  sym_t GetSym();
  const string *GetStr();
  void GetPosition(ScannerPos *pos);
  void InSemiColonStatement();
  void EndSemiColonStatement();
  void InArrayElmDecl();
  void EndArrayElmDecl();

  static Scanner *current_scanner_;

 private:
  void Reset();
  bool UseReturnAsSep();
  char CurChar();
  char NextChar();
  char ReadAhead(int a);

  void SkipNonToken();
  void SkipComment();
  bool IsCommentStart();
  bool IsEof();

  void GoAhead();

  void ClearToken();
  void PushChar(char c);

  int ReadNum();
  int ReadSym();
  int ReadStr();
  int ReadOp(struct OperatorTableEntry *s);

  struct OperatorTableEntry *LookupOp();

  bool IsDec(char c);
  bool IsHexDec(char c);
  bool IsSpace(char c);
  bool IsSymHead(char c);
  bool IsSymBody(char c);

 private:
  static const int MAX_TOKEN = 256;
  std::unique_ptr<FileImage> im_;
  ScannerFile *file_;
  int cur_pos_;

  char token_[MAX_TOKEN];
  int token_len_;
  int ln_;
  bool in_semicolon_;
  bool in_array_elm_;
  // Unescaped strings in this file.
  vector<string *> strs_;

 public:
  static OperatorTableEntry *op_tab;
  static const ScannerInfo *s_info;
  static bool dbg_scanner;
};

}  // namespace fe

#endif  // _fe_scanner_h_
