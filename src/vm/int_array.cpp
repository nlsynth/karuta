// memory model for interpreted neon
#include "vm/int_array.h"

#include "numeric/numeric_op.h"  // from iroha

#include <map>

using std::map;

namespace {

static const int PAGE_SIZE = 1024;

struct ArrayPage {
  ArrayPage(const iroha::NumericWidth &w);
  iroha::Numeric data[PAGE_SIZE];
};

ArrayPage::ArrayPage(const iroha::NumericWidth &width) {
  int i;
  for (i = 0; i < PAGE_SIZE; i++) {
    data[i].SetValue0(0);
    data[i].type_ = width;
  }
}

}  // namespace

namespace vm {

IntArray::~IntArray() {
  // do nothing
}

class IntArrayImpl : public IntArray {
public:
  IntArrayImpl(const iroha::NumericWidth &width, uint64_t size);
  IntArrayImpl(const IntArrayImpl *src);
  virtual void Write(uint64_t addr, const iroha::Numeric &data);
  virtual void WriteWide(uint64_t addr, const iroha::Numeric &data);
  virtual iroha::Numeric Read(uint64_t addr);
  virtual iroha::Numeric ReadWide(uint64_t addr, int width);
  virtual uint64_t GetLength() const;
  virtual int GetAddressWidth() const;
  virtual const iroha::NumericWidth &GetDataWidth() const;

private:
  ArrayPage *FindPage(uint64_t addr);

  uint64_t size_;
  iroha::NumericWidth data_width_;
  map<uint64_t, ArrayPage *> pages_;
};

IntArray *IntArray::Create(const iroha::NumericWidth &data_width,
			   uint64_t length) {
  return new IntArrayImpl(data_width, length);
}

IntArray *IntArray::Copy(const IntArray *src) {
  const IntArrayImpl *si = (const IntArrayImpl *)src;
  return new IntArrayImpl(si);
}

IntArrayImpl::IntArrayImpl(const iroha::NumericWidth &width,
			   uint64_t size)
  : size_(size), data_width_(width) {
}

IntArrayImpl::IntArrayImpl(const IntArrayImpl *src) {
  data_width_ = src->GetDataWidth();
  size_ = src->GetLength();
  for (const auto it : src->pages_) {
    ArrayPage *p = new ArrayPage(data_width_);
    *p = *(it.second);
    pages_[it.first] = p;
  }
}

void IntArrayImpl::Write(uint64_t addr, const iroha::Numeric &data) {
  ArrayPage *p = FindPage(addr);
  int offset = (addr % PAGE_SIZE);
  p->data[offset] = data;
}

void IntArrayImpl::WriteWide(uint64_t addr, const iroha::Numeric &data) {
  int mw = data_width_.GetWidth();
  addr /= (mw / 8);
  int c = data.type_.GetWidth() / mw;
  for (int i = 0; i < c; ++i) {
    int l = mw * i;
    iroha::Numeric d;
    iroha::Op::SelectBits(data, l + mw - 1, l, &d);
    Write(addr + i, d);
  }
}

iroha::Numeric IntArrayImpl::Read(uint64_t addr) {
  ArrayPage *p = FindPage(addr);
  int offset = (addr % PAGE_SIZE);
  return p->data[offset];
}

iroha::Numeric IntArrayImpl::ReadWide(uint64_t addr, int width) {
  int mw = data_width_.GetWidth();
  addr /= (mw / 8);
  iroha::Numeric n;
  n.type_.SetWidth(0);
  int c = width / mw;
  for (int i = 0; i < c; ++i) {
    iroha::Numeric d;
    d = Read(addr + i);
    iroha::Numeric t;
    iroha::Op::Concat(d, n, &t);
    n = t;
  }
  return n;
}

uint64_t IntArrayImpl::GetLength() const {
  return size_;
}

const iroha::NumericWidth &IntArrayImpl::GetDataWidth() const {
  return data_width_;
}

int IntArrayImpl::GetAddressWidth() const {
  int address_bits;
  uint64_t s = size_ - 1;
  for (address_bits = 0; s > 0; ++address_bits) {
    s >>= 1;
  }
  return address_bits;
}

ArrayPage *IntArrayImpl::FindPage(uint64_t addr) {
  uint64_t page_idx = addr / PAGE_SIZE;
  ArrayPage *p = pages_[page_idx];
  if (!p) {
    p = new ArrayPage(data_width_);
    pages_[page_idx] = p;
  }
  return p;
}

}  // namespace vm
