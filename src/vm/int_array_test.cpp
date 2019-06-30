#include "vm/int_array.h"

#include "iroha/test_util.h"
#include "numeric/numeric_type.h"  // from iroha

namespace vm {

void TestIntArray() {
  iroha::NumericWidth w;
  w.SetWidth(16);
  vector<uint64_t> shape;
  shape.push_back(16);
  IntArray *a = IntArray::Create(w, shape);

  TestUtil::Assert(a->GetAddressWidth() == 4);
  iroha::NumericWidth t;
  iroha::NumericValue v;
  v.SetValue0(0x12345678);
  a->WriteSingle(0, t, v);
  v = a->ReadSingle(0);
  TestUtil::Assert((v.GetValue0() & 0xffff) == 0x5678);
  v = a->ReadSingle(1);
  TestUtil::Assert(v.GetValue0() == 0);
  iroha::Numeric n = a->ReadWide(0, 32);
  TestUtil::Assert(n.type_.GetWidth() == 32);
}

}
