// -*- C++ -*-
#ifndef _numeric_numeric_h_
#define _numeric_numeric_h_

#include "nli.h"
#include "numeric/numeric_type.h"  // from iroha
#include "numeric/numeric_op.h"  // from iroha

namespace numeric {

class WidthUtil {
public:
  static void Dump(const iroha::NumericWidth &w, ostream &os);
};

class Op {
public:
  static void Dump(const iroha::Numeric &num, ostream &os);
};

}  // namespace numeric

#endif  // _numeric_numeric_h_
