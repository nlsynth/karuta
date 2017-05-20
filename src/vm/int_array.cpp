// memory model for interpreted neon
#include <map>
#include "vm/int_array.h"

using std::map;

#define PAGE_SIZE 1024
#define DATA_WIDTH 4
#define PAGE_BYTES (PAGE_SIZE * DATA_WIDTH)

namespace vm {

IntArray::~IntArray() {
  // do nothing
}

struct npage {
  npage(const iroha::NumericWidth &w);
  numeric::Number data[PAGE_SIZE];
};

class IntArrayImpl : public IntArray {
public:
  IntArrayImpl(const iroha::NumericWidth &width, int size);
  IntArrayImpl(const IntArrayImpl *src);
  virtual void Write(uint64_t addr, const numeric::Number &data);
  virtual numeric::Number Read(uint64_t addr);
  virtual long long GetLength() const;
  virtual const iroha::NumericWidth &GetWidth() const;
  virtual int GetAddressWidth() const;

private:
  npage *find_page(uint64_t addr);

  int size_;
  iroha::NumericWidth width_;
  map<uint64_t, npage *> pages_;
};

npage::npage(const iroha::NumericWidth &width) {
  int i;
  for (i = 0; i < PAGE_SIZE; i++) {
    data[i].int_part = 0;
    data[i].type_ = width;
  }
}

IntArray *IntArray::Create(const iroha::NumericWidth &width, int size) {
  return new IntArrayImpl(width, size);
}

IntArray *IntArray::Copy(const IntArray *src) {
  const IntArrayImpl *si = (const IntArrayImpl *)src;
  return new IntArrayImpl(si);
}

IntArrayImpl::IntArrayImpl(const iroha::NumericWidth &width,
			   int size)
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

void IntArrayImpl::Write(uint64_t addr, const numeric::Number &data) {
  npage *p = find_page(addr);
  int offset = (addr % PAGE_BYTES);
  p->data[offset] = data;
}

numeric::Number IntArrayImpl::Read(uint64_t addr) {
  npage *p = find_page(addr);
  int offset = (addr % PAGE_BYTES);
  return p->data[offset];
}

long long IntArrayImpl::GetLength() const {
  return size_;
}

const iroha::NumericWidth &IntArrayImpl::GetWidth() const {
  return width_;
}

int IntArrayImpl::GetAddressWidth() const {
  int address_bits;
  for (address_bits = 0; (1 << address_bits) < size_;
       ++address_bits) {
    // do nothing here.
  }
  return address_bits;
}

npage *IntArrayImpl::find_page(uint64_t addr) {
  uint64_t idx = addr / PAGE_BYTES;
  npage *p = pages_[idx];
  if (!p) {
    p = new npage(width_);
    pages_[idx] = p;
  }
  return p;
}

}  // namespace vm
