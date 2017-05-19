// Copyright (C) Yusuke Tabata 2009-2015
#include "numeric/numeric.h"

#include "nli.h"
#include "base/pool.h"

namespace numeric {

static const Width *g_int_width;
static vector<Width *> Width_list;
static Pool<Width> pool;

const Width *Width::MakeIntPtr(bool is_signed, int int_part) {
  vector<Width *>::iterator it;
  for (Width *nw : Width_list) {
    if (nw->IsSigned() == is_signed &&
	nw->GetWidth() == int_part) {
      return nw;
    }
  }
  Width *nw = new Width(is_signed, int_part);
  pool.Add(nw);
  Width_list.push_back(nw);
  return nw;
}

const Width *Numeric::ValueWidth(const Number &src_num) {
  bool is_signed = false;
  Number num = src_num;
  Number zero;
  Numeric::MakeConst(0, &zero);
  if (Compare(COMPARE_LT, num, zero)) {
    Number tmp = num;
    // negate
    Minus(tmp, &num);
    is_signed = true;
  }
  uint64_t n;
  n = Numeric::GetInt(num);
  int w;
  for (w = 0; n > 0; w++, n /= 2);
  return Width::MakeIntPtr(is_signed, w);
}

const Width *Width::CommonWidth(const Width *w1,
				const Width *w2) {
  if (!w1) {
    return w2;
  }
  if (!w2) {
    return w1;
  }
  bool is_signed;
  int int_part = w1->GetWidth();
  is_signed = w1->IsSigned() || w2->IsSigned();
  if (w2->GetWidth() > w1->GetWidth()) {
    int_part = w2->GetWidth();
  }
  return Width::MakeIntPtr(is_signed, int_part);
}

bool Width::IsWide(const Width *w1,
		   const Width *w2) {
  return w1->GetWidth() >= w2->GetWidth();
}

int Width::GetWidthFromPtr(const Width *w) {
  if (!w) {
    return 32;
  }
  return w->GetWidth();
}

void Numeric::Init() {
  g_int_width = Width::MakeIntPtr(false, 32);
}

Width::Width(bool is_signed, int width) {
  SetIsSigned(is_signed);
  SetWidth(width);
}

bool Width::IsEqual(const Width *w1,
		    const Width *w2) {
  return (w1 == w2);
}

bool Numeric::IsZero(const Number &n) {
  return n.int_part == 0;
}

void Width::Dump(const Width *w,
		 ostream &os) {
  if (!w) {
    os << "<>";
    return ;
  }
  os << "<";
  if (w->IsSigned()) {
    os << "+,";
  }
  os << w->GetWidth();
  os << ">";
}

void Numeric::Add(const Number &x, const Number &y, Number *a) {
  a->int_part = x.int_part + y.int_part;
}

void Numeric::Sub(const Number &x, const Number &y, Number *a) {
  a->int_part = x.int_part - y.int_part;
}

void Numeric::MakeConst(uint64_t int_part, Number *num) {
  num->int_part = int_part;
}

uint64_t Numeric::GetInt(const Number &x) {
  return x.int_part;
}

Number::Number() {
}

void Number::Dump(ostream &os) const {
  os << int_part;
}

void Numeric::CalcBinOp(BinOp op, const Number &x, const Number &y,
			Number *res) {
  switch (op) {
  case BINOP_LSHIFT:
  case BINOP_RSHIFT:
    {
      int c = Numeric::GetInt(y);
      if (op == BINOP_LSHIFT) {
	res->int_part = x.int_part << c;
      } else {
	res->int_part = x.int_part >> c;
      }
    }
    break;
  case BINOP_AND:
    res->int_part = x.int_part & y.int_part;
    break;
  case BINOP_OR:
    res->int_part = x.int_part | y.int_part;
    break;
  case BINOP_XOR:
    res->int_part = x.int_part ^ y.int_part;
    break;
  case BINOP_MUL:
    res->int_part = x.int_part * y.int_part;
    break;
  }
}

void Numeric::Minus(const Number &x, Number *res) {
  *res = x;
  res->int_part *= -1;
}

bool Numeric::Compare(CompareOp op, const Number &x, const Number &y) {
  switch (op) {
  case COMPARE_LT:
    return x.int_part < y.int_part;
  case COMPARE_GT:
    return x.int_part > y.int_part;
  case COMPARE_EQ:
    return x.int_part == y.int_part;
  default:
    break;
  }
  return true;
}

void Numeric::BitInv(const Number &num, Number *res) {
  *res = num;
  res->int_part = ~res->int_part;
}

void Numeric::FixupWidth(const Width *w, Number *num) {
  if (!w) {
    w = g_int_width;
  }
  num->int_part &= w->GetMask();
  num->type = w;
}

void Numeric::SelectBits(const Number &num, int h, int l, Number *res) {
  *res = num;
  res->int_part = 0;
  int width = h - l + 1;
  for (int i = 0; i < width; ++i) {
    if ((1UL << (l + i)) & num.int_part) {
      res->int_part |= (1UL << i);
    }
  }
  res->type = Width::MakeIntPtr(false, width);
}

void Numeric::Concat(const Number &x, const Number &y, Number *a) {
  a->int_part = (x.int_part << y.type->GetWidth()) + y.int_part;
  a->type = Width::MakeIntPtr(false,
			      x.type->GetWidth() + y.type->GetWidth());
}

}  // namespace numeric
