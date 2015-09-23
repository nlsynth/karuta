// Reference implementation of Mersenne twister
#include <iostream>
#include <stdint.h>

using namespace std;

class MT {
public:
  MT();
  void Init(int seed);
  void Dump() const;
  unsigned int ExtractNumber();
  //private:
  void GenerateNumbers();
  unsigned int index_;
  unsigned long mt_[624];
};

MT::MT() {
}

void MT::Init(int seed) {
  index_ = 0;
  mt_[0] = seed;
  for (int i = 1; i < 624; ++i) {
    int64_t v = mt_[i-1] ^ ((mt_[i-1] >> 30));
    int64_t n = (0x6c078965 * v + i); // 0x6c078965
    mt_[i] = n;
  }
}

void MT::Dump() const {
  cout << "index=" << index_ << "\n";
  for (int i = 0; i < 624; ++i) {
    if ((i % 8) == 0) {
      cout << i;
    }
    cout << " " << mt_[i];
    if ((i % 8) == 7) {
      cout << "\n";
    }
  }
}

unsigned int MT::ExtractNumber() {
  if (index_ == 0) {
    GenerateNumbers();
  }
  unsigned int y = mt_[index_];
  index_ = (index_ + 1) % 624;
  y = y ^ (y >> 11);
  y = y ^ ((y << 7) & 2636928640UL);
  y = y ^ ((y << 15) & 4022730752UL);
  y = y ^ (y >> 18);
  return y;
}

void MT::GenerateNumbers() {
  for (int i = 0; i < 624; ++i) {
    unsigned int y = (mt_[i] & 0x80000000) | (mt_[(i + 1) % 624] & 0x7fffffff);
    //cout << i << " " << mt_[i] << endl;
    mt_[i] = mt_[(i + 397) % 624] ^ (y >> 1);
    if ((y % 2) == 1) {
      mt_[i] = mt_[i] ^ 2567483615UL;
    }
    cout << i << " " << mt_[i] << endl;
  }
}

int main(int argc, char **argv) {
  MT mt;
  mt.Init(0);
  mt.Dump();
  //mt.GenerateNumbers();
  cout << mt.ExtractNumber() << "\n";
  return 0;
}
