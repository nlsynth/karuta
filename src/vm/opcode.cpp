#include "vm/opcode.h"

#include <map>

using std::map;

namespace vm {

const char *OpCodeName(enum OpCode node) {
  static map<vm::OpCode, const char *> codes = {
      {vm::OP_INVALID, "invalid"},
      {vm::OP_NUM, "num"},
      {vm::OP_STR, "str"},
      {vm::OP_ELM_REF, "elm_ref"},
      {vm::OP_LOAD_OBJ, "load_obj"},
      {vm::OP_FUNCALL, "funcall"},
      {vm::OP_BIT_RANGE, "bit_range"},
      {vm::OP_FUNCALL_DONE, "funcall_done"},
      {vm::OP_ADD, "add"},
      {vm::OP_SUB, "sub"},
      {vm::OP_ASSIGN, "assign"},
      {vm::OP_LT, "lt"},
      {vm::OP_GT, "gt"},
      {vm::OP_LTE, "lte"},
      {vm::OP_GTE, "gte"},
      {vm::OP_EQ, "eq"},
      {vm::OP_NE, "ne"},
      {vm::OP_AND, "and"},
      {vm::OP_OR, "or"},
      {vm::OP_XOR, "xor"},
      {vm::OP_LSHIFT, "lshift"},
      {vm::OP_RSHIFT, "rshift"},
      {vm::OP_MUL, "mul"},
      {vm::OP_DIV, "div"},
      {vm::OP_LAND, "land"},
      {vm::OP_LOR, "lor"},
      {vm::OP_CONCAT, "concat"},
      {vm::OP_PLUS, "plus"},
      {vm::OP_MINUS, "minus"},
      {vm::OP_POST_INC, "post_inc"},
      {vm::OP_PRE_INC, "pre_inc"},
      {vm::OP_POST_DEC, "post_dec"},
      {vm::OP_PRE_DEC, "pre_dec"},
      {vm::OP_BIT_INV, "bit_inv"},
      {vm::OP_LOGIC_INV, "logic_inv"},
      {vm::OP_IF, "if"},
      {vm::OP_GOTO, "goto"},
      {vm::OP_NOP, "nop"},
      {vm::OP_YIELD, "yield"},
      // Read/Write.
      {vm::OP_ARRAY_READ, "array_read"},
      {vm::OP_ARRAY_WRITE, "array_write"},
      {vm::OP_MEMBER_READ, "member_read"},
      {vm::OP_MEMBER_WRITE, "member_write"},
      // Toplevel.
      {vm::OP_TL_IMPORT, "import"},
      {vm::OP_TL_FUNCDECL, "funcdecl"},
      {vm::OP_TL_VARDECL, "vardecl"},
      {vm::OP_TL_CHANNEL_DECL, "channel_decl"},
      {vm::OP_TL_THREAD_DECL, "thread_decl"},
      {vm::OP_TL_SET_TYPE_OBJECT, "set_type_object"},
      {vm::OP_TL_PUSH_CURRENT_OBJECT, "push_current_object"},
      {vm::OP_TL_POP_CURRENT_OBJECT, "pop_current_object"},
      {vm::OP_TL_FUNCALL_WITH_CHECK, "funcall_with_check"},
      {vm::OP_TL_FUNCALL_DONE_WITH_CHECK, "funcall_done_with_check"},
      {vm::OP_TL_ARRAY_WRITE_WITH_CHECK, "array_write_with_check"},
      {vm::OP_TL_MEMBER_READ_WITH_CHECK, "member_read_with_check"},
      {vm::OP_TL_ADD_MAY_WITH_TYPE, "add_may_with_type"},
      {vm::OP_TL_SUB_MAY_WITH_TYPE, "sub_may_with_type"},
      {vm::OP_TL_MUL_MAY_WITH_TYPE, "mul_may_with_type"},
      {vm::OP_TL_DIV_MAY_WITH_TYPE, "div_may_with_type"},
      {vm::OP_TL_MAY_WITH_TYPE_DONE, "may_with_type_done"},
  };
  auto it = codes.find(node);
  if (it == codes.end()) {
    return "unknown";
  }
  return it->second;
}

}  // namespace vm
