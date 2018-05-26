// Reference model for sha256.karuta
#include <stdint.h>
#include <iostream>

using namespace std;

struct Vec {
  uint32_t a, b, c, d, e, f, g, h;
};

uint32_t k[64] = {
  0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
  0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
  0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
  0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
  0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
  0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
  0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
  0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

uint32_t W[64];
uint32_t buf[16];
uint32_t state[8];

uint32_t Ch(uint32_t x, uint32_t y, uint32_t z) {
  return z ^ (x & (y ^ z));
}

uint32_t Maj(uint32_t x, uint32_t y, uint32_t z) {
  return (x & y) | (z & (x | y));
}

uint32_t Ror(uint32_t v, int s) {
  uint32_t l = (v >> s);
  uint32_t h = (v << (32 - s));
  return l | h;
}

uint32_t e0(uint32_t x) {
  return Ror(x, 2) ^ Ror(x, 13) ^ Ror(x, 22);
}

uint32_t e1(uint32_t x) {
  return Ror(x, 6) ^ Ror(x, 11) ^ Ror(x, 25);
}

uint32_t s0(uint32_t x) {
  return Ror(x, 7) ^ Ror(x, 18) ^ (x >> 3);
}

uint32_t s1(uint32_t x) {
  return Ror(x, 17) ^ Ror(x, 19) ^ (x >> 10);
}

void init() {
  state[0] = 0x6a09e667;
  state[1] = 0xbb67ae85;
  state[2] = 0x3c6ef372;
  state[3] = 0xa54ff53a;
  state[4] = 0x510e527f;
  state[5] = 0x9b05688c;
  state[6] = 0x1f83d9ab;
  state[7] = 0x5be0cd19;
}

Vec iterate(Vec v, int idx) {
  uint32_t t1, t2;
  uint32_t a = v.a;
  uint32_t b = v.b;
  uint32_t c = v.c;
  uint32_t d = v.d;
  uint32_t e = v.e;
  uint32_t f = v.f;
  uint32_t g = v.g;
  uint32_t h = v.h;
  if (idx == 32) {
    cout << a << " " << b << " " << c << " " << d << " " << e << " " << f << " " << g << " " << h << "\n";
  }
  t1 = h + e1(e) + Ch(e,f,g) + k[idx] + W[idx];
  t2 = e0(a) + Maj(a,b,c);    d+=t1;    h=t1+t2;
  t1 = g + e1(d) + Ch(d,e,f) + k[idx + 1] + W[idx + 1];
  t2 = e0(h) + Maj(h,a,b);    c+=t1;    g=t1+t2;
  t1 = f + e1(c) + Ch(c,d,e) + k[idx + 2] + W[idx + 2];
  t2 = e0(g) + Maj(g,h,a);    b+=t1;    f=t1+t2;
  t1 = e + e1(b) + Ch(b,c,d) + k[idx + 3] + W[idx + 3];
  t2 = e0(f) + Maj(f,g,h);    a+=t1;    e=t1+t2;
  t1 = d + e1(a) + Ch(a,b,c) + k[idx + 4] + W[idx + 4];
  t2 = e0(e) + Maj(e,f,g);    h+=t1;    d=t1+t2;
  if (idx == 32) {
    cout << t1 << " " << t2 << " " << k[idx + 4] << " " << W[idx + 4] << "\n";
  }
  t1 = c + e1(h) + Ch(h,a,b) + k[idx + 5] + W[idx + 5];
  t2 = e0(d) + Maj(d,e,f);    g+=t1;    c=t1+t2;
  t1 = b + e1(g) + Ch(g,h,a) + k[idx + 6] + W[idx + 6];
  t2 = e0(c) + Maj(c,d,e);    f+=t1;    b=t1+t2;
  t1 = a + e1(f) + Ch(f,g,h) + k[idx + 7] + W[idx + 7];
  t2 = e0(b) + Maj(b,c,d);    e+=t1;    a=t1+t2;
  v.a = a;  v.b = b;  v.c = c;  v.d = d;
  v.e = e;  v.f = f;  v.g = g;  v.h = h;
  return v;
}

void transform() {
  for (int i = 0; i < 16; i++) {
    W[i] = buf[i];
  }
  for (int i = 16; i < 64; i++) {
    W[i] = s1(W[i-2]) + W[i-7] + s0(W[i-15]) + W[i-16];
    if (i == 34) {
      cout << i << ":" << W[i] << "\n";
      cout << W[i - 2] << " " << W[i-7] << " " << W[i-15] << " " << W[i-16] << "\n";
      cout << s1(W[i-2]) << " " << s0(W[i-15]) << "\n";
    }
  }
  Vec v;
  v.a = state[0];  v.b = state[1];  v.c = state[2];  v.d = state[3];
  v.e = state[4];  v.f = state[5];  v.g = state[6];  v.h = state[7];
  for (int i = 0; i < 64; i += 8) {
    v = iterate(v, i);
  }
  state[0] += v.a; state[1] += v.b; state[2] += v.c; state[3] += v.d;
  state[4] += v.e; state[5] += v.f; state[6] += v.g; state[7] += v.h;
}

void sha256(int blocks) {
  init();
  for (int i = 0; i < blocks; ++i) {
    transform();
  }
  for (int i = 0; i < 8; ++i) {
    cout << i << ":" << hex << state[i] << dec << "\n";
  }
}

int main(int argc, char **argv) {
  for (int i = 0; i < 8; ++i) {
    buf[i] = 0;
  }
  sha256(0);
  // sha256("")
  // e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855
  buf[0] = 1 << 31;
  sha256(1);
  return 0;
}
