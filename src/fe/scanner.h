// -*- C++ -*-
#ifndef _fe_scanner_h_
#define _fe_scanner_h_

#include "nli.h"

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

// This struct can be a part of YYSTYPE union.
struct NumericLiteral {
  uint64_t value;
  // non negative if defined.
  int width;
};

// Language dependent scanner configuration.
class ScannerInfo {
public:
  virtual ~ScannerInfo();
  virtual int LookupKeyword(sym_t sym) const = 0;
  struct OperatorTableEntry *op_tab;
  // parser's token id.
  int num_token;
  int sym_token;
  int str_token;
};

struct ScannerToken {
  sym_t sym;
  NumericLiteral num;
  int sub_op;
  const char *str;
};

struct ScannerPos {
  ScannerPos();

  int line;
  int pos;
  string file;
};

class Scanner {
public:
  Scanner();
  static void Init(const ScannerInfo *si, bool dbg);
  static FileImage *CreateFileImage(const char *fn);
  void SetFileImage(FileImage *im);
  void ReleaseFileImage();

  int GetToken(int *sub);
  NumericLiteral GetNum();
  sym_t GetSym();
  const char *GetStr();
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

  void GoAhead();

  void ClearToken();
  void PushChar(char c);

  int ReadNum();
  int ReadSym();
  int ReadStr();
  int ReadOp(struct OperatorTableEntry *s);

  struct OperatorTableEntry *lookup_op();

  bool IsDec(char c);
  bool IsHexDec(char c);
  bool IsSpace(char c);
  bool IsSymHead(char c);
  bool IsSymBody(char c);
  uint64_t Parse0b();

private:
  static const int MAX_TOKEN = 256;
  std::unique_ptr<FileImage> im_;
  int cur_;

  char token_[MAX_TOKEN];
  int token_len_;
  int ln_;
  bool in_semicolon_;
  bool in_array_elm_;
};

class ScannerInterface {
public:
  static Scanner *CreateScanner();
  static int GetToken(ScannerToken *tk);
  static void GetPosition(ScannerPos *pos);
  static void InSemiColonStatement();
  static void EndSemiColonStatement();
  static void InArrayElmDecl();
  static void EndArrayElmDecl();
};

}  // namespace fe

#endif  // _fe_scanner_h_
