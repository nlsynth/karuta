#include "fe/nodecode.h"

#include <map>
#include <set>

using std::set;
using std::map;

namespace fe {

const char *NodeName(enum NodeCode node) {
  static map<NodeCode, const char *> codes = {
    {EXPR_SYM, "sym"},
    {EXPR_NUM, "num"},
    {EXPR_STR, "str"},
    {EXPR_ELM_SYM_REF, "elm_sym_ref"},
    {EXPR_FUNCALL, "funcall"},
    {EXPR_TRI_TERM, "tri_term"},
    {EXPR_BIT_RANGE, "bit_range"},
    {BINOP_COMMA, "comma"},
    {BINOP_ELM_REF, "elm_ref"},
    {BINOP_ADD, "add"},
    {BINOP_SUB, "sub"},
    {BINOP_ASSIGN, "assign"},
    {BINOP_LT, "lt"},
    {BINOP_GT, "gt"},
    {BINOP_LTE, "lte"},
    {BINOP_GTE, "gte"},
    {BINOP_EQ, "eq"},
    {BINOP_NE, "ne"},
    {BINOP_AND, "and"},
    {BINOP_OR, "or"},
    {BINOP_XOR, "xor"},
    {BINOP_LSHIFT, "lshift"},
    {BINOP_RSHIFT, "rshift"},
    {BINOP_ADD_ASSIGN, "add_assign"},
    {BINOP_SUB_ASSIGN, "sub_assign"},
    {BINOP_MUL_ASSIGN, "mul_assign"},
    {BINOP_DIV_ASSIGN, "div_assign"},
    {BINOP_MOD_ASSIGN, "mod_assign"},
    {BINOP_LSHIFT_ASSIGN, "lshift_assign"},
    {BINOP_RSHIFT_ASSIGN, "rshift_assign"},
    {BINOP_AND_ASSIGN, "and_assign"},
    {BINOP_XOR_ASSIGN, "xor_assign"},
    {BINOP_OR_ASSIGN, "or_assign"},
    {BINOP_MUL, "mul"},
    {BINOP_LAND, "land"},
    {BINOP_LOR, "lor"},
    {BINOP_CONCAT, "concat"},
    {BINOP_ARRAY_REF, "array_ref"},
    {UNIOP_PLUS, "plus"},
    {UNIOP_MINUS, "minus"},
    {UNIOP_POST_INC, "post_inc"},
    {UNIOP_PRE_INC, "pre_inc"},
    {UNIOP_POST_DEC, "post_dec"},
    {UNIOP_PRE_DEC, "pre_dec"},
    {UNIOP_BIT_INV, "bit_inv"},
    {UNIOP_LOGIC_INV, "logic_inv"},
    {STMT_EXPR, "expr"},
    {STMT_VARDECL, "vardecl"},
    {STMT_FUNCDECL, "funcdecl"},
    {STMT_TRANSITION, "transition"},
    {STMT_IF, "if"},
    {STMT_RETURN, "return"},
    {STMT_LABEL, "label"},
    {STMT_GOTO, "goto"},
    {STMT_IMPORT, "import"},
    {STMT_RETURN_TYPE, "return_type"},
    {STMT_PUSH_BINDING, "push_binding"},
    {STMT_POP_BINDING, "pop_binding"},
    {STMT_THREAD_DECL, "thread_decl"},
    {STMT_CHANNEL_DECL, "channel_decl"},
    {STMT_MAILBOX_DECL, "mailbox_decl"},
    {STMT_ENUM_DECL, "enum_decl"},
  };
  auto it = codes.find(node);
  if (it == codes.end()) {
    return "unknown";
  }
  return it->second;
}

bool IsBinOpNode(enum NodeCode node) {
  static set<NodeCode> codes = {
    BINOP_COMMA,
    BINOP_ELM_REF,
    BINOP_ADD,
    BINOP_SUB,
    BINOP_ASSIGN,
    BINOP_LT,
    BINOP_GT,
    BINOP_LTE,
    BINOP_GTE,
    BINOP_EQ,
    BINOP_NE,
    BINOP_AND,
    BINOP_OR,
    BINOP_XOR,
    BINOP_LSHIFT,
    BINOP_RSHIFT,
    BINOP_ADD_ASSIGN,
    BINOP_SUB_ASSIGN,
    BINOP_MUL_ASSIGN,
    BINOP_DIV_ASSIGN,
    BINOP_MOD_ASSIGN,
    BINOP_LSHIFT_ASSIGN,
    BINOP_RSHIFT_ASSIGN,
    BINOP_AND_ASSIGN,
    BINOP_XOR_ASSIGN,
    BINOP_OR_ASSIGN,
    BINOP_MUL,
    BINOP_LAND,
    BINOP_LOR,
    BINOP_CONCAT,
    BINOP_ARRAY_REF,
  };
  if (codes.find(node) != codes.end()) {
    return true;
  }
  return false;
}

}  // namespace fe
