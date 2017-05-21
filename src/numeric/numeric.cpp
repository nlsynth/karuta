// Copyright (C) Yusuke Tabata 2009-2015
#include "numeric/numeric.h"

#include "nli.h"

namespace numeric {

void WidthUtil::Dump(const iroha::NumericWidth &w,
		     ostream &os) {
  os << "<";
  if (w.IsSigned()) {
    os << "+,";
  }
  os << w.GetWidth();
  os << ">";
}

void Op::Dump(const iroha::Numeric &num, ostream &os) {
  os << num.GetValue();
}

}  // namespace numeric
