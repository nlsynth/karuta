// -*- C++ -*-
#ifndef _vm_int_array_h_
#define _vm_int_array_h_

#include "numeric.h"

namespace vm {

class IntArray {
public:
  static IntArray *Create(const NumberWidth *width, int limit);
  static IntArray *Copy(const IntArray *mem);

  virtual ~IntArray();
  virtual void Write(int addr, const Number &data) = 0;
  virtual Number Read(int addr) = 0;
  virtual long long GetLength() const = 0;
  virtual const NumberWidth *GetWidth() const = 0;
};

}  // namespace vm

#endif  // _vm_int_array_h_
