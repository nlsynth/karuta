// -*- C++ -*-
#ifndef _fe_scanner_h_
#define _fe_scanner_h_

#include "nli.h"

namespace fe {

class FileImage {
public:
  ~FileImage();
  string buf;
  string file_name;
};

struct OperatorTableEntry {
  const char *str;
  int op;
  int sub_op;
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
  uint64_t num;
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
  uint64_t GetNum();
  sym_t GetSym();
  const char *GetStr();
  void GetPosition(ScannerPos *pos);
  void InSemiColonStatement();
  void EndSemiColonStatement();

  static Scanner *current_scanner_;

private:
  void Reset();
  char cur_char();
  char next_char();
  char read_ahead(int a);

  void skip_non_token();
  void skip_comment();
  bool is_comment_start();

  void go_ahead();

  void clear_token();
  void push_char(char c);

  int read_num();
  int read_sym();
  int read_str();
  int read_op(struct OperatorTableEntry *s);

  struct OperatorTableEntry *lookup_op();

  bool is_dec(char c);
  bool is_hex_dec(char c);
  bool is_space(char c);
  bool is_symhead(char c);
  bool is_symbody(char c);

private:
  static const int MAX_TOKEN = 256;
  std::unique_ptr<FileImage> im_;
  int cur_;

  char token_[MAX_TOKEN];
  int token_len_;
  int ln_;
  bool in_semicolon_;
};

class ScannerInterface {
public:
  static Scanner *CreateScanner();
  static int GetToken(ScannerToken *tk);
  static void GetPosition(ScannerPos *pos);
  static void InSemiColonStatement();
  static void EndSemiColonStatement();
};

}  // namespace fe

#endif  // _fe_scanner_h_

