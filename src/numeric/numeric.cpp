// Copyright (C) Yusuke Tabata 2009-2015
#include "numeric/numeric.h"

#include "nli.h"
#include "base/pool.h"

namespace numeric {

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

iroha::NumericWidth Op::ValueWidth(const iroha::Numeric &src_num) {
  bool is_signed = false;
  iroha::Numeric num = src_num;
  iroha::Numeric zero;
  Op::MakeConst(0, &zero);
  if (Compare(COMPARE_LT, num, zero)) {
    iroha::Numeric tmp = num;
    // negate
    Minus(tmp, &num);
    is_signed = true;
  }
  uint64_t n;
  n = num.GetValue();
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

bool Op::IsZero(const iroha::Numeric &n) {
  return n.GetValue() == 0;
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

void Op::Add(const iroha::Numeric &x, const iroha::Numeric &y, iroha::Numeric *a) {
  a->SetValue(x.GetValue() + y.GetValue());
}

void Op::Sub(const iroha::Numeric &x, const iroha::Numeric &y, iroha::Numeric *a) {
  a->SetValue(x.GetValue() - y.GetValue());
}

void Op::MakeConst(uint64_t value, iroha::Numeric *num) {
  num->SetValue(value);
}

void Op::Dump(const iroha::Numeric &num, ostream &os) {
  os << num.GetValue();
}

void Op::CalcBinOp(BinOp op, const iroha::Numeric &x, const iroha::Numeric &y,
		   iroha::Numeric *res) {
  switch (op) {
  case BINOP_LSHIFT:
  case BINOP_RSHIFT:
    {
      int c = y.GetValue();
      if (op == BINOP_LSHIFT) {
	res->SetValue(x.GetValue() << c);
      } else {
	res->SetValue(x.GetValue() >> c);
      }
    }
    break;
  case BINOP_AND:
    res->SetValue(x.GetValue() & y.GetValue());
    break;
  case BINOP_OR:
    res->SetValue(x.GetValue() | y.GetValue());
    break;
  case BINOP_XOR:
    res->SetValue(x.GetValue() ^ y.GetValue());
    break;
  case BINOP_MUL:
    res->SetValue(x.GetValue() * y.GetValue());
    break;
  }
}

void Op::Minus(const iroha::Numeric &x, iroha::Numeric *res) {
  *res = x;
  res->SetValue(res->GetValue() * -1);
}

bool Op::Compare(CompareOp op, const iroha::Numeric &x, const iroha::Numeric &y) {
  switch (op) {
  case COMPARE_LT:
    return x.GetValue() < y.GetValue();
  case COMPARE_GT:
    return x.GetValue() > y.GetValue();
  case COMPARE_EQ:
    return x.GetValue() == y.GetValue();
  default:
    break;
  }
  return true;
}

void Op::BitInv(const iroha::Numeric &num, iroha::Numeric *res) {
  *res = num;
  res->SetValue(~res->GetValue());
}

void Op::FixupWidth(const iroha::NumericWidth &w, iroha::Numeric *num) {
  num->SetValue(num->GetValue() & w.GetMask());
  num->type_ = w;
}

void Op::SelectBits(const iroha::Numeric &num, int h, int l,
		    iroha::Numeric *res) {
  *res = num;
  res->SetValue(0);
  int width = h - l + 1;
  for (int i = 0; i < width; ++i) {
    if ((1UL << (l + i)) & num.GetValue()) {
      res->SetValue(res->GetValue() | (1UL << i));
    }
  }
  res->type_ = *(WidthUtil::MakeIntPtr(false, width));
}

void Op::Concat(const iroha::Numeric &x, const iroha::Numeric &y,
		iroha::Numeric *a) {
  a->SetValue((x.GetValue() << y.type_.GetWidth()) + y.GetValue());
  a->type_ = *(WidthUtil::MakeIntPtr(false,
				     x.type_.GetWidth() + y.type_.GetWidth()));
}

}  // namespace numeric
