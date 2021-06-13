// Copyright Yusuke Tabata 2007-2021

#include "fe/scanner.h"

#include <ctype.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <map>

#include "base/stl_util.h"
#include "fe/scanner_pos.h"

namespace fe {

struct FilesMap {
  ~FilesMap() { STLDeleteSecondElements(&files_); }
  ScannerFile *GetScannerFile(const string &fn) {
    auto it = files_.find(fn);
    if (it != files_.end()) {
      return it->second;
    }
    ScannerFile *sf = new ScannerFile();
    sf->file = fn;
    files_[fn] = sf;
    return sf;
  }
  std::map<string, ScannerFile *> files_;

} Files;

OperatorTableEntry *Scanner::op_tab;
const ScannerInfo *Scanner::s_info;

Scanner *Scanner::current_scanner_;
bool Scanner::dbg_scanner;

Scanner::Scanner() {
  Reset();
  token_len_ = 0;
  current_scanner_ = this;
  in_semicolon_ = false;
  in_array_elm_ = false;
  file_ = nullptr;
}

int Scanner::GetToken(int *sub) {
  *sub = 0;
  SkipNonToken();
  char c = CurChar();
  if (IsDec(c)) {
    return ReadNum();
  }
  // An expression ends with a '}'.
  // Injects a semicolon and doesn't proceed.
  if (c == '}' && UseReturnAsSep()) {
    in_semicolon_ = false;
    *sub = 0;
    return ';';
  }
  // operator.
  struct OperatorTableEntry *op = LookupOp();
  if (op) {
    int r;
    r = ReadOp(op);
    *sub = op->sub_op;
    return r;
  }
  // string
  if (c == '\"') {
    return ReadStr();
  }
  // sym.
  if (IsSymHead(c)) {
    return ReadSym();
  }
  if (IsEof()) {
    return -1;
  }
  // non sym char.
  if (c < 0) {
    int ch = c;
    return ch + 256;
  }
  return c;
}

iroha::NumericLiteral Scanner::GetNum() {
  return iroha::NumericLiteral::Parse(string(token_, token_len_));
}

sym_t Scanner::GetSym() { return sym_lookup(token_); }

const string *Scanner::GetStr() { return strs_[strs_.size() - 1]; }

void Scanner::GetPosition(ScannerPos *pos) {
  pos->pos = 0;
  pos->line = ln_;
  pos->file = file_;
}

char Scanner::CurChar() { return im_->buf[cur_pos_]; }

char Scanner::NextChar() { return ReadAhead(1); }

char Scanner::ReadAhead(int a) {
  if (cur_pos_ + a < (int)im_->buf.size()) {
    return im_->buf.data()[cur_pos_ + a];
  }
  return -1;
}

void Scanner::SkipNonToken() {
  while (true) {
    if ((IsSpace(CurChar()))) {
      GoAhead();
    } else if (IsCommentStart()) {
      SkipComment();
    } else {
      return;
    }
  }
}

void Scanner::SkipComment() {
  if (!IsCommentStart()) {
    return;
  }
  char c = CurChar();
  char nc = NextChar();
  if (c == '#' || nc == '/') {
    // # or // comment
    while (CurChar() != '\n' && CurChar() != 0) {
      GoAhead();
    }
  } else {
    // /* comment */
    GoAhead();
    GoAhead();
    while (CurChar() != '*' || NextChar() != '/') {
      GoAhead();
    }
    GoAhead();
    GoAhead();
  }
}

bool Scanner::IsCommentStart() {
  if (cur_pos_ == 0 && CurChar() == '#') {
    // # is allowed only at the beginning for #!
    return true;
  }
  if (CurChar() == '/' && (NextChar() == '*' || NextChar() == '/')) {
    return true;
  }
  return false;
}

bool Scanner::IsEof() { return (cur_pos_ >= im_->buf.size()); }

void Scanner::PushChar(char c) {
  if (token_len_ > MAX_TOKEN - 2) {
    // ignore
    return;
  }
  token_[token_len_] = c;
  token_len_++;
  token_[token_len_] = 0;
}

int Scanner::ReadNum() {
  ClearToken();
  bool hex_dec_mode = false;
  if (CurChar() == '0') {
    char c = NextChar();
    if (c == 'x' || c == 'b') {
      PushChar(CurChar());
      GoAhead();
      PushChar(CurChar());
      GoAhead();
      if (c == 'x') {
        hex_dec_mode = true;
      }
    }
  }
  while (true) {
    char c = CurChar();
    if (c == '_') {
      // skip.
    } else if (hex_dec_mode) {
      if (!IsHexDec(c)) {
        break;
      }
    } else {
      if (!IsDec(c)) {
        break;
      }
    }
    PushChar(CurChar());
    GoAhead();
  }
  return s_info->num_token;
}

int Scanner::ReadSym() {
  ClearToken();
  while (IsSymBody(CurChar())) {
    PushChar(CurChar());
    GoAhead();
  }
  return s_info->sym_token;
}

int Scanner::ReadStr() {
  ClearToken();
  GoAhead();
  while (1) {
    int c = CurChar();
    if (c == '\n') {
      return -1;
    }
    if (c == '\"') {
      GoAhead();
      break;
    }
    if (c == '\\') {
      GoAhead();
      c = CurChar();
    }
    PushChar(c);
    GoAhead();
  }
  strs_.push_back(new string(token_));
  return s_info->str_token;
}

int Scanner::ReadOp(struct OperatorTableEntry *op) {
  int i;
  for (i = strlen(op->str); i > 0; i--) {
    GoAhead();
  }
  return op->op;
}

struct OperatorTableEntry *Scanner::LookupOp() {
  char buf[4];
  buf[0] = CurChar();
  buf[1] = NextChar();
  buf[2] = ReadAhead(2);
  buf[3] = 0;
  if (UseReturnAsSep() && (buf[0] == '\n' || IsEof())) {
    buf[0] = ';';
  }
  for (struct OperatorTableEntry *op = op_tab; op->str; op++) {
    int len = strlen(op->str);
    if (!strncmp(op->str, buf, len)) {
      return op;
    }
  }
  return 0;
}

void Scanner::GoAhead() {
  if (IsEof()) {
    return;
  }
  if (CurChar()) {
    cur_pos_++;
  }
  char c = CurChar();
  if (c == '\n') {
    ln_++;
  }
}

void Scanner::ClearToken() {
  token_len_ = 0;
  token_[0] = 0;
}

bool Scanner::IsHexDec(char c) {
  if (IsDec(c)) {
    return true;
  }
  if ((c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')) {
    return true;
  }
  return false;
}

bool Scanner::IsDec(char c) {
  if (c >= '0' && c <= '9') {
    return true;
  }
  return false;
}

bool Scanner::IsSpace(char c) {
  if (UseReturnAsSep() && c == '\n') {
    return false;
  }
  if (c == ' ' || c == '\t' || c == '\r' || c == '\n') {
    return true;
  }
  return false;
}

bool Scanner::IsSymHead(char c) {
  if (isalpha((unsigned char)c)) {
    return true;
  }
  if (c == '_') {
    return true;
  }
  return false;
}

bool Scanner::IsSymBody(char c) {
  if (IsSymHead(c)) {
    return true;
  }
  if (IsDec(c)) {
    return true;
  }
  return false;
}

void Scanner::Init(const ScannerInfo *si, OperatorTableEntry *ops, bool dbg) {
  op_tab = ops;
  s_info = si;
  dbg_scanner = dbg;
}

FileImage *Scanner::CreateFileImage(const string &fn, std::istream &is) {
  FileImage *im = new FileImage();
  im->file_name = fn;
  std::ostringstream os;
  os << is.rdbuf();
  im->buf = os.str() + "\0";
  return im;
}

void Scanner::SetFileImage(FileImage *im) {
  Reset();
  im_.reset(im);
  if (im != nullptr) {
    file_ = Files.GetScannerFile(im->file_name);
  } else {
    file_ = nullptr;
  }
}

void Scanner::Reset() {
  cur_pos_ = 0;
  ln_ = 1;
  STLDeleteValues(&strs_);
  strs_.clear();
}

bool Scanner::UseReturnAsSep() { return in_semicolon_ && !in_array_elm_; }

void Scanner::ReleaseFileImage() { SetFileImage(nullptr); }

void Scanner::InSemiColonStatement() { in_semicolon_ = true; }

void Scanner::EndSemiColonStatement() { in_semicolon_ = false; }

void Scanner::InArrayElmDecl() { in_array_elm_ = true; }

void Scanner::EndArrayElmDecl() { in_array_elm_ = false; }

}  // namespace fe
