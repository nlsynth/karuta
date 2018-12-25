#include "fe/fe.h"

#include "base/dump_stream.h"
#include "base/status.h"
#include "compiler/compiler.h"
#include "fe/builder.h"
#include "fe/common.h"
#include "fe/emitter.h"
#include "fe/method.h"
#include "fe/nodecode.h"
#include "fe/scanner.h"
#include "vm/method.h"
#include "vm/object.h"
#include "vm/thread.h"
#include "vm/vm.h"
// This should be the last.
#include "fe/parser.h"

static sym_t sym_def, sym_func, sym_enum, sym_import, sym_var;

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
  {"/", '/', BINOP_DIV},
  {"&", '&', 0},
  {"@", '@', 0},
  {0, 0, 0}
};

int yylex() {
  ScannerToken tk;
  tk.sub_op = 0;
  int r = ScannerInterface::GetToken(&tk);
  if (r == SYM) {
    yylval.sym = tk.sym;
  } else if (r == NUM) {
    yylval.num = tk.num;
  } else if (r == STR) {
    yylval.str = tk.str;
  } else if (r == K_ASSIGN || r == K_ADD_SUB ||
	     r == K_INC_DEC || r == K_LG_COMPARE ||
	     r == K_EQ_COMPARE || r == K_SHIFT) {
    yylval.sub_op = tk.sub_op;
  } else {
    yylval.sym = sym_null;
  }
  return r;
}

void yyerror(const char *msg) {
  fe::ScannerPos pos;
  fe::ScannerInterface::GetPosition(&pos);
  ostream &os = Status::os(Status::USER_ERROR);
  os << "[" << msg << "] at line: " << pos.line;
  string fn = Emitter::GetFunctionName();
  if (!fn.empty()) {
    os << " in function " << fn;
  }
  os << " in " << pos.file;
}

namespace fe {

std::unique_ptr<fe::ScannerInfo> FE::scanner_info_;

int ScannerInfo::LookupKeyword(sym_t sym) const {
  if (sym == sym_def) {
    return K_DEF;
  }else if (sym == sym_func) {
    return K_FUNC;
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
  } else if (sym == sym_mailbox) {
    return K_MAILBOX;
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
  } else if (sym == sym_string) {
    return K_STRING;
  } else if (sym == sym_var) {
    return K_VAR;
  }
  return 0;
}

FE::FE(bool dbg_parser, bool dbg_scanner, bool dbg_bytecode)
  : dbg_parser_(dbg_parser) {
  InitSyms();
  scanner_info_.reset(new ScannerInfo);
  InitScannerInfo(scanner_info_.get());
  Scanner::Init(scanner_info_.get(), op_tab, dbg_scanner);
  compiler::Compiler::SetByteCodeDebug(dbg_bytecode);
  vm::Thread::SetByteCodeDebug(dbg_bytecode);
}

void FE::Run(bool vanilla, const vector<string>& files) {
  NodePool::Init();

  vm::VM vm;
  bool ok = true;
  if (!vanilla) {
    ok = RunFile("default-isynth.karuta", &vm);
  }
  if (ok) {
    for (size_t i = 0; i < files.size(); ++i) {
      ok = RunFile(files[i], &vm);
      if (!ok) {
	break;
      }
    }
  }
  vm.GC();

  NodePool::Release();
}

vm::Method *FE::CompileFile(const string &file, bool dbg_parser,
			    vm::VM *vm, vm::Object *obj) {
  Method *parse_tree = ReadFile(file);
  if (parse_tree == nullptr) {
    Status::os(Status::USER_ERROR) << "Failed to load: " << file;
    return nullptr;
  }
  DumpStream ds(cout);
  if (dbg_parser) {
    parse_tree->Dump(ds);
  }

  return
    compiler::Compiler::CompileParseTree(vm, obj, parse_tree);
}

bool FE::RunFile(const string &file, vm::VM *vm) {
  Env::SetCurrentFile(file);
  vm::Object *thr_obj = vm->kernel_object_->Clone();
  vm::Method *method = CompileFile(file, dbg_parser_, vm, thr_obj);
  if (method == nullptr || method->IsCompileFailure()) {
    return false;
  }
  vm->AddThreadFromMethod(nullptr, thr_obj, method, 0);
  vm->Run();
  return true;
}

Method *FE::ReadFile(const string &file) {
  FileImage *im = GetFileImage(file);
  if (!im) {
    return nullptr;
  }
  std::unique_ptr<Scanner> scanner(ScannerInterface::CreateScanner());
  scanner->SetFileImage(im);

  Emitter::BeginFunction(nullptr);
  
  int r = ::yyparse();
  scanner->ReleaseFileImage();

  MethodDecl decl = Emitter::EndFunction();
  if (Status::Check(Status::USER_ERROR, true)) {
    return nullptr;
  }
  if (r != 0) {
    return nullptr;
  }
  return decl.method_;
}

FileImage *FE::GetFileImage(const string &fn) {
  vector<string> paths;
  Env::SearchPathList(fn.c_str(), &paths);
  FileImage *im = nullptr;
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

void FE::InitSyms() {
  sym_def = sym_lookup("def");
  sym_enum = sym_lookup("enum");
  sym_func = sym_lookup("func");
  sym_import = sym_lookup("import");
  sym_var = sym_lookup("var");
}

void FE::InitScannerInfo(ScannerInfo *s_info) {
  s_info->num_token = NUM;
  s_info->sym_token = SYM;
  s_info->str_token = STR;
}

}  // namespace fe
