#include "fe.h"

#include "messages.h"
#include "dump_stream.h"
#include "compiler/compiler.h"
#include "fe/builder.h"
#include "fe/common.h"
#include "fe/emitter.h"
#include "fe/method.h"
#include "fe/nodecode.h"
#include "fe/scanner.h"
#include "vm/method.h"
#include "vm/thread.h"
#include "vm/vm.h"
// This should be the last.
#include "fe/libparse_la-parser.hpp"

void z_yyerror(const char *msg) {
  std::cout << msg;
}

static sym_t sym_def, sym_enum, sym_import, sym_struct, sym_spawn;

static struct OperatorTableEntry op_tab[] = {
  {"<<=", K_ASSIGN, BINOP_LSHIFT_ASSIGN},
  {">>=", K_ASSIGN, BINOP_RSHIFT_ASSIGN},
  {"++", K_INC_DEC, UNIOP_POST_INC},
  {"--", K_INC_DEC, UNIOP_POST_DEC},
  {"<=", K_LG_COMPARE, BINOP_LTE},
  {">=", K_LG_COMPARE, BINOP_GTE},
  {"==", K_EQ_COMPARE, BINOP_EQ},
  {"!=", K_EQ_COMPARE, BINOP_NE},
  {"+=", K_ASSIGN, BINOP_ADD_ASSIGN},
  {"-=", K_ASSIGN, BINOP_SUB_ASSIGN},
  {"*=", K_ASSIGN, BINOP_MUL_ASSIGN},
  {"/=", K_ASSIGN, BINOP_DIV_ASSIGN},
  {"%=", K_ASSIGN, BINOP_MOD_ASSIGN},
  {"&=", K_ASSIGN, BINOP_AND_ASSIGN},
  {"^=", K_ASSIGN, BINOP_XOR_ASSIGN},
  {"|=", K_ASSIGN, BINOP_OR_ASSIGN},
  {"<<", K_SHIFT, BINOP_LSHIFT},
  {">>", K_SHIFT, BINOP_RSHIFT},
  {"&&", K_LOGIC_AND, BINOP_LAND},
  {"||", K_LOGIC_OR, BINOP_LOR},
  {"::", K_BIT_CONCAT, BINOP_CONCAT},
  {"<", K_LG_COMPARE, BINOP_LT},
  {">", K_LG_COMPARE, BINOP_GT},
  {"=", K_ASSIGN, BINOP_ASSIGN},
  {"#", '#', 0},
  {"|", '|', 0},
  {"~", '~', 0},
  {"!", '!', 0},
  {"^", '^', 0},
  {".", '.', 0},
  {",", ',', 0},
  {"(", '(', 0},
  {")", ')', 0},
  {"[", '[', 0},
  {"]", ']', 0},
  {"{", '{', 0},
  {"}", '}', 0},
  {";", ';', 0},
  {":", ':', 0},
  {"?", '?', 0},
  {"+", K_ADD_SUB, BINOP_ADD},
  {"-", K_ADD_SUB, BINOP_SUB},
  {"*", '*', BINOP_MUL},
  {"&", '&', 0},
  {0, 0, 0}
};

static int nfe_lookup_keyword(sym_t sym) {
  if (sym == sym_def) {
    return K_DEF;
  } else if (sym == sym_bool) {
    return K_BOOL;
  } else if (sym == sym_int) {
    return K_INT;
  } else if (sym == sym_object) {
    return K_OBJECT;
  } else if (sym == sym_thread) {
    return K_THREAD;
  } else if (sym == sym_channel) {
    return K_CHANNEL;
  } else if (sym == sym_goto) {
    return K_GOTO;
  } else if (sym == sym_return) {
    return K_RETURN;
  } else if (sym == sym_if) {
    return K_IF;
  } else if (sym == sym_else) {
    return K_ELSE;
  } else if (sym == sym_enum) {
    return K_ENUM;
  } else if (sym == sym_import) {
    return K_IMPORT;
  } else if (sym == sym_for) {
    return K_FOR;
  } else if (sym == sym_while) {
    return K_WHILE;
  } else if (sym == sym_do) {
    return K_DO;
  } else if (sym == sym_const) {
    return K_CONST;
  } else if (sym == sym_struct) {
    return K_STRUCT;
  } else if (sym == sym_switch) {
    return K_SWITCH;
  } else if (sym == sym_case) {
    return K_CASE;
  } else if (sym == sym_default) {
    return K_DEFAULT;
  } else if (sym == sym_break) {
    return K_BREAK;
  } else if (sym == sym_continue) {
    return K_CONTINUE;
  } else if (sym == sym_spawn) {
    return K_SPAWN;
  } else if (sym == sym_string) {
    return K_STRING;
  }
  return 0;
}

static void nfe_init_scanner_info(fe::ScannerInfo *s_info) {
  s_info->op_tab = op_tab;
  s_info->num_token = NUM;
  s_info->sym_token = SYM;
  s_info->str_token = STR;
}

static void nfe_init_syms() {
  sym_def = sym_lookup("def");
  sym_enum = sym_lookup("enum");
  sym_import = sym_lookup("import");
  sym_struct = sym_lookup("struct");
  sym_spawn = sym_lookup("spawn");
}

struct ZScannerInfo : fe::ScannerInfo {
  virtual int LookupKeyword(sym_t sym) const {
    return nfe_lookup_keyword(sym);
  }
};

int z_yylex() {
  scanner_token tk;
  tk.sub_op = 0;
  int r = ScannerInterface::GetToken(&tk);
  if (r == SYM) {
    z_yylval.sym = tk.sym;
  } else if (r == NUM) {
    z_yylval.num = tk.num;
  } else if (r == STR) {
    z_yylval.str = tk.str;
  } else if (r == K_ASSIGN || r == K_ADD_SUB ||
	     r == K_INC_DEC || r == K_LG_COMPARE ||
	     r == K_EQ_COMPARE || r == K_SHIFT) {
    z_yylval.num = tk.sub_op;
  } else {
    z_yylval.sym = sym_null;
  }
  return r;
}

namespace fe {

std::unique_ptr<fe::ScannerInfo> FE::scanner_info_;
string FE::dirname_;

FE::FE(bool dbg_parser, bool dbg_scanner, bool dbg_bytecode)
  : dbg_parser_(dbg_parser) {
  nfe_init_syms();
  scanner_info_.reset(new ZScannerInfo);
  nfe_init_scanner_info(scanner_info_.get());
  Scanner::Init(scanner_info_.get(), dbg_scanner);
  compiler::Compiler::SetByteCodeDebug(dbg_bytecode);
  vm::Thread::SetByteCodeDebug(dbg_bytecode);
}

void FE::Run(bool vanilla, const vector<string>& files) {
  NodePool::Init();

  vm::VM vm;
  if (!vanilla) {
    RunFile("default.n", &vm);
  }
  for (size_t i = 0; i < files.size(); ++i) {
    RunFile(files[i], &vm);
  }

  NodePool::Release();
}

vm::Method *FE::CompileFile(const string &file, bool dbg_parser,
			    vm::VM *vm) {
  Method *parse_tree = ReadFile(file);
  if (!parse_tree) {
    Message::os(Message::USER) << "Failed to load: " << file;
    return NULL;
  }
  DumpStream ds(cout);
  if (dbg_parser) {
    parse_tree->Dump(ds);
  }

  // Compile the top level.
  vm::Method *method =
    compiler::Compiler::CompileMethod(vm, vm->kernel_object_, parse_tree, NULL);

  return method;
}

void FE::RunFile(const string &file, vm::VM *vm) {
  vm::Method *method = CompileFile(file, dbg_parser_, vm);
  if (!method) {
    return;
  }
  vm->AddThreadFromMethod(NULL, method);
  vm->Run();
}

Method *FE::ReadFile(const string &file) {
  FileImage *im = GetFileImage(file);
  if (!im) {
    return NULL;
  }
  std::unique_ptr<Scanner> scanner(ScannerInterface::CreateScanner());
  scanner->SetFileImage(im);

  Emitter::BeginFunction(NULL);
  
  ::z_yyparse();
  scanner->ReleaseFileImage();

  MethodDecl decl = Emitter::EndFunction();
  return decl.method_;
}

FileImage *FE::GetFileImage(const string &fn) {
  vector<string> paths;
  Env::SearchPathList(fn.c_str(), &paths);
  if (!dirname_.empty()) {
    char c = fn[0];
    if (c != '/' && c != '.') {
      paths.push_back(dirname_ + "/" + fn);
    }
  }
  FileImage *im = NULL;
  for (const string &path : paths) {
    im = Scanner::CreateFileImage(path.c_str());
    if (im) {
      break;
    }
  }
  if (!im) {
    LOG(INFO) << "no image";
  }
  return im;
}

}  // namespace fe
