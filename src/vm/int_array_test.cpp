#include "vm/int_array.h"

#include "iroha/test_util.h"
#include "numeric/numeric_type.h"  // from iroha

namespace vm {

void TestIntArray() {
  iroha::NumericWidth w;
  w.SetWidth(16);
  vector<uint64_t> shape;
  shape.push_back(16);
  std::unique_ptr<IntArray> a(IntArray::Create(w, shape));

  {
    TestUtil::Assert(a->GetAddressWidth() == 4);
    iroha::NumericWidth dw = a->GetDataWidth();
    TestUtil::Assert(dw.GetWidth() == 16);
  }
  {
    iroha::NumericWidth t;
    iroha::NumericValue v;
    v.SetValue0(0x12345678);
    a->WriteSingle(0, t, v);
    v = a->ReadSingle(0);
    TestUtil::Assert((v.GetValue0() & 0xffff) == 0x5678);
    v = a->ReadSingle(1);
    TestUtil::Assert(v.GetValue0() == 0);
  }
  {
    iroha::NumericWidth t;
    iroha::NumericValue v;
    t.SetWidth(32);
    v.SetValue0(0x12345678);
    a->WriteWide(0x200, t, v);
    iroha::Numeric n = a->ReadWide(0x200, 32);
    TestUtil::Assert(n.type_.GetWidth() == 32);
    TestUtil::Assert(n.GetValue0() == 0x12345678);
    v = a->ReadSingle(0x101);
    TestUtil::Assert(v.GetValue0() == 0x1234);
    v = a->ReadSingle(0x100);
    TestUtil::Assert(v.GetValue0() == 0x5678);
  }
}

}
