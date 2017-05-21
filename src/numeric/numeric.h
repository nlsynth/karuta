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

  // Used by code in fe/.
  static const iroha::NumericWidth *MakeIntPtr(bool is_signed, int int_part);
  static const iroha::NumericWidth *ToPtr(const iroha::NumericWidth &w);
  static const iroha::NumericWidth DeRef(const iroha::NumericWidth *w);
};

class Op {
public:
  static void Dump(const iroha::Numeric &num, ostream &os);
};

}  // namespace numeric

#endif  // _numeric_numeric_h_
