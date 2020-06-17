#include "vm/io_wrapper.h"

#include "vm/object.h"
#include "vm/vm.h"

namespace vm {

Object *IOWrapper::NewIOWrapper(VM *vm, sym_t name, bool is_output,
				const iroha::NumericWidth &width) {
  return vm->array_prototype_object_->Clone();
}

}  // namespace vm
