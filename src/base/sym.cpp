#include "base/sym.h"

#include <alloca.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list>

#include "base/stl_util.h"

using std::list;

#define BUCKET_COUNT 32

static int tmp_idx;

class sym {
public:
  sym(const char *n);
  ~sym();
  int hash(void);
  const char *str(void);
private:
  char *str_;
  int hash_;
};

class SymTable {
public:
  ~SymTable();
  sym *lookup(const char *str);
private:
  list<sym *> buckets_[BUCKET_COUNT];
} SymTable;

sym_t sym_null, sym_string;
sym_t sym_if, sym_else;
sym_t sym_for, sym_do, sym_while, sym_return, sym_as;
sym_t sym_switch, sym_case, sym_default;
sym_t sym_break, sym_continue, sym_goto;
sym_t sym_int, sym_bool, sym_object, sym_module;
sym_t sym_output, sym_input;

static int str_hash(const char *str) {
  int h = 0;
  while (*str) {
    h += (*str * 1003);
    str++;
  }
  return h;
}

sym::sym(const char *n) {
  str_ = strdup(n);
  hash_ = str_hash(n);
}

sym::~sym() {
  free(str_);
}

int sym::hash(void) {
  return hash_;
}

const char *sym::str(void) {
  return str_;
}

sym *SymTable::lookup(const char *str) {
  if (!str) {
    return sym_null;
  }
  int h = str_hash(str);
  int b = h % BUCKET_COUNT;
  
  for (sym *s : buckets_[b]) {
    if (h != s->hash()) {
      continue;
    }
    if (!strcmp(s->str(), str)) {
      return s;
    }
  }
  // could not find
  sym *s = new sym(str);
  buckets_[b].push_back(s);
  return s;
}

SymTable::~SymTable() {
  for (int i = 0; i < BUCKET_COUNT; ++i) {
    STLDeleteValues(&buckets_[i]);
  }
}

sym_t sym_lookup(const char *str) {
  return SymTable.lookup(str);
}

const char *sym_cstr(const sym_t s) {
  if (s == sym_null) {
    return "null";
  }
  return s->str();
}

std::string sym_str(const sym_t s) {
  return std::string(sym_cstr(s));
}

sym_t sym_alloc_tmp_sym(const char *suffix) {
  char buf[128];
  tmp_idx++;
  sprintf(buf, "_t%s_%d", suffix, tmp_idx);
  return sym_lookup(buf);
}

sym_t sym_append_prefix(sym_t sym, const char *prefix) {
  int len = strlen(prefix) + strlen(sym_cstr(sym)) + 2;
  char *buf = (char *)alloca(len);
  sprintf(buf,"%s%s", prefix, sym_cstr(sym));
  return sym_lookup(buf);
}

sym_t sym_append_idx(sym_t sym, int idx) {
  int len = strlen(sym_cstr(sym)) + 10;
  char *buf = (char *)alloca(len);
  sprintf(buf,"%s_%d", sym_cstr(sym), idx);
  return sym_lookup(buf);
}

void sym_table_init(void) {
  sym_string = sym_lookup("string");
  sym_if = sym_lookup("if");
  sym_else = sym_lookup("else");
  sym_for = sym_lookup("for");
  sym_do = sym_lookup("do");
  sym_while = sym_lookup("while");
  sym_switch = sym_lookup("switch");
  sym_case = sym_lookup("case");
  sym_default = sym_lookup("default");
  sym_break = sym_lookup("break");
  sym_continue = sym_lookup("continue");
  sym_goto = sym_lookup("goto");
  sym_as = sym_lookup("as");
  sym_return = sym_lookup("return");
  sym_int = sym_lookup("int");
  sym_bool = sym_lookup("bool");
  sym_object = sym_lookup("object");
  sym_module = sym_lookup("module");
  sym_output = sym_lookup("output");
  sym_input = sym_lookup("input");
}
