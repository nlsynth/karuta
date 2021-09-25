// -*- c++ -*-
#ifndef _base_sym_h_
#define _base_sym_h_

#include <string>

typedef class sym *sym_t;
void sym_table_init();
sym_t sym_lookup(const char *str);
const char *sym_cstr(const sym_t s);
std::string sym_str(const sym_t s);
sym_t sym_alloc_tmp_sym(const char *suffix);
sym_t sym_append_prefix(sym_t sym, const char *prefix);
sym_t sym_append_idx(sym_t sym, int idx);

extern sym_t sym_null;
extern sym_t sym_string;
extern sym_t sym_if, sym_else;
extern sym_t sym_for, sym_do, sym_while;
extern sym_t sym_switch, sym_case, sym_default;
extern sym_t sym_break, sym_continue, sym_goto;
extern sym_t sym_return, sym_as;
extern sym_t sym_uint, sym_bool, sym_object, sym_module;
extern sym_t sym_output, sym_input, sym_parent;

#endif  // _base_sym_h_
