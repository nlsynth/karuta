// -*- C++ -*-
#ifndef _vm_int_array_h_
#define _vm_int_array_h_

#include "numeric/numeric.h"

namespace vm {

class IntArray {
public:
  static IntArray *Create(const iroha::NumericWidth &width, int limit);
  static IntArray *Copy(const IntArray *mem);

  virtual ~IntArray();
  virtual void Write(uint64_t addr, const numeric::Number &data) = 0;
  virtual numeric::Number Read(uint64_t addr) = 0;
  virtual long long GetLength() const = 0;
  virtual const iroha::NumericWidth &GetWidth() const = 0;
  virtual int GetAddressWidth() const = 0;
};

}  // namespace vm

#endif  // _vm_int_array_h_
