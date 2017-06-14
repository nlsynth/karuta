// memory model for interpreted neon
#include "vm/int_array.h"

#include <map>

using std::map;

static const int PAGE_SIZE = 1024;
#define DATA_WIDTH 4
#define PAGE_BYTES (PAGE_SIZE * DATA_WIDTH)

namespace vm {

IntArray::~IntArray() {
  // do nothing
}

struct npage {
  npage(const iroha::NumericWidth &w);
  iroha::Numeric data[PAGE_SIZE];
};

class IntArrayImpl : public IntArray {
public:
  IntArrayImpl(const iroha::NumericWidth &width, uint64_t size);
  IntArrayImpl(const IntArrayImpl *src);
  virtual void Write(uint64_t addr, const iroha::Numeric &data);
  virtual iroha::Numeric Read(uint64_t addr);
  virtual uint64_t GetLength() const;
  virtual const iroha::NumericWidth &GetWidth() const;
  virtual int GetAddressWidth() const;

private:
  npage *FindPage(uint64_t addr);

  uint64_t size_;
  iroha::NumericWidth width_;
  map<uint64_t, npage *> pages_;
};

npage::npage(const iroha::NumericWidth &width) {
  int i;
  for (i = 0; i < PAGE_SIZE; i++) {
    data[i].SetValue(0);
    data[i].type_ = width;
  }
}

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
  : size_(size), width_(width) {
}

IntArrayImpl::IntArrayImpl(const IntArrayImpl *src) {
  width_ = src->GetWidth();
  size_ = src->GetLength();
  for (const auto it : src->pages_) {
    npage *p = new npage(width_);
    *p = *(it.second);
    pages_[it.first] = p;
  }
}

void IntArrayImpl::Write(uint64_t addr, const iroha::Numeric &data) {
  npage *p = FindPage(addr);
  int offset = (addr % PAGE_SIZE);
  p->data[offset] = data;
}

iroha::Numeric IntArrayImpl::Read(uint64_t addr) {
  npage *p = FindPage(addr);
  int offset = (addr % PAGE_SIZE);
  return p->data[offset];
}

uint64_t IntArrayImpl::GetLength() const {
  return size_;
}

const iroha::NumericWidth &IntArrayImpl::GetWidth() const {
  return width_;
}

int IntArrayImpl::GetAddressWidth() const {
  int address_bits;
  uint64_t s = size_ - 1;
  for (address_bits = 0; s > 0; ++address_bits) {
    s >>= 1;
  }
  return address_bits;
}

npage *IntArrayImpl::FindPage(uint64_t addr) {
  uint64_t page_idx = addr / PAGE_SIZE;
  npage *p = pages_[page_idx];
  if (!p) {
    p = new npage(width_);
    pages_[page_idx] = p;
  }
  return p;
}

}  // namespace vm
