// Copyright (C) Yusuke Tabata 2009-2015
#include "numeric/numeric.h"

#include "nli.h"
#include "base/pool.h"

namespace numeric {

static const iroha::NumericWidth *g_int_width;
static vector<iroha::NumericWidth *> Width_list;
static Pool<iroha::NumericWidth> pool;

const iroha::NumericWidth *WidthUtil::MakeIntPtr(bool is_signed, int int_part) {
  for (auto *nw : Width_list) {
    if (nw->IsSigned() == is_signed &&
	nw->GetWidth() == int_part) {
      return nw;
    }
  }
  auto *nw = new iroha::NumericWidth(is_signed, int_part);
  pool.Add(nw);
  Width_list.push_back(nw);
  return nw;
}

const iroha::NumericWidth *WidthUtil::ToPtr(const iroha::NumericWidth &w) {
  return MakeIntPtr(w.IsSigned(), w.GetWidth());
}

const iroha::NumericWidth WidthUtil::DeRef(const iroha::NumericWidth *w) {
  if (w == nullptr) {
    return iroha::NumericWidth(false, 32);
  }
  return *w;
}

iroha::NumericWidth Numeric::ValueWidth(const Number &src_num) {
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
  return iroha::NumericWidth(is_signed, w);
}

const iroha::NumericWidth WidthUtil::CommonWidth(const iroha::NumericWidth &w1,
						 const iroha::NumericWidth &w2) {
  bool is_signed;
  int int_part = w1.GetWidth();
  is_signed = w1.IsSigned() || w2.IsSigned();
  if (w2.GetWidth() > w1.GetWidth()) {
    int_part = w2.GetWidth();
  }
  return iroha::NumericWidth(is_signed, int_part);
}

void Numeric::Init() {
  g_int_width = WidthUtil::MakeIntPtr(false, 32);
}

bool Numeric::IsZero(const Number &n) {
  return n.int_part == 0;
}

void WidthUtil::Dump(const iroha::NumericWidth &w,
		     ostream &os) {
  os << "<";
  if (w.IsSigned()) {
    os << "+,";
  }
  os << w.GetWidth();
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

void Numeric::FixupWidth(const iroha::NumericWidth &w, Number *num) {
  num->int_part &= w.GetMask();
  num->type_ = w;
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
  res->type_ = *(WidthUtil::MakeIntPtr(false, width));
}

void Numeric::Concat(const Number &x, const Number &y, Number *a) {
  a->int_part = (x.int_part << y.type_.GetWidth()) + y.int_part;
  a->type_ = *(WidthUtil::MakeIntPtr(false,
				     x.type_.GetWidth() + y.type_.GetWidth()));
}

}  // namespace numeric
