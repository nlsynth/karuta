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
  npage(const NumberWidth *w);
  Number data[PAGE_SIZE];
};

class IntArrayImpl : public IntArray {
public:
  IntArrayImpl(const NumberWidth *width, int size);
  IntArrayImpl(const IntArrayImpl *src);
  virtual void Write(int addr, const Number &data);
  virtual Number Read(int addr);
  virtual long long GetLength() const;
  virtual const NumberWidth *GetWidth() const;

private:
  npage *find_page(int addr);

  int size_;
  const NumberWidth *width_;
  map<int, npage *> pages_;
};

npage::npage(const NumberWidth *width) {
  int i;
  for (i = 0; i < PAGE_SIZE; i++) {
    data[i].int_part = 0;
    data[i].frac_part = 0;
    data[i].type = width;
  }
}

IntArray *IntArray::Create(const NumberWidth *width, int size) {
  return new IntArrayImpl(width, size);
}

IntArray *IntArray::Copy(const IntArray *src) {
  const IntArrayImpl *si = (const IntArrayImpl *)src;
  return new IntArrayImpl(si);
}

IntArrayImpl::IntArrayImpl(const NumberWidth *width,
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

void IntArrayImpl::Write(int addr, const Number &data) {
  npage *p = find_page(addr);
  int offset = (addr % PAGE_BYTES);
  p->data[offset] = data;
}

Number IntArrayImpl::Read(int addr) {
  npage *p = find_page(addr);
  int offset = (addr % PAGE_BYTES);
  return p->data[offset];
}

long long IntArrayImpl::GetLength() const {
  return size_;
}

const NumberWidth *IntArrayImpl::GetWidth() const {
  return width_;
}

npage *IntArrayImpl::find_page(int addr) {
  int idx = addr / PAGE_BYTES;
  npage *p = pages_[idx];
  if (!p) {
    p = new npage(width_);
    pages_[idx] = p;
  }
  return p;
}

}  // namespace vm
