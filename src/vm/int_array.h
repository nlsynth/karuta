// -*- C++ -*-
#ifndef _vm_int_array_h_
#define _vm_int_array_h_

#include "numeric/numeric_type.h"  // from iroha
#include "vm/common.h"

#include <map>

namespace vm {

class IntArrayPage;

class IntArray {
public:
  IntArray(const iroha::NumericWidth &width,
	   const vector<uint64_t> &shape);
  IntArray(const IntArray *src);
  virtual ~IntArray();

  static IntArray *Create(const iroha::NumericWidth &data_width,
			  const vector<uint64_t> &shape);
  static IntArray *Copy(const IntArray *mem);

  iroha::Numeric Read(const vector<uint64_t> &indexes);
  iroha::Numeric ReadSingle(uint64_t addr);
  void Write(const vector<uint64_t> &indexes, const iroha::Numeric &data);
  void WriteSingle(uint64_t addr, const iroha::Numeric &data);
  // Assumes the width of data is equal or wider than or the width
  // of this array.
  iroha::Numeric ReadWide(uint64_t byte_addr, int width);
  void WriteWide(uint64_t byte_addr, const iroha::Numeric &data);

  // 0 means unlimited (is actually 2^64). typically for main memory space.
  uint64_t GetLength() const;
  int GetAddressWidth() const;
  const iroha::NumericWidth &GetDataWidth() const;
  const vector<uint64_t> &GetShape() const;

  void ImageIO(const string &fn, bool save);

private:
  IntArrayPage *FindPage(uint64_t addr);
  uint64_t GetIndex(const vector<uint64_t> &indexes);

  const vector<uint64_t> shape_;
  uint64_t size_;
  iroha::NumericWidth data_width_;
  std::map<uint64_t, IntArrayPage *> pages_;
};

}  // namespace vm

#endif  // _vm_int_array_h_
