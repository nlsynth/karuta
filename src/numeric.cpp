// Copyright (C) Yusuke Tabata 2009
#include "numeric.h"

#include "nli.h"
#include "pool.h"

static const NumberWidth *g_int_width;
static const NumberWidth *g_nan_width;
static vector<NumberWidth *> NumberWidth_list;
static Pool<NumberWidth> pool;

Number::Number() {
  // NULL means default 32bits unsigned
  type = NULL;
}

const NumberWidth *NumberWidth::MakeInt(bool is_signed,
					int int_part, int frac_part) {
  vector<NumberWidth *>::iterator it;
  for (NumberWidth *nw : NumberWidth_list) {
    if (nw->is_signed == is_signed &&
	nw->int_width == int_part &&
	nw->frac_width == frac_part) {
      return nw;
    }
  }
  NumberWidth *nw = new NumberWidth();
  pool.Add(nw);
  nw->is_signed = is_signed;
  nw->int_width = int_part;
  nw->frac_width = frac_part;
  NumberWidth_list.push_back(nw);
  return nw;
}

const NumberWidth *Numeric::ValueWidth(const Number &src_num) {
  bool is_signed = false;
  Number num = src_num;
  Number zero;
  Numeric::MakeConst(0, 0, &zero);
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
  return NumberWidth::MakeInt(is_signed, w, 0);
}

const NumberWidth *NumberWidth::CommonWidth(const NumberWidth *w1,
					    const NumberWidth *w2) {
  if (!w1) {
    return w2;
  }
  if (!w2) {
    return w1;
  }
  bool is_signed;
  int int_part = w1->int_width;
  int frac_part = w2->frac_width;
  is_signed = w1->is_signed || w2->is_signed;
  if (w2->int_width > w1->int_width) {
    int_part = w2->int_width;
  }
  if (w2->frac_width > w1->frac_width) {
    frac_part = w2->frac_width;
  }
  return NumberWidth::MakeInt(is_signed, int_part, frac_part);
}

bool NumberWidth::IsWide(const NumberWidth *w1,
			 const NumberWidth *w2) {
  return w1->int_width >= w2->int_width;
}

int NumberWidth::GetWidth(const NumberWidth *w) {
  if (!w) {
    return 32;
  }
  return w->int_width;
}

void Numeric::Init() {
  g_int_width = NumberWidth::MakeInt(false, 32, 0);
  NumberWidth *nan = new NumberWidth();
  g_nan_width = nan;
  pool.Add(nan);
}

const NumberWidth *NumberWidth::Null() {
  return NumberWidth::MakeInt(false, 0, 0);
}

bool NumberWidth::IsNull(const NumberWidth *w) {
  return (w == NumberWidth::MakeInt(false, 0, 0));
}

bool NumberWidth::IsEqual(const NumberWidth *w1,
			  const NumberWidth *w2) {
  return (w1 == w2);
}

bool Numeric::IsZero(const Number &n) {
  return n.int_part == 0 && n.frac_part == 0;
}

const NumberWidth *NumberWidth::DefaultInt() {
  return g_int_width;
}

void NumberWidth::Dump(const NumberWidth *w,
		       ostream &os) {
  if (w == g_nan_width) {
    os << "<NaN>";
    return ;
  }
  if (!w) {
    os << "<>";
    return ;
  }
  os << "<";
  if (w->is_signed) {
    os << "+,";
  }
  os << w->int_width;
  if (w->frac_width) {
    os << "," << w->frac_width;
  }
  os << ">";
}

void Numeric::Add(const Number &x, const Number &y, Number *a) {
  a->int_part = x.int_part + y.int_part;
  a->frac_part = x.frac_part + y.frac_part;
}

void Numeric::Sub(const Number &x, const Number &y, Number *a) {
  a->int_part = x.int_part - y.int_part;
  a->frac_part = x.frac_part - y.frac_part;
}

void Numeric::MakeConst(uint64_t int_part, uint64_t frac_part, Number *num) {
  num->int_part = int_part;
  num->frac_part = frac_part;
}

uint64_t Numeric::GetInt(const Number &x) {
  return x.int_part;
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

void Numeric::FixupWidth(const NumberWidth *w, Number *num) {
  if (!w) {
    w = g_int_width;
  }
  uint64_t mask = 0;
  mask = ~mask;
  mask >>= (64 - w->int_width);
  num->int_part &= mask;
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
  res->type = NumberWidth::MakeInt(false, width, 0);
}

void Numeric::Concat(const Number &x, const Number &y, Number *a) {
  a->int_part = (x.int_part << y.type->int_width) + y.int_part;
  a->type = NumberWidth::MakeInt(false,
				 x.type->int_width + y.type->int_width, 0);
}
