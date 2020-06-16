#include "fe/fe.h"

#include "base/dump_stream.h"
#include "base/status.h"
#include "base/util.h"
#include "compiler/compiler.h"
#include "fe/builder.h"
#include "fe/common.h"
#include "fe/emitter.h"
#include "fe/fe_method.h"
#include "fe/nodecode.h"
#include "fe/scanner.h"
#include "fe/scanner_interface.h"
#include "fe/scanner_pos.h"
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
    yylval.str = tk.str->c_str();
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
  os << "[" << msg << "]";
  string fn = Emitter::GetFunctionName();
  if (!fn.empty()) {
    os << " in function " << fn;
  }
  os << " " << pos.Format();
}

namespace fe {

std::unique_ptr<fe::ScannerInfo> FE::scanner_info_;

int ScannerInfo::LookupKeyword(sym_t sym) const {
  static map<string, int> kw = {
    {"as", K_AS},
    {"bool", K_BOOL},
    {"break", K_BREAK},
    {"case", K_CASE},
    {"channel", K_CHANNEL},
    {"const", K_CONST},
    {"continue", K_CONTINUE},
    {"def", K_DEF},
    {"default", K_DEFAULT},
    {"do", K_DO},
    {"else", K_ELSE},
    {"enum", K_ENUM},
    {"for", K_FOR},
    {"func", K_FUNC},
    {"goto", K_GOTO},
    {"if", K_IF},
    {"import", K_IMPORT},
    {"int", K_INT},
    {"mailbox", K_MAILBOX},
    {"module", K_MODULE},
    {"object", K_OBJECT},
    {"process", K_PROCESS},
    // ram and reg are experimental syntax sugar.
    // We'll make these separate keywords, if users like them.
    {"ram", K_SHARED},
    {"reg", K_SHARED},
    {"return", K_RETURN},
    {"shared", K_SHARED},
    {"string", K_STRING},
    {"switch", K_SWITCH},
    {"thread", K_THREAD},
    {"var", K_VAR},
    {"while", K_WHILE},
    {"with", K_WITH},
  };
  auto it = kw.find(sym_str(sym));
  if (it != kw.end()) {
    return it->second;
  }
  return 0;
}

FE::FE(bool dbg_parser, bool dbg_scanner, string dbg_bytecode)
  : dbg_parser_(dbg_parser) {
  InitSyms();
  ScannerInfo *s_info = BuildScannerInfo();
  scanner_info_.reset(s_info);
  Scanner::Init(s_info, op_tab, dbg_scanner);
  compiler::Compiler::SetByteCodeDebug(dbg_bytecode);
  vm::Thread::SetByteCodeDebug(dbg_bytecode);
}

void FE::Run(bool with_run, bool with_compile, bool vanilla,
	     const vector<string>& files) {
  NodePool::Init();

  vm::VM vm;
  bool ok = true;
  if (!vanilla) {
    ok = RunFile(true, false, false, "default-isynth.karuta", &vm);
  }
  if (ok) {
    for (size_t i = 0; i < files.size(); ++i) {
      ok = RunFile(false, with_run, with_compile, files[i], &vm);
      if (!ok) {
	break;
      }
    }
  }
  vm.GC();

  NodePool::Release();
}

vm::Method *FE::ImportFile(const string &file,
			   vm::VM *vm, vm::Object *thr_obj) {
  return CompileFile(file, true, false, false, false, vm, thr_obj);
}

vm::Method *FE::CompileFile(const string &file, bool is_import,
			    bool with_run, bool with_compile,
			    bool dbg_parser,
			    vm::VM *vm, vm::Object *obj) {
  Method *parse_tree = ReadFile(file, is_import);
  if (parse_tree == nullptr) {
    Status::os(Status::USER_ERROR) << "Failed to load: " << file;
    return nullptr;
  }
  DumpStream ds(cout);
  if (dbg_parser) {
    parse_tree->Dump(ds);
  }

  compiler::CompileOptions opts;
  if (with_compile) {
    string base = Util::BaseNameWithoutSuffix(file);
    opts.outputs.push_back(base + ".v");
    opts.outputs.push_back(base + ".iroha");
  }
  if (with_run) {
    opts.run = true;
  }
  return
    compiler::Compiler::CompileParseTree(vm, obj, opts, parse_tree);
}

bool FE::RunFile(bool is_import ,bool with_run, bool with_compile,
		 const string &file,
		 vm::VM *vm) {
  Env::SetCurrentFile(file);
  vm::Object *thr_obj = vm->kernel_object_->Clone();
  vm::Method *method = CompileFile(file, is_import,
				   with_run, with_compile,
				   dbg_parser_,
				   vm, thr_obj);
  if (method == nullptr || method->IsCompileFailure()) {
    return false;
  }
  vm::Thread *thr =
    vm->AddThreadFromMethod(/* parent */ nullptr, thr_obj, method, 0);
  string base = Util::BaseNameWithoutSuffix(file);
  thr->SetModuleName(base);
  vm->Run();
  return true;
}

Method *FE::ReadFile(const string &file, bool import) {
  FileImage *im = GetFileImage(file, import);
  if (!im) {
    return nullptr;
  }
  std::unique_ptr<Scanner> scanner(ScannerInterface::CreateScanner());
  scanner->SetFileImage(im);

  Emitter::BeginFunction(nullptr, false);
  
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

FileImage *FE::GetFileImage(const string &fn, bool is_import) {
  vector<string> paths;
  if (is_import) {
    string sfn = fn;
    if (Util::HasSuffix(fn)) {
      sfn = fn;
    } else {
      sfn = fn + ".karuta";
    }
    Env::SearchPathList(sfn.c_str(), &paths);
  } else {
    paths.push_back(fn);
  }
  FileImage *im = nullptr;
  for (const string &path : paths) {
    im = Scanner::CreateFileImage(path.c_str());
    if (im != nullptr) {
      break;
    }
  }
  if (im == nullptr) {
    if (fn.substr(0, 5) == "/tmp/") {
      // We should actually detect private /tmp somehow.
      Status::os(Status::INFO)
	<< "Karuta can't see the file under /tmp/ if the "
	<< "installation using private /tmp. "
	<< "If so, please place your file under /home";
    }
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

ScannerInfo *FE::BuildScannerInfo() {
  ScannerInfo *s_info = new ScannerInfo();
  s_info->num_token = NUM;
  s_info->sym_token = SYM;
  s_info->str_token = STR;
  return s_info;
}

}  // namespace fe
