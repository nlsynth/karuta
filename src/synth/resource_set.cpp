#include "synth/resource_set.h"

#include "dfg/dfg.h"
#include "dfg/resource_params.h"
#include "dump_stream.h"
#include "status.h"
#include "vm/insn.h"
#include "vm/opcode.h"

namespace synth {

ResourceSet::ResourceSet(DGraph *graph) : graph_(graph) {
  funcall_ = NULL;
  assign_ = NULL;
  br_ = DGraphUtil::FindResource(graph_, sym_branch, true);
  function_entry_ =
    DGraphUtil::FindResource(graph_, sym_lookup("function_entry"), true);
  mem_if_ = NULL;
  task_entry_ = NULL;
  task_finish_ = NULL;
}

DResource *ResourceSet::AssignResource() {
  if (!assign_) {
    assign_ = DGraphUtil::AllocResource(graph_, sym_assign);
  }
  return assign_;
}

DResource *ResourceSet::BranchResource() {
  return br_;
}

DResource *ResourceSet::FuncallResource() {
  if (!funcall_) {
    funcall_ = DGraphUtil::AllocResource(graph_, sym_lookup("funcall"));
  }
  return funcall_;
}

DResource *ResourceSet::FunctionEntryResource(bool is_task_root) {
  if (is_task_root) {
    if (!task_entry_) {
      task_entry_ = DGraphUtil::AllocResource(graph_, sym_task_entry);
    }
    return task_entry_;
  }
  return function_entry_;
}

DResource *ResourceSet::TaskFinishResource() {
  if (task_finish_ == nullptr) {
    task_finish_ = DGraphUtil::AllocResource(graph_, sym_task_finish);
  }
  return task_finish_;
}

DResource *ResourceSet::GetExtIOResource(sym_t name,
					 ResourceParams *resource,
					 DInsn *insn) {
  for (size_t i = 0; i < ext_io_resources_.size(); ++i) {
    if (ext_io_resources_[i]->name_ == sym_cstr(name)) {
      return ext_io_resources_[i];
    }
  }
  DResource *res = DGraphUtil::AllocResource(graph_, sym_ext_io);
  res->name_ = sym_cstr(name);
  res->imported_resource_ = resource;
  for (DRegister *input : insn->inputs_) {
    res->input_types_.push_back(input->data_type_);
  }
  for (DRegister *output : insn->outputs_) {
    res->output_types_.push_back(output->data_type_);
  }
  ext_io_resources_.push_back(res);
  return res;
}

DResource *ResourceSet::GetOpResource(vm::OpCode op, DType *type) {
  // Remap.
  switch (op) {
  case vm::OP_LT:
  case vm::OP_LTE:
  case vm::OP_GTE:
    op = vm::OP_GT;
    break;
  case vm::OP_NE:
    op = vm::OP_EQ;
    break;
  default:
    break;
  }

  for (size_t i = 0; i < resources_.size(); ++i) {
    ResourceEntry &res = resources_[i];
    if (res.op == op && res.type == type) {
      return res.resource;
    }
  }
  ResourceEntry res;
  res.op = op;
  sym_t resource_type = GetResourceType(op);
  res.resource = DGraphUtil::AllocResource(graph_, resource_type);
  res.type = type;
  PopulateResourceDataType(op, res.resource, type);
  resources_.push_back(res);
  return res.resource;
}

void ResourceSet::PopulateResourceDataType(int op, DResource *res,
					   DType *type) {
  if (!type) {
    type = DTypeUtil::GetIntType(0);
  }
  if (vm::InsnType::IsNumCalculation(op) || op == vm::OP_CONCAT) {
    res->input_types_.push_back(type);
    res->input_types_.push_back(type);
    res->output_types_.push_back(type);
  } else if (vm::InsnType::IsComparison(op)) {
    res->input_types_.push_back(type);
    res->input_types_.push_back(type);
    res->output_types_.push_back(DTypeUtil::GetBoolType());
  }
}

sym_t ResourceSet::GetResourceType(vm::OpCode op) {
  switch (op) {
  case vm::OP_GT: return sym_gt;
  case vm::OP_ADD: return sym_add;
  case vm::OP_SUB: return sym_sub;
  case vm::OP_MUL: return sym_mul;
  case vm::OP_AND: return sym_bit_and;
  case vm::OP_OR: return sym_bit_or;
  case vm::OP_XOR: return sym_bit_xor;
  case vm::OP_CONCAT: return sym_bit_concat;
  case vm::OP_BIT_RANGE: return sym_bit_sel;
  case vm::OP_LOGIC_INV: return sym_logic_inv;
  case vm::OP_EQ: return sym_eq;
  case vm::OP_LAND: return sym_logic_and;
  case vm::OP_LOR: return sym_logic_or;
  default:
    CHECK(false) << "unknown resource type: " << vm::OpCodeName(op);
  }
  return NULL;
}

DResource *ResourceSet::GetImportedResource(ResourceParams *resource) {
  string name = resource->GetResourceName();
  for (size_t i = 0; i < imported_resources_.size(); ++i) {
    DResource *res = imported_resources_[i];
    if (res->opr_->type_ == sym_imported && res->name_ == name) {
      return res;
    }
  }
  DResource *res = DGraphUtil::AllocResource(graph_, sym_imported);
  res->name_ = name;
  res->imported_resource_ = resource;
  return res;
}

DResource *ResourceSet::GetArrayResource(sym_t name) {
  if (!name) {
    if (!mem_if_) {
      mem_if_ = DGraphUtil::FindResource(graph_, sym_memory, true);
    }
    return mem_if_;
  }
  for (size_t i = 0; i < array_resources_.size(); ++i) {
    DResource *res = array_resources_[i];
    if (res->name_ == sym_cstr(name)) {
      return res;
    }
  }
  DResource *res = DGraphUtil::AllocResource(graph_, sym_memory);
  res->name_ = sym_cstr(name);
  array_resources_.push_back(res);
  return res;
}

DResource *ResourceSet::GetChannelResource(const string &name, bool is_write,
					   int data_width) {
  for (size_t i = 0; i < channel_resources_.size(); ++i) {
    DResource *res = channel_resources_[i];
    if (res->name_ == name) {
      // Checks if read/write is consistent.
      if (!((is_write && res->opr_->type_ == sym_write_channel) ||
	    (!is_write && res->opr_->type_ == sym_read_channel))) {
	Status::os(Status::USER)
	  << "'" << name << "' cannot be both read/write port";
	MessageFlush::Get(Status::USER);
	return nullptr;
      }
      return res;
    }
  }
  sym_t op;
  if (is_write) {
    op = sym_write_channel;
  } else {
    op = sym_read_channel;
  }
  DResource *res = DGraphUtil::AllocResource(graph_, op);
  if (is_write) {
    res->input_types_.push_back(DTypeUtil::GetIntType(data_width));
  } else {
    res->output_types_.push_back(DTypeUtil::GetIntType(data_width));
  }
  res->name_ = name;
  channel_resources_.push_back(res);
  return res;
}

DResource *ResourceSet::GetSubModuleCallResource(vm::Object *callee_object,
						 sym_t method_name,
						 sym_t orig_obj_name) {
  for (auto &entry : sub_module_resources_) {
    if (callee_object == entry.obj && method_name == entry.method_name) {
      return entry.resource;
    }
  }
  DResource *res = DGraphUtil::AllocResource(graph_,
					     sym_lookup("sub_module_call"));
  SubModuleCallEntry entry;
  entry.obj = callee_object;
  entry.method_name = method_name;
  entry.orig_obj_name = orig_obj_name;
  entry.resource = res;
  sub_module_resources_.push_back(entry);
  return res;
}

vector<SubModuleCallEntry> &ResourceSet::GetSubModuleCalls() {
  return sub_module_resources_;
}

}  // namespace synth
