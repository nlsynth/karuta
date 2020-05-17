// Memory model for interpreted Karuta
#include "vm/int_array.h"

#include "iroha/numeric.h"

#include <stdlib.h>

namespace vm {

static const int PAGE_SIZE = 1024;

struct IntArrayPage {
  IntArrayPage(const iroha::NumericWidth &w);
  iroha::NumericValue data_[PAGE_SIZE];
  iroha::NumericWidth width_;
};

IntArrayPage::IntArrayPage(const iroha::NumericWidth &width) : width_(width) {
  int i;
  for (i = 0; i < PAGE_SIZE; i++) {
    iroha::Numeric::Clear(width_, &data_[i]);
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

void IntArray::Write(const vector<uint64_t> &indexes,
		     const iroha::Numeric &data) {
  WriteSingle(GetIndex(indexes), data.type_, data.GetArray());
}

void IntArray::WriteSingle(uint64_t addr, const iroha::NumericWidth &width,
			   const iroha::NumericValue &data) {
  IntArrayPage *p = FindPage(addr);
  int offset = (addr % PAGE_SIZE);
  iroha::Numeric::CopyValueWithWidth(data, width, p->width_,
				     nullptr, &p->data_[offset]);
}

void IntArray::WriteWide(uint64_t byte_addr, const iroha::NumericWidth &type,
			 const iroha::NumericValue &data) {
  int mem_width = data_width_.GetWidth();
  uint64_t array_addr = byte_addr / (mem_width / 8);
  int c = type.GetWidth() / mem_width;
  for (int i = 0; i < c; ++i) {
    int l = mem_width * i;
    iroha::Numeric d;
    iroha::Op::SelectBits(data, type, l + mem_width - 1, l,
			  d.GetMutableArray(), &d.type_);
    WriteSingle(array_addr + i, d.type_, d.GetArray());
  }
}

iroha::NumericValue IntArray::Read(const vector<uint64_t> &indexes) {
  return ReadSingle(GetIndex(indexes));
}

iroha::NumericValue IntArray::ReadSingle(uint64_t addr) {
  IntArrayPage *p = FindPage(addr);
  int offset = (addr % PAGE_SIZE);
  return p->data_[offset];
}

iroha::Numeric IntArray::ReadWide(uint64_t byte_addr, int width) {
  int data_bits = data_width_.GetWidth();
  int data_bytes = data_bits / 8;
  uint64_t array_addr = byte_addr / data_bytes;
  iroha::Numeric n;
  n.type_.SetWidth(0);
  int c = width / data_bits;
  for (int i = 0; i < c; ++i) {
    iroha::NumericValue a = ReadSingle(array_addr + i);
    iroha::Numeric t;
    iroha::Op::Concat(a, data_width_, n.GetArray(), n.type_,
		      t.GetMutableArray(), &t.type_);
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

const vector<uint64_t> &IntArray::GetShape() const {
  return shape_;
}

bool IntArray::ImageIO(const string &fn, const string &format, bool save) {
  string raw_fn;
  if (!Env::GetOutputPath(fn.c_str(), &raw_fn)) {
    return false;
  }
  FILE *fp;
  if (save) {
    fp = fopen(raw_fn.c_str(), "w");
  } else {
    fp = fopen(raw_fn.c_str(), "r");
  }
  if (fp == nullptr) {
    return false;
  }
    bool r;
  if (format.empty()) {
    r = BinaryIO(fp, save);
  } else {
    r = TextIO(fp, save);
  }
  fclose(fp);
  return r;
}

bool IntArray::BinaryIO(FILE *fp, bool save) {
  int num_bytes = (data_width_.GetWidth() + 1) / 8;
  for (int i = 0; i < GetLength(); ++i) {
    if (save) {
      iroha::NumericValue nv = ReadSingle(i);
      fwrite((void *)&nv.value_[0], num_bytes, 1, fp);
    } else {
      iroha::Numeric n;
      iroha::NumericValue *nv = n.GetMutableArray();
      fread((void *)&nv->value_[0], num_bytes, 1, fp);
      WriteSingle(i, n.type_, n.GetArray());
    }
  }
  return true;
}

bool IntArray::TextIO(FILE *fp, bool save) {
  // WIP. Probably use some standard format.
  for (int i = 0; i < GetLength(); ++i) {
    if (save) {
      iroha::NumericValue nv = ReadSingle(i);
      fprintf(fp, "%ld\n", nv.GetValue0());
    } else {
      char buf[16];
      fgets(buf, 16, fp);
      iroha::Numeric n;
      iroha::NumericValue *nv = n.GetMutableArray();
      nv->SetValue0(atoll(buf));
      WriteSingle(i, n.type_, n.GetArray());
    }
  }
  return true;
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
