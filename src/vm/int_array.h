// -*- C++ -*-
#ifndef _vm_int_array_h_
#define _vm_int_array_h_

#include "numeric/numeric_type.h"  // from iroha

namespace vm {

class IntArray {
public:
  static IntArray *Create(const iroha::NumericWidth &data_width,
			  uint64_t length);
  static IntArray *Copy(const IntArray *mem);

  virtual ~IntArray();
  virtual void Write(uint64_t addr, const iroha::Numeric &data) = 0;
  virtual iroha::Numeric Read(uint64_t addr) = 0;
  // 0 means unlimited (is actually 2^64). typically for main memory space.
  virtual uint64_t GetLength() const = 0;
  virtual const iroha::NumericWidth &GetWidth() const = 0;
  virtual int GetAddressWidth() const = 0;
};

}  // namespace vm

#endif  // _vm_int_array_h_
