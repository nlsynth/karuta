// -*- C++ -*-
#ifndef _writer_vl_util_h_
#define _writer_vl_util_h_

#include "nli.h"

namespace dfg {
class DGraph;
class DResource;
class DState;
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
  string StateName(const DState *st);
  void OutputStateNameWithoutQuote(const DState *st, ostream &os);
  void OutputStateName(const DState *st, ostream &os);
  void OutputTaskEntryStateName(ostream &os);
  void OutputTaskEntryStateNameWithoutQuote(ostream &os);

private:
  int state_width_;
  int task_entry_state_;
};

class VLUtil {
public:
  static string TaskControlPinName(const DModule *dm);
  
  static bool IsExternalRAM(const DResource *r);
  static bool IsInternalMEM(const DResource *r);
  static bool IsResourceUnshareUniOp(const DResource *r);
  static bool IsResourceUnshareBinOp(const DResource *r);
  static bool IsResourceShareBinOp(const DResource *r);
};

}  // namespace writer

#endif  // _writer_vl_util_h_
