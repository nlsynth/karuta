// -*- C++ -*-
#ifndef _numeric_numeric_h_
#define _numeric_numeric_h_

#include "nli.h"
#include "numeric/numeric_type.h"  // from iroha

namespace numeric {

class WidthUtil {
public:
  static const iroha::NumericWidth *MakeIntPtr(bool is_signed, int int_part);
  static const iroha::NumericWidth *ToPtr(const iroha::NumericWidth &w);
  static const iroha::NumericWidth DeRef(const iroha::NumericWidth *w);
  static const iroha::NumericWidth CommonWidth(const iroha::NumericWidth &w1,
					       const iroha::NumericWidth &w2);
  static void Dump(const iroha::NumericWidth &w, ostream &os);
  static bool IsEqual(const iroha::NumericWidth *w1, const iroha::NumericWidth *w2);
  // Checks if w1 is wider than w2.
  static bool IsWide(const iroha::NumericWidth *w1,
		     const iroha::NumericWidth *w2);
  static int GetWidthFromPtr(const iroha::NumericWidth *w);
};

class Number {
public:
  Number();
  void Dump(ostream &os) const;
  //
  uint64_t int_part;
  iroha::NumericWidth type_;
};

enum CompareOp {
  COMPARE_LT,
  COMPARE_GT,
  COMPARE_EQ,
};

enum BinOp {
  BINOP_LSHIFT,
  BINOP_RSHIFT,
  BINOP_AND,
  BINOP_OR,
  BINOP_XOR,
  BINOP_MUL,
};

class Numeric {
public:
  static void Init();

  static bool IsZero(const Number &n);
  // Gets required width to store given number.
  static iroha::NumericWidth ValueWidth(const Number &n);
  static void Add(const Number &x, const Number &y, Number *a);
  static void Sub(const Number &x, const Number &y, Number *a);
  static void Minus(const Number &num, Number *res);
  static bool Compare(enum CompareOp op, const Number &x, const Number &y);
  static void CalcBinOp(enum BinOp op, const Number &x, const Number &y,
			Number *res);
  static void MakeConst(uint64_t int_part, Number *num);
  static void Concat(const Number &x, const Number &y, Number *a);
  static void SelectBits(const Number &num, int h, int l, Number *res);
  static void BitInv(const Number &num, Number *res);
  // cuts upper bits
  static void FixupWidth(const iroha::NumericWidth &w, Number *num);
  static uint64_t GetInt(const Number &x);
};

}  // namespace numeric

#endif  // _numeric_numeric_h_
