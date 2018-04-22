// Reference model of the behavior of FP16.
//

#include <iostream>
#include <math.h>

using namespace std;

int f2i(float f) {
  int *p = (int *)&f;
  return *p;
}

class FP16 {
public:
  FP16() {
    im_ = 0;
  }
  FP16(float f) {
    im_ = 0;
    int fi = f2i(f);
    if (f < 0) {
      SetSign(true);
    }
    int e = (fi >> 23) & 255;
    // 127 - 15
    SetExponent(e - 112);
    // 23bits -> 10
    int fr = fi & 0x7fffff;
    SetFraction(fr >> 13);
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
    return ((im_ >> 10) & 0x1f);
  }
  void SetExponent(int e) {
    im_ &= (~((int)0x7c00));
    im_ |= (e << 10);
  }
  int GetFraction() {
    return (im_ & 0x3ff);
  }
  void SetFraction(int f) {
    im_ &= (~((int)0x3ff));
    im_ |= (f & 0x3ff);
  }
  void Dump() {
    // exp=0: 0, -0, -- subnormal
    // exp=1: 2^-14
    // exp=15: 2^0
    // exp=30: 2^15
    // exp=31: +-inf -- NaN
    cout << "s=" << GetSign() << ", "
	 << "e=" << GetExponent() << ", "
	 << "f=" << GetFraction() << " ";
    int e = GetExponent();
    double v = 0;
    cout << "value=";
    if (e == 0) {
      double f = GetFraction();
      if (f == 0) {
	if (GetSign()) {
	  cout << "-";
	}
	cout << "ZERO";
      } else {
	if (GetSign()) {
	  cout << "-";
	}
	f /= 1024.0f;
	f /= 16384.0f;
	cout << f;
      }
    } else if (e == 31) {
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
    double f = GetFraction();
    double v = 1 + (f / 1024.0f);
    int e = GetExponent();
    v = v * pow(2, e - 15);
    if (GetSign()) {
      v = -v;
    }
    return v;
  }
private:
  int im_;
};

FP16 MulP1(bool sign, int xe, int ye, int m) {
  FP16 z;
  int c = 0;
  if (m & 0x800) {
    c = 1;
  }
  int e = xe + ye - 15 + c;
  int f;
  if (c) {
    f = m >> 1;
  } else {
    f = m;
  }
  z.SetSign(sign);
  z.SetExponent(e);
  z.SetFraction(f);
  return z;
}

FP16 MulP0(FP16 x, FP16 y) {
  FP16 z;
  bool s = x.GetSign() ^ y.GetSign();
  int xe = x.GetExponent();
  int ye = y.GetExponent();
  int xf = x.GetFraction();
  int yf = y.GetFraction();
  if (xe > 0) {
    xf |= 0x400;
  }
  if (ye > 0) {
    yf |= 0x400;
  }
  int m = (xf * yf) >> 10;
  return MulP1(s, xe, ye, m);
}

FP16 Mul(FP16 x, FP16 y) {
  return MulP0(x, y);
}

FP16 AddSubP4(int r, bool xs, bool ys, int e, bool neg, bool xn, bool yn) {
  if (xn || yn) {
    if ((r & 0x1fe000) == 0) {
      e -= 8;
      r <<= 8;
    }
    if ((r & 0x1e0000) == 0) {
      e -= 4;
      r <<= 4;
    }
    if ((r & 0x180000) == 0) {
      e -= 2;
      r <<= 2;
    }
    if ((r & 0x100000) == 0) {
      e -= 1;
      r <<= 1;
    }
  }
  r >>= 10;
  r &= 0x3ff;
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
  FP16 z;
  z.SetSign(s);
  z.SetExponent(e);
  z.SetFraction(r);
  return z;
}

FP16 AddSubP3(int r, bool xs, bool ys, int e, bool xn, bool yn) {
  bool neg = false;
  if (xn == yn) {
    if (r & 0x200000) {
      // Carry.
      e++;
      if (e > 31) {
	e = 31;
      }
      r >>= 1;
    }
  } else {
    if (r & 0x200000) {
      // positive.
      r &= 0x1fffff;
    } else {
      // negative.
      r = ~r;
      r = r + 1;
      r &= 0x1fffff;
      neg = true;
    }
  }
  return AddSubP4(r, xs, ys, e, neg, xn, yn);
}

FP16 AddSubP2(bool xs, bool ys, int xr, int yr, int xe, bool xn, bool yn) {
  int r = xr + yr;
  if (xn || yn) {
    r += 1;
  }
  return AddSubP3(r, xs, ys, xe, xn, yn);
}

FP16 AddSubP1(FP16 x, FP16 y, bool xn, bool yn) {
  // x.Exponent() >= y.Exponent()
  int d = x.GetExponent() - y.GetExponent();
  int xr = x.GetFraction();
    if (x.GetExponent() > 0) {
    xr |= 0x400;
  }
  xr <<= 10;
  if (xn) {
    xr = ~xr;
    xr &= 0x1fffff;
  }
  int yr = y.GetFraction();
  if (y.GetExponent() > 0) {
    yr |= 0x400;
  }
  if (d <= 10) {
    yr <<= (10 - d);
  } else {
    yr = 0;
  }
  if (yn) {
    yr = ~yr;
    yr &= 0x1fffff;
  }
  return AddSubP2(x.GetSign(), y.GetSign(), xr, yr, x.GetExponent(), xn, yn);
}

FP16 AddSubP0(FP16 x, FP16 y, bool is_sub) {
  bool neg_lhs = false;
  bool neg_rhs = false;
  if (is_sub) {
    y.SetSign(!y.GetSign());
  }
  FP16 lhs, rhs;
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

FP16 AddSub(FP16 x, FP16 y, bool is_sub) {
  return AddSubP0(x, y, is_sub);
}

bool Check(FP16 &n, bool s, int e, int f) {
  if (n.GetSign() == s && n.GetExponent() == e && n.GetFraction() == f) {
    return true;
  }
  FP16 en;
  en.SetSign(s);
  en.SetExponent(e);
  en.SetFraction(f);
  cout << "Failure! Expecting:";
  en.Dump();
  cout << "Got:";
  n.Dump();
  return false;
}

bool CheckFP(FP16 &n, float f) {
  FP16 m(f);
  return Check(n, m.GetSign(), m.GetExponent(), m.GetFraction());
}

void TestMul() {
  cout << "-- Testing multiplier --\n";
  FP16 z = Mul(FP16(1.5), FP16(1.5));
  if (!CheckFP(z, 2.25)) {
  }
}

void TestAdd() {
  cout << "-- Testing adder --\n";
  FP16 fp;
  fp.SetExponent(15);
  fp.SetFraction(256);

  // 1.25 + 1.25
  FP16 z = AddSub(fp, fp, false);
  if (!Check(z, false, 16, 256)) {
  }
  z = AddSub(fp, z, false);
  // 2.5 + 1.25
  if (!Check(z, false, 16, 896)) {
  }

  // 1.25 + 0.03125.
  FP16 x;
  x.SetExponent(10);
  x.SetFraction(0);
  z = AddSub(fp, x, false);
  if (!Check(z, false, 15, 288)) {
  }

  // 1.25 + - 1.5
  z = AddSub(FP16(1.25), FP16(-1.5), false);
  if (!CheckFP(z, -0.25)) {
  }
  // 1.5 +  -1.25
  z = AddSub(FP16(1.5), FP16(-1.25), false);
  if (!CheckFP(z, 0.25)) {
  }

  // -1.5 + 1.25
  z = AddSub(FP16(-1.5), FP16(1.25), false);
  if (!CheckFP(z, -0.25)) {
  }
  // -1.25 + 1.5
  z = AddSub(FP16(-1.25), FP16(1.5), false);
  if (!CheckFP(z, 0.25)) {
  }
  // -1.25 + - 1.5
  z = AddSub(FP16(-1.25), FP16(-1.5), false);
  if (!CheckFP(z, -2.75)) {
  }
}

void TestSub() {
  cout << "-- Testing subtractor --\n";
  FP16 z = AddSub(FP16(1.25), FP16(0.0625), true);
  if (!CheckFP(z, 1.1875)) {
  }

  z = AddSub(FP16(1.25), FP16(2.0), true);
  if (!CheckFP(z, -0.75)) {
  }

  z = AddSub(FP16(-1.25), FP16(-2.0), true);
  if (!CheckFP(z, 0.75)) {
  }

  z = AddSub(FP16(-1.25), FP16(-0.5), true);
  if (!CheckFP(z, -0.75)) {
  }
}

void TestOne() {
  cout << "-- Testing specific issue --\n";
}

int main(int argc, char **argv) {
  TestMul();
  TestAdd();
  TestSub();

  TestOne();
  return 0;
}
