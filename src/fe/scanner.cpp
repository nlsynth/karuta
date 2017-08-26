// Copyright Yusuke Tabata 2007-2017

#include "fe/scanner.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace fe {

static struct OperatorTableEntry *op_tab;
static const ScannerInfo *s_info;

Scanner *Scanner::current_scanner_;
static bool dbg_scanner;

ScannerInfo::~ScannerInfo() {
}

Scanner::Scanner() {
  Reset();
  token_len_ = 0;
  current_scanner_ = this;
  in_semicolon_ = false;
  in_array_elm_ = false;
}

int Scanner::GetToken(int *sub) {
  *sub = 0;
  SkipNonToken();
  //
  char c = CurChar();
  if (is_dec(c)) {
    return read_num();
  }
  //
  struct OperatorTableEntry *op = lookup_op();
  if (op) {
    int r;
    r = read_op(op);
    *sub = op->sub_op;
    return r;
  }
  //
  if (c == '\"') {
    return read_str();
  }
  if (is_symhead(c)) {
    return read_sym();
  }
  return -1;
}

uint64_t Scanner::GetNum() {
  if (token_[0] == '0' &&
      token_[1] == 'x') {
    uint64_t num;
    sscanf(token_, "%llx", (long long unsigned int *)&num);
    return num;
  }
  return atoll(token_);
}

sym_t Scanner::GetSym() {
  return sym_lookup(token_);
}

const char *Scanner::GetStr() {
  return token_;
}

void Scanner::GetPosition(ScannerPos *pos) {
  pos->pos = 0;
  pos->line = ln_;
  pos->file = im_->file_name;
}

char Scanner::CurChar() {
  return im_->buf[cur_];
}

char Scanner::NextChar() {
  return ReadAhead(1);
}

char Scanner::ReadAhead(int a) {
  if (cur_ + a < (int)im_->buf.size()) {
    return im_->buf.data()[cur_ + a];
  }
  return -1;
}

void Scanner::SkipNonToken() {
  while (true) {
    if ((is_space(CurChar()))) {
      GoAhead();
    } else if (IsCommentStart()) {
      SkipComment();
    } else {
      return ;
    }
  }
}

void Scanner::SkipComment() {
  if (!IsCommentStart()) {
    return ;
  }
  char c = NextChar();
  if (c == '/') {
    while (CurChar() != '\n' && CurChar() != 0) {
      GoAhead();
    }
    GoAhead();
  } else {
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
  if (CurChar() == '/' &&
      (NextChar() == '*' || NextChar() == '/')) {
    return true;
  }
  return false;
}

void Scanner::PushChar(char c) {
  if (token_len_ > MAX_TOKEN - 2) {
    // ignore
    return ;
  }
  token_[token_len_] = c;
  token_len_ ++;
  token_[token_len_] = 0;
}

int Scanner::read_num() {
  ClearToken();
  bool hex_dec_mode = false;
  if (CurChar() == '0' &&
      NextChar() == 'x') {
    PushChar(CurChar());
    GoAhead();
    PushChar(CurChar());
    GoAhead();
    hex_dec_mode = true;
  }
  while (true) {
    char c = CurChar();
    if (hex_dec_mode) {
      if (!is_hex_dec(c)) {
	break;
      }
    } else {
      if (!is_dec(c)) {
	break;
      }
    }
    PushChar(CurChar());
    GoAhead();
  }
  return s_info->num_token;
}

int Scanner::read_sym() {
  ClearToken();
  while (is_symbody(CurChar())) {
    PushChar(CurChar());
    GoAhead();
  }
  return s_info->sym_token;
}

int Scanner::read_str() {
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
  return s_info->str_token;
}

int Scanner::read_op(struct OperatorTableEntry *op) {
  int i;
  for (i = strlen(op->str); i > 0; i--) {
    GoAhead();
  }
  return op->op;
}

struct OperatorTableEntry *Scanner::lookup_op() {
  char buf[4];
  buf[0] = CurChar();
  buf[1] = NextChar();
  buf[2] = ReadAhead(2);
  buf[3] = 0;
  if (UseReturnAsSep() && buf[0] == '\n') {
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
  if (CurChar()) {
    cur_ ++;
  }
  char c = CurChar();
  if (c == '\n') {
    ln_ ++;
  }
}

void Scanner::ClearToken() {
  token_len_ = 0;
  token_[0] = 0;
}

bool Scanner::is_hex_dec(char c) {
  if (is_dec(c)) {
    return true;
  }
  if ((c >= 'a' && c <= 'f') ||
      (c >= 'A' && c <= 'F')) {
    return true;
  }
  return false;
}

bool Scanner::is_dec(char c) {
  if (c >= '0' && c <= '9') {
    return true;
  }
  return false;
}

bool Scanner::is_space(char c) {
  if (UseReturnAsSep() && c == '\n') {
    return false;
  }
  if (c == ' ' || c == '\t' || c == '\r' || c == '\n') {
    return true;
  }
  return false;
}

bool Scanner::is_symhead(char c) {
  if (isalpha((unsigned char)c)) {
    return true;
  }
  if (c == '_') {
    return true;
  }
  return false;
}

bool Scanner::is_symbody(char c) {
  if (is_symhead(c)) {
    return true;
  }
  if (is_dec(c)) {
    return true;
  }
  return false;
}

void Scanner::Init(const ScannerInfo *si, bool dbg) {
  op_tab = si->op_tab;
  s_info = si;
  dbg_scanner = dbg;
}

FileImage::~FileImage() {
}

FileImage *Scanner::CreateFileImage(const char *fn) {
  struct stat st;
  if (stat(fn, &st) != 0) {
    return nullptr;
  }
  FILE *fp;
  fp = fopen(fn, "r");
  if (!fp) {
    return nullptr;
  }
  FileImage *im = new FileImage();
  im->file_name = string(fn);
  char *buf = (char *)malloc(st.st_size + 1);
  size_t s = fread(buf, st.st_size, 1, fp);
  buf[st.st_size] = 0;
  im->buf = string(buf, st.st_size + 1);
  free(buf);
  fclose(fp);
  if (s == 0) {
    free(im);
    return nullptr;
  }
  return im;
}

void Scanner::SetFileImage(FileImage *im) {
  Reset();
  im_.reset(im);
}

void Scanner::Reset() {
  cur_ = 0;
  ln_ = 1;
}

bool Scanner::UseReturnAsSep() {
  return in_semicolon_ && !in_array_elm_;
}

void Scanner::ReleaseFileImage() {
  im_.reset(nullptr);
}

void Scanner::InSemiColonStatement() {
  in_semicolon_ = true;
}

void Scanner::EndSemiColonStatement() {
  in_semicolon_ = false;
}

void Scanner::InArrayElmDecl() {
  in_array_elm_ = true;
}

void Scanner::EndArrayElmDecl() {
  in_array_elm_ = false;
}


ScannerPos::ScannerPos() {
  line = -1;
  pos = -1;
}

Scanner* ScannerInterface::CreateScanner() {
  return new Scanner;
}

void ScannerInterface::GetPosition(ScannerPos *pos) {
  Scanner::current_scanner_->GetPosition(pos);
}

int ScannerInterface::GetToken(ScannerToken *tk) {
  int sub_op;
  int r = Scanner::current_scanner_->GetToken(&sub_op);
  tk->sub_op = 0;
  tk->str = nullptr;
  if (r == s_info->num_token) {
    tk->num.value = Scanner::current_scanner_->GetNum();
    if (dbg_scanner) {
      printf("num=(%lu)\n", tk->num.value);
    }
  } else if (r == s_info->sym_token) {
    int k;
    tk->sym = Scanner::current_scanner_->GetSym();
    if (dbg_scanner) {
      printf("sym=(%s)\n", sym_cstr(tk->sym));
    }
    k = s_info->LookupKeyword(tk->sym);
    if (k) {
      return k;
    }
  } else if (r == s_info->str_token) {
    tk->str = Scanner::current_scanner_->GetStr();
    if (dbg_scanner) {
      printf("str=(%s)\n", tk->str);
    }
  } else {
    if (dbg_scanner) {
      printf("op=(%d(%d))\n", r, sub_op);
    }
    tk->sub_op = sub_op;
  }
  return r;
}

void ScannerInterface::InSemiColonStatement() {
  Scanner::current_scanner_->InSemiColonStatement();
}

void ScannerInterface::EndSemiColonStatement() {
  Scanner::current_scanner_->EndSemiColonStatement();
}

void ScannerInterface::InArrayElmDecl() {
  Scanner::current_scanner_->InArrayElmDecl();
}

void ScannerInterface::EndArrayElmDecl() {
  Scanner::current_scanner_->EndArrayElmDecl();
}

}  // namespace fe

