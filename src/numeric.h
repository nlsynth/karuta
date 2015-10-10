// -*- C++ -*-
#ifndef _numeric_h_
#define _numeric_h_

#include "nli.h"

class NumberWidth {
public:
  // signedness affects only for printing.
  bool is_signed;
  int int_width;
  int frac_width;

public:
  static const NumberWidth *Null();
  static const NumberWidth *DefaultInt();
  static const NumberWidth *MakeInt(bool is_signed,
				    int int_part, int frac_part);
  static const NumberWidth *CommonWidth(const NumberWidth *w1,
					const NumberWidth *w2);
  static void Dump(const NumberWidth *w, ostream &os);
  static bool IsNull(const NumberWidth *w);
  static bool IsEqual(const NumberWidth *w1, const NumberWidth *w2);
  // Checks if w1 is wider than w2.
  static bool IsWide(const NumberWidth *w1, const NumberWidth *w2);
  static int GetWidth(const NumberWidth *w);
};

class Number {
public:
  Number();
  void Dump(ostream &os) const;
  //
  uint64_t int_part;
  uint64_t frac_part;
  const NumberWidth *type;
};

class Numeric {
public:
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

  static void Init();

  static bool IsZero(const Number &n);
  // Gets required width to store given number.
  static const NumberWidth *ValueWidth(const Number &n);
  static void Add(const Number &x, const Number &y, Number *a);
  static void Sub(const Number &x, const Number &y, Number *a);
  static void Minus(const Number &num, Number *res);
  static bool Compare(enum CompareOp op, const Number &x, const Number &y);
  static void CalcBinOp(enum BinOp op, const Number &x, const Number &y,
			Number *res);
  static void MakeConst(uint64_t int_part, uint64_t frac_part, Number *num);
  static void Concat(const Number &x, const Number &y, Number *a);
  static void SelectBits(const Number &num, int h, int l, Number *res);
  static void BitInv(const Number &num, Number *res);
  // cuts upper bits
  static void FixupWidth(const NumberWidth *w, Number *num);
  static uint64_t GetInt(const Number &x);
};

#endif  // _numeric_h_
