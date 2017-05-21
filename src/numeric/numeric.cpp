// Copyright (C) Yusuke Tabata 2009-2015
#include "numeric/numeric.h"

#include "nli.h"
#include "base/pool.h"

namespace numeric {

static vector<iroha::NumericWidth *> Width_list;
static Pool<iroha::NumericWidth> pool;

const iroha::NumericWidth *WidthUtil::MakeIntPtr(bool is_signed, int int_part) {
  for (auto *nw : Width_list) {
    if (nw->IsSigned() == is_signed &&
	nw->GetWidth() == int_part) {
      return nw;
    }
  }
  auto *nw = new iroha::NumericWidth(is_signed, int_part);
  pool.Add(nw);
  Width_list.push_back(nw);
  return nw;
}

const iroha::NumericWidth *WidthUtil::ToPtr(const iroha::NumericWidth &w) {
  return MakeIntPtr(w.IsSigned(), w.GetWidth());
}

const iroha::NumericWidth WidthUtil::DeRef(const iroha::NumericWidth *w) {
  if (w == nullptr) {
    return iroha::NumericWidth(false, 32);
  }
  return *w;
}

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
