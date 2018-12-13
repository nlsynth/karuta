// -*- C++ -*-
#ifndef _vm_int_array_h_
#define _vm_int_array_h_

#include "numeric/numeric_type.h"  // from iroha
#include "vm/common.h"

namespace vm {

class IntArray {
public:
  static IntArray *Create(const iroha::NumericWidth &data_width,
			  const vector<uint64_t> &shape);
  static IntArray *Copy(const IntArray *mem);

  virtual ~IntArray();
  virtual iroha::Numeric ReadSingle(uint64_t addr) = 0;
  virtual void WriteSingle(uint64_t addr, const iroha::Numeric &data) = 0;
  // Assumes the width of data is equal or wider than or the width of this array.
  virtual iroha::Numeric ReadWide(uint64_t addr, int width) = 0;
  virtual void WriteWide(uint64_t addr, const iroha::Numeric &data) = 0;

  // 0 means unlimited (is actually 2^64). typically for main memory space.
  virtual uint64_t GetLength() const = 0;
  virtual int GetAddressWidth() const = 0;
  virtual const iroha::NumericWidth &GetDataWidth() const = 0;
};

}  // namespace vm

#endif  // _vm_int_array_h_
