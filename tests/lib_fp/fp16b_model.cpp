// Reference model of the behavior of FP16B.
// 1bit sign
// 8bit exponent
// 7bit fraction
//

#include <iostream>
#include <math.h>

using namespace std;

int f2i(float f) {
  int *p = (int *)&f;
  return *p;
}

float bfloat2f(int b) {
  int bf = (b << 16);
  float *f = (float *)&bf;
  return *f;
}

class FP16B {
public:
  FP16B() {
    im_ = 0;
  }

  FP16B(float f) {
    im_ = 0;
    int fi = f2i(f);
    if (f < 0) {
      SetSign(true);
    }
    int e = (fi >> 23) & 255;
    // 8bits.
    SetExponent(e);
    // 23bits -> 7bits.
    int fr = fi & 0x7fffff;
    SetFraction(fr >> 16);
  }

  FP16B(int s, int e, int f) {
    im_ = 0;
    SetSign(s);
    SetExponent(e);
    SetFraction(f);
  }

  int GetSign() {
    if (im_ & 0x8000) {
      return 1;
    } else {
      return 0;
    }
  }
  void SetSign(int s) {
    if (s) {
      im_ |= 0x8000;
    } else {
      im_ &= (~((int)0x8000));
    }
  }
  int GetExponent() {
    return ((im_ >> 7) & 0xff);
  }
  void SetExponent(int e) {
    im_ &= (~((int)0x7f80));
    im_ |= (e << 7);
  }
  int GetFraction() {
    return (im_ & 0x7f);
  }
  void SetFraction(int f) {
    im_ &= (~((int)0x7f));
    im_ |= (f & 0x7f);
  }
  void Dump() {
    // exp=0: 0, -0, -- subnormal
    // exp=1: 2^-126
    // exp=127: 2^0
    // exp=254: 2^127
    // exp=255: +-inf -- NaN
    cout << "s=" << GetSign() << ", "
	 << "e=" << GetExponent() << ", "
	 << "f=" << GetFraction() << " ";
    int e = GetExponent();
    double v = 0;
    cout << "value=";
    if (e == 0) {
      int f = GetFraction();
      if (f == 0) {
	if (GetSign()) {
	  cout << "-";
	}
	cout << "ZERO";
      } else {
	cout << bfloat2f(im_);
      }
    } else if (e == 255) {
      int f = GetFraction();
      if (f == 0) {
	if (GetSign()) {
	  cout << "-";
	}
	cout << "inf";
      } else {
	cout << "NaN";
      }
    } else {
      cout << GetValue();
    }
    cout << "\n";
  }
  double GetValue() {
    return bfloat2f(im_);
  }
private:
  int im_;
};

bool Check(FP16B &n, bool s, int e, int f) {
  if (n.GetSign() == s && n.GetExponent() == e && n.GetFraction() == f) {
    return true;
  }
  FP16B en;
  en.SetSign(s);
  en.SetExponent(e);
  en.SetFraction(f);
  cout << "Failure! Expecting:";
  en.Dump();
  cout << "Got:";
  n.Dump();
  return false;
}

bool CheckFP(FP16B &n, float f) {
  FP16B m(f);
  return Check(n, m.GetSign(), m.GetExponent(), m.GetFraction());
}

FP16B MulP1(bool sign, int xe, int ye, int m) {
  int c = 0;
  if (m & 0x100) {
    c = 1;
  }
  int e = xe + ye - 127 + c;
  int f;
  if (c) {
    f = m >> 1;
  } else if (e <= 0 || e >= 255 || xe == 255 || ye == 255) {
    // Underflow, overflow.
    f = 0;
  } else {
    f = m;
  }
  if (e < 0 || xe == 0 || ye == 0) {
    // Underflow.
    e = 0;
  }
  if (e >= 255 || xe == 255 || ye == 255) {
    // Overflow.
    e = 255;
  }
  FP16B z;
  z.SetSign(sign);
  z.SetExponent(e);
  z.SetFraction(f);
  return z;
}

FP16B MulP0(FP16B x, FP16B y) {
  bool s = x.GetSign() ^ y.GetSign();
  int xe = x.GetExponent();
  int ye = y.GetExponent();
  int xf = x.GetFraction();
  int yf = y.GetFraction();
  if (xe > 0) {
    xf |= 0x80;
  }
  if (ye > 0) {
    yf |= 0x80;
  }
  int m = (xf * yf) >> 7;
  return MulP1(s, xe, ye, m);
}

FP16B Mul(FP16B x, FP16B y) {
  return MulP0(x, y);
}

FP16B AddSubP4(int r, bool xs, bool ys, int e, bool neg, bool xn, bool yn) {
  if (xn || yn) {
    // Shift up to 7 bits.
    if ((r & 0xe000) == 0) {
      e -= 4;
      r <<= 4;
    }
    if ((r & 0xc000) == 0) {
      e -= 2;
      r <<= 2;
    }
    if ((r & 0x8000) == 0) {
      e -= 1;
      r <<= 1;
    }
  }
  r >>= 7;
  r &= 0x7f;
  bool s = false;
  if (xn != yn) {
    if (yn) {
      s = neg ^ xs;
    } else {
      s = neg ^ ys;
    }
  } else {
    s = xs;
  }
  if (e < 0) {
    e = 0;
    r = 0;
  }
  FP16B z;
  z.SetSign(s);
  z.SetExponent(e);
  z.SetFraction(r);
  return z;
}

FP16B AddSubP3(int r, bool xs, bool ys, int e, bool xn, bool yn) {
  bool neg = false;
  if (xn == yn) {
    if (r & 0x8000) {
      // Carry.
      e++;
      if (e > 255) {
	e = 255;
      }
      r >>= 1;
    }
  } else {
    if (r & 0x8000) {
      // positive.
      r &= 0x7fff;
    } else {
      // negative.
      r = ~r;
      r = r + 1;
      r &= 0x7fff;
      neg = true;
    }
  }
  return AddSubP4(r, xs, ys, e, neg, xn, yn);
}

FP16B AddSubP2(bool xs, bool ys, int xr, int yr, int xe, bool xn, bool yn) {
  int r = xr + yr;
  if (xn || yn) {
    r += 1;
  }
  return AddSubP3(r, xs, ys, xe, xn, yn);
}

FP16B AddSubP1(FP16B x, FP16B y, bool xn, bool yn) {
  // x.Exponent() >= y.Exponent()
  int d = x.GetExponent() - y.GetExponent();
  int xr = x.GetFraction();
    if (x.GetExponent() > 0) {
    xr |= 0x100;
  }
  xr <<= 8;
  if (xn) {
    xr = ~xr;
    // 15 = 7 + 7 + 1
    xr &= 0x7fff;
  }
  int yr = y.GetFraction();
  if (y.GetExponent() > 0) {
    yr |= 0x100;
  }
  if (d <= 7) {
    yr <<= (7 - d);
  } else {
    yr = 0;
  }
  if (yn) {
    yr = ~yr;
    yr &= 0x7fff;
  }
  return AddSubP2(x.GetSign(), y.GetSign(), xr, yr, x.GetExponent(), xn, yn);
}

FP16B AddSubP0(FP16B x, FP16B y, bool is_sub) {
  bool neg_lhs = false;
  bool neg_rhs = false;
  if (is_sub) {
    y.SetSign(!y.GetSign());
  }
  FP16B lhs, rhs;
  if (x.GetExponent() < y.GetExponent()) {
    lhs = y;
    rhs = x;
  } else {
    lhs = x;
    rhs = y;
  }
  bool diff_sign = x.GetSign() ^ y.GetSign();
  if (diff_sign) {
    neg_lhs = lhs.GetSign();
    neg_rhs = rhs.GetSign();
  }
  return AddSubP1(lhs, rhs, neg_lhs, neg_rhs);
}

FP16B AddSub(FP16B x, FP16B y, bool is_sub) {
  return AddSubP0(x, y, is_sub);
}

void TestAdd() {
  cout << "-- Testing adder --\n";
}

void TestMul() {
  cout << "-- Testing multiplier --\n";
  FP16B a(1.25), b(1.25);
  FP16B c = Mul(a, b);
  c.Dump();
}

void TestOne() {
  cout << "-- Testing specific issue --\n";
  FP16B z(1.25);
  z.Dump();
}

int main(int argc, char **argv) {
  TestAdd();
  TestMul();
  TestOne();
  return 0;
}
