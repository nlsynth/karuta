// -*- C++ -*-
#ifndef _synth_dot_output_h_
#define _synth_dot_output_h_

#include "synth/common.h"

namespace iroha {
class Dot;
}  // namespace iroha

namespace synth {

class DotOutput {
public:
  DotOutput(ObjectTree *tree);
  ~DotOutput();

  void Write(const string &fn);

private:
  std::unique_ptr<iroha::Dot> dot_;
  ObjectTree *tree_;
};

}  // namespace synth

#endif  // _synth_dot_output_h_
