// Convert abstract operations like memory store/load into
// real protocol based
//

// memory access
//  sym_memory ->
//   external memory: sram_if
//   internal RAM: sram_if may_write
//   internal ROM: sram_if

#include "synth/interface.h"

#include "dfg/dfg.h"

namespace synth {

void InterfaceCompiler::GenerateSRAMWrite(DGraph *g, DResource *sram,
					  DState *ds, DInsn *mem_insn) {
  // sram insn
  DInsn *insn = DGraphUtil::InsnNew(g, sram);
  insn->inputs_.push_back(*(mem_insn->inputs_.begin()));
  insn->inputs_.push_back(*(mem_insn->inputs_.rbegin()));
  ds->insns_.push_back(insn);
  //
  DStateUtil::EraseInsn(ds, mem_insn);
}

void InterfaceCompiler::GenerateSRAMRead(DGraph *g, DResource *sram,
					 DState *ds, DInsn *mem_insn) {
  DInsn *addr_insn = DGraphUtil::InsnNew(g, sram);
  addr_insn->inputs_.push_back(*(mem_insn->inputs_.begin()));
  ds->insns_.push_back(addr_insn);
  //
  DState *data_state = DGraphUtil::AllocStateNext(g, ds);
  DInsn *data_insn = DGraphUtil::InsnNew(g, sram);
  data_insn->inputs_.push_back(*(mem_insn->inputs_.begin()));
  data_insn->outputs_.push_back(*(mem_insn->outputs_.rbegin()));
  data_state->insns_.push_back(data_insn);
  //
  DState *next_state = DStateUtil::GetNextState(g, ds);
  DStateUtil::SetNextState(g, ds, data_state);
  DStateUtil::SetNextState(g, data_state, next_state);
  //
  DStateUtil::EraseInsn(ds, mem_insn);
}

DResource *InterfaceCompiler::GetSRAM(DGraph *g, DResource *mem) {
  DArray *array = mem->array_;
  map<DArray *, DResource *>::iterator it = srams_.find(array);
  if (it != srams_.end()) {
    return it->second;
  }
  DResource *r = DGraphUtil::AllocResource(g, sym_sram_if);
  r->array_ = array;
  r->name_ = mem->name_;
  srams_[array] = r;
  return r;
}

void InterfaceCompiler::CompileGraph(DGraph *g) {
  // rewrites sym_memory to sram_if.
  vector<DResource *> sram_accesses;
  DGraphUtil::FindResourceAll(g, sym_memory, &sram_accesses);

  vector<DResource *> write_channels;
  DGraphUtil::FindResourceAll(g, sym_write_channel, &write_channels);

  list<DState *> states = g->states_;
  for (list<DState *>::iterator it = states.begin();
       it != states.end(); it++) {
    DState *st = *it;
    for (vector<DResource *>::iterator jt = sram_accesses.begin();
	 jt != sram_accesses.end(); ++jt) {
      DResource *r = *jt;
      DInsn *insn = DStateUtil::FindInsnByResource(st, r);
      if (!insn) {
	continue;
      }
      DResource *sram = GetSRAM(g, r);
      if (insn->inputs_.size() == 2) {
	// memory write
	GenerateSRAMWrite(g, sram, st, insn);
      }
      if (insn->inputs_.size() == 1 &&
	  insn->outputs_.size() == 1) {
	// memory read
	GenerateSRAMRead(g, sram, st, insn);
      }
    }
  }
}

void InterfaceCompiler::CompileInterface(DModule *mod) {
  if (mod->graph_) {
    InterfaceCompiler ic;
    ic.CompileGraph(mod->graph_);
  }
}

}  // namespace synth
