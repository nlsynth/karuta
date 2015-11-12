// dfg dumper
#include <fstream>
#include <sstream>
#include "dfg/dfg.h"
#include "nli.h"

using std::ostream;

namespace dfg {

class DFGDumpContext {
public:
  DFGDumpContext(ostream &s, bool need_close) : os(s), need_close_(need_close) {
  }
  ~DFGDumpContext() {
    if (need_close_) {
      delete &os;
    }
  }
  ostream &os;

  void DumpGraph(DGraph *g, DGraphAnnotation *an);
private:
  void DumpRegister(const DRegister *reg);
  void DumpRegistersAll();
  void DumpSummary();
  void DumpStateRow(DState *st, bool even);
  void DumpInsnsAll(DState *st, DResource *r);
  void DumpInsn(DInsn *insn);
  void DumpResource(DResource *r, ostream &os);

  const DGraph *graph_;
  const DGraphAnnotation *annotation_;
  bool need_close_;
};

void DFGDumpContext::DumpInsn(DInsn *insn) {
  if (!insn->func_name_.empty()) {
    os << "function:" << insn->func_name_ << "<br>";
  }
  if (insn->inputs_.size()) {
    os << "inputs:<br>";
    for (DRegister *reg : insn->inputs_) {
      os << DFG::RegisterName(reg);
      os << "<br>";
    }
  }
  if (insn->outputs_.size()) {
    os << "outputs:<br>";
    for (DRegister *reg : insn->outputs_) {
      os << DFG::RegisterName(reg);
      os << "<br>";
    }
  }
  if (insn->annotation_) {
    insn->annotation_->Output(os);
    os << "<br>";
  }
  if (insn->targets_.size()) {
    os << "next:<br>";
    for (DState *st : insn->targets_) {
      if (st) {
	os << st->state_id_ << "<br>";
      } else {
	os << "NULL<br>";
      }
    }
  }
  os << "id:" << insn->insn_id_<<"<br>";
}

static void DumpType(DType *type, ostream &os) {
  if (type->type_ == DType::ENUM) {
    os << "enum";
  } else {
    os << "int";
  }
  os << ":" << type->size_;
}

void DFGDumpContext::DumpRegister(const DRegister *reg) {
  os << "  <td>";
  switch (reg->reg_type_) {
  case DRegister::REG_CONST:
    os << "const";
    break;
  case DRegister::REG_NORMAL:
    os << "normal";
    break;
  case DRegister::REG_WIRE:
    os << "wire";
    break;
  }
  os << "</td><td>";
  if (reg->reg_type_ == DRegister::REG_NORMAL ||
      reg->reg_type_ == DRegister::REG_WIRE) {
    os << reg->reg_name_;
    if (reg->reg_type_ == DRegister::REG_NORMAL &&
	reg->has_initial_) {
      os << "(" << reg->num_ << ")";
    }
  } else  if (reg->reg_type_ == DRegister::REG_CONST &&
	      reg->data_type_->type_ == DType::ENUM) {
    os << DFG::RegisterName(reg);
  } else {
    os << reg->num_;
  }
  os << "</td><td>";
  DumpType(reg->data_type_, os);
  os << "</td>";
  
}

void DFGDumpContext::DumpSummary() {
  if (!annotation_) {
    return;
  }
  const string s = annotation_->GetSummary();
  if (s.empty()) {
    return;
  }
  os << "Summary:<br>";
  os << s << "<br><br>";
}

void DFGDumpContext::DumpRegistersAll() {
  os << "Registers:"
     << "<table border=1>\n"
     << "<tr><th>alloc type</th><th>name</th><th>data type</th>"
     << "<th>annotation</th></tr>\n";
  
  for (const DRegister *reg : graph_->registers_) {
    os << " <tr>";
    DumpRegister(reg);
    if (annotation_) {
      os << "<td>" << annotation_->GetRegisterAnnotation(reg) << "</td>";
    }
    os << " </tr>\n";
  }
  os << "</table>";
}

void DFGDumpContext::DumpInsnsAll(DState *st, DResource *r) {
  int nr = DStateUtil::GetNrInsnsByResource(st, r);
  if (nr > 1) {
    os << "<td>";
    for (int i = 0; i < nr; i++) {
      if (i > 0) {
	os << "<hr>";
      }
      DInsn *insn = DStateUtil::FindNthInsnByResource(st, r, i);
      DumpInsn(insn);
    }
    os << "</td>";
  } else {
    DInsn *insn = DStateUtil::FindInsnByResource(st, r);
    if (insn) {
      os << "<td>";
      DumpInsn(insn);
      os << "</td>";
    } else {
      os << "<td></td>";
    }
  }
}

void DFGDumpContext::DumpStateRow(DState *st, bool even) {
  // use css class to change color
  if (even) {
    os << " <tr class=even>\n";
  } else {
    os << " <tr class=odd>\n";
  }
  //
  os << "  <th>" << DFG::StateName(st);
  if (st->text_annotation_) {
    os << "(";
    os << st->text_annotation_;
    os << ")";
  }
  if (st->annotation_) {
    os << "(";
    st->annotation_->Output(os);
    os << ")";
  }
  os << "  </th>";
  for (DResource *res : graph_->resources_) {
    DumpInsnsAll(st, res);
  }
  string a;
  if (annotation_) {
    a = annotation_->GetStateAnnotation(st);
  }
  os << "<td>" << a << "</td>";
  os << " </tr>\n";
}

void DFGDumpContext::DumpGraph(DGraph *g, DGraphAnnotation *a) {
  if (!g) {
    return;
  }
  graph_ = g;
  annotation_ = a;
  DumpSummary();
  DumpRegistersAll();
  os << "State Machine: " << g->states_.size()<< "states<br>";
  if (g->annotation_) {
    g->annotation_->Output(os);
  }
  os << "<table border=1>\n";
  os << " <tr><th></th>\n";
  for (DResource *res : g->resources_) {
    os << "<th>";
    DumpResource(res, os);
    os << "</th>";
  }
  os << " <th>annotation</th>"
     << " </tr>\n";
  bool even = true;
  for (DState *st : g->states_) {
    DumpStateRow(st, even);
    even = !even;
  }
  os << "</table>";
}

void DFGDumpContext::DumpResource(DResource *r,
				  ostream &os) {
  os << sym_cstr(r->opr_->type_) << ":" << r->resource_id_;
  if (!r->name_.empty()) {
    os << "<br>(" << r->name_ << ")";
  }
  vector<DType *>::iterator it;
  if (r->input_types_.size()) {
    os << "<br>inputs:";
    for (it = r->input_types_.begin(); it != r->input_types_.end(); it++) {
      os << "<br>";
      DumpType(*it, os);
    }
  }
  if (r->output_types_.size()) {
    os << "<br>outputs:";
    for (it = r->output_types_.begin(); it != r->output_types_.end(); it++) {
      os << "<br>";
      DumpType(*it, os);
    }
  }
  if (r->annotation_) {
    os << "<br>";
    r->annotation_->Output(os);
  }
  if (!r->opr_->is_exclusive_) {
    os << "<br>shared";
  }
  if (r->array_) {
    os << "<br>{...}";
  }
}

DFGDumpContext *DFGDump::Start(const string &fn) {
  cout << "output html file name=(" << (fn) << ")\n";
  ostream *ofs = new std::ofstream(fn);
  DFGDumpContext *ddc = new DFGDumpContext(*ofs, true);

  ddc->os << "<html>\n<head>"
	  << "<title>Neon Light State Machine</title>\n"
	  << " <style type=\"text/css\">\n"
	  << "  table {font-size: x-small;}\n"
	  << "  tr.even {background-color: #c0c0ff}\n"
	  << "  tr.odd {background-color: #ffc0c0}\n"
	  << " </style>"
	  << "</head>"
	  << "<body>\n"
	  << "<!-- NLI_HTML_BODY -->\n";
  return ddc;
}

void DFGDump::AddNote(DFGDumpContext *ddc, const char *note) {
  if (note == NULL) {
    return;
  }
  ddc->os << "<br>" << note << "<hr>\n";
}

void DFGDump::DumpGraph(DFGDumpContext *dc, DGraph *g,
			DGraphAnnotation *a) {
  dc->DumpGraph(g, a);
  dc->os.flush();
}

void DFGDump::DumpModule(DFGDumpContext *dc, DModule *d,
			 DGraphAnnotation *a) {
  string p;
  DumpModuleRec(p, dc, d, a);
  dc->os.flush();
}

void DFGDump::DumpModuleRec(const string &path,
			    DFGDumpContext *dc, DModule *dm,
			    DGraphAnnotation *ann) {
  // type
  if (dm->module_type_ == DModule::MODULE_TASK) {
    dc->os << "(TASK)\n";
  } else if (dm->module_type_ == DModule::MODULE_THREAD) {
    dc->os << "(THREAD)\n";
  } else if (dm->module_type_ == DModule::MODULE_NONE) {
    dc->os << "(NONE)\n";
  } else if (dm->module_type_ == DModule::MODULE_CONTAINER) {
    dc->os << "(CONTAINER)\n";
  }
  // path "." module_name
  string cur_path = path;
  if (cur_path.empty()) {
    cur_path = "-";
  } else {
    cur_path += ".";
  }
  cur_path += dm->module_name_;
  dc->os << "path:" << cur_path << "<br>\n";
  if (dm->graph_) {
    dc->DumpGraph(dm->graph_, ann);
  }
  // channels
  if (dm->channels_.size() > 0) {
    dc->os << "channels:<br>\n";
    for (size_t i = 0; i < dm->channels_.size(); ++i) {
      DChannel *chan = dm->channels_[i];
      dc->os << chan->name_;
      dc->os << " writer=";
      if (chan->writer_) {
	dc->os << chan->writer_->module_name_;
      } else {
	dc->os << "none";
      }
      dc->os << ", reader=";
      if (chan->reader_) {
	dc->os << chan->reader_->module_name_;
      } else {
	dc->os << "none";
      }
      dc->os << "<br>\n";
    }
  }
  // submodules
  dc->os << "<hr>";
  for (size_t i = 0; i < dm->sub_modules_.size(); ++i) {
    DModule *mod = dm->sub_modules_[i];
    DumpModuleRec(cur_path, dc, mod, ann);
  }
}

void DFGDump::End(DFGDumpContext *dc) {
  if (!dc) {
    return ;
  }
  dc->os << "</body></html>\n";
  delete dc;
}

}  // namespace dfg
