// -*- C++ -*-
#ifndef _writer_vl_util_h_
#define _writer_vl_util_h_

#include "nli.h"

namespace dfg {
class DGraph;
class DInsn;
class DRegister;
class DResource;
class DState;
class DType;
class DModule;
}  // namespace dfg
using namespace dfg;

namespace writer {

class VLIOSet {
public:
  enum PinType {
    INPUT,
    OUTPUT,
    INPUT_WIRE,
    OUTPUT_WIRE,
  };

  void AddPin(const string &name, enum PinType type, int width,
	      const string &comment);

  void Output(bool only_names, ostream& os);

private:
  struct Pin {
    string name_;
    enum PinType type_;
    int width_;
    string comment_;
  };
  vector<Pin> pins_;
};

class VLStateEncoder {
public:
  VLStateEncoder(DGraph *graph);

  int GetStateWidth();
  int GetEncodedState(DState *st);
  int GetTaskEntryState();
  string StateNameWithoutQuote(const DState *st);
  string StateName(const DState *st);
  string TaskEntryStateName();
  string TaskEntryStateNameWithoutQuote();

private:
  int state_width_;
  int task_entry_state_;
};

class VLUtil {
public:
  static DModule *GetCalleeTaskModule(const DGraph *graph, const DInsn *insn);
  // ParentModName_ThisTaskModName.
  static string TaskControlPinName(const DModule *dm);
  static string TaskControlPinNameFromCallerInsn(const DGraph *graph,
						 const DInsn *insn);
  // Both for arguments and return values.
  static string TaskParamPinName(const string &pin_base,
				 int nth,
				 const string &dir);
  // "reg [dd:0]"
  static string RegType(const DType *type);
  // "wire [dd:0]"
  static string WireType(const DType *type);
  
  static bool IsExternalRAM(const DResource *r);
  static bool IsInternalMEM(const DResource *r);
  static bool IsResourceUnshareUniOp(const DResource *r);
  static bool IsResourceUnshareBinOp(const DResource *r);
  static bool IsResourceShareBinOp(const DResource *r);

private:
  static string WidthType(const DType *type);
};

}  // namespace writer

#endif  // _writer_vl_util_h_
