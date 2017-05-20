// -*- C++ -*-
#ifndef _numeric_numeric_h_
#define _numeric_numeric_h_

#include "nli.h"
#include "numeric/numeric_type.h"  // from iroha

namespace numeric {

class WidthUtil {
public:
  static const iroha::NumericWidth CommonWidth(const iroha::NumericWidth &w1,
					       const iroha::NumericWidth &w2);
  static void Dump(const iroha::NumericWidth &w, ostream &os);

  // Used by code in fe/.
  static const iroha::NumericWidth *MakeIntPtr(bool is_signed, int int_part);
  static const iroha::NumericWidth *ToPtr(const iroha::NumericWidth &w);
  static const iroha::NumericWidth DeRef(const iroha::NumericWidth *w);
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

class Op {
public:
  static void Dump(const iroha::Numeric &num, ostream &os);
  static bool IsZero(const iroha::Numeric &n);
  // Gets required width to store given number.
  static iroha::NumericWidth ValueWidth(const iroha::Numeric &n);
  static void Add(const iroha::Numeric &x, const iroha::Numeric &y, iroha::Numeric *a);
  static void Sub(const iroha::Numeric &x, const iroha::Numeric &y, iroha::Numeric *a);
  static void Minus(const iroha::Numeric &num, iroha::Numeric *res);
  static bool Compare(enum CompareOp op, const iroha::Numeric &x, const iroha::Numeric &y);
  static void CalcBinOp(enum BinOp op, const iroha::Numeric &x, const iroha::Numeric &y,
			iroha::Numeric *res);
  static void MakeConst(uint64_t value, iroha::Numeric *num);
  static void Concat(const iroha::Numeric &x, const iroha::Numeric &y, iroha::Numeric *a);
  static void SelectBits(const iroha::Numeric &num, int h, int l, iroha::Numeric *res);
  static void BitInv(const iroha::Numeric &num, iroha::Numeric *res);
  // cuts upper bits
  static void FixupWidth(const iroha::NumericWidth &w, iroha::Numeric *num);
};

}  // namespace numeric

#endif  // _numeric_numeric_h_
