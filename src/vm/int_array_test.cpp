#include "vm/int_array.h"

#include "iroha/test_util.h"
#include "numeric/numeric_type.h"  // from iroha

namespace vm {

void TestIntArray() {
  iroha::NumericWidth w;
  vector<uint64_t> shape;
  shape.push_back(16);
  IntArray *a = IntArray::Create(w, shape);

  TestUtil::Assert(a->GetAddressWidth() == 4);
}

}
