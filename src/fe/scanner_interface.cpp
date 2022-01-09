#include "fe/scanner_interface.h"

#include "fe/scanner.h"

namespace fe {

Scanner *ScannerInterface::CreateScanner() { return new Scanner; }

void ScannerInterface::GetPosition(ScannerPos *pos) {
  Scanner::current_scanner_->GetPosition(pos);
}

int ScannerInterface::GetToken(ScannerToken *tk) {
  int sub_op;
  int r = Scanner::current_scanner_->GetToken(&sub_op);
  tk->sub_op = 0;
  tk->str = nullptr;
  if (r == Scanner::s_info->num_token) {
    tk->num = Scanner::current_scanner_->GetNum();
    if (Scanner::dbg_scanner) {
      cout << "num=(" << tk->num.value << ")\n";
    }
  } else if (r == Scanner::s_info->sym_token) {
    int k;
    tk->sym = Scanner::current_scanner_->GetSym();
    if (Scanner::dbg_scanner) {
      cout << "sym=(" << sym_cstr(tk->sym) << ")\n";
    }
    k = Scanner::s_info->LookupKeyword(tk->sym);
    if (k) {
      return k;
    }
  } else if (r == Scanner::s_info->str_token) {
    tk->str = Scanner::current_scanner_->GetStr();
    if (Scanner::dbg_scanner) {
      cout << "str=(" << *(tk->str) << ")\n";
    }
  } else {
    if (Scanner::dbg_scanner) {
      cout << "op=(" << r << "(" << sub_op << "))\n";
    }
    tk->sub_op = sub_op;
  }
  return r;
}

void ScannerInterface::EnterSemiColonStatement() {
  if (Scanner::dbg_scanner) {
    cout << "enter_semicolon\n";
  }
  Scanner::current_scanner_->EnterSemiColonStatement();
}

void ScannerInterface::EndSemiColonStatement() {
  if (Scanner::dbg_scanner) {
    cout << "end_semicolon\n";
  }
  Scanner::current_scanner_->EndSemiColonStatement();
}

void ScannerInterface::InArrayElmDecl() {
  Scanner::current_scanner_->InArrayElmDecl();
}

void ScannerInterface::EndArrayElmDecl() {
  Scanner::current_scanner_->EndArrayElmDecl();
}

}  // namespace fe
