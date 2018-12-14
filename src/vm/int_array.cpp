// Memory model for interpreted Karuta
#include "vm/int_array.h"

#include "numeric/numeric_op.h"  // from iroha

namespace vm {

static const int PAGE_SIZE = 1024;

struct IntArrayPage {
  IntArrayPage(const iroha::NumericWidth &w);
  iroha::Numeric data[PAGE_SIZE];
};

IntArrayPage::IntArrayPage(const iroha::NumericWidth &width) {
  int i;
  for (i = 0; i < PAGE_SIZE; i++) {
    data[i].SetValue0(0);
    data[i].type_ = width;
  }
}

IntArray::~IntArray() {
  // do nothing
}

IntArray *IntArray::Create(const iroha::NumericWidth &data_width,
			   const vector<uint64_t> &shape) {
  return new IntArray(data_width, shape);
}

IntArray *IntArray::Copy(const IntArray *src) {
  const IntArray *si = (const IntArray *)src;
  return new IntArray(si);
}

IntArray::IntArray(const iroha::NumericWidth &width,
		   const vector<uint64_t> &shape)
  : shape_(shape), data_width_(width) {
  size_ = 1;
  for (uint64_t s : shape_) {
    size_ *= s;
  }
}

IntArray::IntArray(const IntArray *src) {
  data_width_ = src->GetDataWidth();
  size_ = src->GetLength();
  for (const auto it : src->pages_) {
    IntArrayPage *p = new IntArrayPage(data_width_);
    *p = *(it.second);
    pages_[it.first] = p;
  }
}

void IntArray::Write(const vector<uint64_t> &indexes, const iroha::Numeric &data) {
  WriteSingle(GetIndex(indexes), data);
}

void IntArray::WriteSingle(uint64_t addr, const iroha::Numeric &data) {
  IntArrayPage *p = FindPage(addr);
  int offset = (addr % PAGE_SIZE);
  p->data[offset] = data;
}

void IntArray::WriteWide(uint64_t addr, const iroha::Numeric &data) {
  int mw = data_width_.GetWidth();
  addr /= (mw / 8);
  int c = data.type_.GetWidth() / mw;
  for (int i = 0; i < c; ++i) {
    int l = mw * i;
    iroha::Numeric d;
    iroha::Op::SelectBits(data, l + mw - 1, l, &d);
    WriteSingle(addr + i, d);
  }
}

iroha::Numeric IntArray::Read(const vector<uint64_t> &indexes) {
  return ReadSingle(GetIndex(indexes));
}

iroha::Numeric IntArray::ReadSingle(uint64_t addr) {
  IntArrayPage *p = FindPage(addr);
  int offset = (addr % PAGE_SIZE);
  return p->data[offset];
}

iroha::Numeric IntArray::ReadWide(uint64_t addr, int width) {
  int mw = data_width_.GetWidth();
  addr /= (mw / 8);
  iroha::Numeric n;
  n.type_.SetWidth(0);
  int c = width / mw;
  for (int i = 0; i < c; ++i) {
    iroha::Numeric d;
    d = ReadSingle(addr + i);
    iroha::Numeric t;
    iroha::Op::Concat(d, n, &t);
    n = t;
  }
  return n;
}

uint64_t IntArray::GetLength() const {
  return size_;
}

const iroha::NumericWidth &IntArray::GetDataWidth() const {
  return data_width_;
}

int IntArray::GetAddressWidth() const {
  int address_bits;
  uint64_t s = size_ - 1;
  for (address_bits = 0; s > 0; ++address_bits) {
    s >>= 1;
  }
  return address_bits;
}

IntArrayPage *IntArray::FindPage(uint64_t addr) {
  uint64_t page_idx = addr / PAGE_SIZE;
  IntArrayPage *p = pages_[page_idx];
  if (!p) {
    p = new IntArrayPage(data_width_);
    pages_[page_idx] = p;
  }
  return p;
}

uint64_t IntArray::GetIndex(const vector<uint64_t> &indexes) {
  uint64_t idx = 0;
  uint64_t s = 1;
  for (int i = 0; i < indexes.size() && i < shape_.size(); ++i) {
    idx += s * (indexes[i] % shape_[i]);
    s *= shape_[i];
  }
  return idx;
}

}  // namespace vm
