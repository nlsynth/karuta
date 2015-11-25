// Copyright Yusuke Tabata 2007-2015

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
}

int Scanner::GetToken(int *sub) {
  *sub = 0;
  skip_non_token();
  //
  char c = cur_char();
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

char Scanner::cur_char() {
  return im_->buf[cur_];
}

char Scanner::next_char() {
  return read_ahead(1);
}

char Scanner::read_ahead(int a) {
  if (cur_ + a < (int)im_->buf.size()) {
    return im_->buf.data()[cur_ + a];
  }
  return -1;
}

void Scanner::skip_non_token() {
  while (1) {
    if ((is_space(cur_char()))) {
      go_ahead();
    } else if (is_comment_start()) {
      skip_comment();
    } else {
      return ;
    }
  }
}

void Scanner::skip_comment() {
  if (!is_comment_start()) {
    return ;
  }
  char c = next_char();
  if (c == '/') {
    while (cur_char() != '\n' && cur_char() != 0) {
      go_ahead();
    }
    go_ahead();
  } else {
    go_ahead();
    go_ahead();
    while (cur_char() != '*' || next_char() != '/') {
      go_ahead();
    }
    go_ahead();
    go_ahead();
  }
}

bool Scanner::is_comment_start() {
  if (cur_char() == '/' &&
      (next_char() == '*' || next_char() == '/')) {
    return true;
  }
  return false;
}

void Scanner::push_char(char c) {
  if (token_len_ > MAX_TOKEN - 2) {
    // ignore
    return ;
  }
  token_[token_len_] = c;
  token_len_ ++;
  token_[token_len_] = 0;
}

int Scanner::read_num() {
  clear_token();
  bool hex_dec_mode = false;
  if (cur_char() == '0' &&
      next_char() == 'x') {
    push_char(cur_char());
    go_ahead();
    push_char(cur_char());
    go_ahead();
    hex_dec_mode = true;
  }
  while (true) {
    char c = cur_char();
    if (hex_dec_mode) {
      if (!is_hex_dec(c)) {
	break;
      }
    } else {
      if (!is_dec(c)) {
	break;
      }
    }
    push_char(cur_char());
    go_ahead();
  }
  return s_info->num_token;
}

int Scanner::read_sym() {
  clear_token();
  while (is_symbody(cur_char())) {
    push_char(cur_char());
    go_ahead();
  }
  return s_info->sym_token;
}

int Scanner::read_str() {
  clear_token();
  go_ahead();
  while (1) {
    int c = cur_char();
    if (c == '\n') {
      return -1;
    }
    if (c == '\"') {
      go_ahead();
      break;
    }
    if (c == '\\') {
      go_ahead();
      c = cur_char();
    }
    push_char(c);
    go_ahead();
  }
  return s_info->str_token;
}

int Scanner::read_op(struct OperatorTableEntry *op) {
  int i;
  for (i = strlen(op->str); i > 0; i--) {
    go_ahead();
  }
  return op->op;
}

struct OperatorTableEntry *Scanner::lookup_op() {
  char buf[4];
  buf[0] = cur_char();
  buf[1] = next_char();
  buf[2] = read_ahead(2);
  buf[3] = 0;
  for (struct OperatorTableEntry *op = op_tab; op->str; op++) {
    int len = strlen(op->str);
    if (!strncmp(op->str, buf, len)) {
      return op;
    }
  }
  return 0;
}

void Scanner::go_ahead() {
  if (cur_char()) {
    cur_ ++;
  }
  char c = cur_char();
  if (c == '\n') {
    ln_ ++;
  }
}

void Scanner::clear_token() {
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
    return NULL;
  }
  FILE *fp;
  fp = fopen(fn, "r");
  if (!fp) {
    return NULL;
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
    return NULL;
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

void Scanner::ReleaseFileImage() {
  im_.reset(NULL);
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
  tk->str = NULL;
  if (r == s_info->num_token) {
    tk->num = Scanner::current_scanner_->GetNum();
    if (dbg_scanner) {
      printf("num=(%lu)\n", tk->num);
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

}  // namespace fe

