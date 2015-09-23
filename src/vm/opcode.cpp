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
    // Read/Write.
    {vm::OP_ARRAY_READ, "array_read"},
    {vm::OP_ARRAY_WRITE, "array_write"},
    {vm::OP_CHANNEL_READ, "channel_read"},
    {vm::OP_CHANNEL_WRITE, "channel_write"},
    {vm::OP_MEMBER_READ, "member_read"},
    {vm::OP_MEMBER_WRITE, "member_write"},
    {vm::OP_MEMORY_READ, "memory_read"},
    {vm::OP_MEMORY_WRITE, "memory_write"},
    // Toplevel.
    {vm::OP_IMPORT, "import"},
    {vm::OP_SPAWN, "spawn"},
    {vm::OP_FUNCDECL, "funcdecl"},
    {vm::OP_VARDECL, "vardecl"},
    {vm::OP_CHANNEL_DECL, "channel_decl"},
    {vm::OP_THREAD_DECL, "thread_decl"},
    {vm::OP_GENERIC_READ, "generic_read"},
    {vm::OP_GENERIC_WRITE, "generic_write"},
  };
  auto it = codes.find(node);
  if (it == codes.end()) {
    return "unknown";
  }
  return it->second;
}

}  // namespace vm
